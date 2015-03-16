#include "JenkinsAccess.h"

#include <iostream>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <kxm/Core/NumberTools.h>

using namespace std;
using namespace std::chrono;
using namespace boost::asio;
using namespace kxm::Core;


namespace Raspiator {

JenkinsAccess::JenkinsAccess(const string &jenkinsServer)
        : jenkinsServer_(jenkinsServer) {
    shared_.terminationRequested = false;
    workerThread_ = thread([this]{ WorkerThread(); });
}

JenkinsAccess::~JenkinsAccess() {
    {
        lock_guard<mutex> critical(lock_);
        shared_.terminationRequested = true;
        shared_.stateChanged.notify_all();
    }
    workerThread_.join();
}

void JenkinsAccess::RequestJobDataUpdate(const string &id, const string &jenkinsJob,
                                         bool buildJob) {
    Request request;
    request.id         = id;
    request.jenkinsJob = jenkinsJob;
    request.buildJob   = buildJob;

    lock_guard<mutex> critical(lock_);
    shared_.requests.push(request);
    shared_.stateChanged.notify_all();
}

void JenkinsAccess::GetJobData(vector<Data> *data) {
    data->clear();

    lock_guard<mutex> critical(lock_);
    while (shared_.data.size()) {
        data->push_back(shared_.data.front());
        shared_.data.pop();
    }
}

void JenkinsAccess::WorkerThread() {
    cout << "worker thread running" << endl;
    bool done = false;
    queue<Request> requests;
    for (;;) {
        for (;;) {
            unique_lock<mutex> critical(lock_);
            if (shared_.terminationRequested) {
                done = true;
                break;
            }
            while (shared_.requests.size()) {
                requests.push(shared_.requests.front());
                shared_.requests.pop();
            }
            if (requests.size())
                break;
            shared_.stateChanged.wait(critical);
        }
        if (done)
            break;

        while (requests.size()) {
            Request &request = requests.front();
            Data data = GetData(request.id, request.jenkinsJob, request.buildJob);
            requests.pop();

            lock_guard<mutex> critical(lock_);
            shared_.data.push(data);
        }
    }
    cout << "worker thread exiting" << endl;
}

JenkinsAccess::Data JenkinsAccess::GetData(const string &id, const string &jenkinsJob,
                                           bool buildJob) {
    cout << "updating " << jenkinsServer_ << ":" << jenkinsJob << endl;

    Data data;
    data.id = id;
    
    int numTotal = 0,
        numRed   = 0;
    
    if (buildJob) {
        numTotal = 10;
        numRed   = 10;

        ip::tcp::iostream stream;
        stream.connect(jenkinsServer_, "8080");
        stream << "GET /job/" << jenkinsJob
               << "/lastCompletedBuild/api/json?pretty=true HTTP/1.0\r\n";
        stream << "Host: " << jenkinsServer_ << "\r\n";
        stream << "Accept: */*\r\n";
        stream << "Connection: close\r\n\r\n";
        stream.flush();

        string line;
        vector<string> tokens;
        while (!stream.eof() && !stream.error()) {
            getline(stream, line);
            boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(":"));
            if (tokens.size() == 2) {
                string left  = tokens[0],
                       right = tokens[1];
                boost::algorithm::trim(left);
                if (left != "\"result\"")
                    continue;
                boost::algorithm::trim(right);
                boost::algorithm::trim_if(right, boost::algorithm::is_any_of("\","));
                
                if (right == "SUCCESS")
                    numRed = 0;
                else if (right == "UNSTABLE")
                    numRed = numTotal/2;
                else
                    numRed = numTotal;
                break;
            }
        }
    }
    else {
        ip::tcp::iostream stream;
        stream.connect(jenkinsServer_, "8080");
        stream << "GET /job/" << jenkinsJob
               << "/lastCompletedBuild/testReport/api/json?pretty=true HTTP/1.0\r\n";
        stream << "Host: " << jenkinsServer_ << "\r\n";
        stream << "Accept: */*\r\n";
        stream << "Connection: close\r\n\r\n";
        stream.flush();

        string line;
        vector<string> tokens;
        while (!stream.eof() && !stream.error()) {
            getline(stream, line);
            boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(":"));
            if (tokens.size() == 2) {
                string left  = tokens[0],
                       right = tokens[1];
                boost::algorithm::trim(left);
                if (left != "\"status\"")
                    continue;
                ++numTotal;
                boost::algorithm::trim(right);
                boost::algorithm::trim_if(right, boost::algorithm::is_any_of("\","));
                if ((right != "PASSED") && (right != "FIXED"))
                    ++numRed;          
            }
        }
    }
    
    // Get progress...
    string startTimeTxt,
           estimatedDurationTxt;
    bool   isBuilding = false;
    {
        ip::tcp::iostream stream;
        stream.connect(jenkinsServer_, "8080");
        stream << "GET /job/" << jenkinsJob
               << "/lastBuild/api/json?pretty=true HTTP/1.0\r\n";
        stream << "Host: " << jenkinsServer_ << "\r\n";
        stream << "Accept: */*\r\n";
        stream << "Connection: close\r\n\r\n";
        stream.flush();

        string line;
        vector<string> tokens;
        while (!stream.eof() && !stream.error()) {
            getline(stream, line);
            boost::algorithm::split(tokens, line, boost::algorithm::is_any_of(":"));
            if (tokens.size() == 2) {
                string left  = tokens[0],
                       right = tokens[1];
                boost::algorithm::trim(left);
                boost::algorithm::trim(right);
                boost::algorithm::trim_if(right, boost::algorithm::is_any_of("\","));
                if (left == "\"building\"") {
                    if (right == "true")
                        isBuilding = true;
                }
                else if (left == "\"timestamp\"") {
                    if (!startTimeTxt.length())
                        startTimeTxt = right;
                }
                else if (left == "\"estimatedDuration\"") {
                    estimatedDurationTxt = right;
                }   
            }
        }
    }
    cout << "start_time='" << startTimeTxt << "'" << endl;
    cout << "estimated_duration='" << estimatedDurationTxt << "'" << endl;
    cout << "is_building=" << isBuilding << endl;
    
    int progressPercent = 100;
    if (isBuilding) {
        progressPercent = 0;
        if (startTimeTxt.length() && estimatedDurationTxt.length()) {
            long long startTimeS = stoll(startTimeTxt) / (long long)1000;
            system_clock::time_point tp = system_clock::now();
            system_clock::duration dtn = tp.time_since_epoch();
            long long nowTimeS           = dtn.count() * system_clock::period::num
                                                       / system_clock::period::den,
                      deltaTimeS         = nowTimeS - startTimeS,
                      estimatedDurationS = stoll(estimatedDurationTxt) / (long long)1000;
            if (estimatedDurationS)
                progressPercent = (int)((float)deltaTimeS / (float)estimatedDurationS * 100.0f);
        }
        NumberTools::Clamp(&progressPercent, 0, 99);
    }

    // TESTING
    {
        if (buildJob) {
            numTotal = 10;
            numRed   = uniform_int_distribution<int>(0, 2)(random_) * 5;
            if (numRed == 5)
                numRed = 4;
        }
        else {
            numTotal = uniform_int_distribution<int>(1, 400)(random_);
            numRed   = uniform_int_distribution<int>(0, numTotal)(random_);
        }
        progressPercent = uniform_int_distribution<int>(0, 100)(random_);
    }

    data.numTotal        = numTotal;
    data.numRed          = numRed;
    data.progressPercent = progressPercent;
    return data;
}

}    // Namespace Raspiator.


#include "JenkinsAccess.h"

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;


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

void JenkinsAccess::RequestJobDataUpdate(const string &id, const string &jenkinsJob) {
    Request request;
    request.id         = id;
    request.jenkinsJob = jenkinsJob;

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
            Data data = GetData(request.id, request.jenkinsJob);
            requests.pop();

            lock_guard<mutex> critical(lock_);
            shared_.data.push(data);
        }
    }
    cout << "worker thread exiting" << endl;
}

JenkinsAccess::Data JenkinsAccess::GetData(const string &id, const string &jenkinsJob) {
    Data data;
    data.id = id;

    ip::tcp::iostream stream;
    stream.expires_from_now(boost::posix_time::seconds(60));
    stream.connect("www.boost.org", "http");
    stream << "GET /LICENSE_1_0.txt HTTP/1.0\r\n";
    stream << "Host: www.boost.org\r\n";
    stream << "Accept: */*\r\n";
    stream << "Connection: close\r\n\r\n";
    stream.flush();

    string line;
    while (!stream.eof() && !stream.error()) {
        getline(stream, line);
    }

    uniform_int_distribution<int> distribution(1, 1200),
                                  progressDistribution(0, 100);
    data.numTotal = distribution(random_);
    uniform_int_distribution<int> redDistribution(1, data.numTotal);
    data.numRed = redDistribution(random_);
    data.progressPercent = progressDistribution(random_);

    return data;
}

}    // Namespace Raspiator.


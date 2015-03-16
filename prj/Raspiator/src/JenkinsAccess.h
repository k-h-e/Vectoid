#ifndef RASPIATOR_JENKINSACCESS_H_
#define RASPIATOR_JENKINSACCESS_H_


#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <random>


namespace Raspiator {
    class JenkinsAccess {
      public:
        struct Data {
            std::string id;
            int         numRed,
                        numTotal,
                        progressPercent;
            Data() : numRed(0), numTotal(0), progressPercent(0) {}
        };

        JenkinsAccess(const std::string &jenkinsServer);
        JenkinsAccess(const JenkinsAccess &other)            = delete;
        JenkinsAccess &operator=(const JenkinsAccess &other) = delete;
        JenkinsAccess(JenkinsAccess &&other)                 = delete;
        JenkinsAccess &operator=(JenkinsAccess &&other)      = delete;
        ~JenkinsAccess();

        void RequestJobDataUpdate(const std::string &id, const std::string &jenkinsJob,
                                  bool buildJob);
        void GetJobData(std::vector<Data> *data);

      private:
        struct Request {
            std::string id;
            std::string jenkinsJob;
            bool        buildJob;
            Request() : buildJob(false) {}
        };

        void WorkerThread();
        Data GetData(const std::string &id, const std::string &jenkinsJob, bool buildJob);

        std::thread                 workerThread_;
        std::mutex                  lock_;
        struct {
            std::condition_variable stateChanged;
            std::queue<Request>     requests;
            std::queue<Data>        data;
            bool                    terminationRequested;
        }                           shared_;

        // Thread data...
        std::string                 jenkinsServer_;
        std::default_random_engine  random_;
    };
}


#endif    // RASPIATOR_JENKINSACCESS_H_


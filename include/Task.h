#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unordered_map>
#include <utility>
#include "SampleJobs.h"

class Task 
{
    public:
        enum class State{
            IDLE = 1,
            RUNNING,
            PAUSED,
            ABORTED,
        };
        Task();
        ~Task(){};

        uint64_t setJob(Jobs jobType);
        void startThread();
        void pauseThread();
        void resumeThread();
        void abortThread();
        std::string getStatusStr();
        uint64_t getJobId() const {return m_jobId;}
    private:
        std::unique_ptr<std::thread> m_thread;
        std::mutex m_threadMutex;
        std::condition_variable m_cv;
        State m_state {State::IDLE};
        uint64_t m_jobId {0};
        std::shared_ptr<std::unordered_map<std::string, bool>> m_controlParameters;

        static uint64_t kUniqueJobIdCounter;

        uint64_t getUniqueJobId(){return ++kUniqueJobIdCounter;}
        void updateIsRunningParam(bool isRunning);
        void updateIsAbortedParam(bool isAborted);
        bool checkIfCompleted();
};
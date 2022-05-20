#include "Task.h"
#include "ControllableInterface.h"
#include "SampleJobs.h"
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <utility>

uint64_t Task::kUniqueJobIdCounter {100};

Task::Task(){
    m_controlParameters = std::make_shared<std::unordered_map<std::string, bool>>();
    m_controlParameters->insert(std::make_pair("isRunning", false));
    m_controlParameters->insert(std::make_pair("isAborted", false));
    m_controlParameters->insert(std::make_pair("isCompleted", false));
};

uint64_t Task::setJob(Jobs jobType)
{
    std::shared_ptr<IControllable> job;
    switch(jobType)
    {
        case Jobs::JOB1:
            job = std::make_shared<Job1>();
            m_thread = std::make_unique<std::thread>(&IControllable::threadProcedure, job, std::ref(m_threadMutex), std::ref(m_cv), std::ref(m_controlParameters));
            break;
        default:
            job = std::make_shared<Job2>();
            m_thread = std::make_unique<std::thread>(&IControllable::threadProcedure, job, std::ref(m_threadMutex), std::ref(m_cv), std::ref(m_controlParameters));
    }    
    m_jobId = getUniqueJobId();
    std::cout << "Job created with JobID: " << m_jobId << std::endl;
    return m_jobId;
}
void Task::startThread()
{
    if(m_state == State::RUNNING) return;
    m_thread->detach();
    
    {
        std::unique_lock<std::mutex> lock(m_threadMutex);
        updateIsRunningParam(true);
    }    
    m_cv.notify_one();
    m_state = State::RUNNING;
}

void Task::pauseThread()
{
    if(checkIfCompleted())
    {
        m_state = State::ABORTED;
        return;
    }
    if(m_state == State::PAUSED) return;

    std::unique_lock<std::mutex> lock(m_threadMutex);
    updateIsRunningParam(false);
    m_state = State::PAUSED;
}

void Task::resumeThread()
{
    if(checkIfCompleted())
    {
        m_state = State::ABORTED;
        return;
    }
    if(m_state == State::RUNNING) return;
    {
        std::unique_lock<std::mutex> lock(m_threadMutex);
        updateIsRunningParam(true);   
    }
    m_cv.notify_one();
    m_state = State::RUNNING;
}

void Task::abortThread()
{
    if(checkIfCompleted())
    {
        m_state = State::ABORTED;
        return;
    }
    if(m_state == State::ABORTED) return;
    resumeThread();
    updateIsAbortedParam(true);
    if(m_thread->joinable())
        m_thread->join();
    m_state = State::ABORTED;
}

std::string Task::getStatusStr()
{
    if(checkIfCompleted())
        m_state = State::ABORTED;

    switch(m_state)
    {
        case State::RUNNING: return std::string("RUNNING");
        case State::PAUSED: return std::string("PAUSED");
        case State::ABORTED: return std::string("ABORTED");
        default:
            return std::string("IDLE");
    }
}

void Task::updateIsRunningParam(bool isRunning)
{
    auto it = m_controlParameters->find("isRunning");

    if(it != m_controlParameters->end())
        it->second = isRunning;
}

void Task::updateIsAbortedParam(bool isAborted)
{
    auto it = m_controlParameters->find("isAborted");

    if(it != m_controlParameters->end())
        it->second = isAborted;
}

bool Task::checkIfCompleted()
{
    auto it = m_controlParameters->find("isCompleted");

    if(it != m_controlParameters->end())
        return it->second;
}
#include "TaskManager.h"
#include "SampleJobs.h"
#include <cstdint>
#include <memory>
#include <utility>

bool TaskManager::initializeTasks(uint64_t numberOfTasks)
{
    uint64_t jobId;

    for(int i = 0; i < numberOfTasks; i++)
    {
        std::shared_ptr<Task> task = std::make_shared<Task>();
        if(i%2 == 0)
            jobId = task->setJob(Jobs::JOB1);
        else
            jobId = task->setJob(Jobs::JOB2);

        m_taskVector.push_back(task);
        m_indexMap.insert(std::make_pair(jobId, i));
    }
        
}

bool TaskManager::executeCommand(std::pair<std::string, uint64_t> command)
{
    if(command.first.compare("status") == 0)
    {
        return executeStatusCommand();
    }
    else if(command.first.compare("start") == 0)
    {
        return executeStartCommand(command.second);
    }
    else if(command.first.compare("pause") == 0)
    {
        return executePauseCommand(command.second);
    }
    else if(command.first.compare("resume") == 0)
    {
        return executeResumeCommand(command.second);
    }
    else if(command.first.compare("abort") == 0)
    {
        return executeAbortCommand(command.second);
    }
    else if(command.first.compare("quit") == 0)
    {
        return executeQuitCommand();
    }
    return true;
}

bool TaskManager::executeStatusCommand() const
{
    std::cout<< "\n\n*** JOB STATUS ***\n";
    for (auto& element: m_taskVector)
    {
        std::cout << "JobId: " << element->getJobId() << " - Status: " << element->getStatusStr() << std::endl;
    }
    std::cout<<"\n\n";
    return true;
}

bool TaskManager::executeStartCommand(uint64_t jobId)
{
    auto it = m_indexMap.find(jobId);

    if(it != m_indexMap.end())
    {
        m_taskVector[it->second]->startThread();
    }
    else  
        std::cout << "No job found to start with id: " << jobId << std::endl;
    return true;

}

bool TaskManager::executePauseCommand(uint64_t jobId)
{
    auto it = m_indexMap.find(jobId);

    if(it != m_indexMap.end())
    {
        m_taskVector[it->second]->pauseThread();
    }
    else  
        std::cout << "No job found to pause with id: " << jobId << std::endl;
    return true;    
}

bool TaskManager::executeResumeCommand(uint64_t jobId)
{
    auto it = m_indexMap.find(jobId);

    if(it != m_indexMap.end())
    {
        m_taskVector[it->second]->resumeThread();
    }
    else  
        std::cout << "No job found to resume with id: " << jobId << std::endl;
    return true;
}

bool TaskManager::executeAbortCommand(uint64_t jobId)
{
    auto it = m_indexMap.find(jobId);

    if(it != m_indexMap.end())
    {
        m_taskVector[it->second]->abortThread();
    }
    else  
        std::cout << "No job found to abort with id: " << jobId << std::endl;
    return true;
}

bool TaskManager::executeQuitCommand()
{
    for(auto element: m_taskVector)
    {
        std::cout<< "Deleting job with id : " << element->getJobId() << std::endl;
        element->abortThread();        
    }
    m_taskVector.clear();
    m_indexMap.clear();
    std::cout<< "Quitting ..." << std::endl;
    return false;
}
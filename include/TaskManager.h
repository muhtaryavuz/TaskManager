#pragma once 

#include <cstdint>
#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
#include "Task.h"
#include <iostream>

class TaskManager
{
    public:
        TaskManager(){};
        ~TaskManager(){};

        bool initializeTasks(uint64_t numberOfTasks);
        bool executeCommand(std::pair<std::string, uint64_t> command);
    private:
        std::vector<std::shared_ptr<Task>> m_taskVector;
        std::unordered_map<uint64_t, uint64_t> m_indexMap;

        bool executeStatusCommand() const;
        bool executeStartCommand(uint64_t jobId);
        bool executePauseCommand(uint64_t jobId);
        bool executeResumeCommand(uint64_t jobId);
        bool executeAbortCommand(uint64_t jobId);
        bool executeQuitCommand();

};
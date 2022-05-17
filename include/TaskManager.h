#pragma once 

#include <cstdint>
#include <utility>
#include <string>

class TaskManager
{
    public:
        TaskManager(){};
        ~TaskManager(){};

        bool initializeTasks(uint64_t numberOfTasks);
        bool executeCommand(std::pair<std::string, uint64_t> command);
};
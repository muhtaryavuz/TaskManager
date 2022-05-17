
#include "InputParser.h"
#include "Menu.h"
#include "TaskManager.h"
#include <cstdint>

void printHelp()
{
    std::cout<<"usage: TaskManager [N | h] [OPTIONAL VALUES]\n";
    std::cout<<"Manage tasks running in parallel\n\n";
    std::cout<<"Only short options are accepted(for now)\n";
    std::cout<<"\t-N [task number] defines number of tasks \n";
    std::cout<<"\t-h               prints help \n";
}

int main(int argc, char** argv) 
{
    InputParser input(argc, argv);
    Menu menu;
    TaskManager taskManager;
    uint64_t numberOfTasks;
    if(input.cmdOptionExists("-N"))
    {
        numberOfTasks = std::stoul(input.getCmdOption("-N"));
        taskManager.initializeTasks(numberOfTasks);
        while(true)
        {
            menu.printMainMenu();
            auto userInput = menu.getInputFromUser();
            auto result = taskManager.executeCommand(userInput);
            if(result == false) break;
        }
    }
    else if(input.cmdOptionExists("-h"))
    {
        printHelp();
    }
    else
    {
        std::cout<<"invalid option\n";
    }
}

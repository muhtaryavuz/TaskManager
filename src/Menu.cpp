#include "Menu.h"
#include <cstdint>
#include <string>
#include <utility>

void Menu::printMainMenu() const
{
    std::cout << "status        -returns ids and status of all registered jobs\n";
    std::cout << "stard <id>    -starts job with the given id\n";
    std::cout << "abort <id>    -aborts execution of a job with the given id\n";
    std::cout << "pause <id>    -halts execution of a job with the given id \n";
    std::cout << "resume <id>   -resumes execution of halted job\n";
    std::cout << "quit          -aborts all running jobs and quits the application\n";
    std::cout << ">";
}

std::pair<std::string, uint64_t> Menu::getInputFromUser()
{
    std::string input;
    std::cin>> input;

    return parseUserInput(input);
}

std::pair<std::string, uint64_t> Menu::parseUserInput(std::string input)
{
    if(input.length() == 0)
        return std::make_pair("", 0);
    
    std::string command;
    std::string value;
    uint64_t id = 0;
    
    std::size_t found = input.find(" ");
    if (found != std::string::npos)
    {
        command = input.substr(0, found);
        value = input.substr(found + 1, input.length());
        id = std::stoul(value);
    }
    else 
    {
        command = input;
    }
    return std::make_pair(command, id);
}
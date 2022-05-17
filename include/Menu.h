#pragma once 

#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>

class Menu
{
    public:
        Menu(){};
        ~Menu(){};

        void printMainMenu() const;
        std::pair<std::string, uint64_t> getInputFromUser();
    private:
        std::pair<std::string, uint64_t> parseUserInput(std::string input);
};
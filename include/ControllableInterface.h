#pragma once 

#include <mutex>
#include <condition_variable>
#include <unordered_map>

class IControllable
{
    public:
        IControllable(){};
        virtual ~IControllable(){};

        void threadProcedure(std::mutex& m, std::condition_variable& cv, std::shared_ptr<std::unordered_map<std::string, bool>> controlParams)
        {
            while(controlParams->find("isRunning")->second == false)
            {
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock, [&](){return controlParams->find("isRunning")->second;});

                if(execute() == false)
                {
                    (*controlParams)["isCompleted"] = true;
                    break;
                }            
            }
        }

        // This method for tasks. Never use loop inside it. 
        virtual bool execute() = 0;
};
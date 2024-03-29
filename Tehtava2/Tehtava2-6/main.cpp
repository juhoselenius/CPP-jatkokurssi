#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

class Game_Task
{
public:
    virtual void perform() = 0;
    virtual ~Game_Task() {}
};

class Task_A : public Game_Task
{
public:
    void perform() override
    {
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Task A finished" << std::endl;
    }
};

class Task_B : public Game_Task
{
public:
    void perform() override
    {
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Task B finished" << std::endl;
    }
};

class Task_C : public Game_Task
{
public:
    void perform() override
    {
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        std::cout << "Task C finished" << std::endl;
    }
};

int main()
{
    srand(time(nullptr));
    
    // Creating tasks
    int numTasks = 20;
    std::vector<Game_Task*> tasks;
    for (int i = 0; i < numTasks; i++)
    {
        int randomValue = rand() % 3;
        switch (randomValue)
        {
            case 0:
                tasks.push_back(new Task_A());
                break;
            case 1:
                tasks.push_back(new Task_B());
                break;
            case 2:
                tasks.push_back(new Task_C());
                break;
            default:
                break;
        }
    }

    // Start running tasks without threading ******************************
    auto startNoThread = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numTasks; i++)
    {
        tasks[i]->perform();
    }
    auto stopNoThread = std::chrono::high_resolution_clock::now();
    // End of running tasks without threading *****************************

    // Start running tasks with threading *********************************
    auto startThreaded = std::chrono::high_resolution_clock::now();
    int numThreads = std::thread::hardware_concurrency() - 1;
    std::cout << "Number of threads: " << numThreads << std::endl;
    std::vector<std::future<void>> threads;

    // Distribution of tasks to threads
    for (int i = 0; i < tasks.size(); i += numThreads)
    {
        // Distributing tasks to the max number of threads on the hardware
        for (int j = 0; j < numThreads && (i + j) < tasks.size(); j++)
        {
            threads.emplace_back(std::async([&tasks, i, j]()
                {
                    tasks[i + j]->perform();
                }));
        }

        // Waiting for all threads to complete
        for (auto& thread : threads)
        {
            thread.get();
        }
        threads.clear();
        
        // Continuing to the next set of tasks
    }

    auto stopThreaded = std::chrono::high_resolution_clock::now();
    // End of running tasks with threading ********************************

    // Cleaning up the completed tasks
    for (auto task : tasks)
    {
        delete task;
    }

    // Printing out the duration of the not threaded execution
    auto durationNoThread = std::chrono::duration_cast<std::chrono::milliseconds>(stopNoThread - startNoThread);
    std::cout << "Synchronous execution time: " << durationNoThread.count() << "ms." << std::endl;

    // Printing out the duration of the threaded execution
    auto durationThreaded = std::chrono::duration_cast<std::chrono::milliseconds>(stopThreaded - startThreaded);
    std::cout << "Asynchronous exection time: " << durationThreaded.count() << "ms." << std::endl;

    return 0;
}
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <vector>

class Game_Task
{
public:
	void perform()
	{
		// Simulate some processing time
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Task finished" << std::endl;
	}
	~Game_Task() {}
};

class TaskQueue
{
private:
	std::queue<Game_Task> _taskQueue;
	std::vector<std::thread> _threads;
	std::mutex _mtx;
	std::condition_variable _cv;
	bool _stop = false;

	void executeThread()
	{
		// Continuously checking for new task from the _taskQueue
		while (true)
		{
			Game_Task task;
			
			// This block handles shared resources, _taskQueue and _stop, so it is locked
			{
				std::unique_lock<std::mutex> lock(_mtx);
				_cv.wait(lock, [&]() { return _stop || !_taskQueue.empty(); });
			
				// Exit condition
				if (_stop && _taskQueue.empty())
				{
					return;
				}

				// If there are still tasks in the queue and stop hasn't been set
				task = _taskQueue.front();
				_taskQueue.pop();
			}

			task.perform();
		}
	}

public:
	TaskQueue(int nof_threads)
	{
		// Setting up the threads
		for (int i = 0; i < nof_threads; i++)
		{
			_threads.emplace_back([this]()
				{
					this->executeThread();
				});
		}
	}

	~TaskQueue()
	{
		// This block handles a shared resource (_stop) so it is locked
		{
			std::unique_lock<std::mutex> lock(_mtx);
			_stop = true;
		}

		// Signaling for all the threads to go
		_cv.notify_all();

		// Waiting for all the threads to join
		for (auto& t : _threads)
		{
			t.join();
		}
		
		std::cout << "Task Queue deleted, tasks finished" << std::endl;
	}

	// Adding a game task to the end of the queue
	void addTask(Game_Task task)
	{
		// This block handles a shared resource (_taskQueue) so it is locked
		std::unique_lock<std::mutex> lock(_mtx);
		_taskQueue.push(task);

		// Notifying for a thread to go
		_cv.notify_one();
	}
};

int main()
{
	// Creating tasks
	int numTasks = 100;
	std::vector<Game_Task> tasks;
	for (int i = 0; i < numTasks; i++)
	{
		Game_Task task;
		tasks.push_back(task);
	}

	// Creating the task queue
	int numThreads = std::thread::hardware_concurrency() - 1;
	std::cout << "Number of threads: " << numThreads << std::endl;
	TaskQueue taskQueue(numThreads);

	// Adding tasks to the task queue
	for (int i = 0; i < numTasks; i++)
	{
		taskQueue.addTask(tasks[i]);
	}
	
	return 0;
}
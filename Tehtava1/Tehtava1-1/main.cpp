#include <iostream>			// std::cout
#include <thread>			// std::thread
#include <vector>			// std::vector
#include <chrono>			// std::chrono

void calculateSum(const int numbersArray[], int partialSumArray[], int arrayIndex, int startIndex, int stopIndex)
{
	int threadSum = 0;
	for (int i = startIndex; i < stopIndex; i++)
	{
		threadSum += numbersArray[i];
	}
	partialSumArray[arrayIndex] = threadSum;
}

int main()
{
	srand(time(nullptr));
	const int numElements = 100000;
	const int numThreads = 4;
	int computedSum = 0;
	int partialSums[numThreads];
	
	// Creating an array holding the numbers
	int numbers[numElements];

	for (int i = 1; i <= numElements; i++)
	{
		numbers[i - 1] = rand() % 100;
	}

	// Creating the threads
	auto startOne = std::chrono::high_resolution_clock::now();
	std::vector<std::thread> threads(numThreads);
	for (int i = 0; i < numThreads; i++)
	{
		int startIndex = i * (numElements / numThreads);
		int stopIndex = (i + 1) * (numElements / numThreads);
		if (i == numThreads - 1)
		{
			stopIndex = numElements;
		}
		threads[i] = std::thread(calculateSum, numbers, partialSums, i, startIndex, stopIndex);
	}

	// Waiting for all threads to join
	for (auto& t : threads)
	{
		t.join();
	}

	// Adding up the partial sums from the threads
	for (int i = 0; i < numThreads; i++)
	{
		computedSum += partialSums[i];
	}
	auto stopOne = std::chrono::high_resolution_clock::now();
	auto durationOne = std::chrono::duration_cast<std::chrono::microseconds>(stopOne - startOne);

	// Printing out the duration of the thread execution
	std::cout << "Calculating threads took " << durationOne.count() << "ms." << std::endl;
	
	// Calculating the expected sum
	auto startTwo = std::chrono::high_resolution_clock::now();
	int expectedSum = 0;
	for (int i = 0; i < numElements; i++)
	{
		expectedSum += numbers[i];
	}
	auto stopTwo = std::chrono::high_resolution_clock::now();
	auto durationTwo = std::chrono::duration_cast<std::chrono::microseconds>(stopTwo - startTwo);

	// Printing out the duration of the thread execution
	std::cout << "Calculating the old fashioned way took " << durationTwo.count() << "ms." << std::endl;

	// Printing out the expected sum
	std::cout << "The expected sum is " << expectedSum << "." << std::endl;

	// Printing out the multithreaded sum
	std::cout << "The multithreaded sum is " << computedSum << "." << std::endl;
	
	return 0;
}
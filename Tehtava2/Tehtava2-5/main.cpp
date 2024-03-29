#include <iostream>			// std::cout
#include <algorithm>		// std::for_each
#include <vector>			// std::vector
#include <chrono>			// std::chrono
#include <execution>

void increaseEach(int& i)
{
	i++;
}

int main()
{
	const int numElements = 10000000;
	
	// Creating an array holding the numbers
	std::vector<int> numbers(numElements);

	for (int i = 0; i < numElements; i++)
	{
		numbers[i] = i;
	}

	// Setting up the algorithm with sequenced policy
	// The sequenced policy ensures that the algorithm is executed sequentially, 
	// following the traditional approach of processing elements in order in one thread.
	auto startSequenced = std::chrono::high_resolution_clock::now();
	std::for_each(std::execution::seq, numbers.begin(), numbers.end(), increaseEach);
	auto stopSequenced = std::chrono::high_resolution_clock::now();
	auto durationSequenced = std::chrono::duration_cast<std::chrono::milliseconds>(stopSequenced - startSequenced);
	std::cout << "The sequenced policy took " << durationSequenced.count() << " ms to complete." << std::endl;

	// Setting up the algorithm with parallel policy
	// The parallel policy allows the algorithm to be executed simultaneously distributing tasks to multiple threads.
	auto startParallel = std::chrono::high_resolution_clock::now();
	std::for_each(std::execution::par, numbers.begin(), numbers.end(), increaseEach);
	auto stopParallel = std::chrono::high_resolution_clock::now();
	auto durationParallel = std::chrono::duration_cast<std::chrono::milliseconds>(stopParallel - startParallel);
	std::cout << "The parallel policy took " << durationParallel.count() << " ms to complete." << std::endl;

	// Setting up the algorithm with parallel unsequenced policy
	// The parallel unsequenced policy enables simultaneous execution without strict sequencing,
	// meaning that the output order may not necessarily be the same as the input order.
	auto startParallelUnseq = std::chrono::high_resolution_clock::now();
	std::for_each(std::execution::par_unseq, numbers.begin(), numbers.end(), increaseEach);
	auto stopParallelUnseq = std::chrono::high_resolution_clock::now();
	auto durationParallelUnseq = std::chrono::duration_cast<std::chrono::milliseconds>(stopParallelUnseq - startParallelUnseq);
	std::cout << "The parallel unsequenced policy took " << durationParallelUnseq.count() << " ms to complete." << std::endl;

	return 0;
}

// Sequenced policy: 56 ms
// Parallel policy: 16 ms
// Parallel unsequenced: 12 ms
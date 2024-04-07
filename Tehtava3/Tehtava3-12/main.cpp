#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <algorithm>

// Helper function for printing the enemy HP
void printHPList(std::vector<int> hpList)
{
	std::cout << "List of Enemy HP" << std::endl;
	for (int i = 0; i < hpList.size(); i++)
	{
		std::cout << "Furry " << i + 1 << " HP: " << hpList[i] << std::endl;
	}
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}

// Helper function for printing just for fun
void castSpell(std::string spell)
{
	std::cout << "Player cast a " << spell << " spell\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// Function for part A
void dealDamage(int &enemyHP)
{
	if (enemyHP >= 100)
	{
		enemyHP -= 100;
	}
	else
	{
		enemyHP = 0;
	}
}

// Functor for part B
class DealDamageFunctor
{
	public:
		void operator() (int &enemyHP)
		{
			if (enemyHP >= 100)
			{
				enemyHP -= 100;
			}
			else
			{
				enemyHP = 0;
			}
		}
};

int main()
{
	std::vector<int> enemyHPList;

	for (int i = 0; i < 10; i++)
	{
		enemyHPList.emplace_back((rand() % 10 + 1) * 100); // Add integers from 100 to 1000
	}

	std::cout << "A wild pack of furries appeared!\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	printHPList(enemyHPList);

	castSpell("function");

	// Assingment A: standalone function
	std::for_each(enemyHPList.begin(), enemyHPList.end(), dealDamage);

	printHPList(enemyHPList);

	castSpell("functor");

	// Assignment B: functor
	DealDamageFunctor damageFunctor;
	std::for_each(enemyHPList.begin(), enemyHPList.end(), damageFunctor);

	printHPList(enemyHPList);

	castSpell("lambda");

	// Assignment C: Lambda expression
	std::for_each(enemyHPList.begin(), enemyHPList.end(), [](int &enemyHP) {
		if (enemyHP >= 100)
		{
			enemyHP -= 100;
		}
		else
		{
			enemyHP = 0;
		}
		});

	printHPList(enemyHPList);

	castSpell("named lambda");

	// Assignment D: Named lambda expression
	auto dealLambdaDamage = [](int& enemyHP)
		{
			if (enemyHP >= 100)
			{
				enemyHP -= 100;
			}
			else
			{
				enemyHP = 0;
			}
		};

	std::for_each(enemyHPList.begin(), enemyHPList.end(), dealLambdaDamage);

	printHPList(enemyHPList);

	// Sorting the list in descending order with lambda expression
	std::sort(enemyHPList.begin(), enemyHPList.end(), [](int a, int b) { return a > b; });

	std::cout << "Leftover enemy HP in descending order:" << std::endl;
	for (auto hp : enemyHPList)
	{
		std::cout << hp << std::endl;
	}
	
	return 0;
}
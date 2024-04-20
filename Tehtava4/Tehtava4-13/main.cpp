#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::string s1 = "kissa";
	std::string s2;

	//std::cout << "Original S1 address: " << &s1 << std::endl;

	// Part a, s1 and s2 point to different memory addresses
	s2 = s1;

	//std::cout << "S2 address after assignment: " << &s2 << std::endl;

	// Part b, s1 has been cleared from its contents and the contents have been moved to s2
	s2 = std::move(s1);

	//std::cout << "S1 address after move: " << &s1 << std::endl;
	//std::cout << "S2 address after move: " << &s2 << std::endl;

	// Part c
	std::vector<std::string> stringVector;
	std::string s3 = "koira";
	stringVector.push_back(s3);
	stringVector.push_back(std::move(s3));
	
	return 0;
}
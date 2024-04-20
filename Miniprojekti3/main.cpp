#include <ctime>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>

int is_straight(int* k);
int is_straight2(int* k, int i);
void populateLookupTables();
int is_quadsorfullhouse(int* k);
int is_quadsorfullhouse2(int* k, int i);
static const std::bitset<16> straightLookup[] = {
	0b0100000000111100, // A,2,3,4,5
	0b0000000001111100, // 2,3,4,5,6
	0b0000000011111000, // 3,4,5,6,7
	0b0000000111110000, // 4,5,6,7,8
	0b0000001111100000, // 5,6,7,8,9
	0b0000011111000000, // 6,7,8,9,10
	0b0000111110000000, // 7,8,9,10,J
	0b0001111100000000,	// 8,9,10,J,Q
	0b0011111000000000,	// 9,10,J,Q,K
	0b0111110000000000	// 10,J,Q,K,A
};
static const std::bitset<16> fullHouseLookup[] = {
	0b0110000000000000, // A,A,A,K,K
	0b0101000000000000, // A,A,A,Q,Q
	0b0100100000000000, // A,A,A,J,J
	0b0100010000000000, // A,A,A,10,10
	0b0100001000000000, // A,A,A,9,9
	0b0100000100000000, // A,A,A,8,8
	0b0100000010000000, // A,A,A,7,7
	0b0100000001000000, // A,A,A,6,6
	0b0100000000100000, // A,A,A,5,5
	0b0100000000010000, // A,A,A,4,4
	0b0100000000001000, // A,A,A,3,3
	0b0100000000000100, // A,A,A,2,2
	0b0011000000000000,
	0b0010100000000000,
	0b0010010000000000,
	0b0010001000000000,
	0b0010000100000000,
	0b0010000010000000,
	0b0010000001000000,
	0b0010000000100000,
	0b0010000000010000,
	0b0010000000001000,
	0b0010000000000100,
	0b0001100000000000,
	0b0001010000000000,
	0b0001001000000000,
	0b0001000100000000,
	0b0001000010000000,
	0b0001000001000000,
	0b0001000000100000,
	0b0001000000010000,
	0b0001000000001000,
	0b0001000000000100,
	0b0000110000000000,
	0b0000101000000000,
	0b0000100100000000,
	0b0000100010000000,
	0b0000100001000000,
	0b0000100000100000,
	0b0000100000010000,
	0b0000100000001000,
	0b0000100000000100,
	0b0000011000000000,
	0b0000010100000000,
	0b0000010010000000,
	0b0000010001000000,
	0b0000010000100000,
	0b0000010000010000,
	0b0000010000001000,
	0b0000010000000100,
	0b0000001100000000,
	0b0000001010000000,
	0b0000001001000000,
	0b0000001000100000,
	0b0000001000010000,
	0b0000001000001000,
	0b0000001000000100,
	0b0000000110000000,
	0b0000000101000000,
	0b0000000100100000,
	0b0000000100010000,
	0b0000000100001000,
	0b0000000100000100,
	0b0000000011000000,
	0b0000000010100000,
	0b0000000010010000,
	0b0000000010001000,
	0b0000000010000100,
	0b0000000001100000,
	0b0000000001010000,
	0b0000000001001000,
	0b0000000001000100,
	0b0000000000110000,
	0b0000000000101000,
	0b0000000000100100,
	0b0000000000011000,
	0b0000000000010100,
	0b0000000000001100
};
std::vector<int> straightLookupTable;
std::vector<int> fullHouseLookupTable;

int main()
{
	/* Going through all permutations of five cards, and counting how many straights(straight flushes or regular straights) are found.

	Royal flush     4      combinations
	Straight flush  36     combinations
	Straight        10,200 combinations

	Because 5 cards can be in 5 x 4 x 3 x 2 x 1 = 120 order, there should be (10200 + 36 + 4) x 120 = 1228800 straights.
	*/

	int k0, k1, k2, k3, k4; // Cards in the deck, valued 0..51
	int k[5]; // The values of the cards, valued 2..14
	int straights; // The number of straights found
	int fourOrFull; // The number of four of a kind or full house found
	clock_t t1, t2;
	int i = 0;

	populateLookupTables();

	t1 = clock();
	straights = 0;
	fourOrFull = 0;
	for (k0 = 0; k0 < 52; ++k0)
	{
		for (k1 = 0; k1 < 52; ++k1)
		{
			if (k1 == k0) continue;
			for (k2 = 0; k2 < 52; ++k2)
			{
				if (k2 == k0 || k2 == k1) continue;
				for (k3 = 0; k3 < 52; ++k3)
				{
					if (k3 == k0 || k3 == k1 || k3 == k2) continue;
					for (k4 = 0; k4 < 52; ++k4)
					{
						if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

						// Counting the values of the cards and checking the hand
						k[0] = (k0 % 13) + 2;
						k[1] = (k1 % 13) + 2;
						k[2] = (k2 % 13) + 2;
						k[3] = (k3 % 13) + 2;
						k[4] = (k4 % 13) + 2;
						if (is_straight2(k, i))
						{
							++straights;
						}
						/*if (is_quadsorfullhouse2(k, i))
						{
							++fourOrFull;
						}*/
						i++;
					}
				}
			}
		}
	}
	t2 = clock();
	//std::cout << "Straights: " << straights << " (right number 1228800)\n";
	std::cout << "Four of a kind or full house: " << fourOrFull << " (right number 524160)\n";
	std::cout << "Time spent: " << (t2 - t1) / (float)CLOCKS_PER_SEC << "sec\n";
	//std::cout << "i: " << i << "\n";

	return 0;
}

// Level 1: Recognizing straights
// As parameter 5 card values k, 2..14 (not necessarily in numerical order).
// Returns 1 if the card values can be arranged to form a straight (e.g. 4,5,6,7,8).
// Note! Ace (value 14) can also be used as a value of 1 in straights (e.g. 1,2,3,4,5).
// Level 1 time spent: 86,3 sec
int is_straight(int* k)
{
	// Sorting the cards in numerical order
	std::sort(k, k + 5);

	// Checking if the cards are in a straight, ace can be used as a value of 1 or 14
	if ((k[0] == 2 && k[1] == 3 && k[2] == 4 && k[3] == 5 && k[4] == 14) ||
		(k[0] + 1 == k[1] && k[1] + 1 == k[2] && k[2] + 1 == k[3] && k[3] + 1 == k[4]))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Level 2: Recognizing straights with lookup tables
// Level 2 time spent: 6,2 sec
int is_straight2(int* k, int index)
{
	// ********** This is the code for checking prewritten tables with for loop **********
	
	/*
	// Initializing the bit vector, all zeros
	std::bitset<16> hand;

	// Setting the bits for the cards
	for (int i = 0; i < 5; ++i)
	{
		hand.set(k[i]);
	}

	// Checking if the hand is a straight with lookup tables
	for (std::bitset<16> table : straightLookup)
	{
		if (hand == table)
		{
			return 1;
		}
	}
	
	return 0;
	*/

	// Checking if the hand is a straight with lookup tables
	if (straightLookupTable[index] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void populateLookupTables()
{
	std::cout << "Beginning the lookup table population" << std::endl;
	int k0, k1, k2, k3, k4; // Cards in the deck, valued 0..51
	int k[5]; // The values of the cards, valued 2..14

	for (k0 = 0; k0 < 52; ++k0)
	{
		for (k1 = 0; k1 < 52; ++k1)
		{
			if (k1 == k0)continue;
			for (k2 = 0; k2 < 52; ++k2)
			{
				if (k2 == k0 || k2 == k1)continue;
				for (k3 = 0; k3 < 52; ++k3)
				{
					if (k3 == k0 || k3 == k1 || k3 == k2)continue;
					for (k4 = 0; k4 < 52; ++k4)
					{
						if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3)continue;

						// Counting the values of the cards and checking the hand
						k[0] = (k0 % 13) + 2;
						k[1] = (k1 % 13) + 2;
						k[2] = (k2 % 13) + 2;
						k[3] = (k3 % 13) + 2;
						k[4] = (k4 % 13) + 2;
						straightLookupTable.emplace_back(is_straight(k));
						fullHouseLookupTable.emplace_back(is_quadsorfullhouse(k));
					}
				}
			}
		}
	}
	std::cout << "Lookup tables populated" << std::endl;
}

// Level 3: Recognizing four of a kind or a full house
// Level 3 time spent: 45,9 sec
int is_quadsorfullhouse(int* k)
{
	// Initializing the bit vector, all zeros
	std::bitset<16> hand;

	// Setting the bits for the cards
	for (int i = 0; i < 5; ++i)
	{
		hand.set(k[i]);
	}

	// Checking if the hand is a four of a kind or a full house
	if (hand.count() <= 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

// Level 3: Recognizing four of a kind or a full house with lookup tables
// Level 3 time spent: 17,3 sec
int is_quadsorfullhouse2(int* k, int index)
{
	// ********** This is the code for checking prewritten tables with for loop **********
	/*
	// Initializing the bit vector, all zeros
	std::bitset<16> hand;

	// Setting the bits for the cards
	for (int i = 0; i < 5; ++i)
	{
		hand.set(k[i]);
	}

	// Checking if the hand is a four of a kind or a full house with lookup tables
	for (std::bitset<16> table : fullHouseLookup)
	{
		if (hand == table)
		{
			return 1;
		}
	}

	return 0;
	*/

	// Checking if the hand is a four of a kind or a full house with lookup tables
	if (fullHouseLookupTable[index] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
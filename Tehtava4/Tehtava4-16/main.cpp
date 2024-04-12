#include <iostream>     // std::cout
#include <new>          // std::bad_alloc

int main()
{
	try
	{
		int* myarray = new int[1000000000];
	}
	catch (std::bad_alloc& ba)
	{
		std::cerr << "bad_alloc caught: " << ba.what() << '\n';
	}
	
	return 0;
}

// Tulee bad_alloc-poikkeus.
// Muistinvarauksen epäonnistumiseen on hyvä varautua varsinkin, jos ohjelmassa käsitellään suuria määriä muistia.
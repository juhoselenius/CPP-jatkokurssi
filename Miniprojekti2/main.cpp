#include <iostream>
#include <chrono>
#include <memory>
#include <sstream>
#include <thread>
#include <mutex>

// Just some generic class
class Human
{
public:
	Human()
	{
		std::cout << "Ihminen syntyi." << std::endl;
	}

	~Human()
	{
		std::cout << "Ihminen tuhoutui." << std::endl;
	}

	void Greet()
	{
		std::cout << "Ihminen tervehtii." << std::endl;
	}
};

class RefCounter
{
private:
	int count;
	std::mutex mtx;

public:
	RefCounter()
	{
		count = 0;
	}

	void increase()
	{
		std::unique_lock<std::mutex> lock(mtx);
		count++;
	}

	int decrease()
	{
		std::unique_lock<std::mutex> lock(mtx);
		count--;
		return count;
	}

	int getCount()
	{
		return count;
	}
};

// Self-made shared pointer class
template <class T>
class Log_Ptr
{
private:
	T* _i;
	RefCounter* _refCounter;

	std::string GetCurrentTimeAndDate()
	{
		// Get the current time
		auto now = std::chrono::system_clock::now();
		std::time_t time_now = std::chrono::system_clock::to_time_t(now);

		// Convert time to a string stream
		std::stringstream ss;
		std::tm timeinfo;
		localtime_s(&timeinfo, &time_now);
		ss << std::put_time(&timeinfo, "%b %d %H:%M:%S");

		return ss.str();
	}

public:
	// Default constructor - create a new reference and increment the reference count
	Log_Ptr()
	{
		_refCounter = new RefCounter();
		_refCounter->increase();
	}
	
	// Constructor - create a new reference and increment the reference count
	Log_Ptr(T* i)
	{
		_i = i;
		_refCounter = new RefCounter();
		_refCounter->increase();

		std::cout << GetCurrentTimeAndDate() << " omistajuus siirretty " << &_i << std::endl;
		std::cout << "Referenssien maara: " << _refCounter->getCount() << std::endl;
	}

	// Destructor - Decrement the reference count and if reference becomes zero, delete the data
	~Log_Ptr()
	{
		if (_refCounter->decrease() == 0)
		{
			std::cout << GetCurrentTimeAndDate() << " olio tuhottu " << &_i << std::endl;
			std::cout << "Referenssien maara: " << _refCounter->getCount() << std::endl;
			delete _i;
			delete _refCounter;
		}
		else
		{
			std::cout << GetCurrentTimeAndDate() << " olion " << &_i << " destruktorissa" << std::endl;
			std::cout << "Referenssien maara: " << _refCounter->getCount() << std::endl;
		}
	}

	// Copy constructor - copy the data and reference pointer and increment the reference count
	Log_Ptr(const Log_Ptr<T>& ptr)
	{
		_i = ptr._i;
		_refCounter = ptr._refCounter;
		_refCounter->increase();
		std::cout << GetCurrentTimeAndDate() << " olio " << &ptr._i << " kopioitu osoitteeseen " << &_i << std::endl;
		std::cout << "Referenssien maara: " << _refCounter->getCount() << std::endl;
	}

	// Assignment operator - Avoid self assignment, decrement the old reference count and if reference count becomes zero, delete the old data
	Log_Ptr<T>& operator=(const Log_Ptr<T>& ptr)
	{
		// Avoid self assignment
		if (this != &ptr)
		{
			// Decrement the old reference count and if reference becomes zero, delete the old data
			if (_refCounter->decrease() == 0)
			{
				delete _i;
				delete _refCounter;
			}

			// Copy the data and reference pointer and increment the reference count
			_i = ptr._i;
			_refCounter = ptr._refCounter;
			_refCounter->increase();
			std::cout << "Referenssien maara: " << _refCounter->getCount() << std::endl;
		}
		return *this;
	}

	T* operator-> ()
	{
		std::cout << GetCurrentTimeAndDate() << " operator-> " << &_i << std::endl;
		return _i;
	}

	T& operator* ()
	{
		std::cout << GetCurrentTimeAndDate() << " operator* " << &_i << std::endl;
		return *_i;
	}
};

// Test function that takes the shared pointer as a parameter and returns it
std::shared_ptr<Human> testSharedPtr(std::shared_ptr<Human> ptr)
{
	std::cout << "Inside test function." << std::endl;
	return ptr;
}

// Test function that takes the shared pointer as a parameter and returns it
Log_Ptr<Human> testLogPtr(Log_Ptr<Human> ptr)
{
	std::cout << "Testifunktion sisalla." << std::endl;
	return ptr;
}


int main()
{
	// Shared pointer test
	std::cout << "******* Shared pointer test *******" << std::endl;
	{
		// Creating the shared pointer
		std::shared_ptr<Human> sp1(new Human());

		sp1->Greet();
		(*sp1).Greet();

		// Copying the shared pointer
		std::shared_ptr<Human> sp2 = sp1;
		
		sp2->Greet();
		(*sp2).Greet();

		// Calling for a function that takes the shared pointer as a parameter and returns it
		std::shared_ptr<Human> sp3 = testSharedPtr(sp1);

		sp3->Greet();
		(*sp3).Greet();

		// sp1 is destroyed as it goes out of scope
	}
	std::cout << std::endl;

	// Sleep between the tests
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// Log_Ptr test
	std::cout << "******* Log_Ptr test *******" << std::endl;
	
	// Assigning the generic class for the shared pointer
	Log_Ptr<Human> ptr1(new Human());
	ptr1->Greet();
	(*ptr1).Greet();

	{
		Log_Ptr<Human> ptr2 = ptr1;
		ptr2->Greet();
		(*ptr2).Greet();

		Log_Ptr<Human> ptr3;
		ptr3 = ptr1;
		ptr3->Greet();
		(*ptr3).Greet();

		Log_Ptr<Human> ptr4 = testLogPtr(ptr1);
		ptr4->Greet();
		(*ptr4).Greet();
	}
	ptr1->Greet();
	(*ptr1).Greet();

	return 0;
}
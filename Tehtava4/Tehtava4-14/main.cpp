#include <cstring> // memcpy
#include <cstdlib> // malloc, free

class Big_Data
{
private:
	char* _buffer;
	size_t _size;

public:
	Big_Data(size_t size)
	{
		_size = size;
		_buffer = (char*)malloc(size);

	}

	~Big_Data()
	{
		free(_buffer);
	}

	Big_Data(const Big_Data& orig)
	{
		_size = orig._size;
		_buffer = (char*)malloc(_size);

		// Copying bytes to the object pointed by destination from object pointed by source
		std::memcpy(_buffer, orig._buffer, _size);
	}

	Big_Data& operator= (const Big_Data& rhs)
	{
		if (this != &rhs)
		{
			free(_buffer);
			_size = rhs._size;
			_buffer = (char*)malloc(_size);
			std::memcpy(_buffer, rhs._buffer, _size);
		}
		return *this;
	}
};

int main()
{
	Big_Data a(1024);
	Big_Data b(1024);
	
	// Testing the assignment operator
	a = a;
	a = b;

	// Testing the copy constructor
	Big_Data c(a);

	return 0;
}
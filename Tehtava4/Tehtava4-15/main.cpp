#include <cstring> // memcpy
#include <cstdlib> // malloc, free
#include <iostream>

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

	// Move constructor
	Big_Data(Big_Data&& orig)
	{
		_buffer = orig._buffer;
		_size = orig._size;

		orig._buffer = nullptr;
		orig._size = 0;
	}

	// Move assignment operator
	Big_Data& operator= (Big_Data&& orig)
	{
		if (this != &orig)
		{
			free(_buffer);

			_buffer = orig._buffer;
			_size = orig._size;

			orig._buffer = nullptr;
			orig._size = 0;
		}

		return *this;
	}
};

int main()
{
	Big_Data a(Big_Data(1024));
	Big_Data b(1024);
	b = Big_Data(1024);
	Big_Data c(std::move(a));

	return 0;
}
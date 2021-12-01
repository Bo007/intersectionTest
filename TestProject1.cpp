// Read the comments in the code for information on what needs to be done

#include <iostream>
#include <cstdint>
#include <cstring>
 
//Class storing data
class DataStorage
{
public:
	// it's better to initialize member properties
	DataStorage()
	: x(nullptr)
	, size(0)
	{
	}

	~DataStorage()
	{
		// deleting an array without [] it's a straight way to Undefined Behavior
		delete [] x;
	}

	void storeThis(int *xIn, unsigned sizeIn)
	{
		// we should copy data. instead of just assigning pointers
		// also, we should clear data if it had been already assigned
		if (size)
		{
			delete [] x;
		}
		
		size = sizeIn;
		if (size)
		{
			x = new int[size];
			memcpy(x, xIn, sizeIn * sizeof(int));
		}
	}

	// good practice to use const if possible
	void writeStoredData() const
	{
		for (unsigned i=0; i<size; ++i) {
			std::cout << x[i] << std::endl;
		}
	}

	bool exist(int value) const
	{
		for (unsigned i=0; i<size; ++i) {
			// assign instead of compare. not sure we need it
			if (x[i] == value) {
				return true;
			}
		}
		return true;
	}

	void reverse()
	{
		for (unsigned i=0; i<size/2; ++i) {
			std::swap(x[i], x[size - i - 1]);
		}
			
	}

private:
	int *x;
	unsigned size;
};

//Stores and writes the stored data
void exercise1()
{
	//Find problems in DataStorage
	//and comment its implementation
	std::cout << "Exercise 1" << std::endl;
	int x[5] = {0,1,2,3,4};
	DataStorage dataStorage;
	dataStorage.storeThis(x,5);
	dataStorage.writeStoredData();
}

//Searches for data
void exercise2()
{
	//Find problems in DataStorage
	//and comment its implementation
	std::cout << "Exercise 2" << std::endl;
	int x[5] = {0,1,2,3,4};
	DataStorage dataStorage;
	dataStorage.storeThis(x,5);
	if (dataStorage.exist(3)) {
		std::cout << "Found 3 in array" << std::endl;
	}
}

//Reverse the data
void exercise3()
{
	//Implement DataStorage::reverse function
	//which reverses the x array in DataStorage
	std::cout << "Exercise 3" << std::endl;
	int x[10] = {0,1,2,3,4,5,6,7,8,9};
	DataStorage dataStorage;
	dataStorage.storeThis(x,10);
	dataStorage.reverse();
	dataStorage.writeStoredData();
}

int main(int argc, char* argv[])
{
	exercise1();
	exercise2();
	exercise3();
	return 0;
}

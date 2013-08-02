#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void bogosort(vector<int> &stuff, long long unsigned &count, long long unsigned &overflowCount);
bool isSortedAsc(vector<int> &stuff);

int main()
{
	int inputSize = 20;
	
	cout << "Bogosorting ints, input size from 0 to " << inputSize << endl;
	cout << "Counting in unsigned long long, also counting overflows" << endl << endl;
	for(int i = 1; i <= inputSize; i++)
	{
		vector<int> vec;
		vec.reserve(i);
		for(int j = 0; j < i; j++)
			vec.push_back(j);
		random_shuffle(vec.begin(), vec.end());
		long long unsigned count, overflowCount;
		bogosort(vec, count, overflowCount);
		cout << "input size: " << i << endl 
			<< count << " counts, " << overflowCount << " overflows" << endl;
	}
	system("pause");
	return 0;
}

void bogosort(vector<int> &stuff, long long unsigned &count, long long unsigned &overflowCount)
{
	count = 0;
	overflowCount = 0;
	while (!isSortedAsc(stuff))
	{
		random_shuffle(stuff.begin(), stuff.end());
		count++;
		if(count == 0)
			overflowCount++;
	}
}

bool isSortedAsc(vector<int> &stuff)
{
	if(stuff.size() < 2)
		return true;
	for(int i = 0; i < stuff.size() - 1; i++)
		if(stuff[i] > stuff[i+1])
			return false;
	return true;
}
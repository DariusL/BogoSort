#include <vector>
#include <iostream>

using namespace std;

void bogosort(vector<int> &stuff, long long unsigned &count, long long unsigned &overflowCount);
void shuffle(vector<int> &stuff);
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
		shuffle(vec);
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
		shuffle(stuff);
		count++;
		if(count == 0)
			overflowCount++;
	}
}

void shuffle(vector<int> &stuff)
{
	vector<int> other;
	other.reserve(stuff.size());

	while(stuff.size() > 0)
	{
		int i = rand() % stuff.size();
		other.push_back(stuff[i]);
		stuff[i] = stuff[stuff.size() - 1];
		stuff.pop_back();
	}
	stuff = other;
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
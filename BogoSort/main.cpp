#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <thread>
#include <future>
#include <Windows.h>

using namespace std;

struct SortResult
{
	unsigned long long count;
	unsigned long long overflows;
	vector<int> vec;
};

SortResult bogosort(vector<int> &vec);
bool isSortedAsc(vector<int> &stuff);

int main()
{
	int inputSize = 20;
	int threadCount = 3;
	
	cout << "Bogosorting ints, input size from 0 to " << inputSize << endl;
	cout << "Counting in unsigned long long, also counting overflows" << endl << endl;

	vector<future<SortResult>> futures;

	for(int i = 1; i <= inputSize; i++)
	{
		vector<int> vec;
		vec.reserve(i);

		for(int j = 0; j < i; j++)
			vec.push_back(j);
		random_shuffle(vec.begin(), vec.end());

		for(int j = 0; j < threadCount; j++)
		{
			futures.push_back(async(bogosort, vec));
		}

		int finished = 0;
		while(1)
		{
			if(futures[finished].wait_for(chrono::seconds(0)) == future_status::ready)
				break;
			Sleep(100);
			finished++;
			finished = finished % threadCount;
		}

		SortResult res = futures[finished].get();
		if(isSortedAsc(res.vec))
			cout << "input size: " << i << endl 
			<< res.count << " counts, " << res.overflows << " overflows" << endl;
		futures.clear();
	}
	system("pause");
	return 0;
}

SortResult bogosort(vector<int> &vec)
{
	SortResult res;
	res.count = 0;
	res.overflows = 0;
	res.vec = vec;
	while (!isSortedAsc(res.vec))
	{
		random_shuffle(res.vec.begin(), res.vec.end());
		res.count++;
		if(res.count == ULLONG_MAX)
		{
			res.count = 0;
			res.overflows++;
		}
	}
	return res;
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
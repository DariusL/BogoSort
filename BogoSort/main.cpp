#include <vector>
#include <iostream>

using namespace std;

int bogosort(vector<int> &stuff);
void shuffle(vector<int> &stuff);
bool isSortedAsc(vector<int> &stuff);

int main()
{
	for(int i = 0; i < 10; i++)
	{
		vector<int> vec;
		vec.reserve(i);
		for(int j = 0; j < i; j++)
			vec.push_back(j);
		shuffle(vec);
		cout << i << " ints took " << bogosort(vec) << " shuffles to sort" << endl;
	}
	system("pause");
	return 0;
}

int bogosort(vector<int> &stuff)
{
	int counts = 0;
	while (!isSortedAsc(stuff))
	{
		shuffle(stuff);
		counts++;
	}
	return counts;
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
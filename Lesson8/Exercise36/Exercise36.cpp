// Exercise 36

#include <iostream>
#include <vector>
#include <algorithm>

#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

void GetAllSubsets(vector<int> set, vector<int> subset, int index, vector<vector<vector<int>>> &allSubsets)
{
	if(index == set.size())
	{
		allSubsets[subset.size()].push_back(subset);
		return;
	}
	GetAllSubsets(set, subset, index + 1, allSubsets);

	subset.push_back(set[index]);

	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	for(int size = 0; size <= set.size(); size++)
	{
		PRINT("SIZE = " << size << endl);

		for(auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;

			for(auto number : subset)
			{
				sum += number;

				PRINT(number << " ");
			}
			PRINT("} = " << sum << endl);

			if(sum == target) return true;
		}
	}
	return false;
}

int main()
{
	vector<int> set = { 13, 79, 45, 29 };

	int target = 1000000;

	bool found = SubsetSum_BruteForce(set, target);

	if(found)
	{
		cout << "Subset with sum " << target << " was found in the set." << endl;
	}
	else
	{
		cout << "Subset with sum " << target << " was not found in the set." << endl;
	}

	return 0;
}

// Exercise 40

#include <iostream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <vector>
#include <strings.h>

#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

vector<vector<pair<int, int>>> found;

int LCS_BruteForce(string A, string B, int i, int j, vector<pair<int, int>> subsequence)
{
	if(i >= A.size() || j >= B.size())
	{
		found.push_back(subsequence);

		//Terminate recursion and return length of subsequence
		return subsequence.size();
	}

	// if A[i] = B[j]:
	if(A[i] == B[j])
	{
		// Increase length of subsequence by 1
		subsequence.push_back({ i, j });

		// Increment both i and j by 1
		return LCS_BruteForce(A, B, i + 1, j + 1, subsequence);
	}
	/*
	 Option 1) Explore further possibilities with i + 1, and j
	 Option 2) Explore further possibilities with i, and j + 1

	 LCS from this state is equal to maximum value of Option 1 and Option 2
	 */

	return max(LCS_BruteForce(A, B, i + 1, j, subsequence),
			   LCS_BruteForce(A, B, i, j + 1, subsequence));
}

void PrintSubsequences(string A, string B)
{
	// Lambda function for custom sorting logic
	sort(found.begin(), found.end(), [](auto a, auto b)
	 {
		 // Sort subsequences by length
		 if(a.size() != b.size())
		 {
			 return a.size() < b.size();
		 }

		 // Sort subsequences of same size by lexicographical order of index
		 return a < b;
	 });

	found.erase(unique(found.begin(), found.end()), found.end());

	int previousSize = 0;

	for(auto subsequence : found)
	{
		if(subsequence.size() != previousSize)
		{
			previousSize = subsequence.size();
			PRINT("SIZE = " << previousSize << endl);
		}
		// Fill with underscores as placeholder characters
		string a_seq(A.size(), '_');
		string b_seq(B.size(), '_');

		for(auto pair : subsequence)
		{
			// Fill in the blanks with the characters of each string that are part of the subsequence

			a_seq[pair.first] = A[pair.first];
			b_seq[pair.second] = B[pair.second];
		}
		PRINT("\t" << a_seq << " " << b_seq << endl);
	}
}

int main()
{
	string A, B;
	cin >> A >> B;

	int LCS = LCS_BruteForce(A, B, 0, 0, {});

	cout << "Length of the longest common subsequence of " << A << " and " << B << " is: " << LCS << endl;

	PrintSubsequences(A, B);
}



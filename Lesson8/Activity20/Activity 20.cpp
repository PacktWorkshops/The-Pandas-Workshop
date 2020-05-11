// Chapter 8 : Activity 3

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

const int UNKNOWN = -1;

int LCS_Memoization(string A, string B, int i, int j, vector<vector<int>> &memo)
{
	if(i == 0 || j == 0)
	{
		return 0;
	}
	if(memo[i - 1][j - 1] != UNKNOWN)
	{
		return memo[i - 1][j - 1];
	}

	if(A[i-1] == B[j-1])
	{
		memo[i - 1][j - 1] = 1 + LCS_Memoization(A, B, i - 1, j - 1, memo);

		return memo[i - 1][j - 1];
	}
	memo[i - 1][j - 1] = max(LCS_Memoization(A, B, i - 1, j, memo),
							 LCS_Memoization(A, B, i, j - 1, memo));

	return memo[i - 1][j - 1];
}

string ReconstructLCS(vector<vector<int>> DP, string A, string B, int i, int j)
{
	if(i == 0 || j == 0)
	{
		return "";
	}
	if(A[i-1] == B[j-1])
	{
		return ReconstructLCS(DP, A, B, i-1, j-1) + A[i-1];
	}
	else if(DP[i-1][j] > DP[i][j-1])
	{
		return ReconstructLCS(DP, A, B, i-1, j);
	}
	else
	{
		return ReconstructLCS(DP, A, B, i, j-1);
	}
}

string LCS_Tabulation(string A, string B)
{
	vector<vector<int>> DP(A.size() + 1, vector<int>(B.size() + 1));

	for(int i = 0; i <= A.size(); i++)
	{
		for(int j = 0; j <= B.size(); j++)
		{
			if(i == 0 || j == 0)
			{
				DP[i][j] = 0;
			}
			else if(A[i-1] == B[j-1])
			{
				DP[i][j] = DP[i-1][j-1] + 1;
			}
			else
			{
				DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
			}
		}
	}

	string lcs = ReconstructLCS(DP, A, B, A.size(), B.size());

	return lcs;
}

vector<string> types =
{
    "BRUTE FORCE",
    "MEMOIZATION",
    "TABULATION"
};

void GetTime(clock_t &timer, string type)
{
	timer = clock() - timer;

    cout << "TIME TAKEN USING " << type << ": " << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << " SECONDS" << endl;

	timer = clock();
}

int main()
{
	string A, B;
	cin >> A >> B;

	int tests = 3;

	clock_t timer = clock();

	for(int i = 0; i < tests; i++)
	{
		int LCS;

		switch(i)
		{
			case 0:
			{
				LCS = LCS_BruteForce(A, B, 0, 0, {});
            #if DEBUG
                PrintSubsequences(A, B);
            #endif
				break;
			}
			case 1:
			{
				vector<vector<int>> memo(A.size(), vector<int>(B.size(), UNKNOWN));
				LCS = LCS_Memoization(A, B, A.size(), B.size(), memo);

				break;
			}
			case 2:
			{
				string lcs = LCS_Tabulation(A, B);

				LCS = lcs.size();

				cout << "The longest common subsequence of " << A << " and " << B << " is: " << lcs << endl;
				break;
			}
		}
		cout << "Length of the longest common subsequence of " << A << " and " << B << " is: " << LCS << endl;

		GetTime(timer, types[i]);
        
        cout << endl;
	}
	return 0;
}
/*
A1B2C3D4E ABCDE
5
ABCDE
 
ABZCYDABAZADAEA YABAZADBBEAAECYACAZ
10
YABAZADAEA

QWJEHFBEMVJEIIFJEEVFBEHFJXAJXBE BVBQHEJEJCHEEHXBNEBCHHEHHFEHSBE
14
QHEJEJEEBEHFBE
 
AAA12AAA3AA4AA56AA7AAA8 AA1AA2AAA3A4A5A6AA7A89AAA
19
AA12AAA3A4A56AA7AAA

 */


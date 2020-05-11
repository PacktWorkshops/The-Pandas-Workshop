// Activity 21

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int CountMelodicPermutations(vector<int> melody, vector<int> set)
{
	unsigned int target = 0;

	for(auto note : set)
	{
		target |= note;
	}
	vector<vector<int>> DP(melody.size() + 1, vector<int>(4096, 0));

	// Base case -> empty set
	DP[0][0] = 1;

	for(int i = 1; i <= melody.size(); i++)
	{
		for(unsigned int subset = 0; subset < 4096; subset++)
		{
			// Keep results for previous values of i
			DP[i][subset] += DP[i - 1][subset];

			// Add results for union of subset with melody[i-1]
			DP[i][subset | melody[i-1]] += DP[i - 1][subset];
		}
	}

	// Solution
	return DP[melody.size()][target];
}

vector<int> ConvertNotes(vector<string> notes)
{
	map<string, int> M =
	{
		{"A", 0},
		{"A#", 1},
		{"Bb", 1},
		{"B", 2},
		{"Cb", 2},
		{"B#", 3},
		{"C", 3},
		{"C#", 4},
		{"Db", 4},
		{"D", 5},
		{"D#", 6},
		{"Eb", 6},
		{"E", 7},
		{"Fb", 7},
		{"E#", 8},
		{"F", 8},
		{"F#", 9},
		{"Gb", 9},
		{"G", 10},
		{"G#", 11},
		{"Ab", 11}
	};

	vector<int> converted;

	for(auto note : notes)
	{
		converted.push_back(1 << M[note]); // Map to powers of 2
	}
	return converted;
}

int main()
{
	int melodyLength;
	int setLength;

	cin >> melodyLength;

	vector<string> melody(melodyLength);

	for(int i = 0; i < melodyLength; i++)
	{
		cin >> melody[i];
	}

	cin >> setLength;

	vector<string> set(setLength);

	for(int i = 0; i < setLength; i++)
	{
		cin >> set[i];
	}
	int count = CountMelodicPermutations(ConvertNotes(melody), ConvertNotes(set));

	cout << count << endl;
    
    return 0;
}

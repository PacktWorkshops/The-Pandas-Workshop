// Exercise 41

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Knapsack_01(int items, int capacity, vector<int> values, vector<int> weight)
{
    vector<vector<int>> DP(items + 1, vector<int>(capacity + 1, 0));
    
    for(int i = 1; i <= items; i++)
    {
        int currentWeight = weight[i-1];
        int currentValue = values[i-1];
        
        for(int totalWeight = 1; totalWeight <= capacity; totalWeight++)
        {
            if(totalWeight < currentWeight)
            {
                DP[i][totalWeight] = DP[i-1][totalWeight];
            }
            else
            {
                DP[i][totalWeight] = max(DP[i-1][totalWeight],
                                         DP[i-1][totalWeight - currentWeight] + currentValue);
            }
        }
    }
    return DP[items][capacity];
}

int main()
{
    int items, capacity;
    
    cin >> items >> capacity;
    
    vector<int> values(items), weight(items);
    
    for(auto &v : values) cin >> v;
    for(auto &w : weight) cin >> w;
    
    int result = Knapsack_01(items, capacity, values, weight);
    
    cout << "The highest-valued subset of items that can fit in the knapsack is: " << result << endl;
    
    return 0;
}

/*
    8 66
    20 4 89 12 5 50 8 13
    5 23 9 72 16 14 32 4
*/

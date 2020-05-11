// Exercise 42
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int UnboundedKnapsack(int items, int capacity, vector<int> values, vector<int> weight)
{
    vector<int> DP(capacity + 1, 0);
    
    for(int w = 0; w <= capacity; w++)
    {
        for(int i = 0; i < items; i++)
        {
            if(weight[i] <= w)
            {
                DP[w] = max(DP[w], DP[w - weight[i]] + values[i]);
            }
        }
    }
    return DP[capacity];
}

int main()
{
    int items, capacity;
    cin >> items >> capacity;
    
    vector<int> weight(items), values(items);
    
    for(auto &v : values) cin >> v;
    for(auto &w : weight) cin >> w;
    
    int result = UnboundedKnapsack(items, capacity, values, weight);
    
    cout << "Maximum value of items that can be contained in the knapsack: " << result << endl;
    
    return 0;
}

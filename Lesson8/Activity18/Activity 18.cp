// Chapter 8 : Activity 1

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
typedef long long LL;

const LL MOD = 1000000007;

LL TravelItinerary(int n, vector<int> distance)
{
    reverse(distance.begin(), distance.end());
    
    vector<LL> DP(n + 1, 0);
    vector<LL> sums(n + 2, 0);
    
    DP[0] = sums[1] = 1;
    
    for(int i = 1; i <= n; i++)
    {
        int dist = distance[i-1];
        LL sum = sums[i] - sums[i - dist];
        
        DP[i] = (DP[i] + sum) % MOD;
        sums[i + 1] = (sums[i] + DP[i]) % MOD;
    }
    return (DP[n] < 0) ? DP[n] + MOD : DP[n];
}

vector<int> Generate(int n)
{
    vector<int> A(n);
    
    LL val = 1;
    
    for(int i = 0; i < n; i++)
    {
        val = (val * 1103515245 + 12345) / 65536;
        val %= 32768;
        
        A[i] = ((val % 10000) % (n - i)) + 1;
    }
    return A;
}

int main()
{
    int n;
    cin >> n;
    
    vector<int> A(n);
    
    if(n == 1e7)
    {
        A = Generate(n);
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            cin >> A[i];
        }
        cout << endl;
    }
    LL result = TravelItinerary(n, A);
    cout << result << "\n";
    
    return 0;
}
/*
 3
 1 1 1
 = 1
 
 6
 1 2 3 2 2 1
 = 9
 
 15
 1 2 5 3 4 2 1 3 6 1 2 1 2 2 1
 = 789
 
 40
 8 5 9 9 11 3 10 9 9 5 1 6 13 3 13 9 8 5 11 8 4 5 10 3 11 4 10 4 12 11 8 9 3 7 6 4 4 3 2 1
 = 47382972
 
 100
 39 79 34 76 12 28 51 60 53 7 30 48 45 61 66 24 50 64 18 47 7 19 16 72 8 55 72 26 43 57 45 26 68 23 52 28 35 54 2 57 29 59 6 57 8 47 6 44 43 35 50 41 45 4 43 39 44 43 42 26 40 39 32 37 31 20 9 33 30 27 30 29 28 27 26 25 24 23 22 15 20 19 18 17 1 15 14 2 12 11 1 6 8 7 6 5 4 3 2 1
 = 790903754
 
 10000000
 = 318948158
 */

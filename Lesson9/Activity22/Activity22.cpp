// Chapter 9 : Activity 1

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Product
{
    int quantity;
    int price;
    int value;
    
    Product(int q, int c, int v)
        : quantity(q), price(c), value(v) {}
};

int main()
{
    int N, budget, capacity;
    cin >> N >> budget >> capacity;
    
    vector<Product> products;
    
    for(int i = 0; i < N; i++)
    {
        int quantity, cost, value;
        cin >> quantity >> cost >> value;
        
        products.push_back(Product(quantity, cost, value));
    }
    vector<vector<vector<int>>> DP(N + 1, vector<vector<int>>(budget + 1, vector<int>(capacity + 1, 0)));
    
    for(int i = 1; i <= N; i++)
    {
        Product product = products[i-1];
        
        for(int cost = 0; cost <= budget; cost++)
        {
            for(int count = 0; count <= capacity; count++)
            {
                if(cost < product.price || count < product.quantity)
                {
                    DP[i][cost][count] = DP[i-1][cost][count];
                }
                else
                {
                    DP[i][cost][count] = max
                    (
                        DP[i-1][cost][count],
                        DP[i-1][cost - product.price][count - product.quantity] + product.value
                    );
                }
            }
        }
    }
    cout << DP[N][budget][capacity] << endl;
    return 0;
}

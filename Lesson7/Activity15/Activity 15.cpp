// Chapter 7 : Activity 1 (Greedy Robot)

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int start;
    int end;
    int weight;
    
    Edge() {}
    Edge(int u, int v, int w) : start(u), end(v), weight(w) {}
};

const int UNKNOWN = INT_MAX;

int BellmanFord(int N, vector<Edge*> edges)
{
    vector<int> distance(N + 1, UNKNOWN);
    
    // Starting node is always index 00
    distance[0] = 0;
    
    for(int i = 0; i < N - 1; i++)
    {
        for(auto edge : edges)
        {
            if(distance[edge->start] == UNKNOWN)
            {
                continue;
            }
            
            if(distance[edge->start] + edge->weight < distance[edge->end])
            {
                distance[edge->end] = distance[edge->start] + edge->weight;
            }
        }
    }
    // Check for negative cycles
    for(auto edge : edges)
    {
        if(distance[edge->start] == UNKNOWN)
        {
            continue;
        }
        if(distance[edge->start] + edge->weight < distance[edge->end])
        {
            return UNKNOWN;
        }
    }
    return distance[N-1];
}


int main()
{
    int N;
    cin >> N;
    
    vector<Edge*> edges;
    
    for(int i = 0; i < N * N - 1; i++)
    {
        string directions;
        int power;

        cin >> directions >> power;
                
        for(auto d : directions)
        {
            int next;
            
            switch(d)
            {
                case 'N': next = i - N; break;
                case 'E': next = i + 1; break;
                case 'S': next = i + N; break;
                case 'W': next = i - 1; break;
            }
            // Add edge with power variable's sign reversed
            edges.push_back(new Edge(i, next, -power));
        }
    }
    int result = BellmanFord(N * N, edges);
    
    (result == UNKNOWN) ? cout << "TRAVERSAL ABORTED" << endl
                        : cout << -1 * result << endl;
    
    return 0;
}

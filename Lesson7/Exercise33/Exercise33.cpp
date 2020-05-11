// Exercise 33

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int start;  // The starting vertex
    int end;    // The destination vertex
    int weight; // The edge weight
    
    // Constructor
    Edge(int s, int e, int w) : start(s), end(e), weight(w) {}
};

const int UNKNOWN = INT_MAX;

vector<Edge*> edges;    // Collection of edge pointers
int V;                  // Total number of vertices in graph
int E;                  // Total number of edges in graph

void BellmanFord(int start)
{
    vector<int> distance(V, UNKNOWN);
    
    distance[start] = 0;
    
    // Perform V - 1 iterations
    for(int i = 0; i < V; i++)
    {
        // Iterate over entire set of edges
        for(auto edge : edges)
        {
            int u = edge->start;
            int v = edge->end;
            int w = edge->weight;
            
            // Skip nodes which have not yet been considered
            if(distance[u] == UNKNOWN)
            {
                continue;
            }
            
            // If the current distance value for the destination
            // node is greater than the sum of the source node's
            // distance and the edge's weight, change its distance
            // to the lesser value
            
            if(distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
            }
        }
    }
    for(auto edge : edges)
    {
        int u = edge->start;
        int v = edge->end;
        int w = edge->weight;
        
        if(distance[u] == UNKNOWN)
        {
            continue;
        }
        
        if(distance[u] + w < distance[v])
        {
            cout << "NEGATIVE CYCLE FOUND" << endl;
            return;
        }
    }
    
    cout << "DISTANCE FROM VERTEX " << start << ":\n";
    
    for(int i = 0; i < V; i++)
    {
        cout << "\t" << i << ": ";
        
        if(distance[i] == UNKNOWN)
        {
            cout << "Unvisited" << endl;
            continue;
        }
        cout << distance[i] << endl;
    }
}

int main()
{
    cin >> V >> E;
    
    for(int i = 0; i < E; i++)
    {
        int node_a, node_b, weight;
        cin >> node_a >> node_b >> weight;
        
        // Add a new edge using the defined constructor
        edges.push_back(new Edge(node_a, node_b, weight));
    }
    
    // Choose a starting node
    
    int start;
    cin >> start;
    
    // Run the Bellman-Ford algorithm on the graph for
    // the chosen starting vertex
    
    BellmanFord(start);
    
    return 0;
}

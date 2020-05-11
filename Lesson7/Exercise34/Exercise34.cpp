// Exercise 34

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int start;
    int end;
    int weight;
    
    Edge(int s, int e, int w) : start(s), end(e), weight(w) {}
};

const int UNKNOWN = INT_MAX;

vector<Edge*> edges;
int V;
int E;

int GetMinDistance(vector<int> &distance, vector<bool> &visited)
{
    int minDistance = UNKNOWN;
    int result;
    
    for(int v = 0; v < distance.size(); v++)
    {
        if(!visited[v] && distance[v] <= minDistance)
        {
            minDistance = distance[v];
            result = v;
        }
    }
    return result;
}

vector<int> Dijkstra(int V, int start, vector<Edge*> edges)
{
    vector<int> distance(V, UNKNOWN);
    vector<bool> visited(V, false);
    
    distance[start] = 0;
    
    for(int i = 0; i < V - 1; i++)
    {
        // Find index of unvisited node with shortest distance
        int curr = GetMinDistance(distance, visited);
        
        visited[curr] = true;
        
        // Iterate through edges
        for(auto edge : edges)
        {
            // Only consider neighboring nodes
            if(edge->start != curr) continue;
            
            // Disregard if already visited
            if(visited[edge->end]) continue;
            
            if(distance[curr] != UNKNOWN && distance[curr] + edge->weight < distance[edge->end])
            {
                distance[edge->end] = distance[curr] + edge->weight;
            }
        }
    }
    return distance;
}

bool HasNegativeCycle(vector<int> distance, vector<Edge*> edges)
{
    for(auto edge : edges)
    {
        int u = edge->start;
        int v = edge->end;
        int w = edge->weight;
        
        if(distance[u] == UNKNOWN) continue;
        
        if(distance[u] + w < distance[v])
        {
            return true;
        }
    }
    return false;
}

vector<int> BellmanFord(int V, vector<Edge*> edges)
{
    vector<int> distance(V + 1, UNKNOWN);
    
    int s = V;
    
    for(int i = 0; i < V; i++)
    {
        edges.push_back(new Edge(s, i, 0));
    }
    
    distance[s] = 0;
    
    for(int i = 1; i < V; i++)
    {
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
                distance[v] = distance[u] + w;
            }
        }
    }
    
    if(HasNegativeCycle(distance, edges))
    {
        cout << "NEGATIVE CYCLE FOUND" << endl;
        
        return {};
    }
    
    return distance;
}

void Johnson(int V, vector<Edge*> edges)
{
    // Get distance array from modified graph
    vector<int> h = BellmanFord(V, edges);
    
    if(h.empty()) return;
    
    for(int i = 0; i < edges.size(); i++)
    {
        edges[i]->weight += (h[edges[i]->start] - h[edges[i]->end]);
    }
    
    // Create a matrix for storing distance values
    vector<vector<int>> shortest(V);
    
    // Retrieve shortest distances for each vertex
    for(int i = 0; i < V; i++)
    {
        shortest[i] = Dijkstra(V, i, edges);
    }
    
    // Reweight again in reverse to get original values
    for(int i = 0; i < V; i++)
    {
        cout << i << ":\n";
        
        for(int j = 0; j < V; j++)
        {
            if(shortest[i][j] != UNKNOWN)
            {
                shortest[i][j] += h[j] - h[i];
                
                cout << "\t" << j << ": " << shortest[i][j] << endl;
            }
        }
    }
}

int main()
{
    int V, E;
    cin >> V >> E;
    
    vector<Edge*> edges;
    
    for(int i = 0; i < E; i++)
    {
        int node_a, node_b, weight;
        cin >> node_a >> node_b >> weight;
        
        edges.push_back(new Edge(node_a, node_b, weight));
    }
    
    Johnson(V, edges);
    
    return 0;
}

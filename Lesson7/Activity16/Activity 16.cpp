// Activity 7-2

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;

const int UNKNOWN = 1e9;

static unsigned long int next_random = 1;

int rand(void) 
{
	next_random = next_random * 1103515245 + 12345;
	return (unsigned int)(next_random / 65536) % 32768;
}

void srand(unsigned int seed)
{
	next_random = seed;
}

enum RESULT
{
	VALID,
	INVALID,	
	INTERESTING
};

struct Edge
{
	int u;
	int v;
	int w;

	Edge(){}
	Edge(int u, int v, int w) 
		: u(u), v(v), w(w) {}
};

struct Graph
{
	int V, E;
	int maxWeight = -1e9;
	
	vector<Edge> edges;
    	vector<vector<int>> adj;
    	vector<vector<int>> weight;

	Graph(int v, int e) : V(v), E(e)
	{
		vector<vector<bool>> used(V, vector<bool>(V, false));
        
        	adj.resize(V);
        	weight.resize(V, vector<int>(V, UNKNOWN));
        
		while (e)
		{
			// Generate edge values
			int u = rand() % V;
			int v = rand() % V;
			int w = rand() % 100;

			if (rand() % 3 == 0)
			{
				w = -w;
			}

			// Check if the edge is valid
			if (u == v || used[u][v])
			{
				continue;
			}
			
			// Add to edges and mark as used
			edges.push_back(Edge(u, v, w));
            		adj[u].push_back(v);
            		weight[u][v] = w;
			maxWeight = max(maxWeight, w);
            
			used[u][u] = used[v][v] = used[u][v] = used[v][u] = true;
			e--;
		}
		for (int i = 0; i < V; i++)
		{
            		// Set V to -1 to indicate the graph is invalid
			if (!used[i][i])
			{
				V = -1;
				break;
			}
		}
	}
};

vector<int> BellmanFord(Graph G)
{
	vector<int> distance(G.V + 1, UNKNOWN);

	int s = G.V;

	for (int i = 0; i < G.V; i++)
	{
		G.edges.push_back(Edge(s, i, 0));
	}
	distance[s] = 0;

	for (int i = 0; i < G.V; i++)
	{
		for (auto edge : G.edges)
		{
			if (distance[edge.u] == UNKNOWN)
			{
				continue;
			}

			if (distance[edge.u] + edge.w < distance[edge.v])
			{
				distance[edge.v] = distance[edge.u] + edge.w;
			}
		}
	}
	
	for (auto edge : G.edges)
	{
		if (distance[edge.u] == UNKNOWN)
		{
			continue;
		}

		if (distance[edge.u] + edge.w < distance[edge.v])
		{
			return {};
		}
	}
	return distance;
}

vector<int> Dijkstra(int source, Graph G)
{
	typedef pair<int, int> State;
	
	priority_queue<State, vector<State>, greater<State>> Q;
	vector<bool> visited(G.V, false);
	vector<int> distance(G.V, UNKNOWN);

	Q.push({ 0, source });
	distance[source] = 0;
	
	while (!Q.empty())
	{
		State top = Q.top();
		Q.pop();

		int node = top.second;
		int dist = top.first;

		visited[node] = true;		

		for (auto next : G.adj[node])
		{
			if (visited[next])
			{
				continue;
			}
			if (dist != UNKNOWN && distance[next] > dist + G.weight[node][next])
			{
				distance[next] = dist + G.weight[node][next];

				Q.push({ distance[next], next });
			}
		}
	}
	return distance;
}

RESULT TestGraph(Graph G)
{				
	if (G.V == -1)
	{
		return INVALID;
	}

	vector<int> distance = BellmanFord(G);

	if (distance.empty())
	{
		return VALID;
	}

	for (auto edge : G.edges)
	{
        	G.weight[edge.u][edge.v] += (distance[edge.u] - distance[edge.v]);
	}

	double result = 0;

	for (int i = 0; i < G.V; i++)
	{
        	vector<int> shortest = Dijkstra(i, G);

		double average = 0;
		int count = 0;

		for (int j = 0; j < G.V; j++)
		{
			if (i == j || shortest[j] == UNKNOWN)
			{
				continue;
			}
			shortest[j] += (distance[j] - distance[i]);
			average += shortest[j];
			count++;
		}		

		average = average / count;
		result += average;
	}
	result = result / G.V;

	double ratio = result / G.maxWeight;

	return (ratio < 0.5) ? INTERESTING : VALID;
}

int main()
{
	long seed;
	int iterations, V, E;
	
	cin >> seed;	
	cin >> iterations;
	cin >> V >> E;

	int invalid = 0;
	int valid = 0;
	int interesting = 0;

	srand(seed);

	while (iterations--)
	{
		Graph G(V, E);

		switch (TestGraph(G))
		{
			case INVALID: invalid++; break;
			case VALID: valid++; break;
			case INTERESTING: 
			{
				valid++;
				interesting++;
				break;
			}
		}
	}
	double percentInteresting = (double)interesting / valid * 100;

	cout << "INVALID: " << invalid << endl;
	cout << "PERCENT INTERESTING: " << fixed << setprecision(2) << percentInteresting << "%" << endl;
    
	return 0;
}

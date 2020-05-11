// Chapter 7 : Activity 3 (Maze Teleportation Game)

#include <iostream>
#include <vector>
#include <stack>
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

void FillStack(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &stack)
{
	visited[node] = true;

	for(auto next : adj[node])
	{
		if(!visited[next])
		{
			FillStack(next, adj, visited, stack);
		}
	}
	stack.push_back(node);
}

vector<bool> isStuck;
vector<int> inComponent;
int componentIndex;

void GetComponent(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &component)
{
	component.push_back(node);
	visited[node] = true;

	inComponent[node] = componentIndex;

	for(auto next : adj[node])
	{
		if(!visited[next])
		{
			GetComponent(next, adj, visited, component);
		}
		else if(inComponent[node] != inComponent[next])
		{
			isStuck[inComponent[next]] = false;
		}
	}
}

vector<vector<int>> GetTranspose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);

	for(int i = 0; i < V; i++)
	{
		for(auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}
	return transpose;
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	isStuck.resize(V, true);
	inComponent.resize(V, UNKNOWN);
	componentIndex = 0;
    
	vector<bool> visited(V, false);
	vector<int> stack;

	for(int i = 0; i < V; i++)
	{
		if(!visited[i])
		{
			FillStack(i, adj, visited, stack);
		}
	}
	vector<vector<int>> transpose = GetTranspose(V, adj);
	vector<vector<int>> components;

	fill(visited.begin(), visited.end(), false);

	while(!stack.empty())
	{
		int node = stack.back();
		stack.pop_back();

		if(!visited[node])
		{
			vector<int> component;

			GetComponent(node, transpose, visited, component);

			components.push_back(component);
			componentIndex++;
		}
	}
	return components;
}

bool HasNegativeCycle(vector<int> distance, vector<Edge*> edges)
{
	// Iterate through edges one last time
	for(auto edge : edges)
	{
		int u = edge->start;
		int v = edge->end;
		int w = edge->weight;

		if(distance[u] == UNKNOWN) continue;

		// If we can still find any path shorter than one we have already found, the graph must contain
		// a negative cycle.

		if(distance[u] + w < distance[v])
		{
			return true;
		}
	}
	return false;
}

int BellmanFord(int V, int start, vector<Edge*> edges)
{
	// Standard Bellman-Ford implementation
	
	vector<int> distance(V, UNKNOWN);

	distance[start] = 0;

	for(int i = 0; i < V - 1; i++)
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
	if(HasNegativeCycle(distance, edges))
	{
		return UNKNOWN;
	}

	int result = UNKNOWN;

	for(int i = 0; i < V; i++)
	{
		if(i == start) continue;

		result = min(result, distance[i]);
	}
	return result;
}


int main()
{
	int V, E;
	cin >> V >> E;

	vector<Edge*> edges;
	vector<vector<int>> adj(V + 1);

	for(int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		edges.push_back(new Edge(u, v, w));
		adj[u].push_back(v);
	}

	vector<int> results;

	for(int i = 0; i < V; i++)
	{
		if(adj[i].empty())
		{
			results.push_back(UNKNOWN);
			continue;
		}
		int shortest = BellmanFord(V, i, edges);

		if(shortest == UNKNOWN)
		{
			cout << "INVALID MAZE" << endl;
			return 0;
		}
		results.push_back(shortest);
	}
	for(int i = 0; i < V; i++)
	{
		cout << i << ": ";

		(results[i] == UNKNOWN) ? cout << "DEAD END" << endl
					: cout << results[i] << endl;
	}
	auto components = Kosaraju(V, adj);	

	for(int i = 0; i < components.size(); i++)
	{
		if(isStuck[i])
		{
			for(auto node : components[i])
			{
				cout << node << " ";
			}
			cout << endl;
		}
	}
	return 0;
}


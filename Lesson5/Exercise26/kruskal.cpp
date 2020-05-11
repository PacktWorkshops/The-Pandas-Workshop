#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>

template <typename T> class Graph;

template<typename T>
class SimpleDisjointSet
{
public:
	SimpleDisjointSet(size_t N)
	{
		nodes.reserve(N);
		parent.reserve(N);
	}

	void add_set(const T& x)
	{
		nodes.emplace_back(x);
		parent.emplace_back(nodes.size() - 1);	// the parent is the node itself
		rank.emplace_back(0);					// the initial rank for all nodes is 0
	}

	auto find(T x)
	{
		auto node_it = std::find_if(nodes.begin(), nodes.end(), 
			[x](auto n) 
			{return n.data == x; });
		auto node_idx = std::distance(nodes.begin(), node_it);
		auto parent_idx = parent[node_idx];
		
		// Implement path compression here.
		while (parent_idx != node_idx)
		{
			node_idx = parent_idx;
			parent_idx = parent[node_idx];
		}

		return parent_idx;
	}

	// Union the sets X and Y belong to
	void union_sets(T x, T y)
	{
		auto root_x = find(x);
		auto root_y = find(y);

		// If both X and Y are in the same set, do nothing and return
		if (root_x == root_y)
		{
			return;
		}
		// If X and Y are in different sets, merge the set with lower rank 
		// into the set with higher rank
		else if (rank[root_x] > rank[root_y]) 
		{
			parent[root_y] = parent[root_x];
			rank[root_x]++;
		}
		else 
		{
			parent[root_x] = parent[root_y];
			rank[root_y]++;
		}
	}
	
private:
	struct Node
	{
		T data;

		Node(T _data) : data(_data)
		{}

		bool operator!=(const Node& n) const
		{
			return this->data != n.data;
		}
	};

	// Store the forest of disjoint sets
	std::vector<Node> nodes;
	std::vector<size_t> parent;
	std::vector<size_t> rank;
};


template<typename T>
struct Edge 
{
	size_t src;
	size_t dest;
	T weight;

	// To compare edges, only compare their weights,
	// and not the source/destination vertices
	inline bool operator< (const Edge<T>& e) const
	{
		return this->weight < e.weight;
	}

	inline bool operator> (const Edge<T>& e) const
	{
		return this->weight > e.weight;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& G)
{
	for (auto i = 1; i < G.vertices(); i++)
	{
		os << i <<":\t";

		auto edges = G.edges(i);
		for (auto& e : edges)
			os << "{" << e.dest << ": " << e.weight << "}, ";
		
		os << std::endl;
	}
	
	return os;
}

template<typename T>
class Graph
{
public:
	// Initialize the graph with N vertices
	Graph(size_t N): V(N)
	{}

	// Return number of vertices in the graph
	auto vertices() const
	{
		return V;
	}

	// Return all edges in the graph
	auto& edges() const
	{
		return edge_list;
	}

	void add_edge(Edge<T>&& e)
	{
		// Check if the source and destination vertices are within range
		if (e.src >= 1 && e.src <= V && 
			e.dest >= 1 && e.dest <= V)
			edge_list.emplace_back(e);
		else
			std::cerr << "Vertex out of bounds" << std::endl;
	}

	// Returns all outgoing edges from vertex v
	auto edges(size_t v) const
	{
		std::vector<Edge<T>> edges_from_v;
		for(auto& e:edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		return edges_from_v;
	}

	// Overloads the << operator so a graph be written directly to a stream
	// Can be used as std::cout << obj << std::endl;
	// template <typename T>
	friend std::ostream& operator<< <>(std::ostream& os, const Graph<T>& G);

private: 
	size_t V;		// Stores number of vertices in graph
	std::vector<Edge<T>> edge_list;
};




// Since a tree is also a graph, we can reuse the Graph class
// However, the result graph should have no cycles
template<typename T>
Graph<T> minimum_spanning_tree(const Graph<T>& G)
{
	// Create a min-heap for the edges
	std::priority_queue<Edge<T>, 
		std::vector<Edge<T>>, 
		std::greater<Edge<T>>> edge_min_heap;

	// Add all edges in the min-heap
	for (auto& e : G.edges()) 
		edge_min_heap.push(e);

	// First step: add all elements to their own sets
	auto N = G.vertices();
	SimpleDisjointSet<size_t> dset(N);
	for (auto i = 0; i < N; i++)
		dset.add_set(i);
	
	// Second step: start merging sets
	Graph<T> MST(N);
	while (!edge_min_heap.empty())
	{
		// Extract the edge with minimum weight from the heap
		auto e = edge_min_heap.top();
		edge_min_heap.pop();

		// Merge the two trees and add edge to the MST only if
		// the two vertices of the edge belong to different trees
		// in the MST
		if (dset.find(e.src) != dset.find(e.dest))
		{
			MST.add_edge(Edge <T>{e.src, e.dest, e.weight});
			dset.union_sets(e.src, e.dest);
		}
	}

	return MST;
}

int main()
{
	using T = unsigned;

	Graph<T> G(9);

	std::map<unsigned, std::vector<std::pair<size_t, T>>> edges;
	edges[1] = { {2, 2}, {5, 3} };
	edges[2] = { {1, 2}, {5, 5}, {4, 1} };
	edges[3] = { {4, 2}, {7, 3} };
	edges[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edges[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
	edges[6] = { {4, 4}, {7, 4}, {8, 1} };
	edges[7] = { {3, 3}, {6, 4} };
	edges[8] = { {4, 5}, {5, 3}, {6, 1} };
	
	for (auto& i : edges)
		for(auto& j: i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });
	
	std::cout << "Original Graph" << std::endl;
	std::cout << G;

	auto MST = minimum_spanning_tree(G);
	std::cout << std::endl << "Minimum Spanning Tree" << std::endl;
	std::cout << MST;

	return 0;
}
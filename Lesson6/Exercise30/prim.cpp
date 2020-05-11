#include <set>
#include <map>
#include <queue>
#include <limits>
#include <string>
#include <vector>
#include <iostream>

template<typename T> class Graph;

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
		os << i << ":\t";

		auto edges = G.outgoing_edges(i);
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
	Graph(size_t N) : V(N)
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
	auto outgoing_edges(size_t v) const
	{
		std::vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		return edges_from_v;
	}

	// Overloads the << operator so a graph be written directly to a stream
	// Can be used as std::cout << obj << std::endl;
	friend std::ostream& operator<< <>(std::ostream& os, const Graph<T>& G);

private:
	size_t V;		// Stores number of vertices in graph
	std::vector<Edge<T>> edge_list;
};

template <typename T>
auto create_reference_graph()
{
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
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });

	return G;
}

template<typename T>
struct Label
{
	size_t vertex_ID;
	T distance_from_frontier;

	Label(size_t _id, T _distance) :
		vertex_ID(_id),
		distance_from_frontier(_distance)
	{}

	// To compare labels, only compare their distances from source
	inline bool operator< (const Label<T>& l) const
	{
		return this->distance_from_frontier < l.distance_from_frontier;
	}

	inline bool operator> (const Label<T>& l) const
	{
		return this->distance_from_frontier > l.distance_from_frontier;
	}

	inline bool operator() (const Label<T>& l) const
	{
		return this > l;
	}
};

template <typename T>
auto prim_MST(const Graph<T>& G, size_t src)
{
	std::priority_queue<Label<T>, std::vector<Label<T>>, std::greater<Label<T>>> heap;
	std::set<int> visited;

	std::vector<T> distance(G.vertices(), std::numeric_limits<T>::max());
	std::vector<size_t> MST;

	heap.emplace(src, 0);

	// Search for the destination vertex in the graph
	while (!heap.empty())
	{
		auto current_vertex = heap.top();
		heap.pop();

		// If the current vertex hasn't been visited in the past
		if (visited.find(current_vertex.vertex_ID) == visited.end())
		{
			MST.push_back(current_vertex.vertex_ID);

			// For each outgoing edge from the current vertex, 
			// create a label for the destination vertex and add it to the heap
			for (auto e : G.outgoing_edges(current_vertex.vertex_ID))
			{
				auto neighbor_vertex_ID = e.dest;
				auto new_distance_to_frontier = e.weight;

				// Check if the new path to the vertex is shorter
				// than the previously known best path. If yes, update the distance 
				if (new_distance_to_frontier < distance[neighbor_vertex_ID])
				{
					heap.emplace(neighbor_vertex_ID, new_distance_to_frontier);
					distance[e.dest] = new_distance_to_frontier;
				}
			}

			visited.insert(current_vertex.vertex_ID);
		}
	}

	return MST;
}

template<typename T>
void test_prim_MST()
{
	auto G = create_reference_graph<T>();
	std::cout << G << std::endl;

	auto MST = prim_MST<T>(G, 1);

	std::cout << "Minimum Spanning Tree:" << std::endl;
	for (auto v : MST)
		std::cout << v << std::endl;
	std::cout << std::endl;
}

int main()
{
	using T = unsigned;
	test_prim_MST<T>();

	return 0;
}
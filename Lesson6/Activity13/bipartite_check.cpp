#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>

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
auto create_bipartite_reference_graph()
{
	Graph<T> G(10);

	std::map<unsigned, std::vector<std::pair<size_t, T>>> edges;
	edges[1] = { {2, 0} };
	edges[2] = { {1, 0}, {3, 0} , {8, 0} };
	edges[3] = { {2, 0}, {4, 0} };
	edges[4] = { {3, 0}, {6, 0} };
	edges[5] = { {7, 0}, {9, 0} };
	edges[6] = { {1, 0}, {4, 0} };
	edges[7] = { {5, 0} };
	edges[8] = { {2,0}, {9, 0} };
	edges[9] = { {5, 0} };


	for (auto& i : edges)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });

	return G;
}

template <typename T>
auto bipartite_check(const Graph<T>& G)
{
	std::stack<size_t> stack;
	std::set<size_t> visited;
	stack.push(1); // Assume that BFS always starts from vertex ID 1

	enum class colors {NONE, RED, BLUE};
	colors current_color{colors::BLUE}; // This variable tracks the color to be assigned to the
										// next vertex that is visited.
	std::vector<colors> vertex_colors(G.vertices(), colors::NONE);

	while (!stack.empty())
	{
		auto current_vertex = stack.top();
		stack.pop();

		// If the current vertex hasn't been visited in the past
		if (visited.find(current_vertex) == visited.end())
		{
			visited.insert(current_vertex);
			vertex_colors[current_vertex] = current_color;
			if (current_color == colors::RED)
			{
				std::cout << "Coloring vertex " << current_vertex << " RED" << std::endl;
				current_color = colors::BLUE;
			}
			else
			{
				std::cout << "Coloring vertex " << current_vertex << " BLUE" << std::endl;
				current_color = colors::RED;
			}

			// Add unvisited adjacent vertices to the stack.
			for (auto e : G.outgoing_edges(current_vertex))
				if (visited.find(e.dest) == visited.end())
					stack.push(e.dest);
		}
		// If the found vertex is already colored and 
		// has a color same as its parent's color, the graph is not bipartite
		else if (visited.find(current_vertex) != visited.end() && 
			((vertex_colors[current_vertex] == colors::BLUE && 
				current_color == colors::RED) ||
			(vertex_colors[current_vertex] == colors::RED && 
				current_color == colors::BLUE)))			
			return false;
	}

	// If all vertices have been colored, the graph is bipartite
	return true;
}

template <typename T>
void test_bipartite()
{
	// Create an instance of and print the graph
	auto BG = create_bipartite_reference_graph<T>();
	std::cout << BG << std::endl;

	if (bipartite_check<T>(BG))
		std::cout << "The graph is bipartite" << std::endl;
	else
		std::cout << "The graph is not bipartite" << std::endl;
}

int main()
{
	using T = unsigned;
	test_bipartite<T>();

	return 0;
}


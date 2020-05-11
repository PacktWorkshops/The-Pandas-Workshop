#include <unordered_map>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T> class Graph;

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
	// template <typename T>
	friend std::ostream& operator<< <>(std::ostream& os, const Graph<T>& G);

private:
	size_t V;		// Stores number of vertices in graph
	std::vector<Edge<T>> edge_list;
};



// Initialize the colors that will be used to color the vertices
std::unordered_map<size_t, std::string> color_map = {
	{1, "Red"},
	{2, "Blue"},
	{3, "Green"},
	{4, "Yellow"},
	{5, "Black"},
	{6, "White"}
};

template<typename T>
auto welsh_powell_coloring(const Graph<T>& G)
{
	auto size = G.vertices();
	std::vector<std::pair<size_t, size_t>> degrees;

	// Collect the degrees of vertices as <vertex_ID, degree> pairs
	for (auto i = 1; i < size; i++)
		degrees.push_back(std::make_pair(i, G.outgoing_edges(i).size()));

	// Sort the vertices in decreasing order of degree
	std::sort(degrees.begin(),
		degrees.end(),
		[](const auto& a, const auto& b)
		{ return a.second > b.second; });

	std::cout << "The vertices will be colored in the following order: " << std::endl;
	std::cout << "Vertex ID \t Degree" << std::endl;
	for (auto const i : degrees)
		std::cout << i.first << "\t\t" << i.second << std::endl;

	std::vector<size_t> assigned_colors(size);
	auto color_to_be_assigned = 1;

	while (true)
	{
		for (auto const i : degrees)
		{
			if (assigned_colors[i.first] != 0)
				continue;

			auto outgoing_edges = G.outgoing_edges(i.first);
			std::set<size_t> neighbour_colors;

			// We assume that the graph is bidirectional
			for (auto e : outgoing_edges)
			{
				auto dest_color = assigned_colors[e.dest];
				neighbour_colors.insert(dest_color);
			}

			if (neighbour_colors.find(color_to_be_assigned) == neighbour_colors.end())
				assigned_colors[i.first] = color_to_be_assigned;
		}

		color_to_be_assigned++;

		// If there are no uncolored vertices left, exit
		if (std::find(assigned_colors.begin() + 1, assigned_colors.end(), 0) ==
			assigned_colors.end())
			break;
	}

	return assigned_colors;
}

void print_colors(std::vector<size_t>& colors)
{
	for (auto i = 1; i < colors.size(); i++)
	{
		std::cout << i << ": " << color_map[colors[i]] << std::endl;
	}
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
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });
	std::cout << "Original Graph" << std::endl;
	std::cout << G;

	auto colors = welsh_powell_coloring<T>(G);
	std::cout << "Vertex Colors: " << std::endl;
	print_colors(colors);
	return 0;
}
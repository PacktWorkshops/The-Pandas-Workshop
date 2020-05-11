#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric>

template<typename T>
auto compute_waiting_times(std::vector<T>& service_times)
{
	std::vector<T> W(service_times.size());
	W[0] = 0;
	
	for (auto i = 1; i < service_times.size(); i++)
		W[i] = W[i - 1] + service_times[i - 1];

	return W;
}

template<typename T>
void print_vector(std::vector<T>& V)
{
	for (auto& i : V)
		std::cout << i << " ";
	std::cout << std::endl;
}

template<typename T>
void compute_and_print_waiting_times(std::vector<T>& service_times)
{
	auto waiting_times = compute_waiting_times<int>(service_times);
	
	std::cout << "Service times: " << std::endl;
	print_vector<T>(service_times);

	std::cout << "Waiting times: " << std::endl;
	print_vector<T>(waiting_times);

	std::cout << "Average waiting time = "
		<< std::accumulate(waiting_times.begin(), waiting_times.end(), 0.0) /
		waiting_times.size();

	std::cout<< std::endl;
}

void shortest_job_first(size_t size)
{
	std::vector<int> service_times;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements as service times
	service_times.reserve(size);
	for (auto i = 0; i < size; i++)
		service_times.push_back(uniform_dist(rand));

	compute_and_print_waiting_times<int>(service_times);

	// Reorder the elements in the queue
	std::sort(service_times.begin(), service_times.end());

	compute_and_print_waiting_times<int>(service_times);
}

int main(int argc, char* argv[])
{
	shortest_job_first(10);
}
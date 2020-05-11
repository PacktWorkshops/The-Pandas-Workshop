#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>

void transform_test(size_t size)
{
	std::vector<int> S, Tr;
	std::random_device rd;
	std::mt19937 rand(rd());
	// distribution in range [1, size]
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::cout << "Map test== " << std::endl<< "Original array, S: ";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;

	// Transform
	std::transform(S.begin(), S.end(), std::back_inserter(Tr), [](int x) {return std::pow(x, 2.0); });

	std::cout << "Transformed array, Tr: ";
	for (auto i : Tr)
		std::cout << i << " ";
	std::cout << std::endl;

	// For_each
	std::for_each(S.begin(), S.end(), [](int &x) {x = std::pow(x, 2.0); });

	std::cout << "After applying for_each to S: ";
	for (auto i : S)
			std::cout << i << " ";
	std::cout << std::endl;
}

void reduce_test(size_t size)
{
	std::vector<int> S;
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::cout << std::endl << "Reduce test== " << std::endl << "Original array, S: ";
	for (auto i : S)
		std::cout << i << " ";
	std::cout << std::endl;

	// Accumulate
	std::cout<<"std::accumulate() = " << std::accumulate(S.begin(), S.end(), 0, 
														[](int acc, int x) {
															return acc+x; 
														});
	std::cout << std::endl;
}


int main() 
{
	transform_test(10);
	reduce_test(10);
	return 0;
}
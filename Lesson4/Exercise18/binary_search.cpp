#include "Chapter4.h"

bool linear_search(int N, std::vector<int>& S)
{
	for (auto i : S)
	{
		if (i == N)
			return true;					// Element found!
	}

	return false;
}

bool binary_search(int N, std::vector<int>& S)
{
	auto first = S.begin();
	auto last = S.end();

	while (true)
	{
		// Get the middle element of the current range
		auto range_length = std::distance(first, last);
		auto mid_element_index = std::floor(range_length / 2);
		auto mid_element = *(first + mid_element_index);

		// Compare the middle element of current range with N
		if (mid_element == N)
			return true;
		else if (mid_element > N)
			std::advance(last, -mid_element_index);
		if (mid_element < N)
			std::advance(first, mid_element_index);

		// If only one element left in the current range
		if (range_length == 1)
			return false;
	}
}

void run_small_search_test()
{
	auto N = 2;
	std::vector<int> S{ 1, 3, 2, 4, 5, 7, 9, 8, 6 };

	std::sort(S.begin(), S.end());

	if (linear_search(N, S))
		std::cout << "Element found in set by linear search!" << std::endl;
	else
		std::cout << "Element not found." << std::endl;

	if (binary_search(N, S))
		std::cout << "Element found in set by binary search!" << std::endl;
	else
		std::cout << "Element not found." << std::endl;
}

void run_large_search_test(int size, int N)
{
	std::vector<int> S;
	std::random_device rd;
	std::mt19937 rand(rd());
	// distribution in range [1, size]
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	// Insert random elements
	for (auto i = 0; i < size; i++)
		S.push_back(uniform_dist(rand));

	std::sort(S.begin(), S.end());

	// To measure the time taken, start the clock
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	bool search_result = binary_search(111, S);

	// Stop the clock
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time taken by binary search = " <<
		std::chrono::duration_cast<std::chrono::microseconds>
		(end - begin).count() << std::endl;

	if (search_result)
		std::cout << "Element found in set!" << std::endl;
	else
		std::cout << "Element not found." << std::endl;
}

int main()
{
	run_small_search_test();

	run_large_search_test(100000, 36543);
	run_large_search_test(1000000, 36543);
	run_large_search_test(10000000, 36543);

	return 0;
}

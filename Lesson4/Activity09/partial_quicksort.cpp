#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

template <typename T>
auto partition(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator end)
{
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true)
	{
		// Starting from the first element of vector, 
		// find an element that is greater than pivot.
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;

		// Starting from the end of vector moving to the beginning, 
		// find an element that is lesser than the pivot.
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		// If left and right iterators meet, there are no elements left to swap. 
		// Else, swap the elements pointed to by the left and right iterators
		if (left_iter == right_iter)
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}
	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter;
}

template <typename T>
void partial_quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last,
	size_t k)
{
	// If there are more than 1 elements in the vector
	if (std::distance(begin, last) >= 1)
	{
		// Apply the partition operation
		auto partition_iter = partition<T>(begin, last);

		// Recursively sort the vectors created by the partition operation
		partial_quick_sort<T>(begin, partition_iter-1, k);
		
		// Sort the right subvector only if the final position of pivot < k 
		if(std::distance(begin, partition_iter) < k)
			partial_quick_sort<T>(partition_iter, last, k);
	}
}

template <typename T>
void quick_sort(typename std::vector<T>::iterator begin,
	typename std::vector<T>::iterator last)
{
	// If there are more than 1 elements in the vector
	if (std::distance(begin, last) >= 1)
	{
		// Apply the partition operation
		auto partition_iter = partition<T>(begin, last);

		// Recursively sort the vectors created by the partition operation
		quick_sort<T>(begin, partition_iter-1);
		quick_sort<T>(partition_iter, last);
	}
}

template <typename T>
void print_vector(std::vector<T> arr)
{
	for (auto i : arr)
		std::cout << i << " ";

	std::cout << std::endl;
}

// Generates random vector of a given size with integers [1, size]
template <typename T>
auto generate_random_vector(T size)
{
	std::vector<T> V;
	V.reserve(size);

	std::random_device rd;
	std::mt19937 rand(rd());

	// the IDs of Student should be in range [1, max]
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	for (T i = 0; i < size; i++)
		V.push_back(uniform_dist(rand));

	return std::move(V);
}

// Sort the first K elements of a random vector of a given 'size'
template <typename T>
void test_partial_quicksort(size_t size, size_t k)
{
		// Create two copies of a random vector to use for the two algorithms
		auto random_vec = generate_random_vector<T>(size);
		auto random_vec_copy(random_vec);

		std::cout << "Original vector: "<<std::endl;
		print_vector<T>(random_vec); 
			
		// Measure the time taken by partial quick sort
		std::chrono::steady_clock::time_point begin_qsort = std::chrono::steady_clock::now();
		partial_quick_sort<T>(random_vec.begin(), random_vec.end()-1, k);
		std::chrono::steady_clock::time_point end_qsort = std::chrono::steady_clock::now();
	
		std::cout << std::endl << "Time taken by partial quick sort = " 
			<<	std::chrono::duration_cast<std::chrono::microseconds>
			(end_qsort - begin_qsort).count() 
			<< " microseconds" << std::endl;
	
		std::cout << "Partially sorted vector (only first "<< k <<" elements):";
		print_vector<T>(random_vec);

		// Measure the time taken by partial quick sort
		begin_qsort = std::chrono::steady_clock::now();
		quick_sort<T>(random_vec_copy.begin(), random_vec_copy.end()-1);
		end_qsort = std::chrono::steady_clock::now();

		std::cout << std::endl <<"Time taken by full quick sort = " 
			<< std::chrono::duration_cast<std::chrono::microseconds>
			(end_qsort - begin_qsort).count() 
			<< " microseconds" << std::endl;
	
		std::cout << "Fully sorted vector: ";
		print_vector<T>(random_vec_copy);
}

int main()
{
	test_partial_quicksort<unsigned>(100, 10);
	return 0;
}

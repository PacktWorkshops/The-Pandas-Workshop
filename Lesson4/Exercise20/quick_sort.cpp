#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>

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
	if (pivot_val > * right_iter)
		std::iter_swap(begin, right_iter);

	return right_iter;
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
		quick_sort<T>(begin, partition_iter - 1);
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

void run_quick_sort_test()
{
	std::vector<int>    S1{ 45, 1, 3, 1, 2, 3, 45, 5, 1, 2, 44, 5, 7 };
	std::vector<float>  S2{ 45.6, 1.0, 3.8 , 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
	std::vector<double> S3{ 45.6, 1.0, 3.8 , 1.01, 2.2, 3.9, 45.3, 5.5, 1.0, 2.0, 44.0, 5.0, 7.0 };
	std::vector<char>   C{ 'b','z','a','e','f','t','q','u','y' };

	std::cout << "Unsorted arrays:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);
	std::cout << std::endl;

	// Called with arr.end() - 1 because the function expects an iterator to the last element of the vector
	quick_sort<int>(S1.begin(), S1.end() - 1);
	quick_sort<float>(S2.begin(), S2.end() - 1);
	quick_sort<double>(S3.begin(), S3.end() - 1);
	quick_sort<char>(C.begin(), C.end() - 1);


	std::cout << "Arrays sorted using quick sort:" << std::endl;
	print_vector<int>(S1);
	print_vector<float>(S2);
	print_vector<double>(S3);
	print_vector<char>(C);
	std::cout << std::endl;
}

int main()
{
	run_quick_sort_test();
	return 0;
}
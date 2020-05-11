// Copyright (c) 2009-2016 Craig Henderson
// https://github.com/cdmh/mapreduce
// The prime number code is based on work from Christian Henning [chhenning@gmail.com]

// Adapted by Payas Rajan <payasrajan@live.com>

#include <iostream>
#include "mapreduce.hpp"

namespace prime_calculator {

	// Checks if a given number is prime using prime factorization
	bool const is_prime(long const number)
	{
		if (number > 2)
		{
			if (number % 2 == 0)
				return false;

			long const n = std::abs(number);
			long const sqrt_number = static_cast<long>(std::sqrt(static_cast<double>(n)));

			for (long i = 3; i <= sqrt_number; i += 2)
			{
				if (n % i == 0)
					return false;
			}
		}
		else if (number == 0 || number == 1)
			return false;

		return true;
	}

	// Defines a source of numbers, will be used to generate range of numbers between
// first and last with a given step size
	template<typename MapTask>
	class number_source : mapreduce::detail::noncopyable
	{
	public:
		number_source(long first, long last, long step)
			: sequence_(0), first_(first), last_(last), step_(step)
		{
		}

		bool const setup_key(typename MapTask::key_type& key)
		{
			key = sequence_++;
			return (key * step_ <= last_);
		}

		bool const get_data(typename MapTask::key_type const& key,
			typename MapTask::value_type& value)
		{
			typename MapTask::value_type val;

			val.first = first_ + (key * step_);
			val.second = std::min(val.first + step_ - 1, last_);

			std::swap(val, value);
			return true;
		}

	private:
		long       sequence_;
		long const step_;
		long const last_;
		long const first_;
	};

	// Defines the Map stage
	struct map_task : public mapreduce::map_task<long, std::pair<long, long> >
	{
		template<typename Runtime>
		void operator()(Runtime& runtime, key_type const&/*key*/, value_type const& value) const
		{
			for (key_type loop = value.first; loop <= value.second; ++loop)
				runtime.emit_intermediate(is_prime(loop), loop);
		}
	};

	// Defines the Reduce stage
	struct reduce_task : public mapreduce::reduce_task<bool, long>
	{
		template<typename Runtime, typename It>
		void operator()(Runtime& runtime, key_type const& key, It it, It ite) const
		{
			if (key)
				std::for_each(it, ite, std::bind(&Runtime::emit, &runtime, true, std::placeholders::_1));
		}
	};

	typedef
		mapreduce::job<
		prime_calculator::map_task,
		prime_calculator::reduce_task,
		mapreduce::null_combiner,
		prime_calculator::number_source<prime_calculator::map_task>> job;
} // namespace prime_calculator

int main(int argc, char* argv[])
{
	mapreduce::specification spec;

	int prime_limit = 1000;

	// Set number of threads to be used
	spec.map_tasks = std::max(1U, std::thread::hardware_concurrency());
	spec.reduce_tasks = std::max(1U, std::thread::hardware_concurrency());

	// Set the source of numbers in given range
	prime_calculator::job::datasource_type datasource(0, prime_limit, prime_limit / spec.reduce_tasks);

	std::cout << "\nCalculating Prime Numbers in the range 0 .. " << prime_limit << " ..." << std::endl;
	std::cout << std::endl << "Using "
		<< std::max(1U, std::thread::hardware_concurrency()) << " CPU cores";

	// Run mapreduce
	prime_calculator::job job(datasource, spec);
	mapreduce::results result;

	job.run<mapreduce::schedule_policy::cpu_parallel<prime_calculator::job> >(result);
	
	std::cout << "\nMapReduce finished in " << result.job_runtime.count() << " seconds with " << std::distance(job.begin_results(), job.end_results()) << " results" << std::endl;

	// Print results
	for (auto it = job.begin_results(); it != job.end_results(); ++it)
		std::cout << it->second << " ";

	return 0;
}

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
#include <list>
#include <algorithm>
#include <iostream>
#include <random>

// Every task is represented as a pair <start_time, end_time>
struct Task
{
	unsigned ID;
	unsigned start_time;
	unsigned end_time;
};

auto initialize_tasks(size_t num_tasks)
{
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, num_tasks);

	// Create and initialize a set of tasks
	std::list<Task> tasks;

	for (unsigned i = 1; i <= num_tasks; i++)
	{
		auto start_time = uniform_dist(rand);
		auto duration = uniform_dist(rand);

		tasks.push_back({ i, start_time, start_time + duration });
	}

	return tasks;
}

auto schedule(std::list<Task> tasks)
{
	// Sort the list of tasks by their end times
	tasks.sort([](const auto& lhs, const auto& rhs)
		{ return lhs.end_time < rhs.end_time; });

	// Remove the tasks that interfere with one another
	for (auto curr_task = tasks.begin(); curr_task != tasks.end(); curr_task++)
	{
		// Point to the next task
		auto next_task = std::next(curr_task, 1);

		// While subsequent tasks interfere with the current task in iter
		while (next_task != tasks.end() &&
			next_task->start_time < curr_task->end_time)
		{
			next_task = tasks.erase(next_task);
		}
	}

	return tasks;
}

void print(std::list<Task>& tasks)
{
	std::cout << "Task ID \t Starting Time \t End time" << std::endl;

	for (auto t : tasks)
		std::cout << t.ID << "\t\t" << t.start_time << "\t\t" << t.end_time << std::endl;
}

void test_interval_scheduling(unsigned num_tasks)
{
	auto tasks = initialize_tasks(num_tasks);

	std::cout << "Original list of tasks: " << std::endl;
	print(tasks);

	std::cout << "Scheduled tasks: " << std::endl;
	auto scheduled_tasks = schedule(tasks);
	print(scheduled_tasks);
}

int main()
{
	test_interval_scheduling(20);
	return 0;
}
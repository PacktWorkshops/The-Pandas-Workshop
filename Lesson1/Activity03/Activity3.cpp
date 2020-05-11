#include <iostream>
#include <queue>

class Job
{
    int id;
    std::string user;
    int time;
    static int count;

public:
    Job(const std::string &u, int t) : user(u), time(t), id(++count)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Job &j)
    {
        os << "id: " << j.id << ", user: " << j.user << ", time: " << j.time << " seconds" << std::endl;
        return os;
    }
};
int Job::count = 0;

template <size_t N>
class Printer
{
    std::queue<Job> jobs;

public:
    bool addNewJob(const Job &job)
    {
        if (jobs.size() == N)
            return false;
        std::cout << "Added job in the queue: " << job;
        jobs.push(job);
        return true;
    }

    void startPrinting()
    {
        while (not jobs.empty())
        {
            std::cout << "Processing job: " << jobs.front();
            jobs.pop();
        }
    }
};

int main()
{
    Printer<5> printer;

    Job j1("John", 10);
    Job j2("Jerry", 4);
    Job j3("Jimmy", 5);
    Job j4("George", 7);
    Job j5("Bill", 8);
    Job j6("Kenny", 10);

    printer.addNewJob(j1);
    printer.addNewJob(j2);
    printer.addNewJob(j3);
    printer.addNewJob(j4);
    printer.addNewJob(j5);

    if (not printer.addNewJob(j6)) // Can't add as queue is full.
    {
        std::cout << "Couldn't add 6th job" << std::endl;
    }

    printer.startPrinting();

    printer.addNewJob(j6); // Can add now, as queue got emptied
    printer.startPrinting();
}

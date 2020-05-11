#include <iostream>
#include <queue>
#include <vector>

struct median
{
    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    void insert(int data)
    {
        if (maxHeap.size() == 0)
        {
            maxHeap.push(data);
            return;
        }

        if (maxHeap.size() == minHeap.size())
        {
            if (data <= get())
                maxHeap.push(data);
            else
                minHeap.push(data);
            return;
        }
        if (maxHeap.size() < minHeap.size())
        {
            if (data > get())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(data);
            }
            else
                maxHeap.push(data);
            return;
        }
        if (data < get())
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
            maxHeap.push(data);
        }
        else
            minHeap.push(data);
    }

    double get()
    {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;
        if (maxHeap.size() < minHeap.size())
            return minHeap.top();
        return maxHeap.top();
    }
};

int main()
{
    median med;
    med.insert(1);
    std::cout << "Median after insert 1: " << med.get() << std::endl;

    med.insert(5);
    std::cout << "Median after insert 5: " << med.get() << std::endl;

    med.insert(2);
    std::cout << "Median after insert 2: " << med.get() << std::endl;

    med.insert(10);
    std::cout << "Median after insert 10: " << med.get() << std::endl;

    med.insert(40);
    std::cout << "Median after insert 40: " << med.get() << std::endl;

    return 0;
}

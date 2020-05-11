#include <iostream>
#include <algorithm>
#include <vector>

struct node
{
    int data;
    int listPosition;
    int dataPosition;
};

std::vector<int> merge(const std::vector<std::vector<int>> &input)
{
    auto comparator = [](const node &left, const node &right) {
        if (left.data == right.data)
            return left.listPosition > right.listPosition;
        return left.data > right.data;
    };

    std::vector<node> heap;
    for (int i = 0; i < input.size(); i++)
    {
        heap.push_back({input[i][0], i, 0});
        std::push_heap(heap.begin(), heap.end(), comparator);
    }

    std::vector<int> result;
    while (!heap.empty())
    {
        std::pop_heap(heap.begin(), heap.end(), comparator);
        auto min = heap.back();
        heap.pop_back();

        result.push_back(min.data);
        int nextIndex = min.dataPosition + 1;
        if (nextIndex < input[min.listPosition].size())
        {
            heap.push_back({input[min.listPosition][nextIndex], min.listPosition, nextIndex});
            std::push_heap(heap.begin(), heap.end(), comparator);
        }
    }

    return result;
}

int main()
{
    std::vector<int> v1 = {1, 3, 8, 15, 105};
    std::vector<int> v2 = {2, 3, 10, 11, 16, 20, 25};
    std::vector<int> v3 = {-2, 100, 1000};
    std::vector<int> v4 = {-1, 0, 14, 18};
    auto result = merge({v1, v2, v3, v4});
    for (auto i : result)
        std::cout << i << ' ';
    return 0;
}

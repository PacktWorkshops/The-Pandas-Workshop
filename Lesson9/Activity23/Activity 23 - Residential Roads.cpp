#include <iostream>
#include <vector>
using namespace std;

const int UNKNOWN = 1e9;
const char EMPTY_SPACE = '.';
const string roads = "-|/\\";

struct Point
{
    int x;
    int y;
    
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    
    bool operator !=(const Point& other) const { return x != other.x || y != other.y; }
};

int N;
int H, W;
int limit;

vector<Point> houses;
vector<vector<int>> terrain;
vector<vector<int>> cost;
vector<string> grid;

int GetDirection(int x_dir, int y_dir)
{
    if (y_dir == 0) return 0;
    if (x_dir == 0) return 1;
    if (x_dir == -1)
    {
        return (y_dir == 1) ? 2 : 3;
    }
    return (y_dir == 1) ? 3 : 2;
}

void DrawPath(int start, int end)
{
    Point a = houses[start];
    Point b = houses[end];
    
    int x_dir = 0;
    int y_dir = 0;
    
    if (a.x != b.x)
    {
        x_dir = (a.x < b.x) ? 1 : -1;
    }
    if (a.y != b.y)
    {
        y_dir = (a.y < b.y) ? 1 : -1;
    }
    int direction = GetDirection(x_dir, y_dir);
    
    char mark = roads[direction];
    
    do
    {
        a.x += x_dir;
        a.y += y_dir;
        
        if (grid[a.y][a.x] == EMPTY_SPACE)
        {
            grid[a.y][a.x] = mark;
        }
        else if(!isalpha(grid[a.y][a.x]))
        {
            // If two roads of differing orientations intersect, replace symbol with '+'
            
            grid[a.y][a.x] = (mark != grid[a.y][a.x]) ? '+' : mark;
        }
    }
    while (a != b);
}

vector<int> GetPath(int start, int end, vector<vector<int>>& next)
{
    vector<int> path = { start };
    
    do
    {
        start = next[start][end];
        
        path.push_back(start);
    }
    while (next[start][end] != end);
    
    return path;
}

void GetShortestPaths()
{
    vector<vector<int>> dist(N, vector<int>(N, UNKNOWN));
    vector<vector<int>> next(N, vector<int>(N, UNKNOWN));
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dist[i][j] = cost[i][j];
            
            if (dist[i][j] != UNKNOWN)
            {
                next[i][j] = j;
            }
        }
        dist[i][i] = 0;
        next[i][i] = i;
    }
    
    for (int mid = 0; mid < N; mid++)
    {
        for (int start = 0; start < N; start++)
        {
            for (int end = 0; end < N; end++)
            {
                if (dist[start][end] > dist[start][mid] + dist[mid][end])
                {
                    dist[start][end] = dist[start][mid] + dist[mid][end];
                    next[start][end] = next[start][mid];
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        vector<int> path = GetPath(i, N - 1, next);
        
        int curr = i;
        
        for (auto neighbor : path)
        {
            DrawPath(curr, neighbor);
            curr = neighbor;
        }
    }
}

bool DirectLine(Point a, Point b)
{
    if (a.x == b.x) return true;
    if (a.y == b.y) return true;
    if (abs(a.x - b.x) == abs(a.y - b.y)) return true;
    
    return false;
}

int GetCost(int start, int end)
{
    Point a = houses[start];
    Point b = houses[end];
    
    // The values by which the coordinates change on each iteration
    int x_dir = 0;
    int y_dir = 0;
    
    if (a.x != b.x)
    {
        x_dir = (a.x < b.x) ? 1 : -1;
    }
    if (a.y != b.y)
    {
        y_dir = (a.y < b.y) ? 1 : -1;
    }
    int cost = 0;
    
    do
    {
        a.x += x_dir;
        a.y += y_dir;
        
        cost += terrain[a.y][a.x];
    }
    while (grid[a.y][a.x] == EMPTY_SPACE);
    
    return (a != b) ? UNKNOWN : cost;
}

void BuildGraph()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i == j) continue;
            
            // Check to see if there is a direct line between each pair of houses
            if (DirectLine(houses[i], houses[j]))
            {
                // If so, get the cost of building a road between them
                cost[i][j] = cost[j][i] = GetCost(i, j);
            }
        }
    }
}

void Input()
{
    cin >> H >> W;
    cin >> N;
    
    grid.resize(H);
    houses.resize(N);
    terrain.resize(H, vector<int>(W, UNKNOWN));
    cost.resize(N, vector<int>(N, UNKNOWN));
    
    // Get property map
    for (int i = 0; i < H; i++)
    {
        cin >> grid[i];
    }
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> terrain[i][j];
        }
    }
    
    // Get house coordinates
    for (int i = 0; i < N; i++)
    {
        cin >> houses[i].x >> houses[i].y;
        
        // Set house labels
        grid[houses[i].y][houses[i].x] = char(i + 'A');
    }
}

int main()
{
    Input();
    BuildGraph();
    GetShortestPaths();
    
    for (auto it : grid)
    {
        cout << it << "\n";
    }
    
    return 0;
}

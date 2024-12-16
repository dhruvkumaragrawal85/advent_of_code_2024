#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void part1()
{
    ifstream infile("input.in");
    vector<string> grid;
    string line;
    while (getline(infile, line))
    {
        grid.push_back(line);
    }
    int n = grid.size();
    int m = grid[0].size();
    int sx = 0, sy = 0, fx = 0, fy = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'S')
                sx = i, sy = j;
            if (grid[i][j] == 'E')
                fx = i, fy = j;
        }
    }
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, 1e9)));
    set<pair<int, vector<int>>> pq;
    dist[sx][sy][0] = 0;
    pq.insert({0, {sx, sy, 0}});
    while (pq.size())
    {
        auto sv = *pq.begin();
        pq.erase(pq.begin());
        int x = sv.second[0];
        int y = sv.second[1];
        int curr_dir = sv.second[2];
        int curr_dist = sv.first;
        // to turn
        int right_dir = ((curr_dir + 1) % 4 + 4) % 4;
        int left_dir = ((curr_dir - 1) % 4 + 4) % 4;
        if (dist[x][y][right_dir] > dist[x][y][curr_dir] + 1000)
        {
            dist[x][y][right_dir] = dist[x][y][curr_dir] + 1000;
            pq.insert({dist[x][y][right_dir], {x, y, right_dir}});
        }
        if (dist[x][y][left_dir] > dist[x][y][curr_dir] + 1000)
        {
            dist[x][y][left_dir] = dist[x][y][curr_dir] + 1000;
            pq.insert({dist[x][y][left_dir], {x, y, left_dir}});
        }
        // move in dir
        int nx = x + dir[curr_dir].first, ny = y + dir[curr_dir].second;
        if (grid[nx][ny] != '#' && dist[nx][ny][curr_dir] > dist[x][y][curr_dir] + 1)
        {
            dist[nx][ny][curr_dir] = dist[x][y][curr_dir] + 1;
            pq.insert({dist[nx][ny][curr_dir], {nx, ny, curr_dir}});
        }
    }
    cout << "Part 1 solution is: " << min({dist[fx][fy][0], dist[fx][fy][1], dist[fx][fy][2], dist[fx][fy][3]}) << endl;
}
void part2()
{
    ifstream infile("input.in");
    vector<string> grid;
    string line;
    while (getline(infile, line))
    {
        grid.push_back(line);
    }
    int n = grid.size();
    int m = grid[0].size();
    int sx = 0, sy = 0, fx = 0, fy = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'S')
                sx = i, sy = j;
            if (grid[i][j] == 'E')
                fx = i, fy = j;
        }
    }
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, 1e9)));
    map<vector<int>, vector<vector<int>>> prev;
    set<pair<int, vector<int>>> pq;
    dist[sx][sy][0] = 0;
    pq.insert({0, {sx, sy, 0}});
    while (pq.size())
    {
        auto sv = *pq.begin();
        pq.erase(pq.begin());
        int x = sv.second[0];
        int y = sv.second[1];
        int curr_dir = sv.second[2];
        int curr_dist = sv.first;
        // to turn
        int right_dir = ((curr_dir + 1) % 4 + 4) % 4;
        int left_dir = ((curr_dir - 1) % 4 + 4) % 4;

        if (dist[x][y][right_dir] > dist[x][y][curr_dir] + 1000)
        {
            dist[x][y][right_dir] = dist[x][y][curr_dir] + 1000;
            pq.insert({dist[x][y][right_dir], {x, y, right_dir}});
            if (prev.find({x, y, right_dir}) != prev.end())
                prev[{x, y, right_dir}].clear();
            prev[{x, y, right_dir}].push_back({x, y, curr_dir});
        }
        else if (dist[x][y][right_dir] == dist[x][y][curr_dir] + 1000)
        {
            prev[{x, y, right_dir}].push_back({x, y, curr_dir});
        }

        if (dist[x][y][left_dir] > dist[x][y][curr_dir] + 1000)
        {
            dist[x][y][left_dir] = dist[x][y][curr_dir] + 1000;
            pq.insert({dist[x][y][left_dir], {x, y, left_dir}});
            if (prev.find({x, y, left_dir}) != prev.end())
                prev[{x, y, left_dir}].clear();
            prev[{x, y, left_dir}].push_back({x, y, curr_dir});
        }
        else if (dist[x][y][left_dir] == dist[x][y][curr_dir] + 1000)
        {
            prev[{x, y, left_dir}].push_back({x, y, curr_dir});
        }

        // move in dir
        int nx = x + dir[curr_dir].first, ny = y + dir[curr_dir].second;
        if (grid[nx][ny] != '#' && dist[nx][ny][curr_dir] > dist[x][y][curr_dir] + 1)
        {
            dist[nx][ny][curr_dir] = dist[x][y][curr_dir] + 1;
            pq.insert({dist[nx][ny][curr_dir], {nx, ny, curr_dir}});
            if (prev.find({nx, ny, curr_dir}) != prev.end())
                prev[{nx, ny, curr_dir}].clear();
            prev[{nx, ny, curr_dir}].push_back({x, y, curr_dir});
        }
        else if (grid[nx][ny] != '#' && dist[nx][ny][curr_dir] == (dist[x][y][curr_dir] + 1))
        {
            prev[{nx, ny, curr_dir}].push_back({x, y, curr_dir});
        }
    }
    set<pair<int, int>> s;
    set<vector<int>> vis;
    s.insert({fx, fy});
    queue<vector<int>> q;
    int min_dist = min({dist[fx][fy][0], dist[fx][fy][1], dist[fx][fy][2], dist[fx][fy][3]});
    for (int i = 0; i < 4; i++)
    {
        if (min_dist == dist[fx][fy][i])
            q.push({fx, fy, i}), vis.insert({fx, fy, i});
    }

    while (q.size())
    {
        auto tv = q.front();
        q.pop();
        s.insert({tv[0], tv[1]});
        for (auto &pr : prev[tv])
        {
            if (vis.find(pr) == vis.end())
            {
                vis.insert(pr);
                q.push(pr);
            }
        }
    }
    cout << "Part 2 solution is: " << s.size() << endl;
}
int main()
{
    part1();
    part2();
}
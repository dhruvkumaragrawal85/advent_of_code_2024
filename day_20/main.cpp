#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
int get_dist(int sx, int sy, int fx, int fy, vector<string> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[sx][sy] = 0;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (q.size())
    {
        auto fr = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = fr.first + moves[i].first;
            int ny = fr.second + moves[i].second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && dist[nx][ny] > 1 + dist[fr.first][fr.second])
            {
                dist[nx][ny] = 1 + dist[fr.first][fr.second];
                q.push({nx, ny});
            }
        }
    }
    return dist[fx][fy];
}
void part1()
{
    ifstream infile("input.in");

    string line;
    vector<string> grid;
    while (getline(infile, line))
    {
        grid.push_back(line);
    }
    int n = grid.size();
    int m = grid[0].size();
    int sx = 0, sy = 0, fx = 0, fy = 0;
    set<pair<int, int>> pts;
    for (int i = 1; i <= n - 2; i++)
    {
        for (int j = 1; j <= m - 2; j++)
        {
            if (grid[i][j] == 'S')
            {
                sx = i, sy = j;
            }
            if (grid[i][j] == 'E')
            {
                fx = i, fy = j;
            }
            for (int k = 0; k < 4; k++)
            {
                int i1 = i, j1 = j, i2 = i + moves[k].first, j2 = j + moves[k].second;
                if (grid[i1][j1] == '#' && grid[i2][j2] == '.')
                {
                    pts.insert({i1, j1});
                }
            }
        }
    }
    int initial_dist = get_dist(sx, sy, fx, fy, grid);
    int res = 0;
    for (auto &x : pts)
    {
        grid[x.first][x.second] = '.';
        int new_dist = get_dist(sx, sy, fx, fy, grid);
        grid[x.first][x.second] = '#';
        if (initial_dist - new_dist >= 100)
            res++;
    }
    cout << "Part 1 solution is: " << res << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    vector<string> grid;
    while (getline(infile, line))
    {
        grid.push_back(line);
    }
    int n = grid.size();
    int m = grid[0].size();
    int sx = 0, sy = 0, fx = 0, fy = 0;
    set<pair<int, int>> pts;
    for (int i = 1; i <= n - 2; i++)
    {
        for (int j = 1; j <= m - 2; j++)
        {
            if (grid[i][j] == 'S')
            {
                sx = i, sy = j;
            }
            if (grid[i][j] == 'E')
            {
                fx = i, fy = j;
            }
            for (int k = 0; k < 4; k++)
            {
                int i1 = i, j1 = j, i2 = i + moves[k].first, j2 = j + moves[k].second;
                if (grid[i1][j1] == '#' && grid[i2][j2] == '.')
                {
                    pts.insert({i1, j1});
                }
            }
        }
    }
    vector<pair<int, int>> path;
    map<pair<int, int>, pair<int, int>> prev;
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[sx][sy] = 0;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (q.size())
    {
        auto fr = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = fr.first + moves[i].first;
            int ny = fr.second + moves[i].second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && dist[nx][ny] > 1 + dist[fr.first][fr.second])
            {
                dist[nx][ny] = 1 + dist[fr.first][fr.second];
                prev[{nx, ny}] = fr;
                q.push({nx, ny});
            }
        }
    }
    // cout << sx << " " << sy << " " << fx << " " << fy << endl;
    while (true)
    {
        path.push_back({fx, fy});
        if (path.back() == make_pair(sx, sy))
            break;
        auto par = prev[{fx, fy}];
        fx = par.first;
        fy = par.second;
    }
    reverse(path.begin(), path.end());
    int len = path.size();
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            int ux = path[i].first, uy = path[i].second, vx = path[j].first, vy = path[j].second;
            int sc_len = abs(ux - vx) + abs(uy - vy);
            if (sc_len > 20)
                continue;
            int new_time = i + (len - j - 1) + sc_len;
            if (len - 1 - new_time >= 100)
                res++;
        }
    }
    cout << "Part 2 solution is: " << res << endl;
}
int main()
{
    // part1();
    part2();
}
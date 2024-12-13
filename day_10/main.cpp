#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
void dfs(int i, int j, char c, vector<string> &grid, set<pair<int, int>> &vis, set<pair<int, int>> &nines)
{
    if (grid[i][j] == '9')
    {
        nines.insert({i, j});
        return;
    }
    vis.insert({i, j});
    for (auto &move : moves)
    {
        int nx = i + move.first;
        int ny = j + move.second;
        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && vis.find({nx, ny}) == vis.end() && grid[nx][ny] == c)
        {
            dfs(nx, ny, (char)(c + 1), grid, vis, nines);
        }
    }
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
    int res = 0;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '0')
            {
                set<pair<int, int>> vis;
                set<pair<int, int>> nines;
                dfs(i, j, '1', grid, vis, nines);
                res = res + nines.size();
            }
        }
    }
    cout << "Part 1 solution is: " << res << endl;
}
void path_cnt(int i, int j, int dir, char c, vector<string> &grid, set<vector<int>> &vis, set<vector<vector<int>>> &nines, vector<vector<int>> &path)
{
    path.push_back({i, j, dir});
    if (grid[i][j] == '9')
    {
        nines.insert(path);
        path.pop_back();
        return;
    }
    for (int f = 0; f < 4; f++)
    {
        int nx = i + moves[f].first;
        int ny = j + moves[f].second;
        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == c)
        {
            path_cnt(nx, ny, f, (int)(c + 1), grid, vis, nines, path);
        }
    }
    path.pop_back();
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
    int res = 0;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '0')
            {
                set<vector<int>> vis;
                set<vector<vector<int>>> nines;
                vector<vector<int>> path;
                path_cnt(i, j, -1, '1', grid, vis, nines, path);
                res = res + nines.size();
            }
        }
    }
    cout << "Part 2 solution is: " << res << endl;
}
int main()
{
    part1();
    part2();
}
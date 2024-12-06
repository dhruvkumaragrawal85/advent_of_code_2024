#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, int>> moves = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
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
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int x = 0, y = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '^')
            {
                x = i, y = j;
            }
        }
    }
    vis[x][y] = 1;
    int cnt = 1;
    int dir = 0;
    while (true)
    {
        int nx = x + moves[dir].first;
        int ny = y + moves[dir].second;
        if (!(nx >= 0 && nx < n && ny >= 0 && ny < m))
        {
            break;
        }
        else if (grid[nx][ny] == '#')
        {
            dir = (dir + 1) % 4;
        }
        else
        {
            if (!vis[nx][ny])
                cnt++;
            vis[nx][ny] = 1;
            x = nx;
            y = ny;
        }
    }
    cout << "Part 1 solution is: " << cnt << endl;
}
void part2()
{
    // slow as shit but works
    ifstream infile("input.in");

    string line;
    vector<string> grid;
    while (getline(infile, line))
    {
        grid.push_back(line);
    }
    int n = grid.size();
    int m = grid[0].size();
    int x = 0, y = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '^')
            {
                x = i, y = j;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((i == x && j == y) || (grid[i][j] == '#'))
                continue;
            // cout << i << " " << j << endl;
            grid[i][j] = '#';
            set<pair<int, pair<int, int>>> s;
            s.insert({0, {x, y}});
            int dir = 0;
            int ix = x;
            int iy = y;
            bool cycle = false;
            while (true)
            {
                int nx = ix + moves[dir].first;
                int ny = iy + moves[dir].second;
                if (!(nx >= 0 && nx < n && ny >= 0 && ny < m))
                {
                    break;
                }
                else if (grid[nx][ny] == '#')
                {
                    dir = (dir + 1) % 4;
                }
                else
                {
                    if (s.find({dir, {nx, ny}}) != s.end())
                    {
                        // cout << i << " " << j << endl;
                        cycle = true;
                        break;
                    }
                    s.insert({dir, {nx, ny}});
                    ix = nx;
                    iy = ny;
                }
            }
            if (cycle)
                cnt++;
            grid[i][j] = '.';
        }
    }
    cout << "Part 2 solution is: " << cnt << endl;
}
int main()
{
    part1();
    part2();
}
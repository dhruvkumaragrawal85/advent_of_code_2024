#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, int>> moves = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
bool is_valid(int i, int j, int n, int m)
{
    return i >= 0 && i < n && j >= 0 && j < m;
}
int get_perimeter(int i, int j, vector<string> &grid)
{
    int p = 0;
    for (auto mv : moves)
    {
        int nx = i + mv.first, ny = j + mv.second;
        p = p + (!is_valid(nx, ny, grid.size(), grid[0].size()) || grid[i][j] != grid[nx][ny]);
    }
    return p;
}
void func(ll i, ll j, vector<vector<bool>> &vis, ll &area, ll &perimeter, char c, vector<string> &grid)
{
    vis[i][j] = true;
    area = area + 1;
    perimeter = perimeter + get_perimeter(i, j, grid);
    for (auto mv : moves)
    {
        int nx = i + mv.first, ny = j + mv.second;
        if (is_valid(nx, ny, grid.size(), grid[0].size()) && c == grid[nx][ny] && !vis[nx][ny])
        {
            func(nx, ny, vis, area, perimeter, c, grid);
        }
    }
}
int get_corner(int i, int j, vector<string> &grid)
{
    int p = 0;
    // cout << i << " " << j << " ";
    for (int t = 0; t < 4; t++)
    {
        int x1 = i + moves[t].first, y1 = j + moves[t].second;
        int x2 = i + moves[(t + 1) % 4].first, y2 = j + moves[(t + 1) % 4].second;
        p = p + ((!is_valid(x1, y1, grid.size(), grid[0].size()) || grid[x1][y1] != grid[i][j]) &&
                 (!is_valid(x2, y2, grid.size(), grid[0].size()) || grid[i][j] != grid[x2][y2]));
    }
    for (int t = 0; t < 4; t++)
    {
        int x1 = i + moves[t].first, y1 = j + moves[t].second;
        int x2 = i + moves[(t + 1) % 4].first, y2 = j + moves[(t + 1) % 4].second;
        int x3 = i + moves[(t + 1) % 4].first + moves[t].first, y3 = j + moves[(t + 1) % 4].second + moves[t].second;
        // if (i == 0 && j == 2)
        // {
        //     cout << '\t' << " " << x1 << " " << y1 << endl;
        //     cout << '\t' << " " << x2 << " " << y2 << endl;
        //     cout << '\t' << " " << x3 << " " << y3 << endl;
        // }
        p = p + ((is_valid(x1, y1, grid.size(), grid[0].size()) && grid[x1][y1] == grid[i][j]) &&
                 (is_valid(x2, y2, grid.size(), grid[0].size()) && grid[i][j] == grid[x2][y2]) &&
                 (is_valid(x3, y3, grid.size(), grid[0].size()) && grid[i][j] != grid[x3][y3]));
    }
    // cout << p << endl;
    return p;
}
void func_II(ll i, ll j, vector<vector<bool>> &vis, ll &area, ll &perimeter, char c, vector<string> &grid)
{
    vis[i][j] = true;
    area = area + 1;
    perimeter = perimeter + get_corner(i, j, grid);
    for (auto mv : moves)
    {
        int nx = i + mv.first, ny = j + mv.second;
        if (is_valid(nx, ny, grid.size(), grid[0].size()) && c == grid[nx][ny] && !vis[nx][ny])
        {
            func_II(nx, ny, vis, area, perimeter, c, grid);
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
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    ll res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ll area = 0, perimeter = 0;
            if (!vis[i][j])
            {
                func(i, j, vis, area, perimeter, grid[i][j], grid);
                res = res + area * perimeter;
            }
        }
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
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    ll res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ll area = 0, sides = 0;
            // HINT: corners==sides
            if (!vis[i][j])
            {
                func_II(i, j, vis, area, sides, grid[i][j], grid);
                res = res + area * sides;
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
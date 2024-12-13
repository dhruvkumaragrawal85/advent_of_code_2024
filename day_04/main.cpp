#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string s = "XMAS";
vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
int search_I(int i, int j, vector<string> &grid, int n, int m)
{
    int cnt = 0;
    for (auto &dir : moves)
    {
        int ix = i, iy = j;
        int matches = 0;
        for (int t = 0; t < 4; t++)
        {
            if (ix >= 0 && ix < n && iy >= 0 && iy < m && grid[ix][iy] == s[matches])
                matches++;
            ix = ix + dir.first;
            iy = iy + dir.second;
        }
        if (matches == 4)
            cnt++;
    }
    return cnt;
}
int search_II(int i, int j, vector<string> &grid, int n, int m)
{
    if (i + 2 >= n || j + 2 >= m)
        return 0;
    if (grid[i + 1][j + 1] != 'A')
        return 0;
    return (grid[i][j] == 'M' && grid[i + 2][j + 2] == 'S' && grid[i + 2][j] == 'M' && grid[i][j + 2] == 'S') ||
           (grid[i][j] == 'M' && grid[i + 2][j + 2] == 'S' && grid[i + 2][j] == 'S' && grid[i][j + 2] == 'M') ||
           (grid[i][j] == 'S' && grid[i + 2][j + 2] == 'M' && grid[i + 2][j] == 'M' && grid[i][j + 2] == 'S') ||
           (grid[i][j] == 'S' && grid[i + 2][j + 2] == 'M' && grid[i + 2][j] == 'S' && grid[i][j + 2] == 'M');
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
    int cnt = 0;
    // cout << grid[0] << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cnt = cnt + search_I(i, j, grid, n, m);
        }
    }
    cout << "Part 1 solution is: " << cnt << endl;
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
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cnt = cnt + search_II(i, j, grid, n, m);
        }
    }
    cout << "Part 2 solution is: " << cnt << endl;
}
int main()
{
    part1();
    part2();
}
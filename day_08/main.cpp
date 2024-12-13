#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
    set<pair<int, int>> s;
    map<char, vector<pair<int, int>>> hsh;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != '.')
                hsh[grid[i][j]].push_back({i, j});
        }
    }
    for (auto &ch : hsh)
    {
        int sz = ch.second.size();
        vector<pair<int, int>> arr = ch.second;
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                if (i == j)
                    continue;
                int nx = 2 * arr[i].first - arr[j].first;
                int ny = 2 * arr[i].second - arr[j].second;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m)
                    s.insert({nx, ny});
            }
        }
    }
    cout << "Part 1 solution is: " << s.size() << endl;
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
    set<pair<int, int>> s;
    map<char, vector<pair<int, int>>> hsh;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] != '.')
                hsh[grid[i][j]].push_back({i, j});
        }
    }
    for (auto &ch : hsh)
    {
        int sz = ch.second.size();
        vector<pair<int, int>> arr = ch.second;
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                if (i == j)
                    continue;

                int nx = arr[i].first;
                int ny = arr[i].second;
                int mult = 2;
                while (nx >= 0 && nx < n && ny >= 0 && ny < m)
                {
                    s.insert({nx, ny});
                    grid[nx][ny] = '1';
                    nx = mult * arr[i].first - (mult - 1) * arr[j].first;
                    ny = mult * arr[i].second - (mult - 1) * arr[j].second;
                    mult++;
                }
            }
        }
    }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //         cout << grid[i][j];
    //     cout << endl;
    // }
    cout << "Part 2 solution is: " << s.size() << endl;
}
int main()
{
    part1();
    part2();
}
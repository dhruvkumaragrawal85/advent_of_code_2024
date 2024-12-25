#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
pair<ll, ll> return_numbers(string line)
{
    regex number_regex("-?\\d+");
    smatch match;

    pair<ll, ll> numbers;
    ll count = 0;

    while (regex_search(line, match, number_regex))
    {
        if (count == 0)
        {
            numbers.first = stoi(match.str());
        }
        else if (count == 1)
        {
            numbers.second = stoi(match.str());
            break;
        }
        count++;
        line = match.suffix().str();
    }
    return numbers;
}
void part1()
{
    ifstream infile("input.in");

    string line;
    vector<pair<ll, ll>> pts;
    while (getline(infile, line))
    {
        pair<ll, ll> pt = return_numbers(line);
        pts.push_back(pt);
    }
    int n = 71, m = 71;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < 1024; i++)
    {
        // cout << pts[i].second << " " << pts[i].first << endl;
        grid[pts[i].second][pts[i].first] = 1;
    }
    // for (auto &x : grid)
    // {
    //     for (auto &y : x)
    //         cout << y;
    //     cout << endl;
    // }
    vector<vector<int>> dist(n, vector<int>(m, 1e9));
    dist[0][0] = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
        auto element = q.front();
        q.pop();
        for (auto &mv : moves)
        {
            int nx = element.first + mv.first;
            int ny = element.second + mv.second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] > 1 + dist[element.first][element.second] && grid[nx][ny] != 1)
            {
                dist[nx][ny] = 1 + dist[element.first][element.second];
                q.push({nx, ny});
            }
        }
    }
    cout << "Part 1 solution is: " << dist[70][70] << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    vector<pair<ll, ll>> pts;
    while (getline(infile, line))
    {
        pair<ll, ll> pt = return_numbers(line);
        pts.push_back(pt);
    }
    int n = 71, m = 71;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < 1024; i++)
    {
        // cout << pts[i].second << " " << pts[i].first << endl;
        grid[pts[i].second][pts[i].first] = 1;
    }
    pair<ll, ll> ans;
    for (int i = 1024; i < pts.size(); i++)
    {
        grid[pts[i].second][pts[i].first] = 1;
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[0][0] = 0;
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty())
        {
            auto element = q.front();
            q.pop();
            for (auto &mv : moves)
            {
                int nx = element.first + mv.first;
                int ny = element.second + mv.second;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] > 1 + dist[element.first][element.second] && grid[nx][ny] != 1)
                {
                    dist[nx][ny] = 1 + dist[element.first][element.second];
                    q.push({nx, ny});
                }
            }
        }
        if (dist[70][70] == 1e9)
        {
            ans = pts[i];
            break;
        }
    }
    cout << "Part 2 solution is: " << ans.first << "," << ans.second << endl;
}
int main()
{
    part1();
    part2();
}
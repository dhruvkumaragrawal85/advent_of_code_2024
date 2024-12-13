#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void part1()
{
    // main input size 19999
    ifstream infile("input.in");
    string line;
    getline(infile, line);
    vector<int> disk;
    vector<int> blanks;
    int id = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < (line[i] - '0'); j++)
                disk.push_back(id);
            id++;
        }
        else
        {
            for (int j = 0; j < (line[i] - '0'); j++)
            {
                blanks.push_back(disk.size());
                disk.push_back(-1);
            }
        }
    }
    for (auto &x : blanks)
    {
        while (disk.back() == -1)
        {
            disk.pop_back();
        }
        if (disk.size() <= x)
            break;
        disk[x] = disk.back();
        disk.pop_back();
    }
    // for (auto &x : disk)
    //     cout << x << " ";
    // cout << endl;
    ll ans = 0;
    for (int i = 0; i < disk.size(); i++)
    {
        ans = ans + disk[i] * i;
    }
    cout << "Part 1 solution is: " << ans << endl;
}
void part2()
{
    ifstream infile("input.in");
    string line;
    getline(infile, line);
    int id = 0, pos = 0;
    map<int, pair<int, int>> files;
    list<pair<int, int>> blanks;

    for (int i = 0; i < line.size(); i++)
    {
        if (i % 2 == 0)
        {
            files[id] = {pos, line[i] - '0'};
            id++;
        }
        else
        {
            if (line[i] != '0')
            {
                blanks.push_back({pos, line[i] - '0'});
            }
        }
        pos = pos + line[i] - '0';
    }
    while (id > 0)
    {
        id--;
        int curr_pos = files[id].first;
        int curr_size = files[id].second;
        for (auto it = blanks.begin(); it != blanks.end(); it++)
        {
            int start = (*it).first;
            int size = (*it).second;
            if (start >= curr_pos)
                break;
            if (curr_size <= size)
            {
                files[id] = {start, curr_size};
                if (curr_size == size)
                    blanks.erase(it);
                else
                    *it = {start + curr_size, size - curr_size};
                break;
            }
        }
    }
    ll ans = 0;
    for (auto &x : files)
    {
        int idx = x.first;
        int curr_start = x.second.first;
        int curr_size = x.second.second;
        for (int i = 0; i < curr_size; i++)
        {
            ans = ans + (i + curr_start) * idx;
        }
    }
    cout << "Part 2 solution is: " << ans << endl;
}
int main()
{
    part1();
    part2();
}
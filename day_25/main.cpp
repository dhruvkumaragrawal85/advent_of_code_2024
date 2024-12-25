#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void part1()
{
    ifstream infile("input.in");
    string line;
    vector<string> curr;
    vector<vector<int>> locks, keys;
    while (getline(infile, line))
    {
        if (line == "")
            continue;
        curr.push_back(line);
        if (curr.size() == 7)
        {
            int sz = curr[0].size();
            vector<int> cnt(sz, -1);
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < sz; j++)
                {
                    if (curr[i][j] == '#')
                        cnt[j]++;
                }
            }

            if (curr[0][0] == '#')
                locks.push_back(cnt);
            else
                keys.push_back(cnt);
            curr.clear();
        }
    }
    int n = locks.size(), m = keys.size();
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool flag = true;
            for (int k = 0; k < 5; k++)
            {
                if (locks[i][k] + keys[j][k] > 5)
                    flag = false;
            }
            if (flag)
                res++;
        }
    }
    cout << "Part 1 solution is: " << res << endl;
}
void part2()
{
    // just visit the links
    ifstream infile("input.in");

    string line;
    while (getline(infile, line))
    {
    }
    cout << "Part 2 solution is: " << endl;
}
int main()
{
    part1();
    part2();
}
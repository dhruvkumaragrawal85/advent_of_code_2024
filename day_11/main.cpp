#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll digits(ll num)
{
    int cnt = 0;
    while (num)
    {
        num = num / 10;
        cnt++;
    }
    return cnt;
}
pair<ll, ll> split(ll number)
{
    ll sz = digits(number);
    string s = to_string(number);
    string fh = s.substr(0, sz / 2);
    string sh = s.substr(sz / 2);
    return {stoi(fh), stoi(sh)};
}
void part1()
{
    ifstream infile("input.in");

    string line;
    list<ll> arr;
    getline(infile, line);
    stringstream ss(line);
    ll num;
    while (ss >> num)
        arr.push_back(num);
    int t = 25;
    while (t--)
    {
        for (auto it = arr.begin(); it != arr.end();)
        {
            if (*it == 0)
            {
                *it = 1;
                ++it;
            }
            else if (digits(*it) % 2)
            {
                *it = (*it) * (2024);
                ++it;
            }
            else
            {
                pair<ll, ll> num = split(*it);
                *it = num.first;
                it = arr.insert(next(it), num.second);
                ++it;
            }
        }
    }
    cout << "Part 1 solution is: " << arr.size() << endl;
}
ll func(ll num, ll moves, map<pair<ll, ll>, ll> &dp)
{
    if (dp.find({num, moves}) != dp.end())
        return dp[{num, moves}];
    if (moves == 0)
        return 1;
    ll res = 0;
    if (num == 0)
        res = res + func(1, moves - 1, dp);
    else if (digits(num) % 2)
        res = res + func(2024 * num, moves - 1, dp);
    else
    {
        pair<ll, ll> halves = split(num);
        res = res + func(halves.first, moves - 1, dp) + func(halves.second, moves - 1, dp);
    }
    return dp[{num, moves}] = res;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    list<ll> arr;
    getline(infile, line);
    stringstream ss(line);
    ll num;
    while (ss >> num)
        arr.push_back(num);
    ll res = 0;
    map<pair<ll, ll>, ll> dp;
    for (auto it = arr.begin(); it != arr.end(); it++)
    {
        res = res + func(*it, 75, dp);
    }
    cout << "Part 2 solution is: " << res << endl;
}
int main()
{
    part1();
    part2();
}
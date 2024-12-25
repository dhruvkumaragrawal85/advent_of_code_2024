#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 16777216;
ll mix_prune(ll a, ll b)
{
    return (a ^ b) % mod;
}
ll ops(ll number)
{
    ll val;
    val = number * 64;
    number = mix_prune(number, val);
    val = number / 32;
    number = mix_prune(number, val);
    val = number * 2048;
    return mix_prune(number, val);
}
void ops_II(ll number, vector<pair<ll, ll>> &vec, ll times)
{
    if (times == 0)
        return;
    ll org = number;
    ll val;
    val = number * 64;
    number = mix_prune(number, val);
    val = number / 32;
    number = mix_prune(number, val);
    val = number * 2048;
    number = mix_prune(number, val);
    int a = number % 10;
    int b = org % 10;
    vec.push_back({a, a - b});
    ops_II(number, vec, times - 1);
}
void part1()
{
    ifstream infile("input.in");

    string line;
    ll res = 0;
    while (getline(infile, line))
    {
        ll number = stoll(line);
        for (int i = 0; i < 2000; i++)
        {
            number = ops(number);
        }
        res = res + number;
    }
    cout << "Part 1 solution is: " << res << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    vector<ll> nums;
    while (getline(infile, line))
    {
        nums.push_back(stoll(line));
    }
    int n = nums.size();
    vector<pair<ll, ll>> seq[nums.size()];
    for (int i = 0; i < n; i++)
    {
        vector<pair<ll, ll>> res;
        ops_II(nums[i], res, 2000);
        seq[i] = res;
    }
    ll best = 0;
    map<vector<ll>, ll> hsh;
    for (int i = 0; i < n; i++)
    {
        set<vector<ll>> s;
        for (int j = 3; j < 2000; j++)
        {
            vector<ll> temp = {seq[i][j - 3].second, seq[i][j - 2].second, seq[i][j - 1].second, seq[i][j].second};
            if (s.find(temp) == s.end())
            {
                hsh[temp] += seq[i][j].first;
                s.insert(temp);
                best = max(best, hsh[temp]);
            }
        }
    }
    cout << "Part 2 solution is: " << best << endl;
}
int main()
{
    part1();
    part2();
}
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void get_chunks(set<string> &chunks, string line)
{
    stringstream ss(line);
    while (ss.good())
    {
        string substr;
        getline(ss, substr, ',');
        reverse(substr.begin(), substr.end());
        while (substr.back() == ' ')
            substr.pop_back();
        reverse(substr.begin(), substr.end());
        chunks.insert(substr);
    }
}
bool check_I(int idx, string s, set<string> &chunks, vector<int> &dp)
{
    int n = s.size();
    if (idx >= n)
    {
        return true;
    }
    if (dp[idx] != -1)
        return dp[idx];
    string curr = "";
    bool res = false;
    for (int i = idx; i < n; i++)
    {
        curr.push_back(s[i]);
        if (chunks.find(curr) != chunks.end())
        {
            res = res | check_I(i + 1, s, chunks, dp);
        }
    }
    return dp[idx] = res;
}
int func_I(string s, set<string> &chunks)
{
    int n = s.size();
    vector<int> dp(n + 1, -1);
    return check_I(0, s, chunks, dp);
}
ll check_II(int idx, string s, set<string> &chunks, vector<ll> &dp)
{
    int n = s.size();
    if (idx >= n)
    {
        return 1;
    }
    if (dp[idx] != -1)
        return dp[idx];
    string curr = "";
    ll res = 0;
    for (int i = idx; i < n; i++)
    {
        curr.push_back(s[i]);
        if (chunks.find(curr) != chunks.end())
        {
            res = res + check_II(i + 1, s, chunks, dp);
        }
    }
    return dp[idx] = res;
}
ll func_II(string s, set<string> &chunks)
{
    int n = s.size();
    vector<ll> dp(n + 1, -1);
    return check_II(0, s, chunks, dp);
}
void part1()
{
    ifstream infile("input.in");
    string line;
    set<string> chunks;
    vector<string> patterns;
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line.empty())
        {
            input_switch = true;
        }
        else
        {
            if (input_switch)
            {
                patterns.push_back(line);
            }
            else
            {
                get_chunks(chunks, line);
            }
        }
    }
    int res = 0;
    for (auto &str : patterns)
    {
        res = res + func_I(str, chunks);
    }
    cout << "Part 1 solution is: " << res << endl;
}
void part2()
{
    ifstream infile("input.in");
    string line;
    set<string> chunks;
    vector<string> patterns;
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line.empty())
        {
            input_switch = true;
        }
        else
        {
            if (input_switch)
            {
                patterns.push_back(line);
            }
            else
            {
                get_chunks(chunks, line);
            }
        }
    }
    ll res = 0;
    for (auto &str : patterns)
    {
        res = res + func_II(str, chunks);
    }
    cout << "Part 2 solution is: " << res << endl;
}
int main()
{
    part1();
    part2();
}
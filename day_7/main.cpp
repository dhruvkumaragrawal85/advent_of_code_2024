#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void custom_iota(int num, char buffer[], int sz)
{
    for (int i = 0; i < sz; i++)
    {
        buffer[i] = (char)('0' + num % 3);
        num = num / 3;
    }
    buffer[sz] = '\0';
}
void input(vector<pair<ll, vector<ll>>> &eqs, string &line)
{
    ll key = 0;
    vector<ll> vals;
    int ptr = 0;
    while (line[ptr] != ':')
    {
        key = key * 10 + (int)(line[ptr] - '0');
        ptr++;
    }
    ptr = ptr + 2;
    string s = line.substr(ptr);
    stringstream ss(s);
    string word;
    while (ss >> word)
    {
        vals.push_back(stoi(word));
    }
    eqs.push_back({key, vals});
}
bool valid(pair<ll, vector<ll>> &eq)
{
    int sz = eq.second.size();
    ll key = eq.first;
    auto arr = eq.second;
    sz--;
    for (int i = 0; i < (1 << sz); i++)
    {
        stack<ll> st;
        st.push(arr[0]);
        for (int j = 0; j < sz; j++)
        {
            if (i & (1 << j))
            {
                ll temp = st.top();
                st.pop();
                st.push(temp * arr[j + 1]);
            }
            else
            {
                ll temp = st.top();
                st.pop();
                st.push(temp + arr[j + 1]);
            }
        }
        if (st.top() == key)
            return true;
    }
    return false;
}
bool valid_2(pair<ll, vector<ll>> &eq)
{
    int sz = eq.second.size();
    ll key = eq.first;
    auto arr = eq.second;
    sz--;
    ll lim = 1;
    for (int i = 0; i < sz; i++)
        lim = lim * 3;
    for (int i = 0; i < lim; i++)
    {
        stack<ll> st;
        char buffer[sz + 1];
        custom_iota(i, buffer, sz);
        // cout << buffer << endl;
        st.push(arr[0]);
        for (int j = 0; j < sz; j++)
        {
            if (buffer[j] == '0')
            {
                ll temp = st.top();
                st.pop();
                st.push(temp * arr[j + 1]);
            }
            else if (buffer[j] == '1')
            {
                ll temp = st.top();
                st.pop();
                st.push(temp + arr[j + 1]);
            }
            else
            {
                ll temp = st.top();
                st.pop();
                ll copy = arr[j + 1];
                while (copy)
                {
                    temp = temp * 10;
                    copy = copy / 10;
                }
                st.push(temp + arr[j + 1]);
            }
            if (st.top() > key)
                break;
        }
        if (st.top() == key)
            return true;
    }
    return false;
}
void part1()
{
    ifstream infile("input.in");

    string line;
    vector<pair<ll, vector<ll>>> eqs;
    while (getline(infile, line))
    {
        input(eqs, line);
    }
    ll ans = 0;
    for (auto &s : eqs)
    {
        if (valid(s))
            ans = ans + s.first;
    }
    cout << "Part 1 solution is: " << ans << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    vector<pair<ll, vector<ll>>> eqs;
    while (getline(infile, line))
    {
        input(eqs, line);
    }
    ll ans = 0;
    for (auto &s : eqs)
    {
        if (valid_2(s))
        {
            ans = ans + s.first;
        }
    }
    cout << "Part 2 solution is: " << ans << endl;
}
int main()
{
    part1();
    part2();
}
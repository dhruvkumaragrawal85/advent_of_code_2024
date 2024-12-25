#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define mod 100000000000000007ll
const long long N = 200005, INF = 2000000000000000000;
////////////////////////
/////////binexp/////////
////////////////////////
ll power(ll a, ll b, ll p)
{
    if (b == 0)
        return 1;
    if (a == 0)
        return 0;
    ll res = 1;
    a %= p;
    while (b > 0)
    {
        if (b & 1)
            res = (1ll * res * a) % p;
        b >>= 1;
        a = (1ll * a * a) % p;
    }
    return res;
}
ll fact[N], inv[N];

void pre()
{
    fact[0] = 1;
    inv[0] = 1;
    for (ll i = 1; i < N; i++)
        fact[i] = (i * fact[i - 1]) % mod;
    for (ll i = 1; i < N; i++)
        inv[i] = power(fact[i], mod - 2, mod);
}
ll nCr(ll n, ll r, ll p)
{
    if (r > n || r < 0)
        return 0;
    if (n == r)
        return 1;
    if (r == 0)
        return 1;
    return (((fact[n] * inv[r]) % p) * inv[n - r]) % p;
}

void part1()
{
    ifstream infile("input.in");
    string line;
    map<string, set<string>> adj;
    set<string> all_nodes;
    while (getline(infile, line))
    {
        string u = line.substr(0, 2);
        string v = line.substr(3, 2);
        adj[u].insert(v);
        adj[v].insert(u);
        all_nodes.insert(u);
        all_nodes.insert(v);
    }
    set<set<string>> vis;
    ll res = 0;
    for (auto &str : all_nodes)
    {
        for (auto &second_str : adj[str])
        {
            for (auto &third : adj[second_str])
            {
                if (adj[str].find(third) != adj[str].end())
                {
                    set<string> temp;
                    temp.insert(str);
                    temp.insert(second_str);
                    temp.insert(third);
                    int cnt = 0;
                    if (str[0] == 't')
                        cnt++;
                    if (second_str[0] == 't')
                        cnt++;
                    if (third[0] == 't')
                        cnt++;

                    if (temp.size() == 3 && cnt)
                        vis.insert(temp);
                }
            }
        }
    }

    cout << "Part 1 solution is: " << vis.size() << endl;
}
void search(string str, map<string, set<string>> &adj, set<string> curr, set<set<string>> &vis)
{
    if (vis.find(curr) != vis.end())
        return;
    vis.insert(curr);
    for (auto neighbor : adj[str])
    {
        if (curr.find(neighbor) != curr.end())
            continue;
        bool all = true;
        for (auto &search_str : curr)
            if (adj[neighbor].find(search_str) == adj[neighbor].end())
                all = false;
        if (!all)
            continue;
        set<string> new_curr = curr;
        new_curr.insert(neighbor);
        search(neighbor, adj, new_curr, vis);
    }
}
void part2()
{
    ifstream infile("input.in");
    string line;
    map<string, set<string>> adj;
    set<string> all_nodes;
    while (getline(infile, line))
    {
        string u = line.substr(0, 2);
        string v = line.substr(3, 2);
        adj[u].insert(v);
        adj[v].insert(u);
    }
    set<set<string>> vis;
    for (auto &pr : adj)
    {
        string s = pr.first;
        search(s, adj, {s}, vis);
    }
    vector<string> res;
    for (auto &s : vis)
    {
        if (s.size() > res.size())
            res = vector<string>(s.begin(), s.end());
    }
    cout << "Part 2 solution is: " << endl;
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i];
        if (i != res.size() - 1)
            cout << ',';
    }
}
int main()
{
    pre();
    part1();
    part2();
}
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
    vector<ll> a, b;
    while (getline(infile, line))
    {
        stringstream ss(line);
        ll num1, num2;
        ss >> num1 >> num2;
        a.push_back(num1);
        b.push_back(num2);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int len = a.size();
    ll ans = 0;
    for (int i = 0; i < len; i++)
    {
        ans = ans + abs(a[i] - b[i]);
    }
    cout << "Part 1 solution is: " << ans << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    vector<ll> a;
    map<ll, ll> b;
    while (getline(infile, line))
    {
        stringstream ss(line);
        ll num1, num2;
        ss >> num1 >> num2;
        a.push_back(num1);
        b[num2]++;
    }
    ll ans = 0;
    for (auto &x : a)
        ans = ans + x * (b[x]);

    cout << "Part 2 solution is: " << ans << endl;
}
int main()
{
    part1();
    part2();
}
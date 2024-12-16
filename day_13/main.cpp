#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
    vector<pair<ll, ll>> button_a, button_b, prize;
    string line;
    ll ctr = 0;
    while (getline(infile, line))
    {
        if (line == "")
            continue;
        auto nums = return_numbers(line);
        if (ctr % 3 == 0)
        {
            button_a.push_back(nums);
        }
        else if (ctr % 3 == 1)
        {
            button_b.push_back(nums);
        }
        else
        {
            prize.push_back(nums);
        }
        ctr++;
    }
    ll n = button_a.size();
    long long res = 0;
    for (ll i = 0; i < n; i++)
    {
        long long curr_res = 1e17;
        for (ll a = 1; a <= 100; a++)
        {
            for (ll b = 1; b <= 100; b++)
            {
                if ((a * button_a[i].first + b * button_b[i].first) != prize[i].first ||
                    (a * button_a[i].second + b * button_b[i].second) != prize[i].second)
                    continue;
                long long curr = 3 * a + 1 * b;
                if (curr < curr_res)
                    curr_res = curr;
            }
        }
        if (curr_res < 1e17)
            res = res + curr_res;
    }
    cout << "Part 1 solution is: " << res << endl;
}
void part2()
{
    ifstream infile("input.in");
    vector<pair<ll, ll>> button_a, button_b, prize;
    string line;
    ll ctr = 0;
    while (getline(infile, line))
    {
        if (line == "")
            continue;
        auto nums = return_numbers(line);
        if (ctr % 3 == 0)
        {
            button_a.push_back(nums);
        }
        else if (ctr % 3 == 1)
        {
            button_b.push_back(nums);
        }
        else
        {
            nums.first = nums.first + 10000000000000;
            nums.second = nums.second + 10000000000000;
            prize.push_back(nums);
        }
        ctr++;
    }
    ll n = button_a.size();
    long long res = 0;
    for (ll i = 0; i < n; i++)
    {
        // ax*s+bx*t=px
        // ay*s+by*t=py
        // s=(px*by-py*bx)/(ax*by-ay*bx)
        // t=(px-ax*s)/bx
        ll ax = button_a[i].first, ay = button_a[i].second, bx = button_b[i].first, by = button_b[i].second, px = prize[i].first, py = prize[i].second;
        ll s = (px * by - py * bx) / (ax * by - ay * bx);
        ll t = (px - ax * s) / bx;
        if (((ax * s + bx * t) == px) && ((ay * s + by * t) == py))
            res = res + s * 3 + t * 1;
    }
    cout << "Part 2 solution is: " << res << endl;
}
int main()
{
    part1();
    part2();
}
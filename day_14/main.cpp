#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> return_numbers(string line)
{
    regex number_regex("-?\\d+");
    smatch match;

    vector<ll> numbers;
    ll count = 0;

    while (regex_search(line, match, number_regex))
    {
        numbers.push_back(stoi(match.str()));
        if (count == 3)
            break;
        count++;
        line = match.suffix().str();
    }
    return numbers;
}
void part1()
{
    ifstream infile("input.in");

    string line;
    vector<vector<ll>> robot;
    while (getline(infile, line))
    {
        vector<ll> format = return_numbers(line);
        swap(format[0], format[1]);
        swap(format[2], format[3]);
        robot.push_back(format);
    }
    int n = 103, m = 101;
    for (auto &r : robot)
    {
        r[0] = (r[0] + n * 100 + r[2] * 100) % n;
        r[1] = (r[1] + m * 100 + r[3] * 100) % m;
    }
    int a = 0, b = 0, c = 0, d = 0;
    for (auto &r : robot)
    {
        if (r[0] >= 0 && r[0] < n / 2)
        {
            if (r[1] >= 0 && r[1] < m / 2)
                a++;
            else if (r[1] < m && r[1] > m / 2)
                b++;
        }
        else if (r[0] > n / 2 && r[0] < n)
        {
            if (r[1] >= 0 && r[1] < m / 2)
                c++;
            else if (r[1] < m && r[1] > m / 2)
                d++;
        }
    }
    // cout << a << " " << b << " " << c << " " << d << endl;
    cout << "Part 1 solution is: " << (a * b * c * d) << endl;
}
void print_grid(int n, int m, int t, vector<vector<ll>> robot)
{
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    for (auto &r : robot)
    {
        grid[r[0]][r[1]]++;
    }
    for (auto &x : grid)
    {
        for (auto &y : x)
            cout << y;
        cout << endl;
    }
}
void part2()
{
    ifstream infile("input.in");

    string line;
    vector<vector<ll>> robot;
    while (getline(infile, line))
    {
        vector<ll> format = return_numbers(line);
        swap(format[0], format[1]);
        swap(format[2], format[3]);
        robot.push_back(format);
    }
    int n = 103, m = 101;
    int time = 0;
    ll min_safe_factor = 1e17;
    for (int t = 1; t <= (3 * 103 * 101); t++)
    {
        for (auto &r : robot)
        {
            r[0] = (r[0] + n + r[2]) % n;
            r[1] = (r[1] + m + r[3]) % m;
        }
        int a = 0, b = 0, c = 0, d = 0;
        for (auto &r : robot)
        {
            if (r[0] >= 0 && r[0] < n / 2)
            {
                if (r[1] >= 0 && r[1] < m / 2)
                    a++;
                else if (r[1] < m && r[1] > m / 2)
                    b++;
            }
            else if (r[0] > n / 2 && r[0] < n)
            {
                if (r[1] >= 0 && r[1] < m / 2)
                    c++;
                else if (r[1] < m && r[1] > m / 2)
                    d++;
            }
        }
        // print_grid(n, m, t, robot);
        ll sf = a * 1LL * b * 1LL * c * 1LL * d;
        if (sf < min_safe_factor)
        {

            // cout << a << " " << b << " " << c << " " << d << " " << sf << endl;
            min_safe_factor = sf;
            time = t;
        }
    }
    print_grid(n, m, time, robot);
    cout << "Part 2 solution is: " << time << endl;
}
int main()
{
    part1();
    part2();
}
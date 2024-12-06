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
    bool input_switch = false;
    set<pair<int, int>> s;
    ll ans = 0;
    while (getline(infile, line))
    {
        if (line == "")
            input_switch = true;
        else if (!input_switch)
        {
            int num1 = 10 * (line[0] - '0') + (line[1] - '0');
            int num2 = 10 * (line[3] - '0') + (line[4] - '0');
            s.insert({num1, num2});
        }
        else
        {
            vector<int> arr;
            stringstream ss(line);
            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                arr.push_back(stoi(substr));
            }
            bool correct = true;
            int n = arr.size();
            // for (int i = 0; i < n; i++)
            //     cout << arr[i] << endl;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (s.find({arr[i], arr[j]}) != s.end())
                    {
                        // cout << arr[j] << " " << arr[i] << endl;
                        correct = false;
                    }
                }
            }
            if (correct)
                ans = ans + arr[n / 2];
        }
    }
    cout << "Part 1 solution is: " << ans << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    bool input_switch = false;
    set<pair<int, int>> s;
    ll ans = 0;
    while (getline(infile, line))
    {
        if (line == "")
            input_switch = true;
        else if (!input_switch)
        {
            int num1 = 10 * (line[0] - '0') + (line[1] - '0');
            int num2 = 10 * (line[3] - '0') + (line[4] - '0');
            s.insert({num1, num2});
        }
        else
        {
            vector<int> arr;
            stringstream ss(line);
            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                arr.push_back(stoi(substr));
            }
            bool correct = true;
            int n = arr.size();
            // for (int i = 0; i < n; i++)
            //     cout << arr[i] << endl;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (s.find({arr[i], arr[j]}) != s.end())
                    {
                        // cout << arr[j] << " " << arr[i] << endl;
                        correct = false;
                    }
                }
            }
            if (correct)
                continue;
            else
            {
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = 0; j < n - i - 1; j++)
                    {
                        if (s.find({arr[j + 1], arr[j]}) != s.end())
                        {
                            swap(arr[j], arr[j + 1]);
                        }
                    }
                }
                ans = ans + arr[n / 2];
            }
        }
    }
    cout << "Part 2 solution is: " << ans << endl;
}
int main()
{
    part1();
    part2();
}
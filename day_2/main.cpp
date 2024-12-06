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
    int cnt = 0;
    while (getline(infile, line))
    {
        vector<int> arr;
        stringstream ss(line);
        int num = 0;
        while (ss >> num)
        {
            arr.push_back(num);
        }
        // for (auto &x : arr)
        //     cout << x << endl;
        bool cond1 = true, cond2 = true;
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            int diff1 = arr[i] - arr[i + 1];
            int diff2 = arr[i + 1] - arr[i];
            if (!(diff1 >= 1 && diff1 <= 3))
                cond1 = false;
            if (!(diff2 >= 1 && diff2 <= 3))
                cond2 = false;
        }
        if (cond1 || cond2)
            cnt++;
    }
    cout << "Part 1 solution is: " << cnt << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    int cnt = 0;
    while (getline(infile, line))
    {
        vector<int> arr;
        stringstream ss(line);
        int num = 0;
        while (ss >> num)
        {
            arr.push_back(num);
        }
        // for (auto &x : arr)
        //     cout << x << endl;
        bool cond1 = true, cond2 = true;
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            int diff1 = arr[i] - arr[i + 1];
            int diff2 = arr[i + 1] - arr[i];
            if (!(diff1 >= 1 && diff1 <= 3))
                cond1 = false;
            if (!(diff2 >= 1 && diff2 <= 3))
                cond2 = false;
        }
        if (cond1 || cond2)
        {
            cnt++;
            continue;
        }
        bool cond3 = false;
        for (int i = 0; i < n; i++)
        {
            cond1 = true, cond2 = true;
            vector<int> temp;
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                temp.push_back(arr[j]);
            }
            for (int j = 0; j < n - 2; j++)
            {
                int diff1 = temp[j] - temp[j + 1];
                int diff2 = temp[j + 1] - temp[j];
                if (!(diff1 >= 1 && diff1 <= 3))
                    cond1 = false;
                if (!(diff2 >= 1 && diff2 <= 3))
                    cond2 = false;
            }
            if (cond1 || cond2)
                cond3 = true;
        }
        if (cond3)
            cnt++;
    }
    cout << "Part 2 solution is: " << cnt << endl;
}
int main()
{
    part1();
    part2();
}
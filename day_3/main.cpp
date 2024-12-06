#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void part1()
{
    ifstream infile("input.in");
    ll ans = 0;
    string line;
    while (getline(infile, line))
    {
        regex regexp("mul\\((\\d{1,3}),(\\d{1,3})\\)");
        for (sregex_iterator it(line.begin(), line.end(), regexp), end_it; it != end_it; ++it)
        {
            // cout << "String that matches the pattern:" << endl;
            // cout << (*it)[0] << endl; // Print the full match
            string s = (*it)[0];
            int n = s.size();
            int num1 = 0, num2 = 0, ptr = 4;
            while (s[ptr] != ',')
                num1 = num1 * 10 + (s[ptr] - '0'), ptr++;
            ptr++;
            while (s[ptr] != ')')
                num2 = num2 * 10 + (s[ptr] - '0'), ptr++;
            ans = ans + (num1 * num2);
        }
    }
    cout << "Part 1 solution is: " << ans << endl;
}
void part2()
{
    ifstream infile("input.in");
    ll ans = 0;
    string line;
    bool on = true;
    while (getline(infile, line))
    {
        regex regexp("do\\(\\)|don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\)");
        for (sregex_iterator it(line.begin(), line.end(), regexp), end_it; it != end_it; ++it)
        {
            // cout << "String that matches the pattern:" << endl;
            // cout << (*it)[0] << endl; // Print the full match
            string s = (*it)[0];
            if (s == "do()")
                on = true;
            else if (s == "don't()")
                on = false;
            else if (on)
            {
                int n = s.size();
                int num1 = 0, num2 = 0, ptr = 4;
                while (s[ptr] != ',')
                    num1 = num1 * 10 + (s[ptr] - '0'), ptr++;
                ptr++;
                while (s[ptr] != ')')
                    num2 = num2 * 10 + (s[ptr] - '0'), ptr++;
                ans = ans + (num1 * num2);
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
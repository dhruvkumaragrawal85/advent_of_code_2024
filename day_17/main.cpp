#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll get_operand(int type, int a, int b, int c, int code)
{
    if (type == 0)
        return code;
    else
    {
        if (0 <= code && code <= 3)
            return code;
        else if (code == 4)
            return a;
        else if (code == 5)
            return b;
        else if (code == 6)
            return c;
        else
            exit(1);
    }
}
ll return_numbers(string line)
{
    ll num = 0;
    for (auto &c : line)
    {
        if (c >= '0' && c <= '9')
            num = num * 10 + (c - '0');
    }
    return num;
}
vector<int> return_seq(string &line)
{
    vector<int> res;
    for (auto &c : line)
    {
        if (c >= '0' && c <= '9')
            res.push_back(c - '0');
    }
    return res;
}
void part1()
{
    ifstream infile("input.in");
    ll a = -1, b = -1, c = -1;
    vector<int> tape;
    string line;
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line.size() == 0)
        {
            input_switch = !input_switch;
        }
        else if (!input_switch)
        {
            if (a == -1)
                a = return_numbers(line);
            else if (b == -1)
                b = return_numbers(line);
            else
                c = return_numbers(line);
        }
        else if (input_switch)
        {
            tape = return_seq(line);
        }
    }
    vector<int> res;
    int n = tape.size();
    for (int i = 0; i < n;)
    {
        if (i > n - 2)
            break;
        ll x = tape[i];
        ll y = tape[i + 1];
        ll output = -1;
        switch (x)
        {
        case 0:
        {
            ll numerator = a;
            ll val = get_operand(1, a, b, c, y);
            ll denominator = (1 << val);
            a = numerator / denominator;
            i = i + 2;
            break;
        }
        case 1:
        {
            ll val = get_operand(0, a, b, c, y);
            b = b ^ val;
            i = i + 2;
            break;
        }
        case 2:
        {
            ll val = get_operand(1, a, b, c, y);
            b = val % 8;
            i = i + 2;
            break;
        }
        case 3:
        {
            if (a)
            {
                ll val = get_operand(0, a, b, c, y);
                i = val;
            }
            else
                i = i + 2;
            break;
        }
        case 4:
        {
            b = b ^ c;
            i = i + 2;
            break;
        }
        case 5:
        {
            ll val = get_operand(1, a, b, c, y);
            res.push_back(val % 8);
            i = i + 2;
            break;
        }
        case 6:
        {
            ll numerator = a;
            ll val = get_operand(1, a, b, c, y);
            ll denominator = (1 << val);
            b = numerator / denominator;
            i = i + 2;
            break;
        }
        case 7:
        {
            ll numerator = a;
            ll val = get_operand(1, a, b, c, y);
            ll denominator = (1 << val);
            c = numerator / denominator;
            i = i + 2;
            break;
        }
        }
        if (output != -1)
            res.push_back(output);
    }
    cout << "Part 1 solution is: ";
    int _ = res.size();
    for (int i = 0; i < _; i++)
    {
        cout << res[i];
        if (i != _ - 1)
            cout << ',';
    }
    cout << endl;
}
ll find(vector<int> tape, ll ans)
{
    if (tape.size() == 0)
        return ans;
    for (int i = 0; i < 8; i++)
    {
        ll a, b, c;
        a = (ans << 3) | i;
        b = a % 8;
        b = b ^ 1;
        c = a >> b;
        b = b ^ 4;
        b = b ^ c;
        if (b % 8 == tape.back())
        {
            int temp = tape.back();
            tape.pop_back();
            ll sub = find(tape, a);
            tape.push_back(temp);
            if (sub == -1)
                continue;
            return sub;
        }
    }
    return -1;
}
void part2()
{
    ifstream infile("input.in");
    ll a = -1, b = -1, c = -1;
    vector<int> tape;
    string line;
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line.size() == 0)
        {
            input_switch = !input_switch;
        }
        else if (!input_switch)
        {
            if (a == -1)
                a = return_numbers(line);
            else if (b == -1)
                b = return_numbers(line);
            else
                c = return_numbers(line);
        }
        else if (input_switch)
        {
            tape = return_seq(line);
        }
    }
    cout << "Part 2 solution is: " << find(tape, 0) << endl;
}
int main()
{
    part1();
    part2();
}
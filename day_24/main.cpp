#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void part1()
{
    ifstream infile("input.in");
    map<string, int> vals;
    multimap<vector<string>, string> relations;
    string line;
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line == "")
        {
            input_switch = true;
        }
        else if (!input_switch)
        {
            stringstream ss(line);
            string a, b;
            ss >> a >> b;
            a.pop_back();
            vals[a] = stoi(b);
        }
        else
        {
            vector<string> input;
            stringstream ss(line);
            string word;
            while (ss >> word)
            {
                input.push_back(word);
            }
            relations.insert({{input[0], input[1], input[2]}, input[4]});
        }
    }
    int sz = relations.size();
    for (int i = 0; i < sz; i++)
    {
        for (auto relation : relations)
        {
            string a = relation.first[0];
            string b = relation.first[2];
            string op = relation.first[1];
            string c = relation.second;
            if (vals.find(a) != vals.end() && vals.find(b) != vals.end())
            {
                int aval = vals[a];
                int bval = vals[b];
                int cval;
                if (op == "OR")
                    cval = aval | bval;
                else if (op == "XOR")
                    cval = aval ^ bval;
                else
                    cval = aval & bval;
                vals[c] = cval;
            }
        }
    }
    ll res = 0;
    for (auto &val : vals)
    {
        string k = val.first;
        int value = val.second;
        // cout << val.first << " " << val.second << endl;
        if (k[0] == 'z' && value)
        {
            int bit = stoi(k.substr(1, 2));
            res = res | (1LL << bit);
        }
    }
    cout << "Part 1 solution is: " << res << endl;
}
bool verify_dc(string wire, int num, map<string, vector<string>> &formulas);
bool verify_rc(string wire, int num, map<string, vector<string>> &formulas);
bool verify_intm_xor(string wire, int num, map<string, vector<string>> &formulas);
bool verify_carry(string wire, int num, map<string, vector<string>> &formulas);
bool verify_z(string wire, int num, map<string, vector<string>> &formulas);

string make_wire(char c, int num)
{
    string res = string(1, c) + "00";
    for (int ptr = 2; ptr >= 1; ptr--)
    {
        // cout << (char)(num % 10 + '0') << endl;
        res[ptr] = (char)(num % 10 + '0');
        num = num / 10;
    }
    return res;
}
bool verify_dc(string wire, int num, map<string, vector<string>> &formulas)
{
    cout << "vd" << " " << wire << " " << num << endl;
    auto pr = formulas[wire];
    string x = pr[0], y = pr[2], op = pr[1];
    if (op != "AND")
        return false;
    string x_correct = make_wire('x', num);
    string y_correct = make_wire('y', num);
    return (x == x_correct && y == y_correct) || (y == x_correct && x == y_correct);
}
bool verify_rc(string wire, int num, map<string, vector<string>> &formulas)
{
    cout << "vr" << " " << wire << " " << num << endl;
    auto pr = formulas[wire];
    string x = pr[0], y = pr[2], op = pr[1];
    if (op != "AND")
        return false;
    return (verify_intm_xor(x, num, formulas) && verify_carry(y, num, formulas)) ||
           (verify_intm_xor(y, num, formulas) && verify_carry(x, num, formulas));
}
bool verify_intm_xor(string wire, int num, map<string, vector<string>> &formulas)
{
    cout << "vx" << " " << wire << " " << num << endl;
    auto pr = formulas[wire];
    string x = pr[0], y = pr[2], op = pr[1];
    if (op != "XOR")
        return false;
    string x_correct = make_wire('x', num);
    string y_correct = make_wire('y', num);
    return (x == x_correct && y == y_correct) || (y == x_correct && x == y_correct);
}
bool verify_carry(string wire, int num, map<string, vector<string>> &formulas)
{
    cout << "vc" << " " << wire << " " << num << endl;
    auto pr = formulas[wire];
    string x = pr[0], y = pr[2], op = pr[1];
    if (num == 1)
    {
        if (op != "AND")
            return false;
        return (x == "x00" && y == "y00") || (y == "x00" && x == "y00");
    }
    if (op != "OR")
        return false;
    return (verify_dc(x, num - 1, formulas) && verify_rc(y, num - 1, formulas)) ||
           (verify_dc(y, num - 1, formulas) && verify_rc(x, num - 1, formulas));
}

bool verify_z(string wire, int num, map<string, vector<string>> &formulas)
{
    cout << "vz" << " " << wire << " " << num << endl;
    auto pr = formulas[wire];
    string x = pr[0], y = pr[2], op = pr[1];
    if (op != "XOR")
        return false;
    if (num == 0)
    {
        return (x == "x00" && y == "y00") || (y == "x00" && x == "y00");
    }
    return (verify_intm_xor(x, num, formulas) && verify_carry(y, num, formulas)) ||
           (verify_intm_xor(y, num, formulas) && verify_carry(x, num, formulas));
}

bool verify(int num, map<string, vector<string>> &relations)
{
    return verify_z(make_wire('z', num), num, relations);
}
void part2()
{
    ifstream infile("input.in");
    map<string, int> vals;
    map<string, vector<string>> relations;
    string line;
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line == "")
        {
            input_switch = true;
        }
        else if (!input_switch)
        {
            stringstream ss(line);
            string a, b;
            ss >> a >> b;
            a.pop_back();
            vals[a] = stoi(b);
        }
        else
        {
            vector<string> input;
            stringstream ss(line);
            string word;
            while (ss >> word)
            {
                input.push_back(word);
            }
            relations.insert({input[4], {input[0], input[1], input[2]}});
        }
    }
    int sz = relations.size();
    for (int i = 0; i < 44; i++)
    {
        if (!verify(i, relations))
            break;
    }
    // nnt, gws, npf, z13, cph, z19 hgj, z33
    cout << "Part 2 solution is: " << endl;
}
int main()
{
    part1();
    part2();
}
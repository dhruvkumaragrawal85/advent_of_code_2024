#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<string> num_keypad = {"789", "456", "123", "#0A"};
vector<string> dir_keypad = {"#^A", "<v>"};
map<pair<char, char>, vector<string>> num_seqs, dir_seqs;
map<pair<char, char>, int> dir_lengths;
map<char, pair<int, int>> arm_moves = {{'^', {-1, 0}}, {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}};
void concat_recurse(vector<string> &res, string &stk, vector<vector<string>> &options, int index)
{
    vector<string> opt = options[index];
    for (auto &s : opt)
    {
        string new_stk = s + stk;
        if (index == 0)
            res.push_back(new_stk);
        else
            concat_recurse(res, new_stk, options, index - 1);
    }
}
vector<string> concat_funtion(vector<vector<string>> &options)
{
    vector<string> res;
    string stk = "";
    if (options.size() > 0)
    {
        concat_recurse(res, stk, options, options.size() - 1);
    }
    return res;
}
map<pair<char, char>, vector<string>> compute_sequences(vector<string> &keypad)
{
    map<char, pair<int, int>> pos;
    for (int i = 0; i < keypad.size(); i++)
    {
        for (int j = 0; j < keypad[0].size(); j++)
        {
            if (keypad[i][j] != '#')
                pos[keypad[i][j]] = {i, j};
        }
    }
    map<pair<char, char>, vector<string>> seqs;
    for (auto &x : pos)
    {
        for (auto &y : pos)
        {
            if (x.first == y.first)
                seqs[{x.first, y.first}] = {"A"};
            else
            {
                vector<string> possibilities;
                queue<pair<pair<int, int>, string>> q;
                q.push({x.second, ""});
                int optimal = 1e9;
                while (!q.empty())
                {
                    bool breaker = false;
                    auto fr = q.front();
                    q.pop();
                    string moves = fr.second;
                    int r = fr.first.first;
                    int c = fr.first.second;
                    for (auto &arm_move : arm_moves)
                    {
                        int nr = r + arm_move.second.first;
                        int nc = c + arm_move.second.second;
                        char nm = arm_move.first;
                        if (nr < 0 || nr >= keypad.size() || nc < 0 || nc >= keypad[0].size())
                            continue;
                        if (keypad[nr][nc] == '#')
                            continue;
                        if (keypad[nr][nc] == y.first)
                        {
                            if (optimal < moves.size() + 1)
                            {
                                breaker = true;
                                break;
                            }
                            optimal = moves.size() + 1;
                            possibilities.push_back(moves + nm + 'A');
                        }
                        else
                            q.push({{nr, nc}, moves + nm});
                    }
                    if (breaker)
                        break;
                }
                seqs[{x.first, y.first}] = possibilities;
            }
        }
    }
    return seqs;
}
vector<string> solve(string str, map<pair<char, char>, vector<string>> &seqs)
{
    vector<vector<string>> options;
    for (int i = 0; i < str.size(); i++)
    {
        char r = 'A';
        if (i > 0)
            r = str[i - 1];
        char c = str[i];
        options.push_back(seqs[{r, c}]);
    }
    vector<string> res;
    res = concat_funtion(options);
    return res;
}
ll compute_length(char x, char y, int depth, map<pair<int, pair<char, char>>, ll> &cache)
{
    if (depth == 1)
        return dir_lengths[{x, y}];
    if (cache.find({depth, {x, y}}) != cache.end())
        return cache[{depth, {x, y}}];
    ll optimal = 1e17;
    for (auto &str : dir_seqs[{x, y}])
    {
        ll length = 0;
        for (int i = 0; i < str.size(); i++)
        {
            char r = 'A';
            if (i > 0)
                r = str[i - 1];
            char c = str[i];
            length = length + compute_length(r, c, depth - 1, cache);
        }
        optimal = min(optimal, length);
    }
    return cache[{depth, {x, y}}] = optimal;
}
void part1()
{
    ifstream infile("input.in");

    string line;
    ll complexity = 0;

    while (getline(infile, line))
    {
        vector<string> robot1 = solve(line, num_seqs);
        vector<string> next = robot1;
        for (int _ = 0; _ < 2; _++)
        {
            vector<string> possible_next;
            for (auto &str : next)
            {
                vector<string> temp_res = solve(str, dir_seqs);
                possible_next.insert(possible_next.end(), temp_res.begin(), temp_res.end());
            }
            int minlen = 1e9;
            for (auto &str : possible_next)
            {
                if (str.size() < minlen)
                {
                    minlen = str.size();
                    next.clear();
                    next.push_back(str);
                }
                else if (str.size() == minlen)
                    next.push_back(str);
            }
        }
        int length = next[0].size();
        complexity += (length * stoi(line.substr(0, 3)));
    }
    cout << "Part 1 solution is: " << complexity << endl;
}
void part2()
{
    ifstream infile("input.in");

    string line;
    ll complexity = 0;

    while (getline(infile, line))
    {
        vector<string> inputs = solve(line, num_seqs);
        ll optimal = 1e17;
        for (auto &seq : inputs)
        {
            ll length = 0;
            for (int i = 0; i < seq.size(); i++)
            {
                char r = 'A';
                if (i > 0)
                    r = seq[i - 1];
                char c = seq[i];
                map<pair<int, pair<char, char>>, ll> cache;
                length = length + compute_length(r, c, 25, cache);
            }
            optimal = min(optimal, length);
        }
        complexity += (optimal * stoi(line.substr(0, 3)));
    }
    cout << "Part 2 solution is: " << complexity << endl;
}
int main()
{
    num_seqs = compute_sequences(num_keypad);
    dir_seqs = compute_sequences(dir_keypad);
    for (auto &pr : dir_seqs)
    {
        dir_lengths[pr.first] = pr.second[0].length();
    }
    part1();
    part2();
}
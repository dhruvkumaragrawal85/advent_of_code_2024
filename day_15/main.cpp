#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<char, pair<int, int>> dir = {{'^', {-1, 0}}, {'>', {0, 1}}, {'<', {0, -1}}, {'v', {1, 0}}};
bool check(int x, int y, int vx, int vy, vector<string> &grid)
{
    switch (grid[x + vx][y + vy])
    {
    case '[':
        return check(x + vx, y + vy, vx, vy, grid) && (vy + 1 == 0 ? true : check(x + vx, y + vy + 1, vx, vy, grid));
    case ']':
        return (vy - 1 == 0 ? true : check(x + vx, y + vy - 1, vx, vy, grid)) && check(x + vx, y + vy, vx, vy, grid);
    case '.':
        return true;
    case '#':
        return false;
    }
    return false;
}
void move(int x, int y, int vx, int vy, vector<string> &grid)
{
    switch (grid[x + vx][y + vy])
    {
    case '[':
        move(x + vx, y + vy, vx, vy, grid);
        if (!vy)
            move(x + vx, y + vy + 1, vx, vy, grid);
        grid[x + vx][y + vy] = grid[x][y];
        grid[x][y] = '.';
        break;
    case ']':
        move(x + vx, y + vy, vx, vy, grid);
        if (!vy)
            move(x + vx, y + vy - 1, vx, vy, grid);
        grid[x + vx][y + vy] = grid[x][y];
        grid[x][y] = '.';
        break;
    case '.':
        grid[x + vx][y + vy] = grid[x][y];
        grid[x][y] = '.';
        break;
    }
}
void part1()
{
    ifstream infile("input.in");
    vector<string> grid;
    string line;
    string moves = "";
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line == "")
        {
            input_switch = true;
        }
        else if (!input_switch)
        {
            grid.push_back(line);
        }
        else
        {
            moves = moves + line;
        }
    }
    int n = grid.size();
    int m = grid[0].size();
    int ix = 0, iy = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '@')
                ix = i, iy = j;
        }
    }
    for (char mv : moves)
    {
        int dx = dir[mv].first;
        int dy = dir[mv].second;
        int dotx = -1, doty = -1;
        int tx = ix, ty = iy;
        while (true)
        {
            if (!(tx >= 0 && tx < n && ty >= 0 && ty < m))
                break;
            char c = grid[tx][ty];
            if (c == '.')
            {
                dotx = tx;
                doty = ty;
                break;
            }
            else if (c == '#')
            {
                break;
            }
            tx = tx + dx;
            ty = ty + dy;
        }
        if (dotx != -1 && doty != -1)
        {
            while (dotx != ix || doty != iy)
            {
                swap(grid[dotx][doty], grid[dotx - dx][doty - dy]);
                dotx = dotx - dx;
                doty = doty - dy;
            }

            ix = ix + dx;
            iy = iy + dy;
        }
    }
    ll res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'O')
                res = res + i * 100 + j;
        }
    }
    cout << "Part 1 solution is: " << res << endl;
}
void part2()
{
    ifstream infile("input.in");
    vector<string> grid;
    string line;
    string moves = "";
    bool input_switch = false;
    while (getline(infile, line))
    {
        if (line == "")
        {
            input_switch = true;
        }
        else if (!input_switch)
        {
            string grid_line = "";
            for (auto &c : line)
                if (c == '#')
                    grid_line.push_back('#'), grid_line.push_back('#');
                else if (c == 'O')
                    grid_line.push_back('['), grid_line.push_back(']');
                else if (c == '.')
                    grid_line.push_back('.'), grid_line.push_back('.');
                else if (c == '@')
                    grid_line.push_back('@'), grid_line.push_back('.');
            grid.push_back(grid_line);
        }
        else
        {
            moves = moves + line;
        }
    }
    int n = grid.size();
    int m = grid[0].size();
    int ix = 0, iy = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '@')
                ix = i, iy = j;
        }
    }
    for (auto &mv : moves)
    {
        if (check(ix, iy, dir[mv].first, dir[mv].second, grid))
        {
            move(ix, iy, dir[mv].first, dir[mv].second, grid);
            ix = ix + dir[mv].first;
            iy = iy + dir[mv].second;
        }
    }
    // for (auto &x : grid)
    //     cout << x << endl;
    ll res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '[')
                res = res + 100 * i + j;
        }
    }
    cout << "Part 2 solution is: " << res << endl;
}
int main()
{
    part1();
    part2();
}
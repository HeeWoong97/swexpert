#include <iostream>
#include <queue>

using namespace std;

typedef struct Dot
{
    int r;
    int c;
} Dot;

typedef struct q_info
{
    Dot pos;
    vector<vector<int>> map;
} q_info;

int N, W, H;
vector<vector<int>> map(15, vector<int>(12)) {};
Dot dir[4] {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void input(void)
{
    cin >> N >> W >> H;
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            cin >> map[r][c];
        }
    }
}

void explosion(int* map[15], Dot target)
{
    queue<q_info> q;
    Dot start_pos = target;
    q_info start = {start_pos, map};
    
    q.push(start);
    while (!q.empty()) {
        q_info cur = q.front();
        q.pop();
        Dot cur_pos = cur.pos;
        vector<vector<int>> cur_map = cur.map;
        int range = map[cur_pos.r][cur_pos.c];
    }
}

void solve(void)
{

}

int main(void)
{

    return 0;
}
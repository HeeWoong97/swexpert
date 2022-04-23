#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

typedef struct Dot
{
    int r;
    int c;
    Dot operator+(Dot d) const {
        return {r + d.r, c + d.c};
    }
} Dot;

int N, W, H;
vector<vector<int>> map(15, vector<int>(12, 0));
int block;
Dot dir[4] {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void input(void)
{
    cin >> N >> W >> H;
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            cin >> map[r][c];
            if (map[r][c] != 0) {
                block++;
            }
        }
    }
}

pair<vector<vector<int>>, int> explosion(vector<vector<int>> map, int block, int c)
{
    vector<vector<int>> cur_map = map;
    int cur_block = block;

    queue<Dot> q;
    Dot start = {H - 1, c};
    for (int r = 0; r < H; r++) {
        if (map[r][c] == 0) {
            continue;
        }
        start = {r, c};
        break;
    }
    if (block == 0) {
        return make_pair(map, block);
    }
    q.push(start);
    cur_map[start.r][start.c] = 0;
    cur_block--;
    while (!q.empty()) {
        Dot cur = q.front();
        q.pop();
        int range = map[cur.r][cur.c] - 1;
        for (int i = 0; i < 4; i++) {
            Dot next = cur;
            for (int j = 0; j < range; j++) {
                next = next + dir[i];
                if (next.r < 0 || next.r >= H || next.c < 0 || next.c >= W) {
                    break;
                }
                if (cur_map[next.r][next.c] == 0) {
                    continue;
                }
                q.push(next);
                cur_map[next.r][next.c] = 0;
                cur_block--;
            }
        }
    }
    for (int c = 0; c < W; c++) {
        int pos = H - 1;
        for (int r = H - 1; r >= 0; r--) {
            if (cur_map[r][c] != 0) {
                int tmp = cur_map[r][c];
                cur_map[r][c] = 0;
                cur_map[pos][c] = tmp;
                pos--;
            }
        }
    }
    return make_pair(cur_map, cur_block);
}

void solve(void)
{
    int solution = W * H;

    stack<pair<int, pair<vector<vector<int>>, int>>> s;
    pair<int, pair<vector<vector<int>>, int>> start = make_pair(0, make_pair(map, block));
    s.push(start);
    while (!s.empty()) {
        pair<int, pair<vector<vector<int>>, int>> cur = s.top();
        s.pop();
        int cur_depth = cur.first;
        vector<vector<int>> cur_map = cur.second.first;
        int cur_block = cur.second.second;
        if (cur_block == 0) {
            printf("0\n");
            return;
        }
        if (cur_depth == N) {
            solution = solution < cur_block ? solution : cur_block;
        }
        else {
            for (int c = 0; c < W; c++) {
                pair<vector<vector<int>>, int> next = explosion(cur_map, cur_block, c);
                s.push(make_pair(cur_depth + 1, next));
            }
        }
    }
    printf("%d\n", solution);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
    
	freopen("input.txt", "r", stdin);
	cin >> T;
	for(test_case = 1; test_case <= T; ++test_case) {
		printf("#%d ", test_case);
		input();
        solve();
        block = 0;
	}

	return 0;
}
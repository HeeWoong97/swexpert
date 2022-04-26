#include <iostream>
#include <queue>

#define EMPTY       -1
#define UNACTIVE    0
#define ACTIVE      1
#define DEAD        2

using namespace std;

typedef struct Dot
{
    int r;
    int c;
    Dot operator+(Dot d) const {
        return {r + d.r, c + d.c};
    }
} Dot;

typedef struct Cell
{
    int state = -1;
    int life;
    int unactve_time;
    int active_time;
} Cell;

int N, M, K;
Cell map[350][350] {};
Dot dir[4] {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void input(void)
{
    for (int r = 0; r < 350; r++) {
        for (int c = 0; c < 350; c++) {
            map[r][c] = Cell{EMPTY, 0, 0, 0};
        }
    }
    cin >> N >> M >> K;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int tmp;
            cin >> tmp;
            if (tmp > 0) {
                map[r + 150][c + 150] = Cell{UNACTIVE, tmp, tmp, tmp};
            }
        }
    }
}

void solve(void)
{
    for (int t = 0; t < K; t++) {
        queue<Dot> q;
        for (int r = 0; r < 350; r++) {
            for (int c = 0; c < 350; c++) {
                if (map[r][c].state == UNACTIVE) {
                    if (map[r][c].unactve_time > 0) {
                        map[r][c].unactve_time--;
                    }
                    if (map[r][c].unactve_time == 0) {
                        map[r][c].state = ACTIVE;
                    }
                }
                else if (map[r][c].state == ACTIVE) {
                    if (map[r][c].active_time > 0) {
                        q.push(Dot{r, c});
                        map[r][c].active_time--;
                    }
                    if (map[r][c].active_time == 0) {
                        map[r][c].state = DEAD;
                    }
                }
            }
        }
        while (!q.empty()) {
            Dot cur = q.front();
            q.pop();
            int life = map[cur.r][cur.c].life;
            for (int i = 0; i < 4; i++) {
                Dot next = cur + dir[i];
                if (next.r < 0 || next.r >= 350 || next.c < 0 || next.c >= 350) {
                    continue;
                }
                if (map[next.r][next.c].state == EMPTY) {
                    map[next.r][next.c] = Cell{UNACTIVE, life, life, life};
                }
                else if (map[next.r][next.c].state == UNACTIVE && map[next.r][next.c].life == map[next.r][next.c].unactve_time) {
                    if (map[next.r][next.c].life < map[cur.r][cur.c].life) {
                        map[next.r][next.c] = Cell{UNACTIVE, life, life, life};
                    }
                }
            }
        }
    }
    int answer = 0;
    for (int r = 0; r < 350; r++) {
        for (int c = 0; c < 350; c++) {
            if (map[r][c].state == UNACTIVE || map[r][c].state == ACTIVE) {
                answer++;
            }
        }
    }
    printf("%d\n", answer);
}

int main(void)
{
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        input();
        printf("#%d ", test_case);
        solve();
    }

    return 0;
}
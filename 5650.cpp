#include <iostream>
#include <vector>

#define RIGHT   0
#define DOWN    1
#define LEFT    2
#define UP      3

using namespace std;

typedef struct Dot
{
    int r;
    int c;
    Dot operator+(Dot d) const {
        return {r + d.r, c + d.c};
    }
    bool operator==(Dot d) const {
        return (r == d.r && c == d.c);
    }
} Dot;

int N;
int map[110][110] {};
vector<Dot> warm_hole[11] {};
Dot dir[4] {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int answer = 0;

void input(void)
{
    for (int i = 0; i < 11; i++) {
        vector<Dot>().swap(warm_hole[i]);
    }
    answer = 0;

    cin >> N;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cin >> map[r][c];
            if (map[r][c] >= 6 && map[r][c] <= 10) {
                warm_hole[map[r][c]].push_back(Dot{r, c});
            }
        }
    }
}

void solve(void)
{
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (map[r][c] != 0) {
                continue;
            }
            Dot start = Dot{r, c};
            for (int i = 0; i < 4; i++) {
                Dot cur = start;
                int cur_dir = i;
                bool finish = false;
                int score = 0;
                while (true) {
                    if (map[cur.r][cur.c] == 1) {
                        if (cur_dir == RIGHT) {
                            cur_dir = LEFT;
                        }
                        else if (cur_dir == DOWN) { 
                            cur_dir = RIGHT;
                        }
                        else if (cur_dir == LEFT) {
                            cur_dir = UP;
                        }
                        else if (cur_dir == UP) {
                            cur_dir = DOWN;
                        }
                        score++;
                    }
                    else if (map[cur.r][cur.c] == 2) {
                        if (cur_dir == RIGHT) {
                            cur_dir = LEFT;
                        }
                        else if (cur_dir == DOWN) {
                            cur_dir = UP;
                        }
                        else if (cur_dir == LEFT) {
                            cur_dir = DOWN;
                        }
                        else if (cur_dir == UP) {
                            cur_dir = RIGHT;
                        }
                        score++;
                    }
                    else if (map[cur.r][cur.c] == 3) {
                        if (cur_dir == RIGHT) {
                            cur_dir = DOWN;
                        }
                        else if (cur_dir == DOWN) {
                            cur_dir = UP;
                        }
                        else if (cur_dir == LEFT) {
                            cur_dir = RIGHT;
                        }
                        else if (cur_dir == UP) {
                            cur_dir = LEFT;
                        }
                        score++;
                    }
                    else if (map[cur.r][cur.c] == 4) {
                        if (cur_dir == RIGHT) {
                            cur_dir = UP;
                        }
                        else if (cur_dir == DOWN) {
                            cur_dir = LEFT;
                        }
                        else if (cur_dir == LEFT) {
                            cur_dir = RIGHT;
                        }
                        else if (cur_dir == UP) {
                            cur_dir = DOWN;
                        }
                        score++;
                    }
                    else if (map[cur.r][cur.c] == 5) {
                        cur_dir = (cur_dir + 2) % 4;
                        score++;
                    }
                    else if (map[cur.r][cur.c] >= 6 && map[cur.r][cur.c] <= 10) {
                        int warm_hole_num = map[cur.r][cur.c];
                        if (cur == warm_hole[warm_hole_num][0]) {
                            cur = warm_hole[warm_hole_num][1];
                        }
                        else {
                            cur = warm_hole[warm_hole_num][0];
                        }
                    }
                    cur = cur + dir[cur_dir];
                    if (cur.r < 0 || cur.r > N - 1 || cur.c < 0 || cur.c > N - 1) {
                        cur_dir = (cur_dir + 2) % 4;
                        cur = cur + dir[cur_dir];
                        score++;
                    }
                    if (cur == start) {
                        finish = true;
                        break;
                    }
                    if (map[cur.r][cur.c] == -1) {
                        finish = true;
                        break;
                    }
                }
                if (finish) {
                    answer = max(answer, score);
                }
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
    for(test_case = 1; test_case <= T; ++test_case) {
        input();
        printf("#%d ", test_case);
        solve();
	}

    return 0;
}
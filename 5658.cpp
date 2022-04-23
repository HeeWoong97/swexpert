#include <iostream>
#include <string>
#include <set>

using namespace std;

string password;
int N, K;
int pw_num;
set<int> check {};

void input(void)
{
    cin >> N >> K;
    cin >> password;
}

bool comp(int i, int j)
{
    return j < i;
}

int hex_to_int(string s)
{
    int num = 0;
    for (int i = 0; i < pw_num; i++) {
        num <<= 4;
        if (s[i] >= '0' && s[i] <= '9') {
            num |= (s[i] - '0');
        }
        else if (s[i] >= 'A' && s[i] <= 'F') {
            num |= (s[i] - 'A' + 10);
        }
    }
    return num;
}

void solve(void)
{
    pw_num = N / 4;
    for (int i = 0; i < pw_num; i++) {
        for (int j = 0; j < 4; j++) {
            check.insert(hex_to_int(password.substr(pw_num * j, pw_num)));
        }

        char first = password.at(0);
        password.erase(password.begin());
        password += first;
    }
    int cnt = 0;
    for (int i : check) {
        if (cnt == check.size() - K) {
            printf("%d\n", i);
            break;
        }
        cnt++;
    }
    
}

int main(void)
{
    int test_case;
	int T;

    freopen("input.txt", "rt", stdin);
    cin>>T;

	for(test_case = 1; test_case <= T; ++test_case) {
        set<int>().swap(check);
        input();
        printf("#%d ", test_case);
        solve();
	}

    return 0;
}
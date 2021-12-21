/*
https://www.acmicpc.net/problem/1003
*/

#include <iostream>
#include <vector>
using namespace std;

struct counter {
    int zeros;  // 0 의 갯 수
    int ones;   // 1 의 갯 수
};

counter operator+(const counter& lhs, const counter& rhs) {
    int zeros = lhs.zeros + rhs.zeros;
    int ones = lhs.ones + rhs.ones;

    return { zeros, ones };
}

ostream& operator<<(ostream& out, const counter& c) {
    out << c.zeros << " " << c.ones;
    return out;
}

/*
// 순환식(점화식)
counter f(int n) {
    if (n == 0) return { 1, 0 };
    else if (n == 1) return { 0, 1 };
    else return f(n - 1) + f(n - 2);
}
*/

// 다이나믹 프로그래밍(dynamic programming) bottom-up 방식
counter f(int n) {
    if (n == 0) return { 1, 0 };
    else if (n == 1) return { 0, 1 };
    else {
        int i = 2;
        counter pprev = { 1, 0 };
        counter prev = { 0, 1 };
        counter answer;

        while (true) {
            answer = pprev + prev;
            if (i == n) return answer;

            pprev = prev;
            prev = answer;
            i++;
        }
    }
}

int main()
{
    vector<int> v;
    int t; // 테스트 케이스 수
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        v.push_back(n);
    }

    for (int value : v) {
        cout << f(value) << '\n';
    }

    return 0;
}


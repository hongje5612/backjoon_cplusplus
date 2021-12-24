/*
    https://www.acmicpc.net/problem/9461
*/

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class p9461 {
public :
    static constexpr size_t SIZE = 100;

    p9461();
    ~p9461();

    long long solve(int);

private :
    long long* _dp;
};


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

    p9461 padovan;

    for (int n : v) {
        cout << padovan.solve(n) << endl;
    }

    return 0;
}

p9461::p9461()
{
    allocator<long long> alloc;

    _dp = alloc.allocate(SIZE);

    for (size_t i = 0; i < SIZE; i++) {
        _dp[i] = -1;
    }
}

p9461::~p9461()
{
    allocator<long long> alloc;

    alloc.deallocate(_dp, SIZE);
}

long long p9461::solve(int n)
{
    if (_dp[n - 1] != -1) return _dp[n - 1];

    if (n == 1) return _dp[n - 1] = 1;
    if (n == 2) return _dp[n - 1] = 1;
    if (n == 3) return _dp[n - 1] = 1;
    if (n == 4) return _dp[n - 1] = 2;
    if (n == 5) return _dp[n - 1] = 2;

    return _dp[n - 1] = solve(n - 1) + solve(n - 5);
}

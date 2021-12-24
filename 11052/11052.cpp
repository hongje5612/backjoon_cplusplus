/*
https://www.acmicpc.net/problem/11052
*/
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

class p11052 {
public :
    p11052();
    ~p11052();

    int solve() const;

private:
    /*
    i번째 카드에서 가지길 원하는 카드 수를 가지기 위해 지불해야 하는 비용의 최대값을 반환합니다.
    
    첫번째 인수는 i번째 카드 더미
    두번째 인수는 가지길 원하는 카드 수
    */
    int max(int, short) const;
    
private :
    short _n; // 민규가 구매하기를 원하는 카드의 수, 입력으로 주어 짐
    short* _prices; // 가격 정보, 입력으로 주어 짐
};

int main()
{
    p11052 problem;
    cout << problem.solve() << endl;
    return 0;
}

p11052::p11052()
{
    allocator<short> alloc;

    cin >> _n;
    _prices = alloc.allocate(_n);
    for (short i = 0; i < _n; i++) {
        cin >> _prices[i];
    }
}

p11052::~p11052() {
    allocator<short> alloc;
    alloc.deallocate(_prices, _n);
}

int p11052::solve() const
{
    return this->max(_n - 1, _n);
}

int p11052::max(int i, short n) const {
    if (i == 0) {
        return _prices[i] * n;
    }
    else {
        int nc = i + 1; // i 번째 카드 더미의 카드 수
        vector<int> v;
        v.push_back(this->max(i - 1, n));
        for (int j = 1; true; j++) {
            int t = nc * j;
            if (n - t >= 0) {
                v.push_back(this->max(i - 1, n - t) + _prices[i] * j);
            }
            else break;
        }

        auto it = max_element(v.begin(), v.end());
        return *it;
    }
}
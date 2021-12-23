/*
https://www.acmicpc.net/problem/1004
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct point {
    point(short, short);

    short x, y;
};

struct circle {
    circle(short, short, short);

    bool inside(const point&) const;

    bool inside(const circle&) const;

    short x, y, radius;
};

bool operator==(const circle& lhs, const circle& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.radius == rhs.radius;
}

class test_case {
public :
    test_case();
    test_case(const test_case&);
    test_case(test_case&&);

    test_case& operator=(const test_case&);
    test_case& operator=(test_case&&);

    ~test_case();

    vector<circle>::size_type solve() const;

private :
    vector<circle>* _planetary_system;
    point* _starting_point;
    point* _destination;
};


int main()
{
    short t; // 테스트 케이스 수;
    vector<test_case> v;

    cin >> t;
    for (int i = 0; i < t; i++) {
        test_case t;
        v.emplace(v.end(), move(t));
    }

    for (const test_case tc : v) {
        cout << tc.solve() << endl;
    }

    return 0;
}

circle::circle(short x, short y, short radius) : x(x), y(y), radius(radius)
{
}

bool circle::inside(const point& p) const
{
    int a = x - p.x;
    int b = y - p.y;

    return a * a + b * b <= (int)radius * (int)radius;
}

bool circle::inside(const circle& other) const
{
    return inside({ other.x, other.y });
}

point::point(short x, short y) : x(x), y(y)
{
}

test_case::test_case()
{
    _planetary_system = new vector<circle>;
    
    short x, y, radius;

    cin >> x >> y;
    _starting_point = new point(x, y);
    cin >> x >> y;
    _destination = new point(x, y);

    short n;
    cin >> n;

    for (short i = 0; i < n; i++) {
        cin >> x >> y >> radius;
        _planetary_system->push_back({ x, y, radius });
    }
}

test_case::test_case(const test_case& other)
{
    _planetary_system = new vector<circle>(other._planetary_system->begin(), other._planetary_system->end());

    _starting_point = new point(*(other._starting_point));
    _destination = new point(*(other._destination));
}

test_case::test_case(test_case&& other)
{
    _planetary_system = other._planetary_system;
    _starting_point = other._starting_point;
    _destination = other._destination;

    other._planetary_system = nullptr;
    other._starting_point = nullptr;
    other._destination = nullptr;
}

test_case& test_case::operator=(const test_case& other)
{
    delete _planetary_system;
    delete _starting_point;
    delete _destination;

    _planetary_system = new vector<circle>(other._planetary_system->begin(), other._planetary_system->end());
    _starting_point = new point(*(other._starting_point));
    _destination = new point(*(other._destination));

    return *this;
}

test_case& test_case::operator=(test_case&& other)
{
    delete _planetary_system;
    delete _starting_point;
    delete _destination;

    _planetary_system = other._planetary_system;
    _starting_point = other._starting_point;
    _destination = other._destination;

    other._planetary_system = nullptr;
    other._starting_point = nullptr;
    other._destination = nullptr;

    return *this;
}

test_case::~test_case()
{
    delete _planetary_system;
    delete _starting_point;
    delete _destination;
}

vector<circle>::size_type test_case::solve() const
{
    vector<circle> ps_s;    // 출발점을 포함하는 행성계
    vector<circle> ps_d;    // 도착점을 포함하는 해성계

    for (const auto& c : *_planetary_system) {
        if (c.inside(*_starting_point)) ps_s.push_back(c);
        if (c.inside(*_destination)) ps_d.push_back(c);
    }

    auto compare = [](const circle& lhs, const circle& rhs) {
        return lhs.radius < rhs.radius;
    };

    sort(ps_s.begin(), ps_s.end(), compare);
    sort(ps_d.begin(), ps_d.end(), compare);

    if (ps_s.size() == 0) return ps_d.size();
    if (ps_d.size() == 0) return ps_s.size();

    circle c1 = *ps_s.begin();
    circle c2 = *ps_d.begin();
    if (c1 == c2) return 0;

    c1 = *(ps_s.end() - 1);
    c2 = *(ps_d.end() - 1);
    if (!c1.inside(c2) && !c2.inside(c1)) return ps_s.size() + ps_d.size();
    
    if (c1.inside(c2)) {
        auto prev = ps_d.end();
        auto it = prev - 1;

        while (true) {
            if (it->inside(*_starting_point) && it->inside(*_destination)) {
                prev = it;
                it--;
            }
            else break;
        }

        vector<circle>::size_type answer = 0;

        for (const auto& c : ps_s) {
            if (c.radius < prev->radius) answer++;
        }

        for (const auto& c : ps_d) {
            if (c.radius < prev->radius) answer++;
        }
        return answer;
    }
    else if (c2.inside(c1)) {
        auto prev = ps_s.end();
        auto it = prev - 1;

        while (true) {
            if (it->inside(*_starting_point) && it->inside(*_destination)) {
                prev = it;
                it--;
            }
            else break;
        }

        vector<circle>::size_type answer = 0;

        for (const auto& c : ps_s) {
            if (c.radius < prev->radius) answer++;
        }

        for (const auto& c : ps_d) {
            if (c.radius < prev->radius) answer++;
        }
        return answer;
    }
}

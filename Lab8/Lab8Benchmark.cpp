#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct TSegment
{
    long long left;
    long long right;
    long long number;
};

bool operator==(const TSegment &lhs, TSegment &rhs) {
    return lhs.left == rhs.left && lhs.right == rhs.right;
}

int find(int m, int n, std::vector<TSegment> list, int j, int right, int value) {
    if(j == n) {
        if(right >= m) {
            return value;
        }
        return -1;
    }
    if(list[j].left >= m && list[j].right <= 0) {
        return find(m, n, list, j+1, right, value);
    }
    if(list[j].right > right && list[j].left < right) {
        int x = find(m, n, list, j + 1, list[j].right, value + 1);
        int y = find(m, n, list, j + 1, right, value);
        if(x == -1 && y == -1) return -1;
        if(x == -1) return y;
        if(y == -1) return x;
        return std::min(x, y);
    }
    else {
        return find(m, n, list, j+1, right, value);
    }
}

int main() { 
    long long n = 0, m = 0;
    long long globalLeft = 0;
    long long globalRight = 0;
    bool flag = true;
    std::cin >> n;
    if(n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<TSegment> list(n);
    std::vector<TSegment> answer;
    std::vector<TSegment> start;

    for(int i = 0; i < n; ++i) {
        std::cin >> list[i].left >> list[i].right;
        list[i].number = i;
    }
    std::cin >> m;
    if(m < 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    
    start = list;
    std::sort(list.begin(), list.end(),
    [](const TSegment v1, const TSegment v2) 
    { return (v1.left < v2.left); });


    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    using std::chrono::steady_clock;
    steady_clock::time_point startc = steady_clock::now();
    int i = -1;
    while(globalLeft < m && flag) {
        int istart = i + 1;
        globalRight = globalLeft;
        for(int j = i + 1; j < n; ++j) {
            if(list[j].left > globalLeft) {
                break;
            }
            if(list[j].right > globalRight) {
                i = j;
                globalRight = list[i].right;
            }
        }
        if(i == istart - 1) {
            flag = false;
        }
        else {
            globalLeft = list[i].right;
            for(int j = 0; j < n; ++j) {
                if(list[i].left == start[j].left && list[i].right == start[j].right) {
                    answer.push_back(start[j]);
                    break;
                }
            }
        }
    }
    steady_clock::duration dur = steady_clock::now() - startc;
    std::cerr << "Greedy algorithm time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
    if(globalLeft >= m) {
        std::cout << answer.size() << std::endl;

        std::sort(answer.begin(), answer.end(),
        [](const TSegment v1, const TSegment v2) 
        { return v1.number < v2.number; });
        for(int i = 0; i < answer.size(); ++i) {
            std::cout << answer[i].left << " " << answer[i].right << std::endl;
        }
    }
    else {
         std::cout << 0 << std::endl;
    }
    int min = 0;
    steady_clock::time_point startc2 = steady_clock::now();
    for(int i = 0; i < m; ++i) {
        int x = find(m, n, list, 0, 0, 0);
        if(x != -1) {
            if(min == 0) {
                min = x;
            }
            else {
                if(x != -1) {
                min = std::min(x, min);
                }
            }
        }
    }
    steady_clock::duration dur2 = steady_clock::now() - startc;
    std::cerr << "Recursive algorithm time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur2).count() << " ms\n";
    std::cout << min << std::endl;

}
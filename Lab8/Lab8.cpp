#include <iostream>
#include <vector>
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
}
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
    long long n, m;
    long long globalLeft = 0;
    long long globalRight = 0;
    std::cin >> n;
    std::vector<TSegment> list(n);
    std::vector<TSegment> answer;

    for(int i = 0; i < n; ++i) {
        std::cin >> list[i].left >> list[i].right;
        list[i].number = i;
    }
    std::cin >> m;
    
    std::sort(list.begin(), list.end(),
    [](const TSegment v1, const TSegment v2) 
    { return (v1.left < v2.left); });


    for(std::vector<TSegment>::iterator it = list.begin(); it != list.end() && globalLeft < m; it++) {
        if(globalLeft >= it->right ) continue;

        std::vector<TSegment>::iterator tmp = it;

        while( globalLeft >= it->left && it != list.end() ) {
            if( it->right >= globalRight ) {
                globalRight = it->right, tmp = it;
            }
            it++;
        }

        answer.push_back(*tmp);
        globalLeft = globalRight;
        if(globalLeft >= it->left ) {
            it--;
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
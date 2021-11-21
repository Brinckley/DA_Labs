#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>


int SubCounter(std::string str, std::string comp, int i, int value) {
    if(i == str.length()) {
        return value;
    }
    int x = 0;
    std::string compc = comp;
    compc.push_back(str[i]);
    bool k = false; 
    for(int j = 0; i < compc.length(); ++i) {
        if(compc[i] != compc[compc.length() - 1]) {
            k = true;
        }
    }
    if(k == false) value++;
    return SubCounter(str, comp, i + 1, value) + SubCounter(str, compc, i + 1, value) - value;
}

long long CountPalindromicSubsequences(std::string str) 
{ 
    int n = str.length(); 

    std::vector<std::vector<long long>> matrix(n + 1, std::vector<long long>(n + 1)); 
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= n; ++j) {
            if(i == j) { // palindromic subsequence of length 1 
                matrix[i][i] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }

    for (int i = 2; i <= n; ++i)  { 
        for (int j = 0; j < n; ++j) { 
            int x = i + j - 1; 
            if(x > n) {
                continue;
            }
            if (str[j] == str[x]) {
                matrix[j][x] = matrix[j][x - 1] + matrix[j + 1][x] + 1; 
            }
            else {
                matrix[j][x] = matrix[j][x - 1] + matrix[j + 1][x] - matrix[j + 1][x - 1]; 
            }
        } 
    }
  
    // highest right corner of the table 
    return matrix[0][n - 1]; 
} 

int main() 
{ 
    std::string str = "";
    std::cin >> str;
    long long length;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    using std::chrono::steady_clock;
    steady_clock::time_point start = steady_clock::now();
    if(str.length() == 0 || str.length() == 1) {
        length = str.length();
    }
    else {
        length = CountPalindromicSubsequences(str);
    }
    steady_clock::duration dur = steady_clock::now() - start;
    std::cerr << "DP time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
    std::cout << length << std::endl;

    //naiv
    steady_clock::time_point start2 = steady_clock::now();
    int x =  SubCounter(str, "", 0, 0);
    std::cout << "dfdfd " << x << std::endl;
    steady_clock::duration dur2 = steady_clock::now() - start2;
    std::cerr << "Nsaive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur2).count() << " ms\n";
} 
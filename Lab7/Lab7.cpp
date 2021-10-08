#include<iostream> 
#include<cstring> 
#include<vector>

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

    for (int i = 2; i < n; ++i)  { 
        for (int j = 0; j < n; ++j) { 
            int x = i + j; 
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
    if(str.length() == 0 || str.length() == 1) {
        length = str.length();
    }
    else {
        length = CountPalindromicSubsequences(str);
    }
    std::cout << length << std::endl;
} 
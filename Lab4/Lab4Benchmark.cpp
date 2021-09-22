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

const int MAX_WORD_SIZE = 16;

namespace NKMP {
    struct TPosition {
        int string;
        int number;
    };

    struct TWord {
        char word[MAX_WORD_SIZE];
        TPosition position;
    };

    bool operator==(const TWord &lhs, const TWord &rhs) {
        for (int i = 0; i < MAX_WORD_SIZE; ++i) {
            if (lhs.word[i] - rhs.word[i] != 0 && abs(lhs.word[i] - rhs.word[i]) != 32) {
                return false;
            } else {
                if (lhs.word[i] == 0 && rhs.word[i] == 0) {
                    return true;
                }
            }
        }
        return true;
    }

    int Max(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    std::vector<int> PrefixFiller(std::vector <TWord> sample) {
        int size = sample.size();
        std::vector<int> pi(size);

        for (int i = 1; i < size; ++i) {
            int j = 0;
            while (i + j < size && sample[j] == sample[i + j]) {
                pi[i + j] = Max(pi[i + j], j + 1);
                j++;
            }
        }
        return pi;
    }

    std::vector <TPosition> KMP(const std::vector <TWord> &sample, const std::vector <TWord> &text) {
        std::vector <TPosition> found;
        std::vector<int> pi = PrefixFiller(sample);

        int textLength = text.size();
        int sampleLength = sample.size();

        if (textLength < sampleLength) {
            return found;
        }

        int i = 0;
        int j = 0;

        while (i < textLength) {
            if (sample[j] == text[i]) {
                ++j;
                ++i;
            }
            if (j == sampleLength) {
                found.push_back(text[i - j].position);
                j = pi[j - 1];
            } else if (i < textLength && !(sample[j] == text[i])) {
                if (j != 0) {
                    j = pi[j - 1];
                } else {
                    ++i;
                }
            }
        }
        return found;
    }
}

using namespace NKMP;
void SetZero(TWord& tmp) {
    for (int i = 0; i < MAX_WORD_SIZE; ++i) {
        tmp.word[i] = 0;
    }
}


int main() {
    std::vector<TWord> text;
    std::vector<TWord> sample;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    using std::chrono::steady_clock;

    std::string textS;
    std::string sampleS;

    TWord tmp;
    SetZero(tmp);
    char switcher = getchar();
    int point = 0;
    while (switcher != '\n') {
        if(switcher == ' ') {
            if(tmp.word[0] != 0) {
                sample.push_back(tmp);
                if(sampleS.size() > 0 && sampleS[sampleS.size() - 1] != ' ') {
                    sampleS += ' ';
                }
                SetZero(tmp);
            }
            point = 0;
            switcher = getchar();
        }
        else {
            tmp.word[point] = switcher;
            sampleS += switcher;
            ++point;
            switcher = getchar();
        }

    }
    sample.push_back(tmp);
    SetZero(tmp);

    int wordCounter = 1;
    int stringCounter = 1;
    point = 0;

    switcher = getchar();
    while (switcher != EOF) {
        if (switcher == ' ') {
            tmp.position.number = wordCounter;
            tmp.position.string = stringCounter;
            point = 0;

            if(textS.size() > 0 && textS[textS.size() - 1] != ' ') {
                textS += ' ';
            }
            if (tmp.word[0] != 0) {
                text.push_back(tmp);
                
                SetZero(tmp);
                ++wordCounter;
            }
            switcher = getchar();
        }
        else if(switcher == '\n') {
            tmp.position.number = wordCounter;
            tmp.position.string = stringCounter;
            ++stringCounter;
            wordCounter = 1;
            point = 0;

            if(textS.size() > 0 && textS[textS.size() - 1] != ' ') {
                textS += ' ';
            }
            if (tmp.word[0] != 0) {
                text.push_back(tmp);
                SetZero(tmp);
            }
            switcher = getchar();
        }
        else {
            tmp.word[point] = switcher;
            ++point;
            textS += switcher;
            switcher = getchar();
        }
    }
    text.push_back(tmp);
    using std::chrono::steady_clock;
    steady_clock::time_point start = steady_clock::now();
    std::vector<TPosition> answer = KMP(sample, text);
    steady_clock::duration dur = steady_clock::now() - start;
    std::cerr << "KMP time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
    for (int i = 0; i < answer.size(); ++i) {
        printf("%d, %d\n", answer[i].string, answer[i].number);
    }

    start = steady_clock::now();
    bool found = true;
    while (found) {
        size_t pos = textS.find(sampleS);
        if(pos != std::string::npos) {
            textS[pos] = ' ';
        }
        else {
            found = false;
        }
    }
    dur = steady_clock::now() - start;
    std::cerr << "String time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";

}
/*
adskj jklaakjl alsadjk
gflgk adskj jklaakjl alsadjkk falf adskj jklaakjl alsadjks lsfdmds adskj jklaakjl alsadjk lkdakl lsdf rs adskj jklaakjl alsadjk
adskj jklaakjl alsadjk
gflgk adskj jklaakjl alsadjkk falf adskj jklaakjl alsadjks lsfdmds adskj jklaakjl alsadjk lkdakl lsdf rs adskj jklaakjl alsadjk
adskj jklaakjl alsadjk
gflgk adskj jklaakjl alsadjkk falf adskj jklaakjl alsadjks lsfdmds adskj jklaakjl alsadjk lkdakl lsdf rs adskj jklaakjl alsadjk
adskj jklaakjl alsadjk
gflgk adskj jklaakjl alsadjkk falf adskj jklaakjl alsadjks lsfdmds adskj jklaakjl alsadjk lkdakl lsdf rs adskj jklaakjl alsadjk

*/
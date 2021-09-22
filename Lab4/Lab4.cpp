#include <iostream>
#include <cstdio>
#include <vector>

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

        if(textLength < sampleLength) {
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
    for(int i = 0; i < MAX_WORD_SIZE; ++i) {
        tmp.word[i] = 0;
    }
}

int main() {
    std::vector<TWord> text;
    std::vector<TWord> sample;

    TWord tmp;
    SetZero(tmp);
    char switcher = getchar();
    int point = 0;
    while (switcher != '\n') {
        if(switcher == ' ') {
            if(tmp.word[0] != 0) {
                sample.push_back(tmp);
                SetZero(tmp);
            }
            point = 0;
            switcher = getchar();
        }
        else {
            tmp.word[point] = switcher;
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

            if(tmp.word[0] != 0) {
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

            if(tmp.word[0] != 0) {
                text.push_back(tmp);
                SetZero(tmp);
            }
            switcher = getchar();
        }
        else {
            tmp.word[point] = switcher;
            ++point;
            switcher = getchar();
        }
    }
    text.push_back(tmp);

    std::vector<TPosition> answer = KMP(sample, text);
    for(int i = 0; i < answer.size(); ++i) {
        printf("%d, %d\n", answer[i].string, answer[i].number);
    }


}

/*
Cat Dog caT doG bird
CAT dog CaT Dog Cat DOG bird CAT
dog cat dog bird

 */
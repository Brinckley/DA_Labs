#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

typedef unsigned long long TUll;

const int MAX_KEY_SIZE = 20;
const int MAX_NUMBER = 11;
const int FIRST_MAX_SIZE = 10;
const int ZERO = 0;
const int ONE = 1;
const int ADDITIONAL_ARRAY_LENGTH = 2;
const char DEFAULT_CHAR_ITEM = '-';

struct TItem {
	char key[MAX_KEY_SIZE]{ DEFAULT_CHAR_ITEM };
	int delta;
	TUll value;
};

namespace NVector {

	class TVector {

	public:
		TVector() {
			size = ZERO;
			maxSize = FIRST_MAX_SIZE;
			mvector = 0;
		}

		void PushBack(TItem &tmp) {
			if (size == ZERO) {
				maxSize = FIRST_MAX_SIZE;
				mvector = new TItem[maxSize];
				mvector[ZERO] = tmp;
				size = ONE;
				return;
			}
			if (size == maxSize) {
				maxSize *= ADDITIONAL_ARRAY_LENGTH;
				TItem* tmpvector = new TItem[maxSize];
				for (int i = 0; i < size; ++i) {
					tmpvector[i] = mvector[i];
				}
				delete[] mvector;
				mvector = tmpvector;
			}
			mvector[size] = tmp;
			size++;
		}

		void Output() {
			for (int i = 0; i < size; ++i) {
				printf("%s  %llu\n", mvector[i].key, mvector[i].value);
			}
		}

		int Size() {
			return size;
		}

		~TVector() {
			delete[] mvector;
			this->mvector = nullptr;
		}

		void RadixSort() {
			for (int i = MAX_KEY_SIZE - 1; i >= 0; --i) {
				TItem* out = new TItem[size];
				int count[MAX_NUMBER] = { ZERO };

				for (int j = 0; j < size; ++j) {
					if (i - mvector[j].delta >= 0) {
						count[mvector[j].key[i - mvector[j].delta] - '0'] ++;
					}
					else {
						count[ZERO] ++;
					}
				}

				for (int j = 1; j < MAX_NUMBER; ++j) {
					count[j] += count[j - 1];
				}

				for (int j = size - 1; j >= 0; --j) {
					if (i - mvector[j].delta >= ZERO) {
						out[count[mvector[j].key[i - mvector[j].delta] - '0'] - 1] = mvector[j];
						count[mvector[j].key[i - mvector[j].delta] - '0'] --;
					}
					else {
						out[count[ZERO] - 1] = mvector[j];
						count[ZERO] --;
					}
				}
				for (int k = 0; k < size; ++k) {
					mvector[k] = out[k];
				}
				delete[] out;
			}
		}


	private:
		int size;
		int maxSize;
		TItem* mvector;
	};

}

using namespace NVector;

bool operator<(const TItem &lhs, const TItem &rhs) {
	for(int i = 0; i < MAX_KEY_SIZE; ++i) {
		if(lhs.key[i] == ZERO && rhs.key[i] == ZERO) {
           return false;
        }
        if(lhs.key[i] == ZERO && rhs.key[i] != ZERO) {
            return true;
        }
        if(lhs.key[i] != ZERO && rhs.key[i] == ZERO) {
            return false;
        }
		if(lhs.key[i] - rhs.key[i] != ZERO) {
			return lhs.key[i] - rhs.key[i] < ZERO;
		}
	}
	return false;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<TItem> vector2;

    TVector vector;
	bool end = true;
	do {
		TItem tmp;
		for (int i = 0; i < MAX_KEY_SIZE; ++ i) {
			tmp.key[i] = DEFAULT_CHAR_ITEM;
		}
		tmp.value = ZERO;
		tmp.delta = ZERO;
		if (scanf("%s %llu", tmp.key, &tmp.value) != EOF) {
			for (int i = 0; i < MAX_KEY_SIZE; ++ i) {
				if (tmp.key[i] == ZERO) {
					tmp.delta = MAX_KEY_SIZE - i;
					break;
				}
			}
			vector.PushBack(tmp);
			vector2.push_back(tmp);
		}
		else
		{
			end = false;
		}
	} while (end);

    using std::chrono::steady_clock;
    steady_clock::time_point start = steady_clock::now();
    vector.RadixSort();
    steady_clock::duration dur = steady_clock::now() - start;
    std::cerr << "Radix Sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
    steady_clock::time_point start2 = steady_clock::now();;
    stable_sort(vector2.begin(),vector2.end());
    steady_clock::duration dur2 = steady_clock::now() - start2;
    std::cerr << "Stable sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur2).count() << " ms\n";
    vector.Output();
}

#include <iostream>
#include <typeinfo>

typedef unsigned long long TUll;

const int MAX_KEY_SIZE = 20;
const int MAX_NUMBER = 11;
const int FIRST_MAX_SIZE = 10;
const int ZERO = 0;
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
			size = 0;
			maxSize = FIRST_MAX_SIZE;
			mvector = 0;
		}

		void PushBack(TItem &tmp) {
			if (size == ZERO) {
				maxSize = FIRST_MAX_SIZE;
				mvector = new TItem[maxSize];
				mvector[ZERO] = tmp;
				size = 1;
				return;
			}
			if (size == maxSize) {
				maxSize *= 2;
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
					if (i - mvector[j].delta >= 0) {
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

int main()
{
	TVector vector;
	bool end = true;
	do {
		TItem tmp;
		for (int i = 0; i < MAX_KEY_SIZE; ++ i) {
			tmp.key[i] = DEFAULT_CHAR_ITEM;
		}
		tmp.value = 0;
		tmp.delta = 0;
		if (scanf("%s %llu", tmp.key, &tmp.value) != EOF) {
			for (int i = 0; i < MAX_KEY_SIZE; ++ i) {
				if (tmp.key[i] == 0) {
					tmp.delta = MAX_KEY_SIZE - i;
					break;
				}
			}
			vector.PushBack(tmp);
		}
		else
		{
			end = false;
		}
	} while (end);

	vector.RadixSort();
	vector.Output();

	return 0;

}
/*
0 15304086347272597642
18446744073709551615  8332868096657407680
0 13545671047587467688
18446744073709551615  9944245427658561165
*/
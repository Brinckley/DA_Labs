//
// Created by alex on 16.03.2021.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

namespace NBigInteger {

    const int BASE = 10000;
    const int DIGIT_LENGTH = 4;

    int MISTAKE = 0;

    class BigInteger {

    public:
        std::vector<int> mnumber;

        BigInteger() {

        }

        BigInteger(int n) {
            mnumber.resize(n, 0);
        }

        BigInteger(const std::string &str) {
            int count = 0;
            while (count < str.size() - 1 and str[count] == '0') {
                count++;
            }
            if (count < str.size()) {
                mnumber.resize(str.size() / DIGIT_LENGTH + 1);
                int n = str.size();
                for (int i = 0; i < mnumber.size(); i++) {
                    int tmp_digit = 0;
                    for (int j = 0; j < DIGIT_LENGTH; j++) {
                        int index = n - (i + 1) * DIGIT_LENGTH + j;
                        if (index >= 0) {
                            tmp_digit = tmp_digit * 10 + str[index] - '0';
                        }
                    }
                    mnumber[i] = tmp_digit;
                }
                while (mnumber.size() > 1 and mnumber.back() == 0) {
                    mnumber.pop_back();
                }
            }
        }

        void DeleteZeroes() {
            while (mnumber.size() > 1 && mnumber.back() == 0) {
                mnumber.pop_back();
            }
        }

        void operator=(const BigInteger &num2) {
            mnumber = num2.mnumber;
        }

    private:

    };


    std::ostream &operator<<(std::ostream &stream, const BigInteger &num)
    {
        int n = num.mnumber.size();
        if (!n)
            return stream;
        stream << num.mnumber[n - 1];
        for (int i = n - 2; i >= 0; --i)
            stream << std::setfill('0') << std::setw(DIGIT_LENGTH) << num.mnumber[i];

        return stream;
    }

    bool operator==(const BigInteger &lhs, const BigInteger &rhs) {
        if (lhs.mnumber.size() != rhs.mnumber.size()) {
            return false;
        }
        for (int i = 0; i < lhs.mnumber.size(); ++i) {
            if (lhs.mnumber[i] != rhs.mnumber[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>(const BigInteger &lhs, const BigInteger &rhs) {
        if (lhs.mnumber.size() != rhs.mnumber.size()) {
            return lhs.mnumber.size() > rhs.mnumber.size();
        }
        for (int i = lhs.mnumber.size() - 1; i > -1; --i) {
            if (lhs.mnumber[i] != rhs.mnumber[i]) {
                return lhs.mnumber[i] > rhs.mnumber[i];
            }
        }
        return false;
    }

    bool operator<(const BigInteger &lhs, const BigInteger &rhs) {
        if (lhs.mnumber.size() != rhs.mnumber.size()) {
            return lhs.mnumber.size() < rhs.mnumber.size();
        }
        for (int i = lhs.mnumber.size() - 1; i > -1; --i) {
            if (lhs.mnumber[i] != rhs.mnumber[i]) {
                return lhs.mnumber[i] < rhs.mnumber[i];
            }
        }
        return false;
    }

    BigInteger operator+(const BigInteger &lhs, const BigInteger &rhs) {
        int k = 0;
        int size = std::max(lhs.mnumber.size(), rhs.mnumber.size());
        BigInteger result(size);
        for (int i = 0; i < size; ++i) {
            int u = 0;
            int v = 0;
            if(lhs.mnumber.size() > i) {
                u = lhs.mnumber[i];
            }
            if(rhs.mnumber.size() > i) {
                v = rhs.mnumber[i];
            }
            int w = (v + u + k) % BASE;
            k = (v + u + k) / BASE;
            result.mnumber[i] = w;
        }
        if (k) {
            result.mnumber.push_back(k);
        }
        return result;
    }

    BigInteger operator-(const BigInteger &lhs, const BigInteger &rhs) {
        if(lhs < rhs) {
            MISTAKE = 1;
            return BigInteger("0");
        }
        BigInteger result = lhs;
        for (int i = std::max(result.mnumber.size(), rhs.mnumber.size()) - 1; i > -1; --i) {
            int u = 0;
            int v = 0;
            if(lhs.mnumber.size() > i) {
                u = lhs.mnumber[i];
            }
            if(rhs.mnumber.size() > i) {
                v = rhs.mnumber[i];
            }
            if (u >= v) {
                result.mnumber[i] = u - v;
            } else {
                for (int j = i + 1; j < std::max(result.mnumber.size(), rhs.mnumber.size()); ++j) {
                    if (result.mnumber[j] > 0) {
                        result.mnumber[j]--;
                        for (int k = j - 1; k > i; --k) {
                            result.mnumber[k] += BASE - 1;
                        }
                        result.mnumber[i] = BASE + u - v;
                        break;
                    }
                }
            }
        }
        result.DeleteZeroes();
        return result;
    }


    BigInteger operator*(const BigInteger &lhs, const BigInteger &rhs) {
        BigInteger result("0");
        result.mnumber.clear();
        result.mnumber.resize(lhs.mnumber.size() * rhs.mnumber.size() + 1, 0);
        for (int j = 0; j < rhs.mnumber.size(); ++j) {
            if (rhs.mnumber[j] == 0) {
                continue;
            }
            int k = 0;
            for (int i = 0; i < lhs.mnumber.size(); ++i) {
                int tmp = lhs.mnumber[i] * rhs.mnumber[j] + k + result.mnumber[i + j];
                result.mnumber[i + j] = tmp % BASE;
                k = tmp / BASE;
            }
            result.mnumber[j + lhs.mnumber.size()] = k;
        }
        result.DeleteZeroes();
        return result;
    }


    BigInteger operator*(const BigInteger &bnum, const int inum) {
        int k = 0;
        int n = bnum.mnumber.size();
        BigInteger result(n + 1);

        for(int i = 0; i < n; ++i) {
            int tmp = inum * bnum.mnumber[i] + k + result.mnumber[i];
            result.mnumber[i] = tmp % BASE;
            k = tmp / BASE;
        }
        result.mnumber[n] = k;
        //result.DeleteZeroes();
        return result;
    }

//    bool CheckDiv(const BigInteger &num, const BigInteger &main, int j) {
//        if(num.mnumber.size() != (main.mnumber.size() - j - 1)) {
//            return num.mnumber.size() > main.mnumber.size();
//        }
//        int k = 0;
//        for(int i = j; j < main.mnumber.size();++j) {
//            if(num.mnumber[k] != main.mnumber[i]) {
//                return num.mnumber[k] > main.mnumber[i];
//            }
//            ++k;
//        }
//        return false;
//    }

    /*
     190519559127547774527068
     000000000000122555565658
     /
     534611045820
     */


/*
    void LevelUp()
    {
        for (int i = amount;i>=1;i--)
            digits[i] = digits[i-1];
        if (digits[amount])
            amount++;
    }

    BigInteger operator/(const BigInteger &a, const BigInteger &b)
    {
        BigInteger res;
        BigInteger curValue;
        for (int i = a.mnumber.size() - 1; i >= 0; i--)
        {
            curValue.LevelUp(); // * osn
            curValue.digits[0] = a.digits[i];
            // подбираем максимальное число x, такое что b * x <= curValue
            int x = 0;
            int l = 0, r = osn;
            while (l <= r)
            {
                int m = (l + r) >> 1;
                BigInt cur = b * m;
                if (cur <= curValue)
                {
                    x = m;
                    l = m+1;
                }
                else
                    r = m-1;
            }
            res.digits[i] = x;
            curValue = curValue - b * x;
        }

        // избавляемся от лидирующих нулей
        res.DeleteZeroes();
        return res;
    }

*/

    BigInteger operator/(const BigInteger &lhs, const BigInteger &rhs) {
        if(rhs == BigInteger("1")) {
            return lhs;
        }
        if(rhs == BigInteger("0")) {
            MISTAKE = 1;
            return BigInteger("0");
        }
        if(lhs < rhs) {
            return BigInteger("0");
        }
        if(rhs == lhs) {
            return BigInteger("1");
        }
///////////////////
        if(rhs.mnumber.size() <= 1) {
            int b = rhs.mnumber.back();
            BigInteger res(lhs.mnumber.size());
            int carry = 0;
            for(int i = lhs.mnumber.size() - 1; i >= 0; --i) {
                int cur = lhs.mnumber[i] + carry  * 1ll * BASE;
                res.mnumber[i] = cur / b;
                carry = cur % b;
            }
            res.DeleteZeroes();
            return res;
        }/////////////

        //Normalize
        int d = BASE / (rhs.mnumber.back() + 1);
        BigInteger q;
        BigInteger un = lhs * d;
        BigInteger vn = rhs * d;
        vn.DeleteZeroes();

        // std::cout << "Un:  " << un << std::endl;
        // std::cout << "Vn:  " << vn << std::endl;

        int n = vn.mnumber.size();
        int m = un.mnumber.size() - n;

        for(int j = m - 1; j >= 0; --j) {
            int q_ = (un.mnumber[j + n] * BASE + un.mnumber[j + n - 1]) / vn.mnumber[n - 1];
            int r_ = (un.mnumber[j + n] * BASE + un.mnumber[j + n - 1]) % vn.mnumber[n - 1];

            //std::cout << "*****  q: " << q_ << std::endl;
            //std::cout << "*****  r: " << r_ << std::endl;
            while ((r_ < BASE) && (q_ == BASE || ((q_ * vn.mnumber[n - 2]) > (BASE * r_ + un.mnumber[j + n - 2])))) {
                q_--;
                r_ += vn.mnumber[n - 2];
            }

            //compare (u(j + n) ....... u(j)) and q * (v(n - 1) ........ v(0))
            BigInteger compare = vn * q_;

            compare.DeleteZeroes();
            BigInteger copyU(un.mnumber.size() - j);
            for(int z = 0; z < copyU.mnumber.size(); ++z) {
                copyU.mnumber[z] = un.mnumber[j + z];
            }
            //std::cout << "----" << copyU << std::endl;
            if(compare > copyU) {
                q_--;
                //std::cout << "In check --- " << q_ << std::endl;
            }
            BigInteger q_vn = vn * q_;
            q_vn.DeleteZeroes();
            //std::cout << "q_vn --  " << q_vn << std::endl;
            for (int i = 0; i < q_vn.mnumber.size(); ++i) {
                if (un.mnumber[i + j] >= q_vn.mnumber[i]) {
                    un.mnumber[j + i] -= q_vn.mnumber[i];
                } else {
                    int zeroWalker = i + j + 1;
                    while (un.mnumber[zeroWalker] == 0) {
                        zeroWalker++;
                    }
                    un.mnumber[zeroWalker]--;
                    for (int k = zeroWalker - 1; k > i + j; k--) {
                        un.mnumber[k] = BASE - 1;
                    }
                    un.mnumber[i + j] = BASE + un.mnumber[i + j] - q_vn.mnumber[i];
                }
            }
            un.DeleteZeroes();
            if (q_ >= BASE) {
                q.mnumber.push_back(q_ / BASE);
                q.mnumber.push_back(q_ % BASE);
            }
            else {
                q.mnumber.push_back(q_);
            }
        }
        std::reverse(q.mnumber.begin(), q.mnumber.end());
        q.DeleteZeroes();
        return q;
    }

    BigInteger operator^(BigInteger &lhs, BigInteger &rhs) {
        BigInteger lhsNew = lhs;
        BigInteger two("2");
        BigInteger one("1");
        BigInteger result("1");
        while (!(rhs.mnumber.size() == 1 && rhs.mnumber[0] == 0)) {
            if (rhs.mnumber[0] % 2 == 0) {
                lhsNew = lhsNew * lhsNew;
                rhs = rhs / two;
            }
            else {
                result = result * lhsNew;
                rhs = rhs - one;
            }
        }
        result.DeleteZeroes();
        return result;
    }
}

using namespace NBigInteger;

int main() {
    std::string str1, str2;
    char method;

    while(std::cin >> str1 >> str2 >> method) {
        BigInteger number1(str1);
        BigInteger number2(str2);
        if(method == '+') {
            BigInteger sum = number1 + number2;
            std::cout << sum << std::endl;
        }
        else if(method == '-') {
            BigInteger subt = number1 - number2;
            if(MISTAKE == 0) {
                std::cout << subt << std::endl;
            }
            else {
                std::cout << "Error" << std::endl;
            }
        }
        else if(method == '*') {
            BigInteger multi = number1 * number2;
            if(MISTAKE == 0) {
                std::cout << multi << std::endl;
            }
            else {
                std::cout << "Error" << std::endl;
            }
        }
        else if(method == '^') {
            if(number1 == BigInteger("0") && number2 == BigInteger("0")) {
                std::cout << "Error" << std::endl;
                continue;
            }
            BigInteger pow = number1 ^ number2;
            std::cout << pow << std::endl;

        }
        else if(method == '/') {
            BigInteger div = number1 / number2;
            if(MISTAKE == 0) {
                std::cout << div << std::endl;
            }
            else {
                std::cout << "Error" << std::endl;
            }
        }
        else if(method == '>') {
            if(number1 > number2) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
            }
        }
        else if(method == '<') {
            if(number1 < number2) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
            }
        }
        else if(method == '=') {
            if(number1 == number2) {
                std::cout << "true" << std::endl;
            }
            else {
                std::cout << "false" << std::endl;
            }
        }
        MISTAKE = 0;
    }
}

/*
9876543210
1234567895
*
12193263160646242950

1000000000000
1000000
/
1038291
 102837191927
 -
 12193263160646242950
1234567895
/
 * */

/*
122555565658
1554556564646
*
190519559127547774527068
190519559127547774527068
1554556564646
/
122555565658
190519559127547774527068
000000000000000001554556564646
/
122555565658
190519559127547774527068
000000000000122555565658
/
534611045820
*/
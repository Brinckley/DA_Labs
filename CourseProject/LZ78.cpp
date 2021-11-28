#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::map;
using std::vector;
using std::endl;

namespace NLZ78 {
    const long long BORDER = 65535; //unsigned short
    const long long FIRST_PART = 65535 / 2;

    struct TNode {
        int pos;
        char next;

        TNode(){}

        TNode(int pos, char next) {
            this->pos = pos;
            this->next = next;
        }
    };

    class TArchiver {

    public:
        vector<TNode> Encode(string &text) {
            map<string, int> dictionary;
            vector<TNode> encoded;
            int n = text.length();
            string buffer = "";
            char last;

            for(int i = 0; i < n; ++i) { // O(n)
                if(dictionary.find(buffer + text[i]) != dictionary.end()) { //O(log n)
                    buffer += text[i];
                }
                else {
                    encoded.push_back(TNode(dictionary[buffer], text[i]));
                    if(dictionary.size() >= BORDER) {
                        dictionary.clear();
                    }
                    dictionary[buffer + text[i]] = dictionary.size();
                    buffer = "";
                }
            }
            if(buffer != "") {
                last = buffer[buffer.length() - 1];
                buffer.pop_back();
                encoded.push_back(TNode(dictionary[buffer], last));
            }
            return encoded;
        }

        string Decode(vector<TNode> &pairs) {
            vector<string> dictionary;
            dictionary.push_back("");
            string decoded = "";

            for(int i = 0; i < pairs.size(); ++i) { // O(m)
                string word = dictionary[pairs[i].pos] + pairs[i].next; //O(n)
                decoded += word;
                if(dictionary.size() >= BORDER) {
                    dictionary.erase(dictionary.begin() + 1, dictionary.begin() + FIRST_PART);
                }
                dictionary.push_back(word);
            }

            return decoded;
        }
    };
}

using namespace NLZ78;

void Display(vector<TNode> &v) {
    for(int i = 0; i < v.size(); ++i) {
        cout << "<" << v[i].pos << ", " << v[i].next << ">" << endl;
    }
}

void Display(string &text) {
    cout << text << endl;
}

int main() {
    TArchiver archiver;
    string command;
    cin >> command;
    if(command == "compress") {
        string decoded;
        cin >> decoded;
        vector<TNode> encoded = archiver.Encode(decoded);
        Display(encoded);
    }
    if(command == "decompress") {
        vector<TNode> encoded;
        string firstPart;
        string secondPart;
        while (cin >> firstPart >> secondPart) {
            firstPart.erase(0,1);
            firstPart.pop_back();
            int pos = std::stoi(firstPart);
            char next = secondPart[0];
            encoded.push_back(TNode(pos, next));
        }
        string decoded = archiver.Decode(encoded);
        Display(decoded);
    }
}
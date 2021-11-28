#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>

using std::cout;
using std::cin;
using std::string;
using std::map;
using std::vector;
using std::endl;

namespace NLZ78 {
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
        vector<TNode> Encode(string text) {
            map<string, int> dictionary;
            vector<TNode> encoded;
            int n = text.length();
            string buffer = "";
            char last;

            for(int i = 0; i < n; ++i) {
                if(dictionary.find(buffer + text[i]) != dictionary.end()) {
                    buffer += text[i];
                }
                else {
                    encoded.push_back(TNode(dictionary[buffer], text[i]));
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

        string Decode(vector<TNode> pairs) {
            vector<string> dictionary;
            dictionary.push_back("");
            string decoded = "";

            for(int i = 0; i < pairs.size(); ++i) {
                string word = dictionary[pairs[i].pos] + pairs[i].next;
                decoded += word;
                dictionary.push_back(word);
            }

            return decoded;
        }
    };
}

using namespace NLZ78;

void Display(vector<TNode> v) {
    for(int i = 0; i < v.size(); ++i) {
        cout << "<" << v[i].pos << ", " << v[i].next << ">" << endl;
    }
}

void Display(string text) {
    cout << text << endl;
}

int main() {
    TArchiver archiver;
    string command;
    cin >> command;
    if(command == "compress") {
        string decoded;
        cin >> decoded;
        using std::chrono::steady_clock;
        steady_clock::time_point start = steady_clock::now();
        vector<TNode> encoded = archiver.Encode(decoded);
        steady_clock::duration dur = steady_clock::now() - start;
        std::cerr << "Compression time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
        Display(encoded);
    }
    if(command == "decompress") {
        vector<TNode> encoded;
        string firstPart;
        string secondPart;
        using std::chrono::steady_clock;
        steady_clock::time_point start = steady_clock::now();
        while (cin >> firstPart >> secondPart) {
            firstPart.erase(0,1);
            firstPart.pop_back();
            int pos = std::stoi(firstPart);
            char next = secondPart[0];
            encoded.push_back(TNode(pos, next));
        }
        string decoded = archiver.Decode(encoded);
        steady_clock::duration dur = steady_clock::now() - start;
        std::cerr << "Decompression time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
        Display(decoded);
    }
}
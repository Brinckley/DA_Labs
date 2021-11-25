#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <chrono>

using std::cin;
using std::cout;
using std::map;
using std::string;

class TNode
{
public:
    std::map<char, TNode *> child;
    std::string::iterator begin, end;
    TNode *suffixLink;
    std::set <int> number_string;
    TNode(std::string::iterator begin, std::string::iterator end);
    ~TNode() {};
};

struct TLCSubstring {
    int length;
    std::vector <TNode *> spath;
    TNode * start;
    TNode * end;
};

class TSuffixTree{
public:
    std::string str1;
    std::string str2;

    TNode *root;
    TNode *activeNode;
    TNode *link;
    std::string::iterator activeEdge;

    int numStr;
    int remaining;
    int activeLength;

    int maxLength;
    std::vector <TLCSubstring> answer;
    TLCSubstring ans;

    TSuffixTree(std::string n_str, std::string n_str2);
    void DeleteTree(TNode *node);
    void Add(std::string::iterator it);
    int Markup(TNode * node);
    void FindMaxLength(TNode * node, int walk);
    void FindLongestSubstrings(TNode * node, int walk, TNode * begin, std::vector <TNode *> path_to_sub);
};

TNode::TNode(std::string::iterator begin, std::string::iterator end) {
    this->begin = begin;
    this->end = end;
    this->suffixLink = nullptr;
}

void TSuffixTree::FindMaxLength(TNode *node, int i) {
    if (node->number_string.size() == 2) {
        if (node != root) {
            i += distance(node->begin, node->end) + 1;
            if (i > maxLength) {
                maxLength = i;
            }
        }
        for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); it++) {
            TNode *next_child = it->second;
            FindMaxLength(next_child, i);
        }
    }
}


void TSuffixTree::FindLongestSubstrings(TNode *node, int walk, TNode *begin, std::vector <TNode *> path_to_sub) {
    if (node->number_string.size() == 2) {
        if(node != root) {

            if(walk == 0) {
                path_to_sub.clear();
            }
            path_to_sub.push_back(node);

            walk += distance(node->begin, node->end) + 1;
            if (walk == maxLength) {
                ans.spath = path_to_sub;
                ans.length = walk;
                answer.push_back(ans);
                path_to_sub.clear();
            }
        }
        for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); it++) {
            TNode *next_child = it->second;
            FindLongestSubstrings(next_child, walk, begin, path_to_sub);
        }
    }
}


int TSuffixTree::Markup(TNode * node) {
    if(node->begin != str1.end()) {
        if(*node->begin == '#')
            node->number_string.insert(1);
        else if(*node->begin == '$')
            node->number_string.insert(2);
    }
    if(distance(node->begin, node->end) > 0) {
        int size_str = str2.size();
        if(distance(node->begin, node->end) > size_str)
            node->number_string.insert(1);
        else if(node->end == str1.end())
            node->number_string.insert(2);
    }


    for (std::map<char, TNode *>::iterator it2 = node->child.begin(); it2 != node->child.end(); it2++) {
        TNode *next_child = it2->second;
        int ans = Markup(next_child);
        if (node->number_string.size() < 2) {
            if (ans == 3) {
                node->number_string.insert(1);
                node->number_string.insert(2);
            }
            if (ans == 1) {
                node->number_string.insert(1);
            }
            if (ans == 2) {
                node->number_string.insert(2);
            }
        }
    }
    if(node->number_string.size() == 2) {
        return 3;
    }
    if(node->number_string.size() == 1) {
        if(*node->number_string.begin() == 1) {
            return 1;
        }
        if(*node->number_string.begin() == 2) {
            return 2;
        }
    }
    return 0;
}

TSuffixTree::TSuffixTree(std::string tstr1, std::string tstr2) {
    str1 = tstr1;
    str2 = tstr2;
    ans.start = nullptr;
    ans.end = nullptr;
    numStr = 1;
    activeEdge = str1.begin();
    root = new TNode(str1.end(), str1.end());
    root->suffixLink = root;
    activeNode = root;
    link = root;
    remaining = 0;
    activeLength = 0;
    ans.length = 0;
    maxLength = 0;

    for(std::string::iterator it = str1.begin(); it != str1.end(); it++) {
        Add(it);
        if(*it == '#') {
            numStr++;
        }
    }
    using std::chrono::steady_clock;
        steady_clock::time_point start = steady_clock::now();
    Markup(root);

    FindMaxLength(root, 0);
    std::vector <TNode *> path_to_sub;
    FindLongestSubstrings(root, 0, root, path_to_sub);
    std::list <std::string> answers;

    int size = answer.size();
    for(int i = 0; i < size;i++) {
        std::string tmp;
        int size_answer_path_to_subs = answer[i].spath.size();
        for(int j = 0; j < size_answer_path_to_subs;j++) {
            std::string next(answer[i].spath[j]->begin,answer[i].spath[j]->end + 1);
            tmp += next;
        }
        answers.push_back(tmp);
    }

    steady_clock::duration dur = steady_clock::now() - start;
    std::cerr << "Ukkonen's time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";

    answers.sort();
    std::cout << maxLength << std::endl;
    for(auto i = answers.begin(); i != answers.end();i++){
        std::cout << *i << std::endl;
    }

}

void TSuffixTree::Add(std::string::iterator it) {
    link = root;
    remaining++;
    while(remaining) {
        if (!activeLength) {
            activeEdge = it;
        }
        std::map<char, TNode *>::iterator it1 = activeNode->child.find(*activeEdge);


        if(it1 == activeNode->child.end()) {
            TNode *n_node = new TNode(it, str1.end());
            activeNode->child[*activeEdge] = n_node;
            if (link != root)
                link->suffixLink = activeNode;
            link = activeNode;
        }
        else {
            TNode * after = it1->second;
            int length = after->end - after->begin + 1;
            if (activeLength >= length) {
                activeEdge += length;
                activeLength -= length;
                activeNode = after;
                continue;
            }
            if( ( (after->begin + activeLength) == str1.end() ) && it == str1.end() ) {
                activeLength++;
                if (link != root)
                    link->suffixLink = activeNode;
                link = activeNode;
                break;
            }
            else {
                if (*(after->begin + activeLength) == *it) {
                    activeLength++;
                    if (link != root)
                        link->suffixLink = activeNode;
                    link = activeNode;
                    break;
                }
            }
            TNode *split = new TNode(after->begin, after->begin + activeLength - 1);
            TNode *leaf = new TNode(it, str1.end());
            activeNode->child[*activeEdge] = split;
            split->child[*it] = leaf;
            after->begin += activeLength;
            split->child[*after->begin] = after;
            if (link != root)
                link->suffixLink = split;
            link = split;

        }
        remaining--;
        if(activeNode == root && activeLength != 0){
            activeLength--;
            activeEdge++;
        }
        else {
            if(activeNode->suffixLink)
                activeNode = activeNode->suffixLink;
            else
                activeNode = root;
        }

    }
}

void TSuffixTree::DeleteTree(TNode *node)
{
    for (std::map<char, TNode *>::iterator it = node->child.begin(); it != node->child.end(); ++it) {
        DeleteTree(it->second);
    }
    delete node;
}

string poisk_podstroki(string a, string b)
{
    int schet = 0;
    string check = "", itog = "";
    while (schet!=a.size())
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (i + schet >= b.size())
                break;
            if (check.size() > itog.size())
                itog = check;
            if (a[i] == b[i + schet])
            {
                check += a[i];
            }
            else
            {
                check = "";
            }
        }
        schet++;
        check = "";
    }
 
    return itog;
}

int main(){
    std::string str1, str2;
    while(cin >> str1 >> str2) {
        using std::chrono::steady_clock;
        steady_clock::time_point start2 = steady_clock::now();
        poisk_podstroki(str1, str2);
        steady_clock::duration dur2 = steady_clock::now() - start2;
        std::cerr << "Naive time: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur2).count() << " ms\n";

        str1 += "#";
        str2 += "$";
        str1 += str2;
        TSuffixTree tree(str1, str2);

        tree.DeleteTree(tree.root);
    }

    return 0;
}
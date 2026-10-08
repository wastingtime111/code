#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {

    string text;

    cout << "Enter a string: ";
    getline(cin, text);

    vector<char> ch;
    vector<int> freq;
    vector<pair<int, int>> child;

    map<char, int> mp;

    for (char c : text)
        mp[c]++;

    for (auto x : mp) {
        ch.push_back(x.first);
        freq.push_back(x.second);
        child.push_back({-1, -1});
    }

    int n = ch.size();

    while (n > 1) {

        int a = -1;

        for (int i = 0; i < (int)freq.size(); i++) {
            if (freq[i] != -1 &&
                (a == -1 || freq[i] < freq[a])) {
                a = i;
            }
        }

        int b = -1;

        for (int i = 0; i < (int)freq.size(); i++) {
            if (freq[i] != -1 && i != a &&
                (b == -1 || freq[i] < freq[b])) {
                b = i;
            }
        }

        ch.push_back('\0');
        freq.push_back(freq[a] + freq[b]);
        child.push_back({a, b});

        freq[a] = -1;
        freq[b] = -1;

        n--;
    }

    int root = ch.size() - 1;

    map<char, string> code;

    vector<pair<int, string>> stack;

    stack.push_back({root, ""});

    while (!stack.empty()) {

        int node = stack.back().first;
        string s = stack.back().second;

        stack.pop_back();

        if (child[node].first == -1) {
            code[ch[node]] = s;
            continue;
        }

        stack.push_back({
            child[node].first,
            s + "0"
        });

        stack.push_back({
            child[node].second,
            s + "1"
        });
    }

    cout << "\nHuffman Codes:\n";

    for (auto x : code) {
        if (x.first == ' ')
            cout << "[space] : " << x.second << endl;
        else
            cout << x.first << " : " << x.second << endl;
    }

    string encoded = "";

    for (char c : text)
        encoded += code[c];

    cout << "\nOriginal : " << text << endl;
    cout << "Encoded  : " << encoded << endl;

    string decoded = "";

    int current = root;

    for (char bit : encoded) {

        if (bit == '0')
            current = child[current].first;
        else
            current = child[current].second;

        if (child[current].first == -1) {
            decoded += ch[current];
            current = root;
        }
    }

    cout << "Decoded  : " << decoded << endl;

    return 0;
}

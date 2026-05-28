//Дан текст. Сколько в тексте слов начинаются и заканчиваются на одну и ту
//же букву.

#include <iostream>
#include <string>
using namespace std;

//Работает только для английских текстов

int main() {
    string s;
    getline(cin, s);
    int count = 0;
    for (size_t i = 0; i < s.length(); ) {
        if (s[i] == ' ') { i++; continue; }
        size_t j = s.find(' ', i);
        if (j == string::npos) j = s.length();
        string word = s.substr(i, j - i);
        if (word[0] == word[word.length() - 1]) count++;
        i = j + 1;
    }
    cout << count << '\n';
    return 0;
}

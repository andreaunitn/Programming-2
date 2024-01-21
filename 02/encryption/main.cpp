#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool IsEncKeyLowercase(string key);
bool IsEncKeyContainsAllLetters(string key);

int main() {

    cout << "Enter the encryption key: ";

    string key; 
    getline(cin, key);

    if(key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    } else if(!IsEncKeyLowercase(key)) {
        cout << "Error! The encryption key must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    } else if(!IsEncKeyContainsAllLetters(key)) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";

    string text;
    getline(cin, text);

    if(!IsEncKeyLowercase(text)) {
        cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
        return EXIT_FAILURE;
    }

    string enc_text = text;

    for(string::size_type i = 0; i < enc_text.length(); i++) {
        enc_text[i] = key[enc_text[i] - 'a'];
    }

    cout << "Encrypted text: " << enc_text << endl;

    return 0;
}

bool IsEncKeyLowercase(string key) {
    bool valid = true;

    for(string::size_type i = 0; i < key.length(); i++) {
        if(isupper(key.at(i))) {
            valid = false;
            break;
        }
    }

    return valid;
}

bool IsEncKeyContainsAllLetters(string key) {
    bool valid = true;

    for(char c = 'a'; c <= 'z'; c++) {
        if(key.find(c) == string::npos) {
            valid = false;
            break;
        }
    }

    return valid;
}
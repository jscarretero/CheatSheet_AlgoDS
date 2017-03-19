#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <unordered_map>
using namespace std;

/* =========================Helper declarations and functions ====================================*/

/* ===================================All Unique Characters=======================================*/
bool allUniqueChars (string& str) {
    vector<bool> found (256, false);
    for (int i = 0; i < str.size(); i++ ) {
        if ( found[str[i]] ) return false;
        found[str[i]] = true;
    }
    return true;
}

/* ======================================Reverse String===========================================*/
void reverse (string& str) {
    int strSize = str.size();
    for (int i = 0; i < strSize / 2; i++) {
        char tmp = str[i];
        str[i] = str[strSize - 1 - i];
        str[strSize - 1 - i] = tmp;
    }
}

/* =======================================Is Permutation==========================================*/
bool isPermutation (string& str1, string& str2) {
    // IDEA: check if strings have identical character counts
    unordered_map<char, int> letters; // we could also use an array of size 128 instead of Hash Tble

    // First build map of char->count for str1
    for (auto& c_: str1) {
        char c = char(c_);
        if (letters.find(c) == letters.end()) {
            pair<char,int> tmp(c,1);
            letters.insert(tmp);
        } else {
            letters[c] = letters[c] + 1;
        }
    }

    // Then traverse str2 chars and decrement map. If we found an entrance with 0, then it is not
    // a permutation

    for (auto & c_: str2) {
        char c = char(c_);
        if (letters.find(c) == letters.end()) return false;
        letters[c] = letters[c] - 1;
        if (letters[c] < 0) return false;
    }
    return true;
}  // O(N) time, O(N) spaces

// Another solution that requires O(NlogN time) and O(1) space is to sort both strings (if we can)
// and compare the sorted strings.

/* ====================================Replace Spaces With %020===================================*/
// You can assume that the string has sufficient space at the end of it to hold the additional
// characters and that you are given the 'true' length of the string.

void replaceSpacesWithString(char str[], int length) {
    // First count spaces
    int spaces = 0;
    for (int i = 0; i < length; i++) {
        spaces += (str[i] == ' ');
    }

    // Calculate new size of string
    int newLength  = length + (spaces * 2);
    str[newLength] = '\0';
        newLength  = newLength - 1;
    for (int i = length - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            str[newLength] = str[i];
            newLength--;
        } else {
            str[newLength]     = '0';
            str[newLength - 1] = '2';
            str[newLength - 2] = '%';
            newLength = newLength - 3;
        }
    }
}

/* =====================================Compress String===========================================*/
// From 'Cracking the Coding Interview' too
// aabcccccaaa becomes a2b1c5a3

int countCompression (string& str) {
    if (str.size() == 0) return 0;

    char last       = str[0];
    int  countEqual = 1;
    int  finalSize  = 0;

    for (int i = 1; i < str.size(); i++) {  //Starts at second character!
        char c = str[i];
        if (c == last) {
            countEqual++;
        } else {
            finalSize  = finalSize + (std::to_string(countEqual).size() + 1);
            last       = c;
            countEqual = 1;

        }
    }
    finalSize += std::to_string(countEqual).size() + 1;
    return finalSize;
}

string compressString (string& str) {
    int size = countCompression(str);
    if (size >= str.size()) return str; //Return upon inefficient compression case

    char* newString = new char[size](); // Initialized to 0

    char last      = str[0];
    int countEqual = 1;
    int  ptr       = 0;
    for (int i = 1; i < str.size(); ++i) {
        char c = str[i];
        if (c == last) {
            countEqual++;
        } else {
            newString[ptr++] = last;
            strcpy(&newString[ptr], std::to_string(countEqual).c_str());
            ptr += std::to_string(countEqual).size();
            last = c;
            countEqual = 1;
        }
    }

    newString[ptr++] = last;
    strcpy(&newString[ptr], std::to_string(countEqual).c_str());

    string result = string(newString);
    delete newString;
    return result;

}
/* ========================================Is Rotation============================================*/
bool isRotation (string& str1, string& str2) {
    if ( (str1.size() == str2.size() ) && str1.size() > 0) {
        string strConcat = str1 + str1;
        return (strConcat.find(str2) != string::npos);
    }
    return false;
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void allUniqueChars_example() {
    string str = "abcd";
    cout << "String 'abcd' has unique characters? is: " << allUniqueChars(str) << endl;
           str = "abcda";
    cout << "String 'abcda' has unique characters? is: " << allUniqueChars(str) << endl;
}
void reverse_example() {
    string str = "Hi! How are you doing?";
    string strOriginal = str;
    reverse(str);
    cout << "Reversed string for '" << strOriginal << "' is : '" << str << "'" << endl;
}
void isPermutation_example() {
    string str1 = "abb";
    string str2 = "bba";
    cout << "Is '" << str2 << "' a permutation of '" << str1 << "' ? : " <<
             isPermutation(str1,str2) << endl;
}
void replaceSpacesWithString_example() {
    char* str = new char[10] (); //initialized to 0 with ()
    strcpy(str, "Hey ya!");
    replaceSpacesWithString(str, 7);
    cout << "Replacing spaces with \%020 for 'Hey ya! is : " << str << endl;
    delete str;
}
void compressString_example() {
    string str = "aabcccccaaa";
    cout << "Compressing '" << str << "' to : '" << compressString(str) << "'" << endl;

}
void isRotation_example() {
    string str1 = "abcd";
    string str2 = "cdab";
    cout << "Is '" << str1 << "' a rotation of '" << str2<< "' ? " << isRotation(str1,str2) << endl;
}

/* ===============================================================================================*/
int main () {
    allUniqueChars_example();
    reverse_example();
    isPermutation_example();
    replaceSpacesWithString_example();
    compressString_example();
    isRotation_example();
}

/* =======================================TODO====================================================*/
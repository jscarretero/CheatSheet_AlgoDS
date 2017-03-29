#include <iostream>
#include <vector>
#include <set>
using namespace std;

/* =========================Helper declarations and functions ====================================*/

/* =================================Print All Permutations of a String============================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

void stringPermutations (string& str, int l, int r) {
    // O(N!) time  (N is str length)
    if (l == r) { cout << str << ", "; return; }

    for (int i = l; i <= r; i++)
    {
        char tmp  = str[l]; str[l] = str[i]; str[i] = tmp;  //swap l with i
        stringPermutations(str, l+1, r);
        char tmp2 = str[l]; str[l] = str[i]; str[i] = tmp2; //unswap l with i
    }
}

/* ===========================String Permutations without Repeats=================================*/
void stringPermutationsNoRepeats (string& str, int l, int r) {
    // O(N!) time (N is str length)
    if (l == r) { cout << str << ", "; return; }

    set<char> startingWith;
    for (int i =l; i <= r; i++) {
        if ( startingWith.find(str[i]) == startingWith.end() )
        {
            // We haven't visited a solution where the element str[i] has been swapped with l
            char tmp  = str[l]; str[l] = str[i]; str[i] = tmp;
            stringPermutationsNoRepeats (str, l+1, r);
            char tmp2 = str[l]; str[l] = str[i]; str[i] = tmp2;
            startingWith.insert(str[i]);
        }
    }
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void stringPermutations_example() {
    string example="HELLO";
    cout << "String Permutations are:\t\t [";
    stringPermutations(example, 0, 3);
    cout << "]" << endl;

}
void stringPermutationsNoRepeats_example() {
    string example="HELLO";
    cout << "String Permutations with no repeats are: [";
    stringPermutationsNoRepeats(example, 0, 3);
    cout << "]" << endl;
}

/* ===============================================================================================*/
int main() {
    stringPermutations_example();
    stringPermutationsNoRepeats_example();
}

/* =======================================TODO====================================================*/
// BACKTRACKING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#Backtracking
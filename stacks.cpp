#include <iostream>
#include <stack>
#include <string>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
void printStack (stack<int>& s) {
    // No iterator for stack in C++ stl :(
    //for (auto& e: s) {
    //    cout << e << ", ";
    //}
    //cout << endl;
    for (stack<int> dump = s; !dump.empty(); dump.pop())
        cout << dump.top() << ", ";
    cout << endl;
}

/* ========================Describe how to implement 3 stacks using an array======================*/
// From 'Cracking the Coding Interview'

// Simple solution: allocate equal fixed amount of space for each stack, and keep three tail pointer



/* ======================Describe how to implement stack that has an O(1) min op==================*/
// From 'Cracking the Coding Interview'

// Simple solution: each stack node holds an extra element that keeps the minimum.
//                  Upon push, we recalculate it. min() returns the min at the top.
// More space-efficient solution: use another stack that keeps the minimum. When pushing an element
// into a stack, we recalculate the minimum (peeking the top). If the new minimum is <= minimum,
// (including the == case) then we push it into the additional stack.



/* =================================Sort stack using another stack================================*/
// From 'Cracking the Coding Interview' (biggest elements on top)
stack<int> sortStack (stack<int>& s) {
    stack<int> res;

    while (!s.empty()) {
        int tmp = s.top();
        s.pop();
        while (!res.empty() && res.top() > tmp) {
            s.push(res.top());
            res.pop();
        }
        res.push(tmp);
    }
    return res;
}

/* =================================Sort Stack Using Recursion====================================*/
// http://www.geeksforgeeks.org/sort-a-stack-using-recursion/

void insertOrderedIntoStack (stack<int>& s, int tmp) {
    if (s.empty() || tmp > s.top()) {s.push(tmp); return; }

    int head = s.top(); s.pop();
    insertOrderedIntoStack(s, tmp);
    s.push(head);
}

void sortStackRecursive (stack<int>& s) {
    if (s.empty()) return;

    int tmp = s.top(); s.pop();  // Values kept in function call stack :)
    sortStackRecursive(s);
    insertOrderedIntoStack(s, tmp);
}

/* ==========================Reverse Stack Using Recursion========================================*/
// http://www.geeksforgeeks.org/reverse-a-stack-using-recursion/
void reverseStack (stack<int>& s, stack<int>& res) {
    if (s.empty()) return;

    res.push(s.top()); s.pop();
    reverseStack(s, res);
}

void insertBottomStack( stack<int>& s, int val) {
    if (s.empty()) { s.push(val); return; }

    int tmp = s.top(); s.pop();  //we undo all the stack to keep it in the function call stack
    insertBottomStack(s, val);
    s.push(tmp);
}

void reverseStack_ (stack<int>& s) { // without using an additional stack (use Function call stack)
    if (s.empty()) return;

    int tmp = s.top(); s.pop();
    reverseStack_(s);
    insertBottomStack(s, tmp);
}

/* ==========================Test if Parens, Brackets and Braces Are Matched======================*/
// http://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/

bool checkParensMatch (string& str) {
    stack<char> open;
    for (int i = 0; i < str.size(); i++) {
        if ((str[i] == '(') || (str[i] == '[') || (str[i] == '{')) {
            open.push(str[i]);
        } else {
            if (open.empty()) return false;
            else if ( ((open.top() != '(') && (str[i] == ')')) ||
                      ((open.top() != '[') && (str[i] == ']')) ||
                      ((open.top() != '{') && (str[i] == '}'))    ) return false;
            else open.pop();
        }
    }
    return open.empty();
}

/* ============================== Towers of Hanoi ================================================*/
// From 'Cracking the Coding Interview'

class Tower {
    private:
        string id;
        stack<int> disks;
    public:
        Tower(string str) : id(str) {}
        ~Tower() {}       // Nothing to do, not needed though

        void add(int dsk) {
            disks.push(dsk);
        }
        void moveDisks(int n, Tower* dst, Tower* tmp) {
            // Temporal cost: O(2^n)   from T(n) = 2T(n-1) + 1 recurrence
            // https://www.wolframalpha.com/input/?i=T(n%2B1)%3D2*T(n)+%2B+1
            if (n > 0) {
                this->moveDisks(n - 1, tmp, dst);

                int el = disks.top();
                disks.pop();
                dst->add(el);

                tmp->moveDisks(n-1, dst, this);
            }
        }
        friend std::ostream& operator<< (std::ostream& stream, const Tower& t) {
            stream << "Tower " << t.id << " is: ";
            for (stack<int> dump = t.disks; !dump.empty(); dump.pop())
                stream << dump.top() << ", ";
            stream << endl;
            return stream;
        }
};

void hanoi (int n) {
    Tower src(string("src"));
    Tower dst(string("dst"));
    Tower tmp(string("tmp"));

    for (int i = n - 1; i >= 0; i--) src.add(i);

    cout << "\tBEFORE: " << endl;
    cout << "\t\t" << src;
    cout << "\t\t" << dst;
    cout << "\t\t" << tmp;

    src.moveDisks(n, &dst, &tmp);

    cout << "\tAFTER: " << endl;
    cout << "\t\t" << src;
    cout << "\t\t" << dst;
    cout << "\t\t" << tmp;
}

/* ==========================Compute Longest Substring with Matching Parens=======================*/
// From 'Elemments of Programming Interviews'

// Simple & inefficient idea: generate all substrings of str, and checl if its parens are matched.
//                            get maximum length among all substrings whose parens are matched.
//                            N^2 substrings, checking parens match is O(N). Temporal cost is O(N^3)
//
// Second idea: For each 'i' (char position of str), find longest substring with matching parens.
//              But when an unmatched closing parens is found,stop looking for bigger suffix strings
//              O(N^2)
//
// Third idea:  Same as second idea, but instead of iterating over all 'i' (char positions of str),
//              Whenever an unmatched right parens is found, we can move 'i' to the next char
//              position after this unmatched right parens.  O(N)


int longestSubstringMatching (string& str) {
    stack<int> open_pars;
    int max_length = 0;
    int last_end   = 0; //keeps latest start position for a valid substring with matching parens

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            open_pars.push(i);
        } else { // ')'
            if (!open_pars.empty()) {
                open_pars.pop();
                int start  = (open_pars.empty() ? last_end : open_pars.top());
                max_length = max(max_length, i - start + 1);
            } else {
                last_end = i + 1;
            }
        }
    }
    return max_length;
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void sortStack_example() {
    stack<int> s;
    for (int i = 9; i >= 0; i--) s.push(i);
    stack<int> res = sortStack(s);
    cout << "Sorted stack is: "; printStack(res);
}
void sortStackRecursive_example() {
    stack<int> s;
    for (int i = 9; i >= 0; i--) s.push(i);
    sortStackRecursive(s);
    cout << "Sorted stack is: "; printStack(s);
}
void reverseStack_example() {
    stack<int> s, res;
    for (int i = 9; i >= 0; i--) s.push(i);
    reverseStack(s, res);
    cout << "Reversed stack is: "; printStack(res);
    reverseStack_(res);
    cout << "Unreversed     is: "; printStack(res);
}
void checkParensMatch_example() {
    string str = "(({}[]))(){}";
    string str2 = "((}[]))(){}";
    cout << "Is " << str  << " well matched? : " << checkParensMatch(str)  << endl;
    cout << "Is " << str2 << " well matched? : " << checkParensMatch(str2) << endl;
}
void hanoi_example() {
    cout << "Hanoi towers: " << endl;
    hanoi(4);
}
void longestSubstringMatching_example() {
    string str = "()()))(((())))()";
    cout << "Longest Substring with matching parens for " << str << " is : " <<
             longestSubstringMatching(str) << endl;
}

/* ===============================================================================================*/
int main () {
    sortStack_example();
    sortStackRecursive_example();
    reverseStack_example();
    checkParensMatch_example();
    hanoi_example();
    longestSubstringMatching_example();
}

/* =======================================TODO====================================================*/
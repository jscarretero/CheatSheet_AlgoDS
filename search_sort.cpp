#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

    // TODO: merge two sorted arrays, given another one with enough space
    // QUICKSTORT, MERGESORT IN ARRAY too
// http://www.geeksforgeeks.org/segregate-0s-and-1s-in-an-array-by-traversing-array-once/
// http://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/
// https://sites.google.com/site/spaceofjameschen/home/sort-and-search/dutch-national-flag

/* =========================Helper declarations and functions ====================================*/

/* ======================All pairs differing by K in a sorted vector==============================*/
// http://www.careercup.com/question?id=5727804001878016
// Given an array of positive, unique, increasingly sorted numbers A,
//      e.g. A = [1, 2, 3, 5, 6, 8, 9, 11, 12, 13].
// Given a positive value K, e.g. K = 3. Output all pairs in A that differ exactly by K. No repeats

void pairsDifferingK (vector<int>& arr, int k) { // O(N) time, O(1) space
    int i = 0;
    int j = 1;
    while (j < arr.size()) {
        if      ( (arr[j] - arr[i]) > k)  i++;
        else if ( (arr[j] - arr[i]) < k)  j++;
        else {
            cout << "(" << i << ", " << j << ") ";
            i++;            // Note that elements must be unique, otherwise this step does not work
        }                   // Consider K = 20 and [ 60, 60, 80, 80] : we either advance i or recede
                            // j, so either indexes (0, 2), (1,2) are generated or (0, 2), (0, 3)
    }
}

/* =========================All pairs summing to value K in a vector==============================*/
// Not necessarily sorted vector, no repeating pairs

void pairsSummingK_ (vector<int>& arr, int k) {
    // O(N*logN) time, O(1) space, modifies vector!
    // WARNING: pair indexes are different to original arr before sorting

    std::sort(arr.begin(), arr.end());  // O(N log N) assumed
    int i = 0;
    int j = arr.size() - 1;
    while (i <= j) {
        if      (arr[i] + arr[j] > k) j--;
        else if (arr[i] + arr[j] < k) i++;
        else {
            cout << "(" << i << ", " << j << ") ";
            i++;            // Same comment as in pairsDifferingK
        }
    }
}

void pairsSummingK (vector<int>& arr, int k) {
    // O(N) time, O(N) space

    unordered_map<int, list<int> > val_pos;
    for (int i = 0; i < arr.size(); i++)
    {
        if (  val_pos.find( k - arr[i] ) != val_pos.end() ) {
            list<int>& l = val_pos[ k - arr[i]];
            for (auto& e: l)
                    cout << "(" << e << ", " << i << ") ";
        }
        val_pos[arr[i]].push_back(i);
    }
}

/* ===========================Given an array of pairs, find all symmetric pairs===================*/
// http://www.geeksforgeeks.org/given-an-array-of-pairs-find-all-symmetric-pairs-in-it/
// Assume first elements of all pairs are distinct !

void symmetricPairs (vector<pair<int, int> >& array) {
    // O(N) time, O(N) space

    unordered_map<int, pair<int, int> > mem; // key is first element of pair, and pair contains
                                             // second element and index position within array

    for (int i = 0; i < array.size(); i++) {
        pair<int,int> el = array[i];
        if ( mem.find(el.second) != mem.end() ) {
            if ( mem[el.second].first == el.first ) {
                cout << "(" << mem[el.second].second << ", " << i << ") ";
            }
        } else {
            // In case previous 'if' was executed, we don't need to add the element to mem
            // becase first elements of all pairs are unique
            pair<int, int> tmp (el.second, i);
            mem[el.first] = tmp;
        }
    }
}

/* =====================Unsorted Subarray Location That Sorting Makes Complete Sorted=============*/
// http://www.geeksforgeeks.org/minimum-length-unsorted-subarray-sorting-which-makes-the-complete-\
//        array-sorted/

void unsortedSubarray (vector<int>& arr, int& s, int& e) {
    // O(N) time, O(1) space

    s = 0; e = arr.size() - 1;

    // From left to right, find element that is smaller than the previous one. Include previous one
    // as initial starting subarray point (to be refined later, potentially including more elements)
    // We include it, because in the best case we would need to swap it with the next element
    for (s = 0; s < arr.size() - 1; s++) {
        if (arr[s] > arr[s+1]) break;
    }

    if (s == arr.size() - 1) {e = 0; return;}

    // From right to left, find element that is smaller than the previous one. Include previous one
    // as initial ending subarray point (to be refined later, potentially including more elements)
    // We include it, because in the best case we would need to swap it with the next element
    for (e = arr.size() - 1; e > 0; e--) {
        if (arr[e] < arr[e-1]) break;
    }

    // Find the minimum and maximum values in arr[s..e]
    int min = arr[s]; int max = arr[s];
    for (int i = s +1; i <= e; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    // Find first element in arr[0..s-1]  that is bigger than min,  make s to point to that element
    for (int i = 0; i <= s - 1; i++) {
        if (arr[i] > min) { s = i; break; }
    }

    // Find last element in arr[e+1..n-1] that is smaller than max, make e to point to that element
    for (int i = arr.size() - 1; i >= e+1; i--) {
        if (arr[i] < max) { e = i; break; }
    }
}

/* ======================Maximum of minimum values for every window in an array===================*/
// http://www.geeksforgeeks.org/find-the-maximum-of-minimums-for-every-window-size-in-a-given-array/

void maxOfMin (vector<int>& array) {
    // O(N^3) time, O(1) space

    for (int s = 1; s <= array.size(); s++) {  // Iterate  over possible sizes
        int window_max = array[0];
        for (int i = 0; i <= (array.size() - s); i++ )   // Iterate over starting points for a size
        {
            int window_min = array[i];
            for (int j = 1; j < s; j++) {
                window_min = min (window_min , array[i+j]);
            }
            window_max = max (window_max, window_min);
        }
        cout << window_max << ", ";
    }

}

/* =========================Maximum Sum in Contiguous Subarray====================================*/
// http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
// http://karmaandcoding.blogspot.com.es/2011/03/maximum-contiguous-sum-in-array.html

int MCS (vector<int>& array, int& s, int& e) {
    // O(N) time, O(1) space
    // IDEA: when we find a negative sum at a given position, if we increase the subarray we will
    //       not find a biggest sum. Therefore we can start considering a new subarray in the next
    //       position

    int max_sum    = 0;  // maximum sum is 0 in the worst case (no subarray)
    int curr_sum   = 0;
    int curr_start = 0;
    int max_start  = 0;
    int max_end    = 0;

    for (int i = 0; i < array.size(); i++) {
        curr_sum = curr_sum + array[i];
        if (curr_sum < 0) {
            curr_sum = 0;
            curr_start = i + 1;
        } else {
            if (curr_sum > max_sum) {
                max_sum   = curr_sum;
                max_start = curr_start;
                max_end   = i;
            }
        }
    }
    s = max_start; e = max_end;
    return max_sum;
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void pairsDifferingK_example() {
    vector<int> v = {1,2,3,5,6,7,9,11,12,13};
    cout << "All pairs differing 3 in array are: "; pairsDifferingK(v, 3); cout << endl;
}
void pairsSummingK_example() {
    vector<int> v = {1,1,0,9,8,8,2};
    cout << "All pairs summing 10 in array are: "; pairsSummingK(v, 10);  cout << endl;
    cout << "All pairs summing 10 in array are: "; pairsSummingK_(v, 10); cout << endl;
}
void symmetricPairs_example() {
    vector<pair<int,int> > v= { make_pair(1,0), make_pair(2,3), make_pair(0,1), make_pair(4,5),
                                make_pair(5,4)};
    cout << "Symmetric pairs are : "; symmetricPairs(v);
    cout << endl;
}
void unsortedSubarray_example() {
    vector<int> v = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
    //vector<int> v = {0,1,2,3,4,5,6};
    int s = 0;
    int e = -1;
    unsortedSubarray(v, s, e);
    cout << "Unsorted subarray lies between : " << s << " and " << e << endl;
}
void maxOfMin_example() {
    vector<int> v = {10, 20, 30, 50, 10, 70, 30};
    cout << "Maxim value of minimum value for all window sizes are : "; maxOfMin(v);
    cout << endl;
}
void MCS_example() {
    vector<int> v1 = {5,7,-3,1,-11,8,12};
    vector<int> v2 = {3,-2,4,-2,-3,5,-6,7,-3,-2,-1,-8};
    int s, e;
    int res = MCS(v1, s, e);
    cout << "Max Contiguous Sum is : " << res << " starting at " << s << " ending at " << e << endl;
        res = MCS(v2, s, e);
    cout << "Max Contiguous Sum is : " << res << " starting at " << s << " ending at " << e << endl;
}
/* ===============================================================================================*/
int main () {
    pairsDifferingK_example();
    pairsSummingK_example();
    symmetricPairs_example();
    unsortedSubarray_example();
    maxOfMin_example();
    MCS_example();
}

/* =======================================TODO====================================================*/


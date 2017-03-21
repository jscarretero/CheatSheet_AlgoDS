#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

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

int maxSumSubarray (vector<int>& array, int& s, int& e) {
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

/* =======================Find Subarray with Given Sum V (non-negative contents)==================*/
// http://www.geeksforgeeks.org/find-subarray-with-given-sum/
// Note: non-negative numbers, non sorted array

void findSubarrayGivenSum_Positive (vector<int>& array, int v, int& s, int& e) {
    // O(N) time, O(1) space

    int curr_start = 0;
    int curr_sum   = 0;
    bool found     = false;

    for (int i = 0; i < array.size()  && !found; i++) {
        curr_sum += array[i];
        if (curr_sum > v) {
            // If curr_sum exceeds value, then when move curr_start pointer either until we find
            // the sum value, or until curr_start overpasses i.
            // curr_sum is increasing
            while ((curr_start <= i) && (curr_sum > v)) {
                curr_sum -= array[curr_start];
                curr_start++;
            }
        }
        if (curr_sum == v) { found = true; s = curr_start; e = i;}
    }

    if (!found) { s= array.size() - 1; e = 0; }
}

void findSubarrayGivenSum_Positive_ (vector<int>& array, int v, int& s, int& e) { //inefficient
    // O(N^2) time, O(1) space
    bool found    = false;

    for (int i = 0; i < array.size() && !found; i++) {
        int  curr_sum = 0;
        for (int j = i; (j < array.size()) && !found; j++) {
            curr_sum = curr_sum + array[j];
            if (curr_sum == v) {
                s = i; e = j;
                found = true;
            }
        }
    }
    if (!found ) { s = array.size() - 1; e = 0; }
}

/* ======================Find Subarray with Given Sum V (with negative contents)==================*/
// http://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/
// Extension of above one

void findSubarrayGivenSum (vector<int>& array, int v, int& s, int& e ) {
    // O(N) time, O(N) space

    // IDEA: Iterate over all positions and accumulate the sum, if at a given index we have a sum x
    //       then we can find in a map if there has been a position whose accumulated value from pos
    //       0 is x-s . If we don't include that prefix subarray, then the sum would be x-(x-s) = s
    //

    unordered_map<int,int> prefix_sum; // key is accumulated sum and value is array index when this
                                       // accumulated sum was observed
    int accum_sum = 0;
    bool found    = false;

    for (int i = 0; i < array.size() && !found; i++) {
        accum_sum += array[i];
        if (accum_sum == v) { s = 0; e = i; found = true; }
        else {
            int offset = accum_sum - v;
            if (prefix_sum.find(offset) != prefix_sum.end()) {
                s = prefix_sum[offset] + 1;
                e = i;
                found = true; //break
            }  else {
                // We keep the longest subarray (first positions are memorized) )
                if (prefix_sum.find(accum_sum) == prefix_sum.end()) {
                    prefix_sum[accum_sum] = i;
                }
            }
        }
    }
    if (!found) { s = array.size() - 1 ; e = 0; }
}

/* =========================Find LARGEST Subarray with 0 Sum======================================*/
// Very similar to previous one, V=0, but we need the largest one
// http://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/

int bigestSubarraySummingZero (vector<int>& array, int& s, int& e) {
    // O(N) time, O(N) space

    unordered_map<int,int> prefix_sum;
    int max_len   = 0;
    int accum_sum = 0;

    s = array.size() - 1;
    e = 0;

    for (int i = 0; i < array.size(); i++) {
        accum_sum += array[i];
        if (accum_sum == 0) { max_len = i; s = 0; e = i; }
        else {
            int offset = accum_sum - 0; //redundant, but added to show similarity wrt previous probl.
            if (prefix_sum.find(offset) != prefix_sum.end()) {
                if (  ( i - (prefix_sum[offset]+1) + 1)  > max_len) {
                    max_len =  i - (prefix_sum[offset] + 1) + 1;
                    s = prefix_sum[offset] + 1;
                    e = i;
                }
            } else {
                prefix_sum[accum_sum] = i;
            }
        }
    }
    return max_len;
}

int bigestSubarraySummingZero_ (vector<int>& array, int& s, int& e) {
    // O(N^2) time
    int max_len = 0;
    s = array.size() - 1;
    e = 0;

    for (int i = 0 ; i < array.size(); i++) {
        int curr_sum = 0;
        for (int j = i; j < array.size(); j++) {
            curr_sum += array[j];
            if (curr_sum == 0) {
                if ((j-i + 1) > max_len) { max_len = j-i + 1;  s = i; e = j; }
            }
        }
    }
}

/* =========================Find a Fixed Point in a given array===================================*/
// http://www.geeksforgeeks.org/find-a-fixed-point-in-a-given-array/
// Assume SORTED & UNIQUE elements!

int fixedPoint (vector<int>& array, int s, int e) {
    // O(N log N), divide & conquer, based on binary search T(N) = T(N/2) + 1
    if (s > e) return -1;

    int h = s + (e - s + 1) / 2 ; // (2s + e -s + 1)/2 == (s + e +1 )/2

    if      (array[h] == h)       return h;
    else if (array[h] >  h)       return fixedPoint(array, s, h-1);
    else                          return fixedPoint(array, h+1, e);
}

/* =================Given 2 sorted arrays A & B, merge them into B (enough space provided)========*/
void mergeArrays (int a[], int b[], int sizeA, int sizeB) {
    // TIP: start from end
    int ptrM = sizeA + sizeB - 1;
    int ptrA = sizeA - 1;
    int ptrB = sizeB - 1;

    while (ptrA >= 0  && ptrB >= 0) {
        if (a[ptrA] > b[ptrB])  { b[ptrM] = a[ptrA]; ptrA--; }
        else                    { b[ptrM] = b[ptrB]; ptrB--; }
        ptrM--;
    }

    for (int i = ptrA; i >= 0; i--) {
        b[ptrM] = a[i];
        ptrM--;
    }
}

/* =================Given 2 sorted arrays A & B, merge them in-place O(1) space===================*/
// http://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/
// Initial numbers (after complete sorting) are in the first array and the remaining numbers are in
// the second array
void mergeInPlace(int* ar1, int* ar2, int m, int n)
{
    // O(m * n) time! That's why mergesort is not used for arrays, unless O(N/2) space used
    // The worst case occurs when all elements of ar1[] are greater than all elements of arb2[]

    /*
       The idea is to begin from last element of ar2[] and search it in ar1[]. If there is a greater
       element in ar1[], then we move last element of ar1[] to ar2[].
       To keep ar1[] and ar2[] sorted, we need to place last element of ar2[] at correct place in
       ar1[]. We can use Insertion Sort type of insertion for this
    */

    // Iterate through all elements of ar2[] starting from the last element
    for (int i = n - 1; i >= 0; i--) {
        /* Find the smallest element greater than ar2[i]. Move all elements one position ahead till
           the smallest greater element is not found */
        int j, last = ar1[m-1];
        for (j = m - 2; j >= 0 && ar1[j] > ar2[i]; j--)
            ar1[j + 1] = ar1[j];

        // If there was a greater element
        if (j != m - 2 || last > ar2[i]) {
            ar1[j + 1] = ar2[i];
            ar2[i]     = last;
        }
    }
}

/* ==========================Search in a row-wise and column-wise sorted matrix===================*/
// http://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/

#define N 4
pair<int,int> searchSortedMatrix (int array[N][N], int val) {
    // O(N) time, O(1) space
    // TIP: start from top-right element
    int i = 0; int j = N-1;
    while (i < N && j >= 0) {
        if       ( array[i][j] > val ) j--;
        else if  ( array[i][j] < val ) i++;
        else     return make_pair(i, j);
    }

    return make_pair(-1,-1);
}

/* ========================Given Two Arrays, Find Element That Has been Deleted===================*/
// http://www.geeksforgeeks.org/find-lost-element-from-a-duplicated-array/
// http://www.geeksforgeeks.org/find-the-missing-number/

int findMissing (vector<int>& array1, vector<int>& array2) {
    // Arrays are not in same order
    // O(N) time
    int checksumA = 0;
    for (int i = 0; i < array1.size(); i++)
        checksumA = checksumA ^ array1[i];

    int checksumB = 0;
    for (int i = 0; i < array2.size(); i++)
        checksumB = checksumB ^ array2[i];

    return checksumB ^ checksumA;
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
void maxSumSubarray_example() {
    vector<int> v1 = {5,7,-3,1,-11,8,12};
    vector<int> v2 = {3,-2,4,-2,-3,5,-6,7,-3,-2,-1,-8};
    int s, e;
    int res = maxSumSubarray(v1, s, e);
    cout << "Max Contiguous Sum is : " << res << " starting at " << s << " ending at " << e << endl;
        res = maxSumSubarray(v2, s, e);
    cout << "Max Contiguous Sum is : " << res << " starting at " << s << " ending at " << e << endl;
}
void findSubarrayGivenSum_Positive_example() {
    vector<int> v = {15, 2, 4, 8, 9, 5, 10, 23};
    int s, e;
    findSubarrayGivenSum_Positive(v, 23, s, e);
    cout << "Subarray with sum 23 is between : " << s << " and " << e << endl;
}
void findSubarrayGivenSum_example() {
    vector<int> v = {1, -3, 4, 8, 2, -14, 3, -1, 10, 6};
    int s, e;
    findSubarrayGivenSum(v, 9, s, e);
    cout << "Subarray with sum 9 is between : " << s << " and " << e << endl;
}
void bigestSubarraySummingZero_example() {
    vector<int> v = {15, -2, 2, -8, 1, 7, 10, 23};
    int s, e;
    bigestSubarraySummingZero (v, s, e);
    cout << "Biggest subarray with sum 0 is between : " << s << " and " << e << endl;
}
void fixedPoint_example() {
    vector<int> v= {-10, -1, 0, 3, 10, 11, 30, 50, 100};
    int res = fixedPoint(v, 0, v.size() - 1);
    cout << "Fixed point for array is : " << res << endl;
}
void mergeArrays_example() {
    int a[] = {3,4,5,22,40};
    int b[] = {1,2,11,15,20,54,-1,-1,-1,-1,-1};
    int n = sizeof(a)/sizeof(a[0]);
    int m = (sizeof(b)/sizeof(b[0])) - n;
    mergeArrays(a,b,n,m);
    cout << "Merged arrays is: ";
    for (int i = 0; i < n+m; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
}
void mergeInPlace_example() {
    int a[] = {3,4,5,22,40};
    int b[] = {1,2,11,15,20,54};
    mergeInPlace(a,b,5,6);
    cout << "Merged arrays are: ";
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) cout << a[i] << " ";
    cout << " | ";
    for (int i = 0; i < sizeof(b)/sizeof(b[0]); i++) cout << b[i] << " ";
    cout << endl;
}
void searchSortedMatrix_example() {
    int mat[N][N] = { {10, 20, 30, 40},
                      {15, 25, 35, 45},
                      {27, 29, 37, 48},
                      {32, 33, 39, 50},
                    };
    pair<int,int> res = searchSortedMatrix(mat, 29);
    cout << "Found element 29 in matrix position : (" << res.first << ", " << res.second << ")";
    cout << endl;
}
void findMissing_example() {
    vector<int> v1 = {9,1,3,7,2,-2,-3};
    vector<int> v2 = {-2,7,-3,2,9,1};
    cout << "Missing element between two arrays is: " << findMissing(v1, v2) << endl;
}

/* ===============================================================================================*/
int main () {
    pairsDifferingK_example();
    pairsSummingK_example();
    symmetricPairs_example();
    unsortedSubarray_example();
    maxOfMin_example();
    maxSumSubarray_example();
    findSubarrayGivenSum_Positive_example();
    findSubarrayGivenSum_example();
    bigestSubarraySummingZero_example();
    fixedPoint_example();
    mergeArrays_example();
    mergeInPlace_example();
    searchSortedMatrix_example();
    findMissing_example();
}

/* =======================================TODO====================================================*/
// SEARCH AND SORTING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#SearchingandSorting
// NICE link: http://www.nayuki.io/page/master-theorem-solver-javascript
//            http://www.cs.unipr.it/purrs/
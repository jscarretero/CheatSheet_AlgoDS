#include <iostream>
#include <vector>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
// --Notes:--
//
//  Multiplying by 2^n just shifts a number to the left by n.
//  XORing a value with its negated value retturns a sequence of 1's
//
//                 XOR Facts            AND Facts           OR Facts
//          -------------------------------------------------------------------
//                X ^ 0s   = X         X & 0s = 0s         X | 0s = X
//                X ^ 1s   = ~X        X & 1s = X          X | 1s = 1s
//                X ^ X    = 0s        X & X  = X          X | X  = X
//                X ^ ~X   = 1s
//
//  General idea: play with specific masks
bool getNBit (int v, int n) {
    return ((v & (1 << n)) != 0);
}

int setNBit (int v, int n) {
    return (v | (1 << n));
}

int clearNBit (int v, int n) {
    return (v & ~(1 << n));
}

int clearNRightBits (int v, int n) {
    return (v & (~0 << n));
}

int clearNLeftBits (int v, int n) {
    return (v & (~0 >> n));
}

int updateNBit (int v, int n, int b) {
    int tmp = (v & ~(1 << n));   // clear n bit
        tmp = tmp | (b << n);    // set   n bit  to b
    return tmp;
}

void printBinary (int val) {
    int v = val;
    int s = sizeof(v) * 8;
    for (int i = s-1; i >= 0; i--) {
        cout << getNBit(v, i) << " ";
    }
    cout << endl;
}

/* ==============================Swap Two Numbers Without Temporal================================*/
void swap (int& a, int&b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

/* =============================r = a ? b : c Without If==========================================*/
// BUT:  a > 0 is true, a == 0 is false
int conditional_ (int a, int b, int c) {
       return (!!a * b) + (!a * c);
}

/* ============================= Is Power of 2? ==================================================*/
// NOTE: also flips first 1 in the left to 0.
bool isPowerOfTwo (int a) {
    return ( (a & (a - 1)) == 0);
}

/* =============================r = (a > b) ? a : b Without If====================================*/
// TIP: This is equivalent to r = (a >= b ? a : b), therefore finding the maximum
// TIP: r = (a - b) >= 0 ? a : b
int maximum_ (int a, int b) {
    int nbr = sizeof(int) * 8;
    // int isNegative = (a - b) & ( 1 << (nbr-1) );
    // return !!isNegative * b + !isNegative * a;
    int isNegative = ((a - b) >> (nbr - 1)) & 1;
    return isNegative * b + !isNegative * a;
}
int maximum_v2 (int a, int b) {
    int t = a - b;
    int nbr = sizeof(int) * 8;
    int neg = ( (a-b) >> (nbr - 1)) & 1;
    int res = a - neg * t;
    return res;

}
/* =========================Number of Bit Flips to Convert A to B=================================*/
int bitFlipsToTransform (int a, int b) {
    int c  = a ^ b;
    int res = 0;
    while (c) {
        res += c & 1;
        c = c >> 1;
    }
    return res;
}

int bitFlipsToTransform_ (int a, int b) {
    int c   = a ^ b;
    int res = 0;
    while (c) {
        res++;
        c = c & (c-1);
    }
    return res;
}

/* =========================Swap Bits in Odd positions with Even Positions========================*/
int swapEvenOddBits (int a) {
    int maskEven = 0xaaaaaaaa;
    int maskOdd  = 0x55555555;
    maskEven = a & maskEven;
    maskOdd  = a & maskOdd;
    maskEven = maskEven >> 1;
    maskOdd  = maskOdd  << 1;
    return maskEven | maskOdd;
}

/* =========================Sum without arithmetic operations ====================================*/
int sum_ (int a, int b) {
    if (!b) return a;
    int carry = a & b;
    int sum   = a ^ b;
    return sum_ (sum, carry << 1);
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void printBinary_example() {
    cout << "-1  is: "; printBinary(-1);
    cout << "127 is: "; printBinary(127);
}
void swap_example() {
    int a = 4;
    int b = 10;
    swap(a,b);
    cout << "Swapping a=4 b=10 is: " << a << " " << b << endl;
}
void conditional_example() {
    cout << "Conditional a ? b : c , where a = 4, b = 2, c = 1 is: " << conditional_(4,2,1) << endl;
    cout << "Conditional a ? b : c , where a = 0, b = 2, c = 1 is: " << conditional_(0,2,1) << endl;
}
void maximum_example() {
    cout << "Maximum between 8   and 17 is: " << maximum_(8,17)    << endl;
    cout << "Maximum between 19  and 1  is: " << maximum_(19,1)    << endl;
    cout << "Maximum between 4   and 12 is: " << maximum_v2(4,12)  << endl;
    cout << "Maximum between -12 and 1  is: " << maximum_v2(-12,1) << endl;
}
void isPowerOfTwo_example() {
    cout << "4  is power of 2 ? : " << isPowerOfTwo(4)  << endl;
    cout << "0  is power of 2 ? : " << isPowerOfTwo(0)  << endl;
    cout << "64 is power of 2 ? : " << isPowerOfTwo(64) << endl;
    cout << "-8 is power of 2 ? : " << isPowerOfTwo(-8) << endl;
    cout << "7  is power of 2 ? : " << isPowerOfTwo(7)  << endl;
}
void bitFlipsToTransform_example() {
    cout << "Bit flips to transform 29  to 15 is : "  << bitFlipsToTransform(29, 15) << endl;
    cout << "Bit flips to transform 126 to 127 is : " << bitFlipsToTransform_(126, 127) << endl;
}
void swapEvenOddBits_example() {
    cout << "Swapping even and odd bits of \n\t"; printBinary(787397085);
    cout << "\t"; printBinary(swapEvenOddBits(787397085));
}
void sum_example() {
    cout << "Adding 127 and 1151 is : " << sum_(127,1151) << endl;
}

/* ===============================================================================================*/
int main () {
    printBinary_example();
    swap_example();
    conditional_example();
    maximum_example();
    isPowerOfTwo_example();
    bitFlipsToTransform_example();
    swapEvenOddBits_example();
    sum_example();
}

/* =======================================TODO====================================================*/
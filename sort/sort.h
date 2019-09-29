#pragma once
#include <vector>
#include <cmath>

// Sorting algorithms that Leon Wang implemented while studing them.
// Time taken for 10000 integer sorting can be found in the main() comments in .cpp file.

using vint=std::vector<int>;

class my_sort {
public:
    virtual void mysort(vint& list) {};
    virtual void show() {};
};

// O(n^2). In-place sorting.
class BubbleSort : public my_sort {
public:
    void mysort(vint& list) override;
};

// O(n*log(n)). vector data copy is required at each divide or merge.
class MergeSort : public my_sort {
private:
    void MergeOrdered(vint& left, vint& right, vint& merged);
public:
    void mysort(vint& list) override;
};

// O(n^2) worst case but close to O(n*log(n)) in practice due to pivot value chosen. in-place sort.
class QuickSort : public my_sort {
private:
    int Partition(vint& list, int low, int high); // In place partition is performed from low to high inclusive. The last element is used as pivotal value.
    void mysort(vint& list, int low, int high);   // Internal in place sorting from low to high inclusive in ascending order. This is to eliminate vector copy when sorting.
public:
    void mysort(vint& list) override;
};

// O(n^2), in-place sort.
class InsertionSort : public my_sort {
public:
    void mysort(vint& list) override;
};

// RadixSorter retuires additional space of n to hold data for each digit data bin. It's not an in-place sorting. 
/* The following comments are copied from https://www.geeksforgeeks.org/radix-sort/. There is an interesting implementation there.

What is the running time of Radix Sort?
Let there be d digits in input integers. Radix Sort takes O(d*(n+b)) time where b is the base for representing numbers, 
for example, for decimal system, b is 10. What is the value of d? If k is the maximum possible value, then d would be 
O(logb(k)). So overall time complexity is O((n+b) * logb(k)). Which looks more than the time complexity of comparison 
based sorting algorithms for a large k. Let us first limit k. Let k <= nc where c is a constant. In that case, the 
complexity becomes O(nLogb(n)). But it still doesn’t beat comparison based sorting algorithms.
What if we make value of b larger?. What should be the value of b to make the time complexity linear? 
If we set b as n, we get the time complexity as O(n). In other words, we can sort an array of integers with 
range from 1 to nc if the numbers are represented in base n (or every digit takes log2(n) bits).

Is Radix Sort preferable to Comparison based sorting algorithms like Quick-Sort?
If we have log2n bits for every digit, the running time of Radix appears to be better than Quick Sort for a wide 
range of input numbers. The constant factors hidden in asymptotic notation are higher for Radix Sort and 
Quick-Sort uses hardware caches more effectively. Also, Radix sort uses counting sort as a subroutine and counting 
sort takes extra space to sort numbers.
*/
// This implementation supports positive numbers in the range 1 to RAND_MAX on the system.
class RadixSort : public my_sort {
#define DIGIT_BINS (256)   // Numbers in a digit
#define BITS_PER_DIGIT (8)
#define DIGIT_MASK (0xff)
public:
    RadixSort() { // When RAND_MAX is 32767, maxKeySize is 4;
        int largest = RAND_MAX;
        maxKeySize = 1;
        while ((largest >>= BITS_PER_DIGIT) != 0) maxKeySize++;
    };
    void mysort(vint& list) override;
    void show() {
        std::cout << "maxKeySize=" << maxKeySize << " BITS_PER_DIGIT=" << BITS_PER_DIGIT << " DIGIT_BINS=" << DIGIT_BINS << std::endl;
    }
private:
    unsigned int maxKeySize;  // Number of digits of the maximum number in list. 
    //const int bits_per_digit= int_log2(DIGIT_BINS);
    constexpr static unsigned int int_log2(unsigned int x) {
        unsigned int i = 0;
        while (x >>= 1) i++;
        return i;
    }
};
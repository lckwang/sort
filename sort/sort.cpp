// sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "sort.h"

int main()
{
    using namespace std;
    // Note that time taken is run in  in Debug mode and in a single thread.
    //BubbleSort sorter;   // 4393ms for 10000 elements
    //MergeSort  sorter;      // 88ms for 10000 elements
    //QuickSort  sorter;      // 13 ms for 10000 elements.  47ms for 30000 elements.
    //InsertionSort  sorter;      // 1394 ms for 10000 elements
    RadixSort sorter;         // 18ms for 10000 elements.  53ms for 30000 elements when digit base is 16. 36ms for 30000 elements when digit base is 256. 

    sorter.show();

    cout << "RAND_MAX= " << RAND_MAX << endl << endl;;
    //cout << sorter2.maxKeySize << endl;

    auto v = vint{ 64*300+35, 5,32,88,99,1088, 1204+256+3, 67,3,16,275,4,1,17,307 };
    cout << "input=  ";
    for_each(v.begin(), v.end(), [](auto x) {cout << x << ","; });
    cout << endl << "output= ";
    sorter.mysort(v);
    for (auto x : v) {
        std::cout << x << ",";
    }
    cout << endl << endl;
    v = vint{ 5};
    cout << "input=  ";
    for_each(v.begin(), v.end(), [](auto x) {cout << x << ","; });
    cout << endl << "output= ";
    sorter.mysort(v);
    for (auto x : v) {
        std::cout << x << ",";
    }
    cout << endl << endl;

#if 1  // Large array sort. Time taken will be printed in ms.
    int n = 30000;
    v = vint(n);
    for (int i = 0; i < n; i++) v[i] = rand();
    cout << "input=  ";
//    for_each(v.begin(), v.end(), [](auto x) {cout << x << ","; });
    cout << endl << "output= ";
    clock_t time_req = clock();
    sorter.mysort(v);
    time_req = clock() - time_req;
    for (auto x : v) {
        std::cout << x << ",";
    }
    cout << endl << endl;
    cout << (float)time_req / (CLOCKS_PER_SEC / 1000) << " ms is taken for " << n << " elements sort().";
    cout << endl << endl;
#endif

}

using namespace std;
void BubbleSort::mysort(vint& list) {
    int size = list.size();
    if (size == 0) return;

    for (int i = 0; i < (size - 1); i++) {
        for (int j = i; j < size; j++) {
            if (list[i] > list[j])
                swap(list[i], list[j]);
        }
    }
}

// Merge two ordered list to the merged list.
void MergeSort::MergeOrdered(vint& left, vint& right, vint& merged) {
    unsigned int i, j;

    i = j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            merged[i + j] = left[i];
            i++;
        }
        else {
            merged[i + j] = right[j];
            j++;
        }
    }
    for (; i < left.size(); i++)  merged[i + j] = left[i];
    for (; j < right.size(); j++) merged[i + j] = right[j];
}
void MergeSort::mysort(vint& list) {
    if (list.size() <= 1) return;

    int m = list.size() / 2;

    vint left(m), right(list.size() - m);

    copy(list.begin(), list.begin() + m, left.begin()); // copy m elements to the left vector
    copy(list.begin() + m, list.end(), right.begin()); // copy size-m elements to the right vector

    mysort(left);
    mysort(right);
    MergeOrdered(left, right, list);
    return;
}

int QuickSort::Partition(vint& list, int low, int high) {
    // In place partition is performed from low to high inclusive. The last element is used as pivotal value.
    auto pivot = list[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (list[j] < pivot) {
            std::swap(list[i], list[j]);
            i++;
        }
    }
    std::swap(list[i], list[high]);
    return i;
}

void QuickSort::mysort(vint& list, int low, int high) {
    // In place sort is performed from low to high inclusive in ascending order.
    if ( (high-low) <= 1) return;
    int i = Partition(list, low, high);
    mysort(list, low, i - 1);
    mysort(list, i + 1, high);
}
void QuickSort::mysort(vint& list) {
    mysort(list, 0, list.size() - 1);
}

void InsertionSort::mysort(vint& list) {
    unsigned int unsorted =1;
    int i;
    while (unsorted < list.size()) {
        auto hold = list[unsorted];
        for (i = unsorted - 1; i >= 0 && hold < list[i]; i--) {
            list[i + 1] = list[i];
        }
        list[i+1] = hold;
        unsorted++;
    }
}

//template <int nth>
//constexpr auto bits_to_shift() { return nth * BITS_PER_DIGIT; }
//#define GET_DIGIT(x, nth) ((x>>(bits_to_shift<nth>())) & DIGIT_MASK)
void RadixSort::mysort(vint& list) {
#define GET_DIGIT0(x) (x & DIGIT_MASK)
#define GET_DIGIT(x, nth) ((x>>(nth*BITS_PER_DIGIT)) & DIGIT_MASK)
    vector<vint> oldbins(DIGIT_BINS);
    vector<vint> newbins(DIGIT_BINS);
    for (auto& x : list) {
        oldbins[GET_DIGIT0(x)].push_back(x);
    }

#if 1
    for (unsigned int n = 1; n < maxKeySize; n++) {
        for (int i = 0; i < DIGIT_BINS; i++) {
            for (unsigned int j = 0; j < oldbins[i].size(); j++) {
                newbins[GET_DIGIT(oldbins[i][j], n)].push_back(oldbins[i][j]);
            }
        }
        for (int i = 0; i < DIGIT_BINS; i++) {
            oldbins[i] = move(newbins[i]);
        }
    }
    list.clear();
    for (int i = 0; i < DIGIT_BINS; i++) {
        for (unsigned int j = 0; j < oldbins[i].size(); j++) {
            list.push_back(oldbins[i][j]);
        }
    }
#endif
    return;
}


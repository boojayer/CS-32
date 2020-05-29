#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;


bool somePredicate(double x)
{
    return x < 0;
}

// Return true if the somePredicate function returns false for at
 // least one of the array elements; return false otherwise.
bool anyFalse(const double a[], int n)
{
    if (n == 0)
        return false;
    if (somePredicate(*a))
        return true;
    else
        return anyFalse(a + 1, n - 1);
}


// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n == 0)
        return false;
    if(somePredicate(*a))
        return 1 + countTrue(a + 1, n - 1);
    else
        return 0 + countTrue(a + 1, n - 1);
}


// Return the subscript of the first element in the array for which
// the somePredicate function returns true. If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n == 0)
        return -1;
    
    if (somePredicate(*a))
        return *a;
    else
        return firstTrue(a + 1, n - 1);
}


// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1). If the function is told to examine no
// elements, return -1.
int positionOfSmallest(const double a[], int n)
{
    if (n == 0)
        return -1;
    if (n == 1)
        return 0;
    
    n -= 1;
    int temp = positionOfSmallest(a , n);
    if (a[n] < a[temp])
        return n ;
    else
        return temp;
}


// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
// 10 50 40 20 50 40 30
// then the function should return true if a2 is
// 50 20 30
// or
// 50 40 40
// and it should return false if a2 is
// 50 30 20
// or
// 10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 == 0)
        return true;
    if (n1 == 0)
        return false;

    if (a1[0] == a2[0])
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    else
        return contains(a1 + 1, n1 - 1, a2, n2);
}/*int main(){
    double a1[1] = {1};
    double a2[1] = {-1};
    double a3[5] = {-1, -2, -3, -4, -5};
    double a4[5] = {3, 5, 2, 1, 4};
    double a5[5] = {-1, -2, -3, -4, 5};
    double a6[6] = {1, 2, 3, 4, -5, 6};
    double s6[3] = { 1, 3, -5 };

   /*
    assert(anyFalse(a1, 1) == false);
    assert(anyFalse(a2, 1) == true);
    assert(anyFalse(a3, 5) == true);
    assert(anyFalse(a4, 5) == false);
    assert(anyFalse(a5, 5) == true);
    assert(anyFalse(a6, 5) == true);
    
    assert(countTrue(a1, 1) == 0);
    assert(countTrue(a2, 1) == 1);
    assert(countTrue(a3, 5) == 5);
    assert(countTrue(a4, 5) == 0);
    assert(countTrue(a5, 5) == 4);
    assert(countTrue(a6, 5) == 1);

    assert(firstTrue(a1, 1) == -1);
    assert(firstTrue(a2, 1) == -1);
    assert(firstTrue(a3, 5) == -1);
    assert(firstTrue(a4, 5) == -1);
    assert(firstTrue(a5, 5) == -1);
    assert(firstTrue(a6, 5) == -5);
    
    assert(positionOfSmallest(a1, 1) == 0);
    assert(positionOfSmallest(a2, 1) == 0);
    assert(positionOfSmallest(a3, 5) == 4);
    assert(positionOfSmallest(a4, 5) == 3);
    assert(positionOfSmallest(a5, 5) == 3);
    assert(positionOfSmallest(a6, 5) == 4);           assert(contains(a1, 1, a1, 1) == true);
   assert(contains(a3, 5, a2, 1) == true);
   assert(contains(a2, 1, a3, 5) == false);
   assert(contains(a6, 5, s6, 3) == true);
   assert(contains(a6, 6, s6, 3) == true);
   assert(contains(a6, 3, s6, 3) == false);   assert(contains(a4, 3, s6, 3) == false);   cout << "All tests passed." << endl;}*/
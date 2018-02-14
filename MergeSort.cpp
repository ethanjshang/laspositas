/*
 --------------------------------------------------------------------------------------------
 |                          | Bubble Sort               | Merge Sort                        |
 --------------------------------------------------------------------------------------------
 | Performance (Best)       | N                         | N logN                            |
 --------------------------------------------------------------------------------------------
 | Performance (Worst)      | N^2                       | N logN                            |
 --------------------------------------------------------------------------------------------
 | Performance (Average)    | ~N^2                      | N logN                            |
 --------------------------------------------------------------------------------------------
 | Memory Allocated         | -Only array to be sorted  | -Mutiple arrays must be allocated |
 |                          | -Contained in 1 function  | -Mutiple functions must be called |
 --------------------------------------------------------------------------------------------
 | Type of Algorithm        | Iterative                 | Recursive                         |
 --------------------------------------------------------------------------------------------
 | Difficulty to Write      | Introductory level        | Moderately difficult              |
 --------------------------------------------------------------------------------------------
 | Lines used to Write      | Relatively few            | Multiple functions needed         |
 --------------------------------------------------------------------------------------------
 
 
 */




#include<iostream>
#include<string>
#include<vector>
#include <time.h>
#include <stdlib.h>

using namespace std;
const int SIZE2 = 100;
int * myMerge(int A[], int size1, int B[], int size2, int &);
int * merge_sort(int [], int n, int &);
int * bubbleSortArray(int[], int, int &);

int main() {
    int *T;
    int *S;
    static int compsT = 0;
    static int compsS = 0;
    int E[SIZE2];
    srand(time(NULL));
    for (int i =0; i < SIZE2; i++){
        E[i] = rand() % 100; //Generate random numbers 0-99
    }
    cout << "The array to be sorted is the following:" << endl;
    for (int k = 0; k < SIZE2; k++) {
        cout << "  " << E[k];
        if (k%10 == 9){
            cout << endl;
        }
    }
    cout << endl << endl;
    T = merge_sort(E, SIZE2, compsT);
    S = bubbleSortArray(E,SIZE2, compsS);
    cout << "(1) MERGE SORT" << endl;
    cout << "Comparisons made in Merge Sort: " << compsT << endl;
    cout << "Merge Sort Output of two arrays is:" << endl;
        for (int k = 0; k < SIZE2; k++) {
            cout << "  " << T[k];
            if (k%10 == 9){
                cout << endl;
            }
        }
        cout << endl << endl;
    
    cout << "(2) BUBBLE SORT" << endl;
    cout << "Comparisons made in Bubble Sort: " << compsS << endl;
    cout << "Bubble Sort Output is:" << endl;
        for (int k = 0; k < SIZE2; k++) {
            cout << "  " << S[k];
            if (k%10 == 9){
                cout << endl;
            }
        }
        cout << endl << endl;
    
    return 0;

}
int * myMerge(int A[], int size1, int B[], int size2, int & compNum){
    int *T = new int[size1+size2];
    int iA = 0, iB = 0;
    int iT = 0;
    for (int i = 0; i < size1+size2; i++){
        T[i] = 0;
    }
    for (iT = 0; iT < (size1+size2); iT++) {
        if (A[iA] < B[iB]){
            T[iT] = A[iA];
            iA++;
            compNum++;
        }
        else if (A[iA] > B[iB]){
            T[iT] = B[iB];
            iB++;
            compNum++;
        }
        else if (A[iA] == B[iB]){
            T[iT] = A[iA];
            iT++;
            iA++;
            T[iT] = B[iB];
            iB++;
            compNum++;
        }
        if (iA == size1 || iB == size2)
            break;
    }
    iT = iA + iB;
    if (iA< size1){
        for (int i = iA; i<size1;i++, iT++){
            T[iT] = A[i];
        }
    }
    else if (iB<size2){
        for (int i = iB;i<size2;i++,iT++){
            T[iT] = B[i];
        }
    }
    
    return T;
}

int * merge_sort(int arr[], int n, int & comp){
    if (n<2){
        return arr;
    }
    int mid = n/2;
    int *T1 = merge_sort(arr,mid, comp);
    int *T2 = merge_sort(arr+mid,n-mid, comp);
    return myMerge(T1,mid,T2,n-mid,comp);
}


int * bubbleSortArray(int array[], int elems, int & comp) {
    bool swap;
    int temp;
    int bottom = elems - 1; // bottom indicates the end part of the
    // array where the largest values have settled in order
    do {
        swap = false;
        for (int count = 0; count < bottom; count++) {
            if (array[count] > array[count + 1]) { // the next three lines do a swap
                temp = array[count];
                array[count] = array[count + 1];
                array[count + 1] = temp;
                swap = true; // indicates that a swap occurred
            }
            comp++;
        }
        bottom--; // bottom is decremented by 1 since each pass through
        // the array adds one more value that is set in order
    } while (swap != false);
    // loop repeats until a pass through the array with
    // no swaps occurs
    return array;
}


// The following is remnants of the process used to write this code
// in case you wanted to see work.
//
// const int SIZE = 5;
// int A[SIZE] = { 3, 6, 23, 26, 28 };
// int B[SIZE] = { 8, 11, 23, 88, 99 };
//T = myMerge(A,SIZE,B,SIZE);
//int C[2*SIZE] = {99,3,11,23,88,23,26,6,8,28};
//int D[2*SIZE] = {99,3,11,23,88,23,26,6,8,28};

//    T = merge_sort(C,2*SIZE,compsT);
//    S = bubbleSortArray(D, 2*SIZE, compsS);
//    cout << "Merge Sort Output of two arrays is";
//    for (int k = 0; k < 2 * SIZE; k++) {
//        cout << "  " << T[k];
//    }
//    cout << endl;
//    cout << "Comparisons made in Merge Sort: " << compsT << endl;
//    cout << "Bubble Sort Output is";
//    for (int k = 0; k < 2 * SIZE; k++) {
//        cout << "  " << S[k];
//    }
//    cout << endl;
//    cout << "Comparisons made in Bubble Sort: " << compsS << endl;


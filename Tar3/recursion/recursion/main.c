#include <stdio.h>
#include <time.h>
#include "ass3.h"
#define _CRT_SECURE_NO_WARNINGS

extern int counter;

void powManager(double base, int exp) {
    double iter = iterPow(base, exp);
    printf("iter: %g^%d = %g\n", base, exp, iter);
     printf("%d\n", counter);
    counter = 0;
    double rec  = recPow(base, exp);
    printf("rec : %g^%d = %g\n", base, exp, rec);
     printf("%d\n", counter);
    counter = 0;
    double effi  = recEffiPow(base, exp);
    printf("effi: %g^%d = %g\n", base, exp, effi);
     printf("%d\n", counter);
	counter = 0;
}

void arrManager() {
	int arr[MAX][MAX] = {{1,2,3,4},{555,6,77,8},{9999,10,11111,12}};
	//int arr[5][5] = { {1,2,3,4},{555,6,77,8},{9999,10,11111,12} };
	printArr2D(arr, 3, 4);
}

void checkPerm(int arr1[], int size1, int arr2[], int size2) {
    if (isPermutation(arr1, size1, arr2, size2)) {
        printf("Yes!\n");
    } else {
        printf("No!\n");
    }
}

void permManager() {
	int arr1[MAX] = {1,2,3,4,5};
    int arr2[MAX] = {5,3,2,1,4};
	//int arr1[MAX] = {0,3,0,3};
	//int arr2[MAX] = {0,0,3,0};
	int size1 = sizeof(arr1) / sizeof(int);
	int size2 = sizeof(arr2) / sizeof(int);
	checkPerm(arr1, size1, arr2, size2);
	arr2[0] = 0;
	checkPerm(arr1, size1, arr2, size2);

	for (int i = 0; i < size1; i++) {
		arr1[i] = i;
	}
	for (int i = 0; i < size2; i++) {
		arr2[i] = size2 - 1 - i;
	}
	checkPerm(arr1, size1, arr2, size2);
}

int main() {
	//permManager();
    powManager(1.5, 3);
    powManager(0,10);
    powManager(2, 8);
    powManager(0, -2);
    arrManager();
    permManager();
}

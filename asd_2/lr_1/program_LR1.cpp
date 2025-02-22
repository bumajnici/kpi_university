#include<iostream>
#include<iomanip>
#include<ctime>
#include<chrono>
#include<array>

using namespace std;
using namespace chrono;

void printArray(int[], int);
void copyArray(int*, int*, int);
void fillArray(int*, int);
void reverseFillArray(int*, int);
void fillArrayWithRandomNumbers(int*, int, int, int);

const int minInteger = 1;
const int size10 = 10;
const int size100 = 100;
const int size1000 = 1000;
const int size5000 = 5000;
const int size10000 = 10000;
const int size20000 = 20000;
const int size50000 = 50000;

void sortArraysWithUserInputSize_TEST(int);

array<double, 3> bubbleSort(int arr[], int n) {
    array<double, 3> iter_replaces_seconds_Count = { 0,0,0 };
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                iter_replaces_seconds_Count[1]++;
            }
            iter_replaces_seconds_Count[0]++;
        }
    }
    auto end = high_resolution_clock::now();
    iter_replaces_seconds_Count[2] = duration_cast<microseconds>(end - start).count() / 1000000.0;
    return iter_replaces_seconds_Count;
}
array<double, 3> modBubbleSort(int arr[], int n) {
    array<double, 3> iter_replaces_seconds_Count = { 0, 0, 0 };
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                iter_replaces_seconds_Count[1]++;
            }
            iter_replaces_seconds_Count[0]++;
        }
        n--;
        if (!swapped)
            break;
    }
    auto end = high_resolution_clock::now();
    iter_replaces_seconds_Count[2] = duration_cast<microseconds>(end - start).count() / 1000000.0;
    return iter_replaces_seconds_Count;
}
array<double, 3> combSort(int arr[], int n) {
    array<double, 3> iter_replaces_seconds_Count = { 0, 0, 0 };
    auto start = high_resolution_clock::now();
    int gap = n;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1)
            gap = 1;
        swapped = false;
        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
                iter_replaces_seconds_Count[1]++;
            }
            iter_replaces_seconds_Count[0]++;
        }
    }
    auto end = high_resolution_clock::now();
    iter_replaces_seconds_Count[2] = duration_cast<microseconds>(end - start).count() / 1000000.0;
    return iter_replaces_seconds_Count;
}

int main(void)
{
    system("color F0");
    srand(time(0));

    int inputSize;
    cout << "Enter size: ";
    cin >> inputSize;
    sortArraysWithUserInputSize_TEST(inputSize);

    return 0;
}

void sortArraysWithUserInputSize_TEST(int size) {
    int* sortedArray = new int[size];
    int* reverseSortedArray = new int[size];
    int* randomFilledArray = new int[size];

    array<double, 3> sortedToBubbleSort, sortedToModBubbleSort, sortedToCombSort;
    array<double, 3> reverseSortedToBubbleSort, reverseSortedToModBubbleSort, reverseSortedToCombSort;
    array<double, 3> randomFilledToBubbleSort, randomFilledToModBubbleSort, randomFilledToCombSort;

    fillArray(sortedArray, size);
    reverseFillArray(reverseSortedArray, size);
    fillArrayWithRandomNumbers(randomFilledArray, size, minInteger, size);

    int* copyForBubbleSort = new int[size];
    int* copyForModBubbleSort = new int[size];
    int* copyForCombSort = new int[size];

    copyArray(sortedArray, copyForBubbleSort, size);
    copyArray(sortedArray, copyForModBubbleSort, size);
    copyArray(sortedArray, copyForCombSort, size);
    sortedToBubbleSort = bubbleSort(copyForBubbleSort, size);
    sortedToModBubbleSort = modBubbleSort(copyForModBubbleSort, size);
    sortedToCombSort = combSort(copyForCombSort, size);
    cout << "Array before sort(already sorted):" << endl;
    printArray(sortedArray, size);
    cout << "Array after sort(already sorted):" << endl;
    printArray(copyForBubbleSort, size);
    cout << "RESULT FOR BUBBLE SORT:" << endl;
    cout << "Iterations:\t" << sortedToBubbleSort[0] << endl;
    cout << "Replaces:\t" << sortedToBubbleSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << sortedToBubbleSort[2] << endl;
    cout << fixed << setprecision(0);
    cout << "RESULT FOR MOD BUBBLE SORT:" << endl;
    cout << "Iterations:\t" << sortedToModBubbleSort[0] << endl;
    cout << "Replaces:\t" << sortedToModBubbleSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << sortedToModBubbleSort[2] << endl;
    cout << fixed << setprecision(0);
    cout << "RESULT FOR COMB SORT:" << endl;
    cout << "Iterations:\t" << sortedToCombSort[0] << endl;
    cout << "Replaces:\t" << sortedToCombSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << sortedToCombSort[2] << endl;
    cout << fixed << setprecision(0);

    copyArray(reverseSortedArray, copyForBubbleSort, size);
    copyArray(reverseSortedArray, copyForModBubbleSort, size);
    copyArray(reverseSortedArray, copyForCombSort, size);
    reverseSortedToBubbleSort = bubbleSort(copyForBubbleSort, size);
    reverseSortedToModBubbleSort = modBubbleSort(copyForModBubbleSort, size);
    reverseSortedToCombSort = combSort(copyForCombSort, size);
    cout << "Array before sort(reverse sorted):" << endl;
    printArray(reverseSortedArray, size);
    cout << "Array after sort(reverse sorted):" << endl;
    printArray(copyForBubbleSort, size);
    cout << "RESULT FOR BUBBLE SORT:" << endl;
    cout << "Iterations:\t" << reverseSortedToBubbleSort[0] << endl;
    cout << "Replaces:\t" << reverseSortedToBubbleSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << reverseSortedToBubbleSort[2] << endl;
    cout << fixed << setprecision(0);
    cout << "RESULT FOR MOD BUBBLE SORT:" << endl;
    cout << "Iterations:\t" << reverseSortedToModBubbleSort[0] << endl;
    cout << "Replaces:\t" << reverseSortedToModBubbleSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << reverseSortedToModBubbleSort[2] << endl;
    cout << fixed << setprecision(0);
    cout << "RESULT FOR COMB SORT:" << endl;
    cout << "Iterations:\t" << reverseSortedToCombSort[0] << endl;
    cout << "Replaces:\t" << reverseSortedToCombSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << reverseSortedToCombSort[2] << endl;
    cout << fixed << setprecision(0);

    copyArray(randomFilledArray, copyForBubbleSort, size);
    copyArray(randomFilledArray, copyForModBubbleSort, size);
    copyArray(randomFilledArray, copyForCombSort, size);
    randomFilledToBubbleSort = bubbleSort(copyForBubbleSort, size);
    randomFilledToModBubbleSort = modBubbleSort(copyForModBubbleSort, size);
    randomFilledToCombSort = combSort(copyForCombSort, size);
    cout << "Array before sort(randomly filled):" << endl;
    printArray(randomFilledArray, size);
    cout << "Array after sort(randomly filled):" << endl;
    printArray(copyForBubbleSort, size);
    cout << "RESULT FOR BUBBLE SORT:" << endl;
    cout << "Iterations:\t" << randomFilledToBubbleSort[0] << endl;
    cout << "Replaces:\t" << randomFilledToBubbleSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << randomFilledToBubbleSort[2] << endl;
    cout << fixed << setprecision(0);
    cout << "RESULT FOR MOD BUBBLE SORT:" << endl;
    cout << "Iterations:\t" << randomFilledToModBubbleSort[0] << endl;
    cout << "Replaces:\t" << randomFilledToModBubbleSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << randomFilledToModBubbleSort[2] << endl;
    cout << fixed << setprecision(0);
    cout << "RESULT FOR COMB SORT:" << endl;
    cout << "Iterations:\t" << randomFilledToCombSort[0] << endl;
    cout << "Replaces:\t" << randomFilledToCombSort[1] << endl;
    cout << fixed << setprecision(15);
    cout << "Time(seconds):\t" << randomFilledToCombSort[2] << endl;
    cout << fixed << setprecision(0);

    delete[] sortedArray;
    delete[] reverseSortedArray;
    delete[] randomFilledArray;
    delete[] copyForBubbleSort;
    delete[] copyForModBubbleSort;
    delete[] copyForCombSort;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void copyArray(int* source, int* destination, int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}
void fillArray(int* arr, int size) {
    for (int i = 0; i < size;i++) {
        arr[i] = i + 1;
    }
}
void reverseFillArray(int* arr, int size) {
    int j = size;
    for (int i = 0; i < size;i++) {
        arr[i] = j;
        j--;
    }
}
void fillArrayWithRandomNumbers(int* array, int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        array[i] = min + rand() % (max - min + 1);
    }
}
#include "Array.hpp"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    
    // usage:
    /*
        int intArr[5] = {5, 3, 1, 4, 2};
        ArrayLib::Array<int> intArray(intArr, 5);

        cout << "Int array: " << intArray << endl;
        cout << "Element at index 2: " << intArray[2] << endl;

        intArray.sort();
        cout << "Sorted int array: " << intArray << endl;

        ++intArray;
        cout << "After ++: " << intArray << endl;

        double doubleArr[5] = {5.5, 4.5, 3.5, 2.5, 1.5};
        ArrayLib::Array<double> doubleArray(doubleArr, 5);

        cout << "\nDouble array: " << doubleArray << endl;
        cout << "Element at index 2: " << doubleArray[2] << endl;

        doubleArray.sort();
        cout << "Sorted double array: " << doubleArray << endl;

        ++doubleArray;
        cout << "After ++: " << doubleArray << endl;

        ArrayLib::Array<double> copyArray = doubleArray;
        cout << "\nCopied array: " << copyArray << endl;

        ArrayLib::Array<double> arr1(doubleArr, 5);
        ArrayLib::Array<double> arr2(doubleArr, 5);

        try {
            ArrayLib::Array<double> sum = arr1 + arr2;
            cout << "\nSum of arrays: " << sum << endl;
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }

        ArrayLib::Array<int> arr5(5);
        cout << "array of NULLS: " << arr5 << endl;

        ArrayLib::Array<int> array(5);
        cout << "Enter 5 integers: ";
        for (int i = 0; i < 5; i++) {
            cin >> array[i];
        }
        cout << "Your array: " << array << endl;

        ArrayLib::Array<int> array2(5);
        cout << "Enter another 5 integers: ";
        for (int i = 0; i < 5; i++) {
            cin >> array2[i];
        }
        cout << "Second array: " << array2 << endl;

        if (array == array2) {
            cout << "the same" << endl;
        } else {
            cout << "not same" << endl;
        }
    */
    return 0;
}
#include <iostream>

using namespace std;

// Function template for selection sort
template <typename T>
void selectionSort(T arr[], int size) {
    // Iterate through the array
    for (int i = 0; i < size - 1; i++) {
        // Initialize the minimum index
        int minIndex = i;

        // Find the minimum element in the unsorted part of the array
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted part
        T temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

// Function to print the array
template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // Example usage with integers
    int size,arr[100];
    float floatarr[100];
    while(true){
        int ch;
        cout<<"Enter choice\n1.int\n2.flaot";
        cin>>ch;
        switch(ch){
            case 1:
                cout<<"Enter no. of elements";
                cin>>size;
                for(int i=0;i<size;i++){
                    cin>>arr[i];
                }
                selectionSort(arr,size);
                printArray(arr,size);
                break;
            case 2:
                cout<<"Enter no. of elements";
                cin>>size;
                for(int i=0;i<size;i++){
                    cin>>floatarr[i];
                }
                selectionSort(floatarr,size);
                printArray(floatarr,size);
                break;
            default:
                cout<<"INvalid choice";
                
        }
    }
    return 0;
}
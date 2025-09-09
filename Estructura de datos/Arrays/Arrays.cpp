#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    arr[0] = 10;
    int valor = arr[2];
    cout << "Valor 2 del array: " << valor << endl;
    for(int i = 0; i < 5; i++){
        cout << arr[i] << endl;
    }
    return 0;
}

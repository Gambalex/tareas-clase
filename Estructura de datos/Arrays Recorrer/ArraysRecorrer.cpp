#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> datos = {10, 25, 37, 42, 58};

    cout << "Recorrido del arreglo:" << endl;
    for (int val : datos) {
        cout << val << endl;
    }

    return 0;
}

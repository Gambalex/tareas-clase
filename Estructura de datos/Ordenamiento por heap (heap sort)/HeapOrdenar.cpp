#include <iostream>
using namespace std;

void HeapOrdenar(int arreglo[], int n) {
    // Implementación del algoritmo HeapOrdenar
}

int main() {
    int arreglo[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);
    HeapOrdenar(arreglo, n);
    for (int i = 0; i < n; i++) cout << arreglo[i] << " ";
}

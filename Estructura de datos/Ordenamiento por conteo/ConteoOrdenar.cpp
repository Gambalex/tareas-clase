#include <iostream>
using namespace std;

void ConteoOrdenar(int arreglo[], int n) {
    // Implementación del algoritmo ConteoOrdenar
}

int main() {
    int arreglo[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);
    ConteoOrdenar(arreglo, n);
    for (int i = 0; i < n; i++) cout << arreglo[i] << " ";
}

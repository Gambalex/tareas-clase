#include <iostream>
using namespace std;

void RapidoOrdenar(int arreglo[], int n) {
    // Implementación del algoritmo RapidoOrdenar
}

int main() {
    int arreglo[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arreglo) / sizeof(arreglo[0]);
    RapidoOrdenar(arreglo, n);
    for (int i = 0; i < n; i++) cout << arreglo[i] << " ";
}

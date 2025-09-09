#include <iostream>
#include <vector>
using namespace std;

void colRecorrido(const vector<vector<int>>& mat) {
    if (mat.empty() || mat[0].empty()) {
        cout << "Matriz vacía\n";
        return;
    }

    int filas = mat.size();
    int cols = mat[0].size();

    cout << "Recorrido por columnas:\n";
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < filas; i++) {
            cout << "Col " << j << ", Fila " << i << ": " << mat[i][j] << "\n";
        }
        cout << "\n";
    }
}

int main() {
    vector<vector<int>> datos = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    colRecorrido(datos);
    return 0;
}

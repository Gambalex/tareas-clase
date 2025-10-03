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
    int sumaCol0 =0;
    int sumaCol1 =0;
    int sumaCol2 =0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < filas; i++) {
            if (j == 0){
                sumaCol0 = sumaCol0 + mat[i][j];
            }
            if (j == 1){
                sumaCol1 = sumaCol1 + mat[i][j];
            }
            if (j == 2){
                sumaCol2 = sumaCol2 + mat[i][j];
            }
        }
        

    }
    cout << "La suma de la columna 0 es: " << sumaCol0 << "\n";
    cout << "La suma de la columna 1 es: " << sumaCol1 << "\n";
    cout << "La suma de la columna 2 es: " << sumaCol2 << "\n";
}

int main() {
    vector<vector<int>> datos = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };

    colRecorrido(datos);
    return 0;
}

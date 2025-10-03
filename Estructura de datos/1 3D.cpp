/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

bool buscarValor(const vector<vector<vector<int>>>& mat, int valor) {
    int capas = mat.size();   
    int filas = mat[0].size(); 
    int cols = mat[0][0].size(); 

    for (int k = 0; k < capas; k++) {              
        for (int i = 0; i < filas; i++) {        
            for (int j = 0; j < cols; j++) {      
                if (mat[k][i][j] == valor) {
                    cout << "El valor que buscas esta en ñla capa " << k << " fila " << i << " columna " << j << "\n";
                    return true;  
                }
            }
        }
    }
    cout << "Valor no encontrado" << endl;
    return false; 
}

int main() {
 
    vector<vector<vector<int>>> datos = {
        { //capa 0
            {1,2,3},
            {4,5,6},
            {7,8,9}
        },
        {//capa 1
            {10,11,12},
            {13,14,15},
            {16,17,18}
        }
    };

  
    int valor;
    cout << "Ingresa el valor a buscar: \n";
    cin >> valor;
    buscarValor(datos, valor);
    return 0;
}

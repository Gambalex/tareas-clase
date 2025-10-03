/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int>datos = {1,2,3,4,5,6,7,8,9,10}; 
    int acomulador = 0;
    int resultado = 0;
    cout << "Recorrido del arreglo:" << endl;
    for (int val : datos) {
        resultado = val % 2;
        if(resultado == 1){
            cout << "El numero " << val << " es impar \n";
            }
        else{
            cout << "El numero " << val << " es par\n";
            acomulador++;
        }
    }
    cout << "Despues de comparar los numeros, hay " << acomulador << " pares \n";
    

    return 0;
}

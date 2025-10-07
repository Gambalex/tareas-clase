#include <iostream>

using namespace std;

int main() {
    int datos[10];
    int result = 0;
    int contador = 0;
    for (int i = 0; i < 10; ++i) {
        contador++;
        cout << "Ingresa valor " << i << ": "<< endl;
        std::cin >> result;
        if(result >= 0){
            datos[i] = result;
        }
        else{
            i = 10;
            cout << "Introduciste "<< result<< " el cual es un valor negativo, por ende no se guardo y se cancelo la operacion" << endl;
        }
        }
    cout << "Recorrido del arreglo:" << endl;
    for (int i = 0; i < contador-1; ++i) {
        cout << datos[i] << endl;
    }

    return 0;
}

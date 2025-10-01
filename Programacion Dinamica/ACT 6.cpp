// C++ program to manually convert textoing to
// char array using a loop
#include <bits/stdc++.h>
using namespace std;

int main() {
    string texto = "Alex Gamboa";
    int n = texto.length();
    int numeroVocalA = 0;
    int numeroVocalE = 0;
    int numeroVocalI = 0;
    int numeroVocalO = 0;
    int numeroVocalU = 0;
    char arr[n + 1];

    arr[n] = '\0';


    for (int i = 0; i < n; i++){
        arr[i] = texto[i];
        if(isalpha(arr[i])) {
        if(toupper(arr[i])=='A')
            numeroVocalA++;
        if(toupper(arr[i])=='E')
            numeroVocalE++;
        if(toupper(arr[i])=='I')
            numeroVocalI++;
        if(toupper(arr[i])=='O')
            numeroVocalO++;
        if(toupper(arr[i])=='U')
            numeroVocalU++;
        }
    }

    cout << "Numero de caracteres: " << n << "\n";
    cout << "Numero de vocal (A): " << numeroVocalA << "\n";
    cout << "Numero de vocal (E): " << numeroVocalE << "\n";
    cout << "Numero de vocal (I): " << numeroVocalI << "\n";
    cout << "Numero de vocal (O): " << numeroVocalO << "\n";
    cout << "Numero de vocal (U): " << numeroVocalU << "\n";
    return 0;
    
}

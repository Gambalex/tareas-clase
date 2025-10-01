#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;

int main()
{
	long n1=0, n2=1, n3=0;
	int i = 0;
	int numeroSeries = 0;
	cout << "Ingresa el numero de veces a realizar la serie Fibonacci (del 1 al 20):";
	cin >> numeroSeries;
    if (numeroSeries >20){
    	cout << "Lo siento el numero es mayor de 20";
	}
	if (numeroSeries <= 20){
    	for(i=1; i<numeroSeries; i++){
	n3 = n1 + n2;
	n1 = n2;
	n2=n3;	
	cout << n3 << "\n";
	}
	}
	
}

#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int repetir = 1;
    while(repetir = 1){
        float divDolar = 18.37;
    float divEuro = 21.54;
    int bVeinte = 0;
    int bCincuenta = 0;
    int bCien = 0;
    int bDocientos = 0;
    int bQuinientos = 0;
    int bMil = 0;
    int mCincuenta = 0;
    int mUno = 0;
    int mDos = 0;
    int mCinco = 0;
    int mDiez = 0;
    float sumaMonedas = 0;
    float sumaBilletes = 0;
    float sumaTotal = 0;
    char divisa;
    cout << "ABACO EN DIVISAS" << endl;
    cout << "Ingresa cantidad de billetes de $20:" << endl;
    cin >> bVeinte;
    cout << "Ingresa cantidad de billetes de $50:" << endl;
    cin >> bCincuenta;
    cout << "Ingresa cantidad de billetes de $100:" << endl;
    cin >> bCien;
    cout << "Ingresa cantidad de billetes de $200:" << endl;
    cin >> bDocientos;
    cout << "Ingresa cantidad de billetes de $500:" << endl;
    cin >> bQuinientos;
    cout << "Ingresa cantidad de billetes de $1,000:" << endl;
    cin >> bMil;
    cout << "Ingresa cantidad de monedas de $0.50:" << endl;
    cin >> mCincuenta;
    cout << "Ingresa cantidad de monedas de $1:" << endl;
    cin >> mUno;
    cout << "Ingresa cantidad de monedas de $2:" << endl;
    cin >> mDos;
    cout << "Ingresa cantidad de monedas de $5:" << endl;
    cin >> mCinco;
    cout << "Ingresa cantidad de monedas de $10:" << endl;
    cin >> mDiez;
    sumaBilletes = (bVeinte*20) + (bCincuenta*50) + (bCien*100) + (bDocientos*200) + (bQuinientos*500) + (bMil*1000);
    sumaMonedas = (mCincuenta *0.5) + (mUno *1) + (mDos *2) + (mCinco *5) + (mDiez *10);
    sumaTotal = sumaBilletes + sumaMonedas;

    cout << "RESULTADO:" << endl;
    cout << "Suma en billetes: " << sumaBilletes << endl;
    cout << "Suma en monedas: " << sumaMonedas << endl;
    cout << "Suma en total: " << sumaTotal << endl;
    cout << "¿Quieres convertirlo a DOLAR (D) o EURO? (E) o ninguno (N)" << endl;
    cin >> divisa;
    if(divisa == 'D'){
        cout << endl << "DIVISAS:" << sumaTotal << endl;
        cout << "Suma en billetes (en dollar): " << sumaBilletes / divDolar << endl;
        cout << "Suma en monedas (en dollar): " << sumaMonedas /divDolar<< endl;
        cout << "Suma en total (en dollar): " << sumaTotal /divDolar<< endl;
    }
    if(divisa == 'E'){
        cout << endl << "DIVISAS:" << sumaTotal << endl;
        cout << "Suma en billetes (en euro): " << sumaBilletes / divDolar << endl;
        cout << "Suma en monedas (en euro): " << sumaMonedas /divDolar<< endl;
        cout << "Suma en total (en euro): " << sumaTotal /divDolar<< endl;
    }
    if(divisa == 'N'){
        cout << endl << "BYE" << sumaTotal << endl;

    }
    cout << "Quieres repetirlo(SI = 1 , NO = 0)?" << endl;
    cin >> repetir;



    }

    return 0;

}

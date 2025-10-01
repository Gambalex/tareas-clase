#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <windows.h> 
using namespace std;
void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void parImpar() {
    int numero{};
    int resultado{};
    system("cls");

    color(11);
    cout << "+--------------------------------+\n";
    cout << "¦           1- PAR O IMPAR      ¦\n";
    cout << "+--------------------------------+\n";

    color(15);
    cout << "Ingresa un numero ENTERO: ";
    cin >> numero;

    resultado = numero % 2;
    if(resultado == 1)
        cout << "El numero " << numero << " es impar";
    else
        cout << "El numero " << numero << " es par";

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void diaSemana() {
    int numero{};
    system("cls");

    color(11);
    cout << "+--------------------------------+\n";
    cout << "¦       2- DIA DE LA SEMANA     ¦\n";
    cout << "+--------------------------------+\n";

    color(15);
    cout << "Ingresa un numero entero del 1 al 7: ";
    cin >> numero;

    switch(numero){
        case 1: cout << "El numero " << numero << " corresponde al dia LUNES"; break;
        case 2: cout << "El numero " << numero << " corresponde al dia MARTES"; break;
        case 3: cout << "El numero " << numero << " corresponde al dia MIERCOLES"; break;
        case 4: cout << "El numero " << numero << " corresponde al dia JUEVES"; break;
        case 5: cout << "El numero " << numero << " corresponde al dia VIERNES"; break;
        case 6: cout << "El numero " << numero << " corresponde al dia SABADO"; break;
        case 7: cout << "El numero " << numero << " corresponde al dia DOMINGO"; break;
        default: cout << "No coloco un numero dentro del parametro solicitado"; break;
    }

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void mesAno() {
    int numero{};
    system("cls");

    color(11);
    cout << "+--------------------------------+\n";
    cout << "¦          3- MES DEL AÑO       ¦\n";
    cout << "+--------------------------------+\n";

    color(15);
    cout << "Ingresa un numero entero del 1 al 12: ";
    cin >> numero;

    switch(numero){
        case 1: cout << "El numero " << numero << " corresponde al dia ENERO"; break;
        case 2: cout << "El numero " << numero << " corresponde al dia FEBRERO"; break;
        case 3: cout << "El numero " << numero << " corresponde al dia MARZO"; break;
        case 4: cout << "El numero " << numero << " corresponde al dia ABRIL"; break;
        case 5: cout << "El numero " << numero << " corresponde al dia MAYO"; break;
        case 6: cout << "El numero " << numero << " corresponde al dia JUNIO"; break;
        case 7: cout << "El numero " << numero << " corresponde al dia JULIO"; break;
        case 8: cout << "El numero " << numero << " corresponde al dia AGOSTO"; break;
        case 9: cout << "El numero " << numero << " corresponde al dia SEPTIEMBRE"; break;
        case 10: cout << "El numero " << numero << " corresponde al dia OCTUBRE"; break;
        case 11: cout << "El numero " << numero << " corresponde al dia NOVIEMBRE"; break;
        case 12: cout << "El numero " << numero << " corresponde al dia DICIEMBRE"; break;
        default: cout << "No coloco un numero dentro del parametro solicitado"; break;
    }

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void positivoNegativo() {
    float numero{};
    system("cls");

    color(11);
    cout << "+--------------------------------+\n";
    cout << "¦       4- POSITIVO O NEGATIVO  ¦\n";
    cout << "+--------------------------------+\n";

    color(15);
    cout << "Ingresa un numero: ";
    cin >> numero;

    if(numero > 0.0)
        cout << "El numero " << numero << " es positivo";
    else if(numero < 0.0)
        cout << "El numero " << numero << " es negativo";
    else
        cout << "El numero " << numero << " es igual a 0";

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void mayorQueCien() {
    float numero{};
    system("cls");

    color(11);
    cout << "+--------------------------------+\n";
    cout << "¦           5- MAYOR QUE 100    ¦\n";
    cout << "+--------------------------------+\n";

    color(15);
    cout << "Ingresa un numero: ";
    cin >> numero;

    if(numero > 100)
        cout << "El numero " << numero << " es mayor de 100";
    else if(numero < 100)
        cout << "El numero " << numero << " es menor de 100";
    else
        cout << "El numero " << numero << " es igual a 100";

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void letraVocal() {
    char letra{};
    system("cls");

    color(11);
    cout << "+--------------------------------+\n";
    cout << "¦   6- LETRA VOCAL O CONSONANTE ¦\n";
    cout << "+--------------------------------+\n";

    color(15);
    cout << "Ingresa una sola letra: ";
    cin >> letra;

    if(isalpha(letra)) {
        if(toupper(letra)=='A'||toupper(letra)=='E'||toupper(letra)=='I'||toupper(letra)=='O'||toupper(letra)=='U')
            cout << "La letra " << (char)toupper(letra) << " es vocal";
        else
            cout << "La letra " << (char)toupper(letra) << " es consonante";
    } else {
        cout << "El caracter " << (char)toupper(letra) << " no es una letra, revisa porfavor";
    }

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void numeroIgualSuma() {
    int num1{}, num2{}, num3{};
    system("cls");

    color(11);
    cout << "+-------------------------------------------------+\n";
    cout << "¦ 7- UN NUMERO ES IGUAL A LA SUMA DE 2 NUMEROS  ¦\n";
    cout << "+-------------------------------------------------+\n";

    color(15);
    cout << "Ingresa tres numeros enteros:\n";
    cout << "PRIMER NUMERO (SUMA): "; cin >> num1;
    cout << "SEGUNDO NUMERO (SUMA): "; cin >> num2;
    cout << "TERCER NUMERO (COMPARACION): "; cin >> num3;

    int suma = num1+num2;
    if(suma == num3)
        cout << "La suma de " << num1 << " + " << num2 << " es igual a " << suma << " , y el numero 3 es " << num3 << " , por lo tanto si es igual.";
    else if(suma > num3)
        cout << "La suma de " << num1 << " + " << num2 << " es igual a " << suma << " , y el numero 3 es " << num3 << " , por lo tanto la suma es mayor al numero 3";
    else
        cout << "La suma de " << num1 << " + " << num2 << " es igual a " << suma << " , y el numero 3 es " << num3 << " , por lo tanto la suma es menor al numero 3";

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void numeroIgualMultiplicacion() {
    int num1{}, num2{}, num3{};
    system("cls");

    color(11);
    cout << "+----------------------------------------------------+\n";
    cout << "¦ 8- UN NUMERO ES IGUAL A LA MULTIPLICACION DE 2 NUMEROS ¦\n";
    cout << "+----------------------------------------------------+\n";

    color(15);
    cout << "Ingresa tres numeros enteros:\n";
    cout << "PRIMER NUMERO (MULTIPLICA): "; cin >> num1;
    cout << "SEGUNDO NUMERO (MULTIPLICA): "; cin >> num2;
    cout << "TERCER NUMERO (COMPARACION): "; cin >> num3;

    int multi = num1*num2;
    if(multi == num3)
        cout << "La multiplicacion de " << num1 << " * " << num2 << " es igual a " << multi << " , y el numero 3 es " << num3 << " , por lo tanto si es igual.";
    else if(multi > num3)
        cout << "La multiplicacion de " << num1 << " * " << num2 << " es igual a " << multi << " , y el numero 3 es " << num3 << " , por lo tanto la multiplicacion es mayor al numero 3";
    else
        cout << "La multiplicacion de " << num1 << " * " << num2 << " es igual a " << multi << " , y el numero 3 es " << num3 << " , por lo tanto la multiplicacion es menor al numero 3";

    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}



void mostrarMenu() {
	
    color(11);
    cout << "+-------------------------------+\n";
    cout << "¦         MENU PRINCIPAL        ¦\n";
    cout << "+-------------------------------+\n";
    cout << "¦ 1 - PAR O IMPAR               ¦\n";
    cout << "¦ 2 - DIA DE LA SEMANA          ¦\n";
    cout << "¦ 3 - MES DEL ANO               ¦\n";
    cout << "¦ 4 - POSITIVO O NEGATIVO       ¦\n";
    cout << "¦ 5 - MAYOR QUE 100             ¦\n";
    cout << "¦ 6 - LETRA VOCAL O CONSONANTE  ¦\n";
    cout << "¦ 7 - SALIR                     ¦\n";
    cout << "+-------------------------------+\n";
}

int main() {

    char repetir = 'S';
    int opcion;

    do {
        system("cls"); 
        mostrarMenu();

        color(14);
        cout << "Ingresa tu opcion: ";
        cin >> opcion;
        color(15); 

        switch(opcion) {
            case 1: parImpar(); break;
            case 2: diaSemana(); break;
            case 3: mesAno(); break;
            case 4: positivoNegativo(); break;
            case 5: mayorQueCien(); break;
            case 6: letraVocal(); break;
            case 7:
                color(12); // Rojo
                cout << "¡Adiós!\n";
                repetir = 'N';
                continue;
            default:
                color(12);
                cout << "Opción invalida\n";
                color(15);
                break;
        }

        if (repetir != 'N') {
            char letra;
            while (true) {
                color(14);
                cout << "\n¿Desea realizar otra operacion? (S/N): ";
                cin >> letra;
                letra = toupper(letra);

                if (letra == 'S' || letra == 'N') {
                    repetir = letra;
                    break;
                } else {
                    color(12); 
                    cout << "Error: solo se permiten S o N.\n";
                    color(14);
                }
            }
            color(15); 
        }

    } while (repetir == 'S');

    return 0;
}


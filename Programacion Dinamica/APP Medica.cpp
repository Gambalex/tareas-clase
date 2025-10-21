#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>  
using namespace std;

void LimpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

struct Paciente {
    string nombre;
    int edad;
    string telefono; 
    float peso;     
    string diagnostico;
};

int LeerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, ingrese un número válido.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

double leerDouble(const string& mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, ingrese un número válido.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}


int main() {
    vector<Paciente> pacientes;
    int op;

    do {
        LimpiarPantalla();
        cout << "\n= MENU DE PACIENTES =" << endl;
        cout << "1. Agregar Paciente" << endl;
        cout << "2. Eliminar Paciente" << endl;
        cout << "3. Mostrar Pacientes" << endl;
        cout << "4. Editar Paciente" << endl;
        cout << "5. Salir" << endl;
        
        op = LeerEntero("Seleccione una opcion: ");

        switch (op) {
        case 1: {
            LimpiarPantalla();
            Paciente nuevo;
            cout << "\n-- Agregar Paciente --" << endl;
            
            cout << "Nombre del Paciente: ";
            getline(cin, nuevo.nombre);
            
            nuevo.edad = LeerEntero("Edad: ");
            
            cout << "Telefono: ";
            getline(cin, nuevo.telefono);
            
            nuevo.peso = leerDouble("Peso (kg): ");
            
            cout << "Diagnostico: ";
            getline(cin, nuevo.diagnostico);

            pacientes.push_back(nuevo);
            cout << "\nPaciente agregado exitosamente.\n";
            break;
        }
        case 2: {
            LimpiarPantalla();
            cout << "\n-- Eliminar Paciente --" << endl;
            if (pacientes.empty()) {
                cout << "No hay pacientes registrados.\n";
                break;
            }
            cout << "Ingrese el numero del paciente a eliminar (1-" << pacientes.size() << "): ";
            size_t indice;
            cin >> indice;

            if (!cin.fail() && indice >= 1 && indice <= pacientes.size()) {
                pacientes.erase(pacientes.begin() + indice - 1);
                cout << "Paciente eliminado correctamente.\n";
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Indice invalido.\n";
            }
            break;
        }
        case 3: {
            LimpiarPantalla();
            cout << "\n-- Lista de Pacientes --" << endl;
            if (pacientes.empty()) {
                cout << "No hay pacientes registrados.\n";
            } else {
                for (size_t i = 0; i < pacientes.size(); ++i) {
                    cout << "--------------------------------------\n";
                    cout << "Paciente #" << i + 1 << "\n";
                    cout << "  Nombre:      " << pacientes[i].nombre << "\n";
                    cout << "  Edad:        " << pacientes[i].edad << "\n";
                    cout << "  Telefono:    " << pacientes[i].telefono << "\n";
                    cout << "  Peso:        " << pacientes[i].peso << " kg\n";
                    cout << "  Diagnostico: " << pacientes[i].diagnostico << endl;
                }
                cout << "--------------------------------------\n";
            }
            break;
        }
        case 4: {
            LimpiarPantalla();
            cout << "\n-- Editar Paciente --" << endl;
            if (pacientes.empty()) {
                cout << "No hay pacientes registrados.\n";
                break;
            }
        
            for (size_t i = 0; i < pacientes.size(); ++i) {
                    cout << "--------------------------------------\n";
                    cout << "Paciente #" << i + 1 << "\n";
                    cout << "  Nombre:      " << pacientes[i].nombre << "\n";
                }
                cout << "--------------------------------------\n";
            cout << "Ingrese el numero del paciente a editar (1-" << to_string(pacientes.size()) << "): ";
            
            size_t indice = LeerEntero("");
            if (indice >= 1 && indice <= pacientes.size()) {
                Paciente &p = pacientes[indice - 1];
                
                cout << "Editando Paciente #" << indice << ": " << p.nombre << "\n";
                cout << "(Deje en blanco y presione Enter para no cambiar el dato)\n\n";

                cout << "Nuevo nombre (" << p.nombre << "): ";
                string nuevoNombre;
                getline(cin, nuevoNombre);
                if (!nuevoNombre.empty()) p.nombre = nuevoNombre;

                cout << "Nueva edad (" << p.edad << "): ";
                string edadStr;
                getline(cin, edadStr);
                if (!edadStr.empty()) {
                    try {
                        p.edad = stoi(edadStr);
                    } catch (...) {
                        cout << "Entrada de edad inválida. No se actualizó.\n";
                    }
                }
                
                cout << "Nuevo telefono (" << p.telefono << "): ";
                string nuevoTel;
                getline(cin, nuevoTel);
                if (!nuevoTel.empty()) p.telefono = nuevoTel;

                cout << "Nuevo peso (" << p.peso << "): ";
                string pesoStr;
                getline(cin, pesoStr);
                if (!pesoStr.empty()) {
                     try {
                        p.peso = stod(pesoStr);
                    } catch (...) {
                        cout << "Entrada de peso inválida. No se actualizó.\n";
                    }
                }

                cout << "Nuevo diagnostico (" << p.diagnostico << "): ";
                string nuevoDiag;
                getline(cin, nuevoDiag);
                if (!nuevoDiag.empty()) p.diagnostico = nuevoDiag;

                cout << "\nPaciente actualizado correctamente.\n";
            } else {
                cout << "Indice invalido.\n";
            }
            break;
        }
        case 5:
            cout << "\nSaliendo del programa...\n";
            break;
        default:
             cout << "Opción inválida. Intente de nuevo.\n";
             break;
        }
        
        if (op != 5) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }

    } while (op != 5);

    return 0;
}

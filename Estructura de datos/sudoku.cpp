/*
 * PROYECTO SUDOKU C++ COMPLETO (Versión en Español)
 *
 * (Actualizado con Tabla de Marcadores)
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // Para guardar y leer archivos (usuarios)
#include <chrono>       // Para el temporizador
#include <random>       // Para generar números aleatorios
#include <algorithm>    // Para std::shuffle
#include <iomanip>      // Para imprimir el tablero bonito (setw)
#include <thread>       // Para std::this_thread::sleep_for
#include <cstdlib>      // Para system("cls || clear")
#include <limits>       // Para limpiar el buffer de entrada (cin)
#include <sstream>      // Para construir strings dinámicamente

// Incluir la cabecera de Windows solo si se compila en Windows
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Constante para el tamaño del tablero
const int N = 9;

// --- DEFINICIÓN DE COLORES ANSI ---
const string RESET = "\033[0m";
const string NEGRITA = "\033[1m";
const string ROJO = "\033[31m";
const string VERDE = "\033[32m";
const string AMARILLO = "\033[33m";
const string AZUL = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string BLANCO = "\033[37m";
const string GRIS = "\033[90m";
const string ROJO_NEGRITA = "\033[1;31m";
const string VERDE_NEGRITA = "\033[1;32m";
const string AMARILLO_NEGRITA = "\033[1;33m";
const string AZUL_NEGRITA = "\033[1;34m";
const string CYAN_NEGRITA = "\033[1;36m";
const string BLANCO_NEGRITA = "\033[1;37m";

// --- HABILITAR COLORES EN WINDOWS ---
void habilitarColoresWindows() {
    #ifdef _WIN32
        HANDLE hSalida = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hSalida != INVALID_HANDLE_VALUE) {
            DWORD dwModo = 0;
            if (GetConsoleMode(hSalida, &dwModo)) {
                dwModo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hSalida, dwModo);
            }
        }
    #endif
}

// --- FUNCIÓN DE UTILIDAD ---
void pausarYLimpiar() {
    cout << GRIS << "\nPresiona Enter para continuar..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("cls || clear");
}

// --- DECLARACIÓN DE CLASES ---
class GeneradorSudoku;
class Usuario;
class Juego;
class GestorMarcadores;

// --- ESTRUCTURA PARA MARCADORES ---
struct Marcador {
    string nombre;
    int dificultad; // 0-4
    string nombreDificultad;
    double tiempo;
};

// --- CLASE 1: GENERADORSUDOKU ---
// (Esta clase no tiene cambios)
class GeneradorSudoku {
private:
    int tablero[N][N];
    int solucion[N][N];
    mt19937 generadorAleatorio; 

    bool esSeguro(int tableroTemp[N][N], int fila, int col, int num) {
        for (int c = 0; c < N; c++) {
            if (tableroTemp[fila][c] == num) return false;
        }
        for (int r = 0; r < N; r++) {
            if (tableroTemp[r][col] == num) return false;
        }
        int filaInicio = fila - fila % 3;
        int colInicio = col - col % 3;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (tableroTemp[r + filaInicio][c + colInicio] == num) return false;
            }
        }
        return true;
    }

    bool buscarCeldaVacia(int tableroTemp[N][N], int& fila, int& col) {
        for (fila = 0; fila < N; fila++) {
            for (col = 0; col < N; col++) {
                if (tableroTemp[fila][col] == 0) return true;
            }
        }
        return false;
    }

    bool resolverYGenerar() {
        int fila, col;
        if (!buscarCeldaVacia(tablero, fila, col)) {
            return true;
        }
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        shuffle(nums.begin(), nums.end(), generadorAleatorio);
        for (int num : nums) {
            if (esSeguro(tablero, fila, col, num)) {
                tablero[fila][col] = num;
                if (resolverYGenerar()) {
                    return true;
                }
                tablero[fila][col] = 0; // Backtrack
            }
        }
        return false;
    }

public:
    GeneradorSudoku() {
        unsigned semilla = chrono::system_clock::now().time_since_epoch().count();
        generadorAleatorio.seed(semilla);
    }

    void crearPuzzle(int pistas) {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                tablero[r][c] = 0;
            }
        }
        resolverYGenerar();
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                solucion[r][c] = tablero[r][c];
            }
        }
        int celdasAEliminar = (N * N) - pistas;
        while (celdasAEliminar > 0) {
            int fila = generadorAleatorio() % N;
            int col = generadorAleatorio() % N;
            if (tablero[fila][col] != 0) {
                tablero[fila][col] = 0;
                celdasAEliminar--;
            }
        }
    }

    void obtenerPuzzle(int tableroDestino[N][N]) {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                tableroDestino[r][c] = tablero[r][c];
            }
        }
    }

    void obtenerSolucion(int solucionDestino[N][N]) {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                solucionDestino[r][c] = solucion[r][c];
            }
        }
    }
};

// --- CLASE 2: USUARIO ---
// (Casi sin cambios, solo se usa para obtener el nombre de la dificultad)
class Usuario {
public:
    string nombreUsuario;
    int vidas;
    int puzzlesCompletados[5]; // Índices 0=MF, 1=F, 2=M, 3=D, 4=MD

    Usuario(string nombre) : nombreUsuario(nombre), vidas(3) {
        for (int i = 0; i < 5; i++) {
            puzzlesCompletados[i] = 0;
        }
    }

    void cargar() {
        ifstream archivo(nombreUsuario + ".txt");
        if (archivo.is_open()) {
            archivo >> vidas;
            for (int i = 0; i < 5; i++) {
                archivo >> puzzlesCompletados[i];
            }
            archivo.close();
            cout << VERDE << "¡Bienvenido de nuevo, " << AMARILLO_NEGRITA << nombreUsuario << VERDE << "!" << RESET << endl;
        } else {
            cout << AMARILLO << "Creando nuevo usuario: " << AMARILLO_NEGRITA << nombreUsuario << RESET << endl;
            guardar();
        }
    }

    void guardar() {
        ofstream archivo(nombreUsuario + ".txt");
        if (archivo.is_open()) {
            archivo << vidas << endl;
            for (int i = 0; i < 5; i++) {
                archivo << puzzlesCompletados[i] << " ";
            }
            archivo << endl;
            archivo.close();
        } else {
            cout << ROJO_NEGRITA << "Error: No se pudo guardar el progreso de " << nombreUsuario << RESET << endl;
        }
    }

    // Función estática para que GestorMarcadores pueda usarla
    static string obtenerNombreDificultad(int dif) {
        switch (dif) {
            case 0: return "Muy Facil";
            case 1: return "Facil";
            case 2: return "Medio";
            case 3: return "Dificil";
            case 4: return "Muy Dificil";
            default: return "Desconocido";
        }
    }

    int obtenerPistasPorDificultad(int dif) {
        switch (dif) {
            case 0: return 43; // MF
            case 1: return 34; // F
            case 2: return 29; // M
            case 3: return 25; // D
            case 4: return 18; // MD
            default: return 30;
        }
    }

    void imprimirProgreso() {
        cout << AMARILLO_NEGRITA << "--- Progreso de " << nombreUsuario << " ---" << RESET << endl;
        for (int i = 0; i < 5; i++) {
            cout << BLANCO << i + 1 << ". " << obtenerNombreDificultad(i) << ": " << RESET;
            
            if (puzzlesCompletados[i] == 5) {
                cout << VERDE_NEGRITA;
            } else if (puzzlesCompletados[i] > 0) {
                cout << AMARILLO;
            } else {
                cout << GRIS;
            }
            cout << puzzlesCompletados[i] << " / 5 completados" << RESET << endl;
        }
        cout << AMARILLO_NEGRITA << "----------------------------------" << RESET << endl;
    }

    int seleccionarDificultad() {
        int opcion = -1;
        while (opcion < 1 || opcion > 5) {
            cout << "\n" << CYAN_NEGRITA << "--- Elige la Dificultad ---" << RESET << endl;
            imprimirProgreso();
            cout << BLANCO_NEGRITA << "Elige un nivel (1-5): " << RESET;
            cin >> opcion;
            if (cin.fail() || opcion < 1 || opcion > 5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ROJO << "Entrada invalida. Por favor, elige un numero del 1 al 5." << RESET << endl;
                opcion = -1;
            }
        }
        return opcion - 1; // Retorna el índice 0-4
    }
};


// --- CLASE 4: GESTORMARCADORES ---
// NUEVA CLASE para manejar los marcadores (high scores)
class GestorMarcadores {
private:
    static string const ARCHIVO_MARCADORES;

    // Función de ayuda para ordenar:
    // 1. Por dificultad (más difícil primero, 4 > 3 > 2...)
    // 2. Por tiempo (más rápido primero)
    static bool compararMarcadores(const Marcador& a, const Marcador& b) {
        if (a.dificultad != b.dificultad) {
            return a.dificultad > b.dificultad;
        }
        return a.tiempo < b.tiempo;
    }

public:
    // Guarda un nuevo marcador en el archivo
    static void guardarMarcador(const string& nombre, int dificultad, double tiempo) {
        ofstream archivo(ARCHIVO_MARCADORES, ios::app); // ios::app para añadir al final
        if (archivo.is_open()) {
            archivo << nombre << " " << dificultad << " " << tiempo << endl;
            archivo.close();
        } else {
            cout << ROJO << "Error: No se pudo guardar el marcador." << RESET << endl;
        }
    }

    // Carga todos los marcadores desde el archivo
    static vector<Marcador> cargarMarcadores() {
        vector<Marcador> marcadores;
        ifstream archivo(ARCHIVO_MARCADORES);
        string nombre;
        int dificultad;
        double tiempo;

        if (archivo.is_open()) {
            while (archivo >> nombre >> dificultad >> tiempo) {
                Marcador m;
                m.nombre = nombre;
                m.dificultad = dificultad;
                m.tiempo = tiempo;
                m.nombreDificultad = Usuario::obtenerNombreDificultad(dificultad);
                marcadores.push_back(m);
            }
            archivo.close();
        }
        return marcadores;
    }

    // Carga, ordena y muestra los marcadores
    static void imprimirMarcadores() {
        vector<Marcador> marcadores = cargarMarcadores();

        if (marcadores.empty()) {
            cout << AMARILLO << "Aun no hay marcadores registrados. ¡Se el primero!" << RESET << endl;
            return;
        }

        // Ordenar el vector
        sort(marcadores.begin(), marcadores.end(), compararMarcadores);

        cout << CYAN_NEGRITA << "--- MEJORES PUNTUACIONES ---" << RESET << endl;
        cout << left; // Alinear texto a la izquierda
        cout << BLANCO_NEGRITA 
             << setw(15) << "Usuario" 
             << setw(15) << "Dificultad" 
             << setw(10) << "Tiempo (seg)" << RESET << endl;
        cout << GRIS << "------------------------------------------" << RESET << endl;

        for (const auto& m : marcadores) {
            cout << AMARILLO << setw(15) << m.nombre << RESET
                 << BLANCO << setw(15) << m.nombreDificultad << RESET
                 << CYAN << fixed << setprecision(2) << setw(10) << m.tiempo << RESET << endl;
        }
    }
};

// Inicializar la variable estática
string const GestorMarcadores::ARCHIVO_MARCADORES = "highscores.txt";


// --- CLASE 3: JUEGO ---
// (Modificada para guardar el marcador al ganar)
class Juego {
private:
    Usuario& usuario;
    int puzzle[N][N];
    int solucion[N][N];
    bool pistasOriginales[N][N];
    int dificultad;
    int vidasAlInicio;
    bool perdioVidaEnNivel;

public:
    Juego(Usuario& u, int dif) : usuario(u), dificultad(dif) {
        vidasAlInicio = usuario.vidas;
        perdioVidaEnNivel = false;

        GeneradorSudoku generador;
        int pistas = usuario.obtenerPistasPorDificultad(dificultad);
        generador.crearPuzzle(pistas);
        generador.obtenerPuzzle(puzzle);
        generador.obtenerSolucion(solucion);

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                pistasOriginales[r][c] = (puzzle[r][c] != 0);
            }
        }
    }

    void imprimirTablero() {
        system("cls || clear");
        cout << CYAN_NEGRITA << "--- SUDOKU: " << Usuario::obtenerNombreDificultad(dificultad) << " ---" << RESET << endl;
        cout << BLANCO << "Vidas restantes: " << (usuario.vidas > 1 ? VERDE_NEGRITA : ROJO_NEGRITA) << usuario.vidas << RESET << endl;
        cout << GRIS << "   1 2 3   4 5 6   7 8 9" << RESET << endl;
        cout << GRIS << " -------------------------" << RESET << endl;
        for (int r = 0; r < N; r++) {
            if (r % 3 == 0 && r != 0) {
                cout << GRIS << " |-------+-------+-------|" << RESET << endl;
            }
            cout << GRIS << r + 1 << "| " << RESET;
            for (int c = 0; c < N; c++) {
                if (c % 3 == 0 && c != 0) {
                    cout << GRIS << "| " << RESET;
                }
                
                if (pistasOriginales[r][c]) {
                    cout << AZUL_NEGRITA << puzzle[r][c] << " " << RESET;
                } else if (puzzle[r][c] == 0) {
                    cout << GRIS << ". " << RESET;
                } else {
                    cout << BLANCO_NEGRITA << puzzle[r][c] << " " << RESET;
                }
            }
            cout << GRIS << "|" << RESET << "\n";
        }
        cout << GRIS << " -------------------------" << RESET << endl;
    }

    bool estaResuelto() {
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (puzzle[r][c] == 0) {
                    return false;
                }
                if (puzzle[r][c] != solucion[r][c]) {
                     return false;
                }
            }
        }
        return true;
    }

    bool jugar() {
        auto tiempoInicio = chrono::high_resolution_clock::now();

        while (true) {
            imprimirTablero();

            // 1. Verificar si ya ganó
            if (estaResuelto()) {
                auto tiempoFin = chrono::high_resolution_clock::now();
                chrono::duration<double> duracion = tiempoFin - tiempoInicio;
                double tiempoTranscurrido = duracion.count();
                
                cout << "\n" << VERDE_NEGRITA << "¡Felicidades! Puzzle resuelto." << RESET << endl;
                cout << BLANCO << "Tiempo: " << fixed << setprecision(2) << tiempoTranscurrido << " segundos." << RESET << endl;

                // --- NUEVO: GUARDAR MARCADOR ---
                GestorMarcadores::guardarMarcador(usuario.nombreUsuario, dificultad, tiempoTranscurrido);
                cout << VERDE << "¡Tu tiempo ha sido guardado en los marcadores!" << RESET << endl;
                // --- FIN DE LO NUEVO ---


                if (!perdioVidaEnNivel) {
                    usuario.vidas = vidasAlInicio + 1;
                    cout << VERDE << "¡No perdiste vidas! Ganas 1 vida extra para el siguiente nivel." << RESET << endl;
                } else {
                    usuario.vidas = vidasAlInicio;
                    cout << AMARILLO << "Recuperas las vidas que tenias al inicio del nivel." << RESET << endl;
                }

                usuario.puzzlesCompletados[dificultad]++;
                if (usuario.puzzlesCompletados[dificultad] == 5 && dificultad < 4) {
                    cout << VERDE_NEGRITA << "¡Completaste los 5 sudokus de este nivel!" << RESET << endl;
                }
                
                usuario.guardar();
                return true;
            }

            // 2. Pedir jugada
            cout << "\n" << BLANCO << "Ingresa Fila, Columna y Numero (ej. 3 4 8)" << RESET << endl;
            cout << GRIS << "O ingresa '0 0 0' para rendirte y salir: " << RESET;
            int r, c, num;
            cin >> r >> c >> num;

            // 3. Validar entrada
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << ROJO << "Entrada invalida. Intentalo de nuevo." << RESET << endl;
                chrono::milliseconds dura(1500);
                std::this_thread::sleep_for(dura);
                continue;
            }

            // 4. Salir
            if (r == 0 || c == 0 || num == 0) {
                cout << AMARILLO << "¿Seguro que quieres rendirte? (s/n): " << RESET;
                char confirmar;
                cin >> confirmar;
                if (confirmar == 's' || confirmar == 'S') {
                    cout << ROJO << "Nivel no completado. Tu progreso no se guardara." << RESET << endl;
                    usuario.vidas = vidasAlInicio; 
                    return false;
                }
                continue;
            }

            // 5. Validar rangos
            if (r < 1 || r > 9 || c < 1 || c > 9 || num < 1 || num > 9) {
                cout << ROJO << "Valores fuera de rango (deben ser 1-9)." << RESET << endl;
                chrono::milliseconds dura(1500);
                std::this_thread::sleep_for(dura);
                continue;
            }
            r--; // Convertir a índice 0-8
            c--;

            // 6. Verificar si es pista original
            if (pistasOriginales[r][c]) {
                cout << AMARILLO << "No puedes cambiar una pista original." << RESET << endl;
                chrono::milliseconds dura(1500);
                std::this_thread::sleep_for(dura);
                continue;
            }

            // 7. Verificar la jugada
            if (solucion[r][c] == num) {
                cout << VERDE << "¡Correcto!" << RESET << endl;
                puzzle[r][c] = num;
            } else {
                cout << ROJO_NEGRITA << "¡Incorrecto! Pierdes una vida." << RESET << endl;
                usuario.vidas--;
                perdioVidaEnNivel = true;
                puzzle[r][c] = 0; // Borra la respuesta incorrecta

                if (usuario.vidas == 0) {
                    imprimirTablero();
                    cout << ROJO_NEGRITA << "¡GAME OVER! Te has quedado sin vidas." << RESET << endl;
                    return false;
                }
            }
            chrono::milliseconds dura(1000);
            std::this_thread::sleep_for(dura);
        }
    }
};

// --- FUNCIÓN PRINCIPAL ---
// (Actualizada con la opción 3. Ver Marcadores)

int main() {
    // --- ¡IMPORTANTE! HABILITAR COLORES ---
    habilitarColoresWindows();

    string nombreUsuario;
    cout << CYAN_NEGRITA << "--- BIENVENIDO A SUDOKU C++ ---" << RESET << endl;
    cout << BLANCO_NEGRITA << "Ingresa tu nombre de usuario: " << RESET;
    cin >> nombreUsuario;

    Usuario usuarioActual(nombreUsuario);
    usuarioActual.cargar();

    pausarYLimpiar(); 

    int opcion = 0;
    while (opcion != 4) { // <-- CAMBIO A 4
        cout << "\n" << AMARILLO_NEGRITA << "--- MENU PRINCIPAL ---" << RESET << endl;
        cout << BLANCO << "Usuario: " << AMARILLO << usuarioActual.nombreUsuario << RESET
             << BLANCO << " | Vidas: " << (usuarioActual.vidas > 1 ? VERDE : ROJO) << usuarioActual.vidas << RESET << endl;
        cout << BLANCO << "1. Jugar" << RESET << endl;
        cout << BLANCO << "2. Ver Progreso" << RESET << endl;
        cout << BLANCO << "3. Ver Marcadores" << RESET << endl; // <-- NUEVA OPCIÓN
        cout << BLANCO << "4. Salir" << RESET << endl;        // <-- CAMBIO A 4
        cout << BLANCO_NEGRITA << "Elige una opcion: " << RESET;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ROJO << "Entrada invalida." << RESET << endl;
            opcion = 0; // Resetea la elección
            pausarYLimpiar();
            continue;
        }

        switch (opcion) {
            case 1: { // Jugar
                if (usuarioActual.vidas == 0) {
                    cout << AMARILLO << "No tienes vidas. Se reiniciaran a 3." << RESET << endl;
                    usuarioActual.vidas = 3;
                }
                
                int dificultad = usuarioActual.seleccionarDificultad();
                Juego nuevaPartida(usuarioActual, dificultad);
                bool nivelSuperado = nuevaPartida.jugar();

                if (!nivelSuperado && usuarioActual.vidas == 0) {
                    cout << ROJO << "Tus vidas se reiniciaran a 3 para el proximo intento." << RESET << endl;
                    usuarioActual.vidas = 3;
                }
                usuarioActual.guardar();
                pausarYLimpiar(); 
                break;
            }
            case 2: // Ver Progreso
                usuarioActual.imprimirProgreso();
                pausarYLimpiar();
                break;
            
            // --- NUEVO CASE ---
            case 3: // Ver Marcadores
                GestorMarcadores::imprimirMarcadores();
                pausarYLimpiar();
                break;
            
            case 4: // Salir
                usuarioActual.guardar();
                cout << VERDE << "¡Gracias por jugar! Tu progreso ha sido guardado." << RESET << endl;
                break;
            default:
                cout << ROJO << "Opcion invalida. Intentalo de nuevo." << RESET << endl;
                pausarYLimpiar();
                break;
        }
    }

    return 0;
}

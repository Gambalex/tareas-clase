import numpy as np 
from colorama import Fore, Style, init
import os

# Inicializar colorama
init(autoreset=True)

numeroFilas = 7
numeroColumnas = 7

# Simbolos y colores para jugadores
FICHA1 = Fore.RED + "●" + Style.RESET_ALL
FICHA2 = Fore.YELLOW + "●" + Style.RESET_ALL
VACIO = "."

def LimpiarConsola():
    os.system("cls" if os.name == "nt" else "clear")

def CrearTablero():
    return np.zeros((numeroFilas, numeroColumnas), dtype=int)
    
def ImprimirTablero(tablero):
    # Encabezado con los numeros de columna
    LimpiarConsola()
    print("   " + "  ".join(str(i+1) for i in range(numeroColumnas)))
    print("  " + "---"*numeroColumnas)

    # Mostrar filas de arriba hacia abajo
    for f in reversed(range(numeroFilas)):
        fila_str = []
        for c in range(numeroColumnas):
            if tablero[f][c] == 1:
                fila_str.append(FICHA1)
            elif tablero[f][c] == 2:
                fila_str.append(FICHA2)
            else:
                fila_str.append(VACIO)
        print("  " + "  ".join(fila_str))
    print()

def MovimientoValido(tablero, col):
    return tablero[numeroFilas-1][col] == 0

def ObtenerFila(tablero, col):
    for f in range(numeroFilas):
        if tablero[f][col] == 0:
            return f

def SoltarFicha(tablero, fila, col, ficha):
    tablero[fila][col] = ficha
    
def PedirColumna(jugador, color):
    while True:
        try:
            entrada = input(color + f"Jugador {jugador} (1-7): " + Style.RESET_ALL)
            if entrada.strip() == "":
                print("❌ No puedes dejar vacio, escribe un numero")
                continue

            col = int(entrada) - 1

            if 0 <= col < numeroColumnas:
                return col
            else:
                print("❌ Columna invalida, intenta de nuevo")
        except ValueError:
            print("❌ Ingresa un numero valido")

def Victoria(tablero, ficha):
    # Horizontal
    for c in range(numeroColumnas-3):
        for f in range(numeroFilas):
            if all(tablero[f][c+i] == ficha for i in range(4)):
                return True

    # Vertical
    for c in range(numeroColumnas):
        for f in range(numeroFilas-3):
            if all(tablero[f+i][c] == ficha for i in range(4)):
                return True

    # Diagonal positiva
    for c in range(numeroColumnas-3):
        for f in range(numeroFilas-3):
            if all(tablero[f+i][c+i] == ficha for i in range(4)):
                return True

    # Diagonal negativa
    for c in range(numeroColumnas-3):
        for f in range(3, numeroFilas):
            if all(tablero[f-i][c+i] == ficha for i in range(4)):
                return True
    return False

def Jugar():
    tablero = CrearTablero()
    ImprimirTablero(tablero)
    juegoTerminado = False
    turno = 0

    while not juegoTerminado:
        if turno % 2 == 0:
            col = PedirColumna(1, Fore.RED)
            ficha = 1
        else:
            col = PedirColumna(2, Fore.YELLOW)
            ficha = 2

        if col < 0 or col >= numeroColumnas:
            print("❌ Columna invalida, intenta de nuevo")
            continue

        if MovimientoValido(tablero, col):
            fila = ObtenerFila(tablero, col)
            SoltarFicha(tablero, fila, col, ficha)

            ImprimirTablero(tablero)

            if Victoria(tablero, ficha):
                print(f"🎉 Jugador {ficha} gana")
                juegoTerminado = True
            else:
                turno += 1
        else:
            print("⚠️ Columna llena, intenta de nuevo")

Jugar()

using System;

class BatallaNaval
{
static int size = 10;
static char[,] tablero1 = new char[size, size];
static char[,] tablero2 = new char[size, size];
static char[,] oculto1 = new char[size, size];
static char[,] oculto2 = new char[size, size];


static void Main()
{
    InicializarTablero(tablero1);
    InicializarTablero(tablero2);
    InicializarTablero(oculto1);
    InicializarTablero(oculto2);

    Console.WriteLine("Jugador 1 coloca sus barcos:");
    ColocarBarcos(tablero1);

    Console.Clear();
    Console.WriteLine("Jugador 2 coloca sus barcos:");
    ColocarBarcos(tablero2);

    bool juegoActivo = true;
    int jugador = 1;

    while (juegoActivo)
    {
        if (jugador == 1)
            juegoActivo = Turno(tablero2, oculto2, "Jugador 1");
        else
            juegoActivo = Turno(tablero1, oculto1, "Jugador 2");

        if (juegoActivo)
            jugador = (jugador == 1) ? 2 : 1;
    }

    Console.WriteLine("Juego terminado!");
}

static void InicializarTablero(char[,] tablero)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            tablero[i, j] = '~'; // agua
}

static void MostrarTablero(char[,] tablero)
{
    Console.Write("  ");
    for (int j = 0; j < size; j++)
        Console.Write(j + " ");
    Console.WriteLine();

    for (int i = 0; i < size; i++)
    {
        Console.Write(i + " ");
        for (int j = 0; j < size; j++)
        {
            if (tablero[i, j] == '~')
                Console.ForegroundColor = ConsoleColor.Blue;
            else if (tablero[i, j] == 'B')
                Console.ForegroundColor = ConsoleColor.Gray;
            else if (tablero[i, j] == 'X')
                Console.ForegroundColor = ConsoleColor.Red;
            else if (tablero[i, j] == 'O')
                Console.ForegroundColor = ConsoleColor.Yellow;

            Console.Write(tablero[i, j] + " ");
            Console.ResetColor();
        }
        Console.WriteLine();
    }
}

static void ColocarBarcos(char[,] tablero)
{
    int[] barcos = { 5, 4, 3, 3, 2 };
    foreach (int tamaño in barcos)
    {
        bool colocado = false;
        while (!colocado)
        {
            Console.Clear();
            MostrarTablero(tablero);
            Console.WriteLine($"Coloca barco de tamaño {tamaño}");

            var (fila, col) = LeerCoordenadas("Ingresa fila y columna inicial (ej: 2 4): ");

            Console.Write("Orientación (H/V): ");
            char orientacion = char.ToUpper(Console.ReadKey().KeyChar);
            Console.WriteLine();

            if (PuedeColocar(tablero, fila, col, tamaño, orientacion))
            {
                for (int i = 0; i < tamaño; i++)
                {
                    if (orientacion == 'H')
                        tablero[fila, col + i] = 'B';
                    else
                        tablero[fila + i, col] = 'B';
                }
                colocado = true;
            }
            else
            {
                Console.WriteLine("No se puede colocar aquí. Intenta de nuevo...");
                Console.ReadKey();
            }
        }
    }
}

static bool PuedeColocar(char[,] tablero, int fila, int col, int tamaño, char orientacion)
{
    if (orientacion == 'H')
    {
        if (col + tamaño > size) return false;
        for (int i = 0; i < tamaño; i++)
            if (tablero[fila, col + i] != '~') return false;
    }
    else
    {
        if (fila + tamaño > size) return false;
        for (int i = 0; i < tamaño; i++)
            if (tablero[fila + i, col] != '~') return false;
    }
    return true;
}

static bool Turno(char[,] tableroOponente, char[,] tableroOculto, string jugador)
{
    bool seguir = true;
    while (seguir)
    {
        Console.Clear();
        Console.WriteLine($"{jugador}, es tu turno:");
        MostrarTablero(tableroOculto);

        var (fila, col) = LeerCoordenadas("Ingresa fila y columna del disparo (ej: 5 7): ");

        if (tableroOponente[fila, col] == 'B')
        {
            tableroOponente[fila, col] = 'X';
            tableroOculto[fila, col] = 'X';
            Console.WriteLine("¡Impacto!");
            if (JuegoTerminado(tableroOponente))
            {
                Console.WriteLine($"{jugador} gana!");
                return false;
            }
        }
        else if (tableroOponente[fila, col] == '~')
        {
            tableroOponente[fila, col] = 'O';
            tableroOculto[fila, col] = 'O';
            Console.WriteLine("Agua...");
            seguir = false;
        }
        else
        {
            Console.WriteLine("Ya disparaste aquí. Pierdes el turno.");
            seguir = false;
        }
        Console.ReadKey();
    }
    return true;
}

static bool JuegoTerminado(char[,] tablero)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (tablero[i, j] == 'B')
                return false;
    return true;
}

static (int fila, int col) LeerCoordenadas(string mensaje)
{
    int fila = -1, col = -1;
    bool valido = false;

    do
    {
        Console.Write(mensaje);
        string input = Console.ReadLine();

        string[] partes = input.Split(new char[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries); // Se divide el input en 2 partes, se separa por un espacio o uina coma, asi mismo ignora los espacios vacvios o las comas.

        if (partes.Length == 2 &&
            int.TryParse(partes[0], out fila) &&
            int.TryParse(partes[1], out col) &&
            fila >= 0 && fila < size &&
            col >= 0 && col < size)
        {
            valido = true;
        }
        else
        {
            Console.WriteLine("❌ Entrada inválida. Usa formato: fila columna (ejemplo: 3 5)");
        }

    } while (!valido);

    return (fila, col);
}


}

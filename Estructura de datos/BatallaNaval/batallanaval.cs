using System;

class Tablero
{
    private const int tamañoTablero = 10;
    private const char aguaTablero = '~';
    private const char misBarcos = 'S';
    private const char aciertoTablero = 'X';
    private const char errorTablero = 'O';

    private char[,] grid = new char[tamañoTablero, tamañoTablero];

    public Tablero()
    {
        for (int i = 0; i < tamañoTablero; i++)
            for (int j = 0; j < tamañoTablero; j++)
                grid[i, j] = aguaTablero;
    }

    public void Print(bool verMisBarcos = false)
    {
        Console.Write("   ");
        for (int i = 1; i <= tamañoTablero; i++)
            Console.Write(i.ToString().PadLeft(2) + " ");
        Console.WriteLine();

        for (int i = 0; i < tamañoTablero; i++)
        {
            Console.Write((i + 1).ToString().PadLeft(2) + " ");
            for (int j = 0; j < tamañoTablero; j++)
            {
                char cell = grid[i, j];
                if (!verMisBarcos && cell == misBarcos)
                    Console.Write(aguaTablero + "  ");
                else
                    Console.Write(cell + "  ");
            }
            Console.WriteLine();
        }
    }

    public bool PlacemisBarcos(int size, int x, int y, bool horizontal)
    {
        if (horizontal)
        {
            if (y + size > tamañoTablero) return false;
            for (int i = 0; i < size; i++)
                if (grid[x, y + i] == misBarcos) return false;

            for (int i = 0; i < size; i++)
                grid[x, y + i] = misBarcos;
        }
        else
        {
            if (x + size > tamañoTablero) return false;
            for (int i = 0; i < size; i++)
                if (grid[x + i, y] == misBarcos) return false;

            for (int i = 0; i < size; i++)
                grid[x + i, y] = misBarcos;
        }
        return true;
    }

    public bool Shoot(int x, int y)
    {
        if (grid[x, y] == misBarcos)
        {
            grid[x, y] = aciertoTablero;
            return true;
        }
        else if (grid[x, y] == aguaTablero)
        {
            grid[x, y] = errorTablero;
            return false;
        }
        else
        {
            Console.WriteLine("Ya has disparado en esa posición.");
            return false;
        }
    }

    public bool AllmisBarcossSunk()
    {
        foreach (char cell in grid)
            if (cell == misBarcos) return false;
        return true;
    }
}

class Program
{
    static void PlacemisBarcoss(Tablero Tablero, string playerName)
    {
        int[] misBarcosSizes = { 5, 4, 3, 3, 2 };

        Console.WriteLine($"\n{playerName}, coloca tus barcos.");
        foreach (int size in misBarcosSizes)
        {
            bool placed = false;
            while (!placed)
            {
                Console.WriteLine($"Barco de tamaño {size}. Ingresa fila, columna y dirección (0=horizontal, 1=vertical):");
                try
                {
                    string[] input = Console.ReadLine().Split();
                    int x = int.Parse(input[0]) - 1;
                    int y = int.Parse(input[1]) - 1;
                    bool horizontal = input[2] == "0";

                    if (x < 0 || x >= 10 || y < 0 || y >= 10)
                    {
                        Console.WriteLine("Coordenadas fuera de rango. Intenta nuevamente.");
                        continue;
                    }

                    if (Tablero.PlacemisBarcos(size, x, y, horizontal))
                    {
                        Tablero.Print(true);
                        placed = true;
                    }
                    else
                    {
                        Console.WriteLine("Posición inválida o superposición. Intenta de nuevo.");
                    }
                }
                catch
                {
                    Console.WriteLine("Entrada inválida. Usa el formato: fila columna dirección (ej: 3 4 0)");
                }
            }
        }
        Console.Clear();
    }

    static void Main()
    {
        Console.WriteLine("=== BATALLA NAVAL 2 JUGADORES ===");

        Console.Write("Nombre del Jugador 1: ");
        string jugadorNumeroUno = Console.ReadLine();

        Console.Write("Nombre del Jugador 2: ");
        string jugadorNumeroDos = Console.ReadLine();

        Tablero Tablero1 = new Tablero();
        Tablero Tablero2 = new Tablero();

        // Colocar barcos
        PlacemisBarcoss(Tablero1, jugadorNumeroUno);
        PlacemisBarcoss(Tablero2, jugadorNumeroDos);

        bool turnoJugadorUno = true;
        while (true)
        {
            string currentPlayer = turnoJugadorUno ? jugadorNumeroUno : jugadorNumeroDos;
            Tablero opponentTablero = turnoJugadorUno ? Tablero2 : Tablero1;

            Console.Clear();
            Console.WriteLine($"Turno de {currentPlayer}:");
            opponentTablero.Print(false);

            Console.WriteLine("Ingresa coordenadas para disparar (fila columna):");
            try
            {
                string[] input = Console.ReadLine().Split();
                int x = int.Parse(input[0]) - 1;
                int y = int.Parse(input[1]) - 1;

                if (x < 0 || x >= 10 || y < 0 || y >= 10)
                {
                    Console.WriteLine("Coordenadas fuera de rango. Presiona Enter para continuar.");
                    Console.ReadLine();
                    continue;
                }

                bool aciertoTablero = opponentTablero.Shoot(x, y);
                Console.WriteLine(aciertoTablero ? "¡Tocado!" : "¡Agua!");
                Console.WriteLine("Presiona Enter para continuar.");
                Console.ReadLine();

                if (opponentTablero.AllmisBarcossSunk())
                {
                    Console.Clear();
                    Console.WriteLine($"¡{currentPlayer} ha ganado la batalla naval!");
                    break;
                }

                turnoJugadorUno = !turnoJugadorUno;
            }
            catch
            {
                Console.WriteLine("Entrada inválida. Usa el formato: fila columna (ej: 5 6). Presiona Enter para continuar.");
                Console.ReadLine();
            }
        }
    }
}

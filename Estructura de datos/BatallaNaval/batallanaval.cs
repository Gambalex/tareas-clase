using System;

class Board
{
    private const int BoardSize = 10;
    private const char Water = '~';
    private const char Ship = 'S';
    private const char Hit = 'X';
    private const char Miss = 'O';

    private char[,] grid = new char[BoardSize, BoardSize];

    public Board()
    {
        for (int i = 0; i < BoardSize; i++)
            for (int j = 0; j < BoardSize; j++)
                grid[i, j] = Water;
    }

    public void Print(bool showShips = false)
    {
        Console.Write("   ");
        for (int i = 1; i <= BoardSize; i++)
            Console.Write(i.ToString().PadLeft(2) + " ");
        Console.WriteLine();

        for (int i = 0; i < BoardSize; i++)
        {
            Console.Write((i + 1).ToString().PadLeft(2) + " ");
            for (int j = 0; j < BoardSize; j++)
            {
                char cell = grid[i, j];
                if (!showShips && cell == Ship)
                    Console.Write(Water + "  ");
                else
                    Console.Write(cell + "  ");
            }
            Console.WriteLine();
        }
    }

    public bool PlaceShip(int size, int x, int y, bool horizontal)
    {
        if (horizontal)
        {
            if (y + size > BoardSize) return false;
            for (int i = 0; i < size; i++)
                if (grid[x, y + i] == Ship) return false;

            for (int i = 0; i < size; i++)
                grid[x, y + i] = Ship;
        }
        else
        {
            if (x + size > BoardSize) return false;
            for (int i = 0; i < size; i++)
                if (grid[x + i, y] == Ship) return false;

            for (int i = 0; i < size; i++)
                grid[x + i, y] = Ship;
        }
        return true;
    }

    public bool Shoot(int x, int y)
    {
        if (grid[x, y] == Ship)
        {
            grid[x, y] = Hit;
            return true;
        }
        else if (grid[x, y] == Water)
        {
            grid[x, y] = Miss;
            return false;
        }
        else
        {
            Console.WriteLine("Ya has disparado en esa posición.");
            return false;
        }
    }

    public bool AllShipsSunk()
    {
        foreach (char cell in grid)
            if (cell == Ship) return false;
        return true;
    }
}

class Program
{
    static void PlaceShips(Board board, string playerName)
    {
        int[] shipSizes = { 5, 4, 3, 2, 2 };

        Console.WriteLine($"\n{playerName}, coloca tus barcos.");
        foreach (int size in shipSizes)
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

                    if (board.PlaceShip(size, x, y, horizontal))
                    {
                        board.Print(true);
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
        string player1 = Console.ReadLine();

        Console.Write("Nombre del Jugador 2: ");
        string player2 = Console.ReadLine();

        Board board1 = new Board();
        Board board2 = new Board();

        // Colocar barcos
        PlaceShips(board1, player1);
        PlaceShips(board2, player2);

        bool player1Turn = true;
        while (true)
        {
            string currentPlayer = player1Turn ? player1 : player2;
            Board opponentBoard = player1Turn ? board2 : board1;

            Console.Clear();
            Console.WriteLine($"Turno de {currentPlayer}:");
            opponentBoard.Print(false);

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

                bool hit = opponentBoard.Shoot(x, y);
                Console.WriteLine(hit ? "¡Tocado!" : "¡Agua!");
                Console.WriteLine("Presiona Enter para continuar.");
                Console.ReadLine();

                if (opponentBoard.AllShipsSunk())
                {
                    Console.Clear();
                    Console.WriteLine($"¡{currentPlayer} ha ganado la batalla naval!");
                    break;
                }

                player1Turn = !player1Turn;
            }
            catch
            {
                Console.WriteLine("Entrada inválida. Usa el formato: fila columna (ej: 5 6). Presiona Enter para continuar.");
                Console.ReadLine();
            }
        }
    }
}

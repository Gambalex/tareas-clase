using System;

class Columna {
    static void colRecorrido(int[,] mat) {
        if (mat == null || mat.Length == 0) {
            Console.WriteLine("Matriz vacía");
            return;
        }

        int filas = mat.GetLength(0);
        int cols = mat.GetLength(1);

        Console.WriteLine("Recorrido por columnas:");
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < filas; i++) {
                Console.WriteLine($"Col {j}, Fila {i}: {mat[i, j]}");
            }
            Console.WriteLine();
        }
    }

    static void Main() {
        int[,] datos = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        colRecorrido(datos);
    }
}

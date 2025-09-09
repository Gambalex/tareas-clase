using System;

class Recorrer
{
    static void Main()
    {
        int[] datos = {10, 25, 37, 42, 58};

        Console.WriteLine("Recorrido del arreglo:");
        foreach (int val in datos)
        {
            Console.WriteLine(val);
        }
    }
}

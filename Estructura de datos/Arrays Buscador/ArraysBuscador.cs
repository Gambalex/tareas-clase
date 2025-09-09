using System;

class Busqueda
{
    static int busca(int[] nums, int x)
    {
        for (int i = 0; i < nums.Length; i++)
            if (nums[i] == x) return i;
        return -1;
    }

    static void Main()
    {
        int[] datos = { 5, 2, 8, 1, 9, 3 };
        int val = 8;

        int pos = busca(datos, val);

        if (pos != -1)
            Console.WriteLine($"Valor {val} en pos {pos}");
        else
            Console.WriteLine($"Valor {val} no hallado");
    }
}

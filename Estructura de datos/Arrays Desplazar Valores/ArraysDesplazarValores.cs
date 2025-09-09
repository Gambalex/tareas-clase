using System;
using System.Collections.Generic;
using System.Linq;

class Desplazar
{
    static List<int> InsertarDesplazar(List<int> nums, int idx, int val)
    {
        if (idx < 0 || idx >= nums.Count) 
            throw new ArgumentOutOfRangeException("Índice fuera de rango");

        var res = new List<int>();
        res.AddRange(nums.Take(idx));
        res.Add(val);
        res.AddRange(nums.Skip(idx).Take(nums.Count - idx - 1));
        return res;
    }

    static void Main()
    {
        var datos = new List<int> {1,2,3,4,5,6,7,8,9,10};

        Console.WriteLine("Original: " + string.Join(" ", datos));
        Console.WriteLine("Inserta 99 en índice 5");

        try
        {
            var res = InsertarDesplazar(datos, 5, 99);
            Console.WriteLine("Resultado: " + string.Join(" ", res));
        }
        catch (ArgumentOutOfRangeException e)
        {
            Console.WriteLine("Error: " + e.Message);
        }
    }
}

using System;

class Program {
    static void Main() {
        int[] arr = {1, 2, 3, 4, 5};
        arr[0] = 10;
        int valor = arr[2];
        Console.WriteLine("Valor 2 del array: " + valor);
        foreach(int i in arr){
            Console.WriteLine(i);
        }
    }
}

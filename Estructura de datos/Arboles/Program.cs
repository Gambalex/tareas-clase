using System;
using System.Collections.Generic;

namespace BSTConsoleApp
{
    class Program
    {
        private static BST bst = new BST();
        private const string SAVE_FILE = "bst_data.txt";
        private const string EXPORT_FILE = "inorden_export.txt";

        static void Main(string[] args)
        {
            Console.WriteLine("==============================================");
            Console.WriteLine("  GESTOR DE NÚMEROS CON ÁRBOL BINARIO DE BÚSQUEDA");
            Console.WriteLine("==============================================");
            
            // Cargar datos persistentes si existen
            bst.LoadFromFile(SAVE_FILE);
            
            ShowHelp();
            
            bool exit = false;
            while (!exit)
            {
                Console.Write("\n> ");
                string command = Console.ReadLine().Trim().ToLower();
                
                if (string.IsNullOrEmpty(command))
                    continue;

                string[] parts = command.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                string mainCommand = parts[0];

                switch (mainCommand)
                {
                    case "insert":
                        HandleInsert(parts);
                        break;
                    case "search":
                        HandleSearch(parts);
                        break;
                    case "delete":
                        HandleDelete(parts);
                        break;
                    case "inorder":
                        DisplayTraversal(bst.Inorder(), "Inorden");
                        break;
                    case "preorder":
                        DisplayTraversal(bst.Preorder(), "Preorden");
                        break;
                    case "postorder":
                        DisplayTraversal(bst.Postorder(), "Postorden");
                        break;
                    case "height":
                        Console.WriteLine($"Altura del árbol: {bst.Height()}");
                        break;
                    case "size":
                        Console.WriteLine($"Número de nodos: {bst.Size()}");
                        Console.WriteLine($"Verificación de consistencia: {(bst.VerifyCount() ? "OK" : "ERROR - contador inconsistente")}");
                        break;
                    case "export":
                        bst.ExportInorder(EXPORT_FILE);
                        break;
                    case "save":
                        bst.SaveToFile(SAVE_FILE);
                        break;
                    case "load":
                        bst.LoadFromFile(SAVE_FILE);
                        break;
                    case "help":
                        ShowHelp();
                        break;
                    case "exit":
                        exit = true;
                        Console.WriteLine("Guardando datos...");
                        bst.SaveToFile(SAVE_FILE);
                        Console.WriteLine("¡Hasta luego!");
                        break;
                    case "test":
                        RunTests();
                        break;
                    default:
                        Console.WriteLine($"Comando desconocido: '{mainCommand}'. Escribe 'help' para ver los comandos disponibles.");
                        break;
                }
            }
        }

        #region Manejadores de comandos

        static void HandleInsert(string[] parts)
        {
            if (parts.Length < 2)
            {
                Console.WriteLine("Uso: insert <número>");
                return;
            }

            if (int.TryParse(parts[1], out int number))
            {
                if (bst.Insert(number))
                {
                    Console.WriteLine($"Número {number} insertado correctamente.");
                }
                // Si no se insertó (por ser duplicado), ya se mostró un mensaje en el método Insert
            }
            else
            {
                Console.WriteLine($"Error: '{parts[1]}' no es un número válido.");
            }
        }

        static void HandleSearch(string[] parts)
        {
            if (parts.Length < 2)
            {
                Console.WriteLine("Uso: search <número>");
                return;
            }

            if (int.TryParse(parts[1], out int number))
            {
                var result = bst.Search(number);
                if (result.found)
                {
                    Console.WriteLine($"Número {number} encontrado.");
                    Console.WriteLine($"Ruta: {result.path}");
                }
                else
                {
                    Console.WriteLine($"Número {number} no encontrado en el árbol.");
                }
            }
            else
            {
                Console.WriteLine($"Error: '{parts[1]}' no es un número válido.");
            }
        }

        static void HandleDelete(string[] parts)
        {
            if (parts.Length < 2)
            {
                Console.WriteLine("Uso: delete <número>");
                return;
            }

            if (int.TryParse(parts[1], out int number))
            {
                if (bst.Delete(number))
                {
                    Console.WriteLine($"Número {number} eliminado correctamente.");
                }
                else
                {
                    Console.WriteLine($"Número {number} no encontrado en el árbol.");
                }
            }
            else
            {
                Console.WriteLine($"Error: '{parts[1]}' no es un número válido.");
            }
        }

        static void DisplayTraversal(List<int> traversal, string name)
        {
            if (traversal.Count == 0)
            {
                Console.WriteLine("El árbol está vacío.");
                return;
            }

            Console.WriteLine($"Recorrido {name}:");
            for (int i = 0; i < traversal.Count; i++)
            {
                Console.Write(traversal[i]);
                if (i < traversal.Count - 1)
                {
                    Console.Write(", ");
                }
            }
            Console.WriteLine();
            Console.WriteLine($"Total de elementos mostrados: {traversal.Count}");
        }

        #endregion

        #region Funciones auxiliares

        static void ShowHelp()
        {
            Console.WriteLine("\nCOMANDOS DISPONIBLES:");
            Console.WriteLine("-------------------");
            Console.WriteLine("insert <número>     - Insertar un número en el árbol (no se permiten duplicados)");
            Console.WriteLine("search <número>     - Buscar un número y mostrar su ruta");
            Console.WriteLine("delete <número>     - Eliminar un número del árbol");
            Console.WriteLine("inorder             - Mostrar recorrido inorden");
            Console.WriteLine("preorder            - Mostrar recorrido preorden");
            Console.WriteLine("postorder           - Mostrar recorrido postorden");
            Console.WriteLine("height              - Mostrar altura del árbol");
            Console.WriteLine("size                - Mostrar número de nodos y verificar consistencia");
            Console.WriteLine("export              - Exportar recorrido inorden a archivo");
            Console.WriteLine("save                - Guardar árbol en archivo");
            Console.WriteLine("load                - Cargar árbol desde archivo");
            Console.WriteLine("test                - Ejecutar casos de prueba");
            Console.WriteLine("help                - Mostrar esta ayuda");
            Console.WriteLine("exit                - Salir del programa");
        }

        static void RunTests()
        {
            Console.WriteLine("\n=== EJECUTANDO CASOS DE PRUEBA ===");
            
            BST testBst = new BST();
            
            // Caso 1: Insertar secuencia
            Console.WriteLine("\n1. Insertando secuencia: 45 15 79 90 10 55 12 20 50");
            int[] testSequence = { 45, 15, 79, 90, 10, 55, 12, 20, 50 };
            foreach (int num in testSequence)
            {
                testBst.Insert(num);
            }
            
            // Verificar inorder
            var inorder = testBst.Inorder();
            Console.WriteLine("Inorden esperado: 10 12 15 20 45 50 55 79 90");
            Console.Write("Inorden obtenido: ");
            DisplayTraversal(inorder, "");
            
            // Caso 2: Insertar duplicados
            Console.WriteLine("\n2. Probando inserción de duplicados:");
            Console.WriteLine("Intentando insertar 45 (ya existe):");
            testBst.Insert(45); // Ya existe
            Console.WriteLine($"Número de nodos después de intentar insertar duplicado: {testBst.Size()}");
            
            // Caso 3: Buscar elementos
            Console.WriteLine("\n3. Buscando elementos:");
            var search20 = testBst.Search(20);
            Console.WriteLine($"Buscar 20: {(search20.found ? $"Encontrado. Ruta: {search20.path}" : "No encontrado")}");
            
            var search100 = testBst.Search(100);
            Console.WriteLine($"Buscar 100: {(search100.found ? $"Encontrado. Ruta: {search100.path}" : "No encontrado")}");
            
            // Caso 4: Eliminar elementos
            Console.WriteLine("\n4. Eliminando elementos:");
            
            Console.WriteLine($"Altura antes de eliminar: {testBst.Height()}");
            Console.WriteLine($"Nodos antes de eliminar: {testBst.Size()}");
            Console.WriteLine($"Consistencia del contador: {(testBst.VerifyCount() ? "OK" : "ERROR")}");
            
            // Eliminar hoja 90
            Console.WriteLine("\nEliminando hoja (90):");
            bool deleted90 = testBst.Delete(90);
            Console.WriteLine($"Resultado eliminación 90: {(deleted90 ? "Éxito" : "Falló")}");
            Console.WriteLine("Después de eliminar hoja (90):");
            DisplayTraversal(testBst.Inorder(), "Inorden");
            Console.WriteLine($"Nodos después: {testBst.Size()}");
            
            // Eliminar nodo con un hijo 79
            Console.WriteLine("\nEliminando nodo con un hijo (79):");
            bool deleted79 = testBst.Delete(79);
            Console.WriteLine($"Resultado eliminación 79: {(deleted79 ? "Éxito" : "Falló")}");
            Console.WriteLine("Después de eliminar nodo con un hijo (79):");
            DisplayTraversal(testBst.Inorder(), "Inorden");
            Console.WriteLine($"Nodos después: {testBst.Size()}");
            
            // Eliminar nodo con dos hijos 45
            Console.WriteLine("\nEliminando nodo con dos hijos (45):");
            bool deleted45 = testBst.Delete(45);
            Console.WriteLine($"Resultado eliminación 45: {(deleted45 ? "Éxito" : "Falló")}");
            Console.WriteLine("Después de eliminar nodo con dos hijos (45):");
            DisplayTraversal(testBst.Inorder(), "Inorden");
            Console.WriteLine($"Nodos después: {testBst.Size()}");
            
            // Intentar eliminar un nodo que no existe
            Console.WriteLine("\nIntentando eliminar nodo que no existe (999):");
            bool deleted999 = testBst.Delete(999);
            Console.WriteLine($"Resultado eliminación 999: {(deleted999 ? "Éxito" : "Falló (esperado)")}");
            
            Console.WriteLine($"\nAltura después de eliminar: {testBst.Height()}");
            Console.WriteLine($"Nodos después de eliminar: {testBst.Size()}");
            Console.WriteLine($"Consistencia final del contador: {(testBst.VerifyCount() ? "OK" : "ERROR")}");
            
            Console.WriteLine("\n=== PRUEBAS COMPLETADAS ===");
        }

        #endregion
    }
}
using System;
using System.Collections.Generic;
using System.IO;

namespace BSTConsoleApp
{
    /// <summary>
    /// Implementación de un Árbol Binario de Búsqueda (BST)
    /// </summary>
    public class BST
    {
        private Nodo _root;
        private int _nodeCount;

        public BST()
        {
            _root = null;
            _nodeCount = 0;
        }

        #region Operaciones básicas

        /// <summary>
        /// Inserta una nueva clave en el árbol
        /// Complejidad: O(h) donde h es la altura del árbol
        /// </summary>
        public bool Insert(int key)
        {
            bool inserted = false;
            _root = InsertRec(_root, key, ref inserted);
            if (inserted)
            {
                _nodeCount++;
            }
            return inserted;
        }

        private Nodo InsertRec(Nodo root, int key, ref bool inserted)
        {
            if (root == null)
            {
                inserted = true;
                return new Nodo(key);
            }

            if (key < root.Key)
            {
                root.Left = InsertRec(root.Left, key, ref inserted);
            }
            else if (key > root.Key)
            {
                root.Right = InsertRec(root.Right, key, ref inserted);
            }
            else
            {
                // Clave duplicada - no se inserta
                inserted = false;
                Console.WriteLine($"Advertencia: El número {key} ya existe en el árbol. No se insertó duplicado.");
            }

            return root;
        }

        /// <summary>
        /// Busca una clave en el árbol y devuelve la ruta si existe
        /// Complejidad: O(h) donde h es la altura del árbol
        /// </summary>
        public (bool found, string path) Search(int key)
        {
            return SearchRec(_root, key, "");
        }

        private (bool found, string path) SearchRec(Nodo root, int key, string path)
        {
            if (root == null)
            {
                return (false, "");
            }

            if (key == root.Key)
            {
                return (true, path + root.Key);
            }
            else if (key < root.Key)
            {
                return SearchRec(root.Left, key, path + root.Key + " -> ");
            }
            else
            {
                return SearchRec(root.Right, key, path + root.Key + " -> ");
            }
        }

        /// <summary>
        /// Elimina una clave del árbol
        /// Complejidad: O(h) donde h es la altura del árbol
        /// </summary>
        public bool Delete(int key)
        {
            bool deleted = false;
            _root = DeleteRec(_root, key, ref deleted);
            if (deleted)
            {
                _nodeCount--;
            }
            return deleted;
        }

        private Nodo DeleteRec(Nodo root, int key, ref bool deleted)
        {
            if (root == null)
            {
                return null;
            }

            if (key < root.Key)
            {
                root.Left = DeleteRec(root.Left, key, ref deleted);
            }
            else if (key > root.Key)
            {
                root.Right = DeleteRec(root.Right, key, ref deleted);
            }
            else
            {
                // Nodo encontrado
                deleted = true;
                
                // Caso 1: Nodo hoja o con un solo hijo
                if (root.Left == null)
                {
                    return root.Right;
                }
                else if (root.Right == null)
                {
                    return root.Left;
                }

                // Caso 2: Nodo con dos hijos
                // Encontrar el sucesor inorden (mínimo en el subárbol derecho)
                root.Key = MinValue(root.Right);
                
                // Eliminar el sucesor (no decrementar contador aquí, ya se hizo arriba)
                bool tempDeleted = false;
                root.Right = DeleteRec(root.Right, root.Key, ref tempDeleted);
            }

            return root;
        }

        private int MinValue(Nodo root)
        {
            int minValue = root.Key;
            while (root.Left != null)
            {
                root = root.Left;
                minValue = root.Key;
            }
            return minValue;
        }

        #endregion

        #region Recorridos

        /// <summary>
        /// Recorrido Inorden (izquierda, raíz, derecha)
        /// </summary>
        public List<int> Inorder()
        {
            List<int> result = new List<int>();
            InorderRec(_root, result);
            return result;
        }

        private void InorderRec(Nodo root, List<int> result)
        {
            if (root != null)
            {
                InorderRec(root.Left, result);
                result.Add(root.Key);
                InorderRec(root.Right, result);
            }
        }

        /// <summary>
        /// Recorrido Preorden (raíz, izquierda, derecha)
        /// </summary>
        public List<int> Preorder()
        {
            List<int> result = new List<int>();
            PreorderRec(_root, result);
            return result;
        }

        private void PreorderRec(Nodo root, List<int> result)
        {
            if (root != null)
            {
                result.Add(root.Key);
                PreorderRec(root.Left, result);
                PreorderRec(root.Right, result);
            }
        }

        /// <summary>
        /// Recorrido Postorden (izquierda, derecha, raíz)
        /// </summary>
        public List<int> Postorder()
        {
            List<int> result = new List<int>();
            PostorderRec(_root, result);
            return result;
        }

        private void PostorderRec(Nodo root, List<int> result)
        {
            if (root != null)
            {
                PostorderRec(root.Left, result);
                PostorderRec(root.Right, result);
                result.Add(root.Key);
            }
        }

        #endregion

        #region Métodos auxiliares

        /// <summary>
        /// Devuelve la altura del árbol
        /// </summary>
        public int Height()
        {
            return HeightRec(_root);
        }

        private int HeightRec(Nodo root)
        {
            if (root == null)
            {
                return 0;
            }

            int leftHeight = HeightRec(root.Left);
            int rightHeight = HeightRec(root.Right);

            return Math.Max(leftHeight, rightHeight) + 1;
        }

        /// <summary>
        /// Devuelve el número de nodos en el árbol
        /// </summary>
        public int Size()
        {
            return _nodeCount;
        }

        /// <summary>
        /// Devuelve el número real de nodos contando recursivamente
        /// (método auxiliar para verificación)
        /// </summary>
        public int CountNodes()
        {
            return CountNodesRec(_root);
        }

        private int CountNodesRec(Nodo root)
        {
            if (root == null)
            {
                return 0;
            }
            return 1 + CountNodesRec(root.Left) + CountNodesRec(root.Right);
        }

        /// <summary>
        /// Verifica la consistencia del contador de nodos
        /// </summary>
        public bool VerifyCount()
        {
            int actualCount = CountNodesRec(_root);
            return actualCount == _nodeCount;
        }

        /// <summary>
        /// Exporta el recorrido inorden a un archivo de texto
        /// </summary>
        public void ExportInorder(string filename)
        {
            try
            {
                List<int> inorderList = Inorder();
                using (StreamWriter writer = new StreamWriter(filename))
                {
                    writer.WriteLine("Recorrido Inorden del Árbol Binario de Búsqueda");
                    writer.WriteLine("==============================================");
                    writer.WriteLine($"Número de elementos: {inorderList.Count}");
                    writer.WriteLine($"Altura del árbol: {Height()}");
                    writer.WriteLine($"Consistencia del contador: {(VerifyCount() ? "OK" : "ERROR")}");
                    writer.WriteLine("----------------------------------------------");
                    
                    for (int i = 0; i < inorderList.Count; i++)
                    {
                        writer.Write(inorderList[i]);
                        if (i < inorderList.Count - 1)
                        {
                            writer.Write(", ");
                        }
                    }
                    writer.WriteLine();
                }
                Console.WriteLine($"Recorrido inorden exportado exitosamente a '{filename}'");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error al exportar: {ex.Message}");
            }
        }

        /// <summary>
        /// Guarda las claves del árbol en un archivo para persistencia
        /// </summary>
        public void SaveToFile(string filename)
        {
            try
            {
                List<int> inorderList = Inorder();
                using (StreamWriter writer = new StreamWriter(filename))
                {
                    foreach (int key in inorderList)
                    {
                        writer.WriteLine(key);
                    }
                }
                Console.WriteLine($"Árbol guardado exitosamente en '{filename}'");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error al guardar: {ex.Message}");
            }
        }

        /// <summary>
        /// Carga las claves desde un archivo y reconstruye el árbol
        /// </summary>
        public void LoadFromFile(string filename)
        {
            try
            {
                if (!File.Exists(filename))
                {
                    Console.WriteLine($"El archivo '{filename}' no existe.");
                    return;
                }

                _root = null;
                _nodeCount = 0;
                
                string[] lines = File.ReadAllLines(filename);
                int loadedCount = 0;
                
                foreach (string line in lines)
                {
                    if (int.TryParse(line.Trim(), out int key))
                    {
                        if (Insert(key))
                        {
                            loadedCount++;
                        }
                    }
                }
                Console.WriteLine($"Árbol cargado exitosamente desde '{filename}'");
                Console.WriteLine($"Número de elementos únicos cargados: {loadedCount}");
                Console.WriteLine($"Total de nodos en el árbol: {Size()}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error al cargar: {ex.Message}");
            }
        }

        #endregion
    }
}
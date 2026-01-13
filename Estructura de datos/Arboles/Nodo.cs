namespace BSTConsoleApp
{
    /// <summary>
    /// Representa un nodo en el Árbol Binario de Búsqueda
    /// </summary>
    public class Nodo
    {
        public int Key { get; set; }
        public Nodo Left { get; set; }
        public Nodo Right { get; set; }

        public Nodo(int key)
        {
            Key = key;
            Left = null;
            Right = null;
        }
    }
}
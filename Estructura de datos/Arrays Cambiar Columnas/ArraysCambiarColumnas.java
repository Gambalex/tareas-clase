public class Columna {
    
    public static void colRecorrido(int[][] mat) {
        if (mat == null || mat.length == 0 || mat[0].length == 0) {
            System.out.println("Matriz vacía");
            return;
        }

        int filas = mat.length;
        int cols = mat[0].length;

        System.out.println("Recorrido por columnas:");
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < filas; i++) {
                System.out.println("Col " + j + ", Fila " + i + ": " + mat[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] datos = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        colRecorrido(datos);
    }
}

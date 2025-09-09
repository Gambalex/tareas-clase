public class Busqueda {
    
    public static int busca(int[] nums, int val) {
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == val) return i;
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] datos = {5, 2, 8, 1, 9, 3};
        int x = 8;

        int pos = busca(datos, x);

        if (pos != -1)
            System.out.println("Valor " + x + " en pos " + pos);
        else
            System.out.println("Valor " + x + " no hallado");
    }
}


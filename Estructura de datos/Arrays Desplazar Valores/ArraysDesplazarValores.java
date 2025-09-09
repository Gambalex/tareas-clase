import java.util.Arrays;
import java.util.ArrayList;

public class Desplaza {

    public static ArrayList<Integer> insertarDesplazar(ArrayList<Integer> nums, int idx, int val) {
        if (idx < 0 || idx >= nums.size()) throw new IllegalArgumentException("Índice fuera de rango");

        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < idx; i++) res.add(nums.get(i));
        res.add(val);
        for (int i = idx; i < nums.size() - 1; i++) res.add(nums.get(i));
        return res;
    }

    public static void main(String[] args) {
        ArrayList<Integer> datos = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8,9,10));

        System.out.println("Original: " + datos);
        System.out.println("Inserta 99 en índice 5");

        try {
            ArrayList<Integer> res = insertarDesplazar(datos, 5, 99);
            System.out.println("Resultado: " + res);
        } catch (IllegalArgumentException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}

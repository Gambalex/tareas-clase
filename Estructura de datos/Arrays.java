public class Main {
    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};
        arr[0] = 10;
        int valor = arr[2];
        System.out.println("Valor 2 del array: " + valor);
        for(int i : arr){
            System.out.println(i);
        }
    }
}

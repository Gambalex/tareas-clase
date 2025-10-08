import java.io.*;
import java.util.*;

public class JuegoLaberinto {
    static final int NIVELES = 3;
    static final int FILAS = 25;
    static final int COLUMNAS = 25;

    static char[][][] laberinto = new char[NIVELES][FILAS][COLUMNAS];
    static boolean[][][] caminoRecorrido = new boolean[NIVELES][FILAS][COLUMNAS];

    static int nivelActual = 0;
    static int jugadorFila, jugadorColumna;
    static int vidas = 2;
    static int llaves = 1;
    static int escudos = 1;
    static boolean juegoActivo = true;
    static Random random = new Random();

    static int puntuacion = 0;
    static int rangoVision = 20; // celdas visibles alrededor del jugador

    // ANSI colores
    static final String RESET = "\u001B[0m";
    static final String ROJO = "\u001B[31m";
    static final String VERDE = "\u001B[32m";
    static final String AMARILLO = "\u001B[33m";
    static final String AZUL = "\u001B[34m";
    static final String MAGENTA = "\u001B[35m";
    static final String CYAN = "\u001B[36m";
    static final String GRIS = "\u001B[90m";

    public static void main(String[] args) throws IOException {
        generarLaberintos();
        colocarJugador();

        Scanner sc = new Scanner(System.in);
        while (juegoActivo && vidas > 0) {
            mostrarLaberinto();
            mostrarInventario();
            leerMovimiento();
        }

        System.out.println("\n🕹️ Juego terminado. Puntuación final: " + puntuacion);
        guardarPuntuacion(puntuacion);
        mostrarPuntuaciones();
    }

    // ==========================================
    // ======== GENERACIÓN DE LABERINTO =========
    // ==========================================
    static void generarLaberintos() {
        for (int n = 0; n < NIVELES; n++) {
            generarLaberintoDFS(n);
            colocarSalida(n);
            colocarElementos(n);
        }
    }

    static void generarLaberintoDFS(int nivel) {
        for (int f = 0; f < FILAS; f++)
            Arrays.fill(laberinto[nivel][f], '1');

        int fila = random.nextInt(FILAS);
        int col = random.nextInt(COLUMNAS);
        laberinto[nivel][fila][col] = ' ';
        dfs(laberinto[nivel], fila, col);
    }

    static void dfs(char[][] mapa, int f, int c) {
        int[] dirF = {-2, 2, 0, 0};
        int[] dirC = {0, 0, -2, 2};
        int[] orden = {0, 1, 2, 3};
        mezclar(orden);
        for (int i : orden) {
            int nf = f + dirF[i], nc = c + dirC[i];
            if (nf >= 0 && nc >= 0 && nf < FILAS && nc < COLUMNAS && mapa[nf][nc] == '1') {
                mapa[nf][nc] = ' ';
                mapa[f + dirF[i] / 2][c + dirC[i] / 2] = ' ';
                dfs(mapa, nf, nc);
            }
        }
    }

    static void mezclar(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            int j = random.nextInt(arr.length);
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }

    static void colocarSalida(int nivel) {
        // Escoge una celda aleatoria accesible para la salida
        int f, c;
        do {
            f = random.nextInt(FILAS);
            c = random.nextInt(COLUMNAS);
        } while (laberinto[nivel][f][c] != ' ');
        laberinto[nivel][f][c] = 'S';
    }

    static void colocarElementos(int nivel) {
        colocarAleatorioSeguro(nivel, 'L', 3);
        colocarAleatorioSeguro(nivel, 'T', 3);
        colocarAleatorioSeguro(nivel, 'C', 2);
        colocarAleatorioSeguro(nivel, 'E', 1);
        colocarAleatorioSeguro(nivel, 'X', 1); // escudo opcional
    }

    static void colocarAleatorioSeguro(int nivel, char simbolo, int cantidad) {
        for (int i = 0; i < cantidad; i++) {
            int f, c;
            do {
                f = random.nextInt(FILAS);
                c = random.nextInt(COLUMNAS);
            } while (laberinto[nivel][f][c] != ' ');
            laberinto[nivel][f][c] = simbolo;
        }
    }

    static void colocarJugador() {
        for (int f = 0; f < FILAS; f++)
            for (int c = 0; c < COLUMNAS; c++)
                if (laberinto[0][f][c] == ' ') {
                    jugadorFila = f;
                    jugadorColumna = c;
                    caminoRecorrido[0][f][c] = true;
                    return;
                }
    }

    // ==========================================
    // ============ MOVIMIENTO ==================
    // ==========================================
    static void leerMovimiento() throws IOException {
        int tecla = System.in.read();

        if (tecla == 27) { // flechas
            System.in.read(); // [
            tecla = System.in.read();
            switch (tecla) {
                case 'A': moverJugador(-1, 0); break;
                case 'B': moverJugador(1, 0); break;
                case 'C': moverJugador(0, 1); break;
                case 'D': moverJugador(0, -1); break;
            }
        } else if (tecla == 'g' || tecla == 'G') {
            guardarPartida();
        } else if (tecla == 'c' || tecla == 'C') {
            cargarPartida();
        } else if (tecla == 'q' || tecla == 'Q') {
            juegoActivo = false;
        }
    }

    static void moverJugador(int df, int dc) {
        int nf = jugadorFila + df;
        int nc = jugadorColumna + dc;

        if (nf < 0 || nc < 0 || nf >= FILAS || nc >= COLUMNAS) return;

        char celda = laberinto[nivelActual][nf][nc];
        switch (celda) {
            case '1': return;
            case 'L': llaves++; puntuacion += 50; break;
            case 'X': escudos++; System.out.println(CYAN + "🛡 Escudo recogido!" + RESET); break;
            case 'T':
                if (escudos > 0) {
                    escudos--;
                    System.out.println(CYAN + "🛡 Escudo usado, trampa evitada!" + RESET);
                } else {
                    vidas--;
                    System.out.println(ROJO + "☠️ Caíste en una trampa!" + RESET);
                }
                break;
            case 'C':
                if (llaves > 0) { llaves--; System.out.println("🔓 Puerta abierta."); }
                else return;
                break;
            case 'S':
                System.out.println(VERDE + "🏁 Nivel completado!" + RESET);
                nivelActual = Math.min(nivelActual + 1, NIVELES - 1);
                return;
            case 'E':
                nivelActual = random.nextInt(NIVELES);
                System.out.println(MAGENTA + "✨ Teletransportado al nivel " + (nivelActual + 1) + RESET);
                return;
        }

        // Marcar el camino recorrido
        caminoRecorrido[nivelActual][jugadorFila][jugadorColumna] = true;
        jugadorFila = nf;
        jugadorColumna = nc;
    }

    // ==========================================
    // ============ VISUALIZACIÓN ===============
    // ==========================================
    static void mostrarLaberinto() {
        System.out.println("\nNivel: " + (nivelActual + 1));
        for (int f = 0; f < FILAS; f++) {
            for (int c = 0; c < COLUMNAS; c++) {
                boolean dentroVision = Math.abs(f - jugadorFila) <= rangoVision && Math.abs(c - jugadorColumna) <= rangoVision;
                if (f == jugadorFila && c == jugadorColumna) {
                    System.out.print(AZUL + "P" + RESET);
                } else if (caminoRecorrido[nivelActual][f][c]) {
                    System.out.print(GRIS + "░" + RESET); // camino recorrido
                } else if (dentroVision) {
                    System.out.print(colorSimbolo(laberinto[nivelActual][f][c]));
                } else {
                    System.out.print("·");
                }
            }
            System.out.println();
        }
    }

    static String colorSimbolo(char ch) {
        switch (ch) {
            case '1': return GRIS + "#" + RESET;
            case '░': return GRIS + "░" + RESET;
            case 'L': return AMARILLO + "L" + RESET;
            case 'T': return ROJO + "T" + RESET;
            case 'C': return CYAN + "C" + RESET;
            case 'S': return VERDE + "S" + RESET;
            case 'E': return MAGENTA + "E" + RESET;
            case 'X': return CYAN + "🛡" + RESET;
            default: return " ";
        }
    }

    static void mostrarInventario() {
        System.out.println("❤️ Vidas: " + vidas + " | 🔑 Llaves: " + llaves + " | 🛡 Escudos: " + escudos + " | ✨ Puntos: " + puntuacion);
        System.out.println("Comandos: [G]uardar, [C]argar, [Q]uit");
    }

    // ==========================================
    // ======= GUARDAR Y CARGAR PARTIDA =========
    // ==========================================
    static void guardarPartida() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("partida.dat"))) {
            oos.writeObject(laberinto);
            oos.writeObject(caminoRecorrido);
            oos.writeInt(nivelActual);
            oos.writeInt(jugadorFila);
            oos.writeInt(jugadorColumna);
            oos.writeInt(vidas);
            oos.writeInt(llaves);
            oos.writeInt(escudos);
            oos.writeInt(puntuacion);
            System.out.println("💾 Partida guardada.");
        } catch (Exception e) {
            System.out.println("Error al guardar.");
        }
    }

    static void cargarPartida() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("partida.dat"))) {
            laberinto = (char[][][]) ois.readObject();
            caminoRecorrido = (boolean[][][]) ois.readObject();
            nivelActual = ois.readInt();
            jugadorFila = ois.readInt();
            jugadorColumna = ois.readInt();
            vidas = ois.readInt();
            llaves = ois.readInt();
            escudos = ois.readInt();
            puntuacion = ois.readInt();
            System.out.println("📂 Partida cargada.");
        } catch (Exception e) {
            System.out.println("No se pudo cargar partida.");
        }
    }

    // ==========================================
    // ========= PUNTUACIONES ===================
    // ==========================================
    static void guardarPuntuacion(int p) {
        try (FileWriter fw = new FileWriter("puntuaciones.txt", true)) {
            fw.write(p + "\n");
        } catch (Exception ignored) {}
    }

    static void mostrarPuntuaciones() {
        try {
            List<Integer> lista = new ArrayList<>();
            Scanner sc = new Scanner(new File("puntuaciones.txt"));
            while (sc.hasNextInt()) lista.add(sc.nextInt());
            sc.close();

            for (int i = 0; i < lista.size(); i++)
                for (int j = 0; j < lista.size() - 1; j++)
                    if (lista.get(j) < lista.get(j + 1)) {
                        int tmp = lista.get(j);
                        lista.set(j, lista.get(j + 1));
                        lista.set(j + 1, tmp);
                    }

            System.out.println("\n🏆 Mejores puntuaciones:");
            for (int i = 0; i < Math.min(5, lista.size()); i++)
                System.out.println((i + 1) + ". " + lista.get(i));
        } catch (Exception ignored) {}
    }
}

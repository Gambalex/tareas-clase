import java.io.*;
import java.util.*;

public class Main {
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
    static int rangoVision = 5; // celdas visibles alrededor del jugador

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
        mostrarLaberintoCompleto();
        mostrarInventario();

        while (juegoActivo && vidas > 0) {
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
        colocarAleatorioSeguro(nivel, 'X', 1);
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
        colocarJugadorEnNivelActual();
    }

    static void colocarJugadorEnNivelActual() {
        for (int f = 0; f < FILAS; f++)
            for (int c = 0; c < COLUMNAS; c++)
                if (laberinto[nivelActual][f][c] == ' ') {
                    jugadorFila = f;
                    jugadorColumna = c;
                    caminoRecorrido[nivelActual][f][c] = true;
                    return;
                }
    }

    // ==========================================
    // ============ MOVIMIENTO ==================
    // ==========================================
    static void leerMovimiento() throws IOException {
        int tecla = System.in.read();
        switch (tecla) {
            case 'w', 'W': moverJugador(-1, 0); break;
            case 's', 'S': moverJugador(1, 0); break;
            case 'a', 'A': moverJugador(0, -1); break;
            case 'd', 'D': moverJugador(0, 1); break;
            case 'g', 'G': guardarPartida(); break;
            case 'c', 'C': cargarPartida(); break;
            case 'q', 'Q': juegoActivo = false; break;
        }
    }

    static int nivelMultiplicador() {
        return switch (nivelActual) {
            case 0 -> 1;
            case 1 -> 3;
            case 2 -> 5;
            default -> 1;
        };
    }

    static void moverJugador(int df, int dc) {
        int oldF = jugadorFila;
        int oldC = jugadorColumna;

        int nf = jugadorFila + df;
        int nc = jugadorColumna + dc;

        if (nf < 0 || nc < 0 || nf >= FILAS || nc >= COLUMNAS) return;

        char celda = laberinto[nivelActual][nf][nc];

        switch (celda) {
            case '1':
                mostrarFlashMensaje("Choque contra pared.");
                return;
            case 'L':
                llaves++;
                puntuacion += 50 * nivelMultiplicador();
                mostrarFlashMensaje(AMARILLO + "🔑 Llave recogida! +" + (50 * nivelMultiplicador()) + " pts" + RESET);
                laberinto[nivelActual][nf][nc] = ' ';
                break;
            case 'X':
                escudos++;
                mostrarFlashMensaje(CYAN + "🛡 Escudo recogido!" + RESET);
                laberinto[nivelActual][nf][nc] = ' ';
                break;
            case 'T':
                if (escudos > 0) {
                    escudos--;
                    mostrarFlashMensaje(CYAN + "🛡 Escudo usado, trampa evitada!" + RESET);
                } else {
                    vidas--;
                    mostrarFlashMensaje(ROJO + "☠️ Caíste en una trampa! Vidas -" + RESET);
                }
                laberinto[nivelActual][nf][nc] = ' ';
                break;
            case 'C':
                if (llaves > 0) {
                    llaves--;
                    mostrarFlashMensaje("🔓 Puerta abierta.");
                    laberinto[nivelActual][nf][nc] = ' ';
                } else {
                    mostrarFlashMensaje("Necesitas una llave para abrir la puerta.");
                    return;
                }
                break;
            case 'S':
                mostrarFlashMensaje(VERDE + "🏁 Nivel completado!" + RESET);
                 System.out.print("\u001B[2J"); // Borra toda la pantalla
                    System.out.print("\u001B[H");  // Mueve el cursor a la posición 0,0
                    System.out.flush();
                nivelActual = Math.min(nivelActual + 1, NIVELES - 1);
                colocarJugadorEnNivelActual();
                mostrarLaberintoCompleto();
                mostrarInventario();
                return;
            case 'E':
                nivelActual = random.nextInt(NIVELES);
                mostrarFlashMensaje(MAGENTA + "✨ Teletransportado al nivel " + (nivelActual + 1) + RESET);
                colocarJugadorEnNivelActual();
                mostrarLaberintoCompleto();
                mostrarInventario();
                return;
            default: break;
        }

        // Marcar camino recorrido
        caminoRecorrido[nivelActual][oldF][oldC] = true;
        jugadorFila = nf;
        jugadorColumna = nc;

        actualizarVision();
        mostrarInventario();
    }

    // ==========================================
    // ============ VISUALIZACIÓN ===============
    // ==========================================
    static void mostrarLaberintoCompleto() {
        System.out.println("\nNivel: " + (nivelActual + 1));
        for (int f = 0; f < FILAS; f++) {
            for (int c = 0; c < COLUMNAS; c++) {
                System.out.print(dibujarCelda(f, c));
            }
            System.out.println();
        }
    }

    static void actualizarVision() {
        for (int f = 0; f < FILAS; f++) {
            for (int c = 0; c < COLUMNAS; c++) {
                // Si dentro del rango de visión actual, mostrar símbolo real
                if (Math.abs(f - jugadorFila) <= rangoVision && Math.abs(c - jugadorColumna) <= rangoVision) {
                    System.out.print("\u001B[" + (f + 1) + ";" + (c + 1) + "H" + colorSimbolo(laberinto[nivelActual][f][c]));
                } else if (caminoRecorrido[nivelActual][f][c]) {
                    System.out.print("\u001B[" + (f + 1) + ";" + (c + 1) + "H" + GRIS + "░" + RESET);
                } else {
                    System.out.print("\u001B[" + (f + 1) + ";" + (c + 1) + "H" + "·");
                }
            }
        }
        // Mostrar jugador
        System.out.print("\u001B[" + (jugadorFila + 1) + ";" + (jugadorColumna + 1) + "H" + AZUL + "P" + RESET);
    }

    static String dibujarCelda(int f, int c) {
        if (f == jugadorFila && c == jugadorColumna) return AZUL + "P" + RESET;
        else if (caminoRecorrido[nivelActual][f][c]) return GRIS + "░" + RESET;
        else if (Math.abs(f - jugadorFila) <= rangoVision && Math.abs(c - jugadorColumna) <= rangoVision)
            return colorSimbolo(laberinto[nivelActual][f][c]);
        else return "·";
    }

    static String colorSimbolo(char ch) {
        return switch (ch) {
            case '1' -> GRIS + "#" + RESET;
            case '░' -> GRIS + "░" + RESET;
            case 'L' -> AMARILLO + "L" + RESET;
            case 'T' -> ROJO + "T" + RESET;
            case 'C' -> CYAN + "C" + RESET;
            case 'S' -> VERDE + "S" + RESET;
            case 'E' -> MAGENTA + "E" + RESET;
            case 'X' -> CYAN + "🛡" + RESET;
            default -> " ";
        };
    }

    static void mostrarInventario() {
        System.out.print("\u001B[" + (FILAS + 2) + ";1H"); // mover cursor debajo del laberinto
        System.out.println("❤️ Vidas: " + vidas + " | 🔑 Llaves: " + llaves + " | 🛡 Escudos: " + escudos + " | ✨ Puntos: " + puntuacion);
        System.out.println("Comandos: [WASD] mover, [G]uardar, [C]argar, [Q]uit");
    }

    static void mostrarFlashMensaje(String msg) {
        System.out.print("\u001B[" + (FILAS + 4) + ";1H"); // línea de mensaje
        System.out.print("                                                     "); // limpiar línea
        System.out.print("\u001B[" + (FILAS + 4) + ";1H"); // volver al inicio
        System.out.println(msg);
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
            mostrarFlashMensaje("💾 Partida guardada.");
        } catch (Exception e) {
            mostrarFlashMensaje("Error al guardar.");
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
            mostrarFlashMensaje("📂 Partida cargada.");
            mostrarLaberintoCompleto();
            mostrarInventario();
        } catch (Exception e) {
            mostrarFlashMensaje("No se pudo cargar partida.");
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

            lista.sort(Collections.reverseOrder());

            System.out.println("\n🏆 Mejores puntuaciones:");
            for (int i = 0; i < Math.min(5, lista.size()); i++)
                System.out.println((i + 1) + ". " + lista.get(i));
        } catch (Exception ignored) {}
    }
}

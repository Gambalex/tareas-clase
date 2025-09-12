// Matriz principal que representa el tablero del juego
var gatito = [['', '', ''], ['', '', ''], ['', '', '']];
// Variable para contar el número de turnos jugados
var turnos = 0;
// Variable para almacenar el modo de juego seleccionado (computadora o otro jugador)
var modoJuego;
// Variable para saber si ya hay un ganador (si no hay ganador es una cadena vacía)
var ganador = '';

/*
 * Inicia o reinicia el juego.
 * Restablece el tablero, los turnos y las variables de estado.
 */
function iniciar() {
    let i, j;
    // Bucle para recorrer todas las casillas del tablero
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            let button = document.getElementById('button[' + i + '][' + j + ']');
            button.innerHTML = ''; // Limpia el contenido del botón (borra X u O)
            button.disabled = false; // Habilita el botón para que se pueda hacer clic
            // Quita las clases de color de la partida anterior
            button.classList.remove('btn-success', 'btn-danger');
            // Vuelve a añadir la clase de estilo original del botón
            button.classList.add('btn-outline-dark');
        }
    }
    // Restablece los contadores y las variables de estado
    turnos = 0;
    ganador = ''; // CORRECCIÓN: Reinicia la variable del ganador aquí
    modoJuego = document.getElementById('modo-juego').value;
    // Reinicia el tablero en memoria
    gatito = [['', '', ''], ['', '', ''], ['', '', '']];


    // Si el modo es "computadora" y la suerte lo decide, la computadora juega primero
    if (modoJuego === 'computadora' && Math.random() < 0.5) {
        turno_computadora();
    }
}

/*
 * Función principal para gestionar un turno de juego, ya sea un jugador o de computadora.
 * @param {number} i - Índice de la fila del botón que se dfa click.
 * @param {number} j - Índice de la columna del botón que se da click.
 */
function turno(i, j) {
    // Si ya hay un ganador, no permite más movimientos
    if (ganador !== '') {
        return;
    }
    
    // Determina qué símbolo poner (X si el turno es par, O si es impar)
    let casilla = (turnos % 2 === 0) ? 'X' : '0';
    let button = document.getElementById('button[' + i + '][' + j + ']');
    
    button.innerHTML = casilla; // Muestra el símbolo en el botón
    button.disabled = true; // Deshabilita el botón para que no se pueda volver a clicar
    gatito[i][j] = casilla; // Actualiza la matriz del tablero con el símbolo
    
    // Cambia el estilo del botón para mostrar que fue seleccionado
    button.classList.remove('btn-outline-dark');
    button.classList.add(casilla === 'X' ? 'btn-success' : 'btn-danger');
    
    turnos++; // Incrementa el contador de turnos

    ganador = verificar_ganador(); // Llama a la función para ver si hay un ganador
    
    if (ganador !== '') {
        // Muestra una alerta si hay un ganador y finaliza el juego
        alert(ganador === '0' ? 'Ha ganado el jugador 0' : 'Ha ganado el jugador X');
        finalizar_juego();
    } else if (turnos === 9) {
        // Si no hay ganador y el tablero está lleno, es un empate
        alert('Empate');
        finalizar_juego();
    } else if (modoJuego === 'computadora' && casilla === 'X') {
        // Si el modo es contra la computadora, es el turno de la IA
        turno_computadora();
    }
}

/*
 * Verifica si hay un ganador en el tablero.
 * Retorna el símbolo del ganador (X o un O) o un string vacio si no hay nada .
 */
function verificar_ganador() {
    // Verificar filas
    for (let k = 0; k < 3; k++) {
        if (gatito[k][0] !== '' && gatito[k][0] === gatito[k][1] && gatito[k][1] === gatito[k][2]) {
            return gatito[k][0];
        }
    }
    // Verificar columnas
    for (let k = 0; k < 3; k++) {
        if (gatito[0][k] !== '' && gatito[0][k] === gatito[1][k] && gatito[1][k] === gatito[2][k]) {
            return gatito[0][k];
        }
    }
    // Verificar diagonales
    if (gatito[0][0] !== '' && gatito[0][0] === gatito[1][1] && gatito[1][1] === gatito[2][2]) {
        return gatito[0][0];
    }
    if (gatito[0][2] !== '' && gatito[0][2] === gatito[1][1] && gatito[1][1] === gatito[2][0]) {
        return gatito[0][2];
    }
    return ''; // No hay ganador
}

/*
 * Deshabilita todos los botones del tablero para finalizar el juego.
 */
function finalizar_juego() {
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            document.getElementById('button[' + i + '][' + j + ']').disabled = true;
        }
    }
}

/*
 * Maneja el turno de la computadora.
 * Elige una casilla aleatoria y la juega.
 */
function turno_computadora() {
    if (ganador !== '') {
        return; // No juega si el juego ya terminó
    }
    
    let i, j;
    // Bucle para encontrar una casilla vacía de forma aleatoria
    do {
        i = parseInt(Math.random() * 3);
        j = parseInt(Math.random() * 3);
    } while (gatito[i][j] !== '');
    
    let button = document.getElementById('button[' + i + '][' + j + ']');
    button.innerHTML = '0'; // Muestra el símbolo de la computadora
    button.disabled = true;
    gatito[i][j] = '0';
    
    button.classList.remove('btn-outline-dark');
    button.classList.add('btn-danger'); // Le da un color rojo a la jugada de la IA

    turnos++;
    
    ganador = verificar_ganador();

    if (ganador !== '') {
        alert('La computadora ha ganado');
        finalizar_juego();
    } else if (turnos === 9) {
        alert('Empate');
        finalizar_juego();
    }
}
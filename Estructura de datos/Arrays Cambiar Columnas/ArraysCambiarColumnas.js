function colRecorrido(mat) {
    if (!mat || mat.length === 0 || !mat[0] || mat[0].length === 0) {
        console.log("Matriz vacía");
        return;
    }

    const filas = mat.length;
    const cols = mat[0].length;

    console.log("Recorrido por columnas:");
    for (let j = 0; j < cols; j++) {
        for (let i = 0; i < filas; i++) {
            console.log(`Col ${j}, Fila ${i}: ${mat[i][j]}`);
        }
        console.log();
    }
}

const datos = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

colRecorrido(datos);

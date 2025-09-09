def col_recorrido(mat):
    if not mat or not mat[0]:
        print("Matriz vacía")
        return

    filas = len(mat)
    cols = len(mat[0])

    print("Recorrido por columnas:")
    for j in range(cols):
        for i in range(filas):
            print(f"Col {j}, Fila {i}: {mat[i][j]}")
        print()

# Ejemplo
datos = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

col_recorrido(datos)

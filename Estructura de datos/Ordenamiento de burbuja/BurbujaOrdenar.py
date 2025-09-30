def Burbuja(arreglo):
    n = len(arreglo)
    for i in range(n-1):
        for j in range(n-i-1):
            if arreglo[j] > arreglo[j+1]:
                arreglo[j], arreglo[j+1] = arreglo[j+1], arreglo[j]

arreglo = [5, 2, 9, 1, 5, 6]
Burbuja(arreglo)
print(arreglo)

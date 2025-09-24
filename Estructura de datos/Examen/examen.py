arr = [10,10,10,5]
npar = 0
nimpar = 0
suma = 0
contador = 0
promedio = 0
for i in arr:
    if i % 2 == 1:
        nimpar = nimpar + 1
    if i % 2 == 0:
        npar = npar + 1
    suma = suma + i
    contador = contador + 1
    promedio = suma / contador
    
print("Cantidad de numero par:")
print (npar)
print("Cantidad de numero impar:")
print (nimpar)
print("Promedio:")
print (promedio)

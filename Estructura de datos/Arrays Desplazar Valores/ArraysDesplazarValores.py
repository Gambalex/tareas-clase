def insertar_desplazar(nums, idx, val):
    if idx < 0 or idx >= len(nums):
        raise ValueError("Índice fuera de rango")
    return nums[:idx] + [val] + nums[idx:-1]

# Uso
datos = [1,2,3,4,5,6,7,8,9,10]

print("Original:", datos)
print("Inserta 99 en índice 5")

resultado = insertar_desplazar(datos, 5, 99)
print("Resultado:", resultado)

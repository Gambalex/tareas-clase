def busca(nums, x):
    for i in range(len(nums)):
        if nums[i] == x:
            return i
    return -1

datos = [5, 2, 8, 1, 9, 3]
val = 8

pos = busca(datos, val)

if pos != -1:
    print(f"Valor {val} en pos {pos}")
else:
    print(f"Valor {val} no encontrado")

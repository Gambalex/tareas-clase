import time # Para medicion de tiempo
import random # Para generación de arreglos aleatorios
import sys # Para ajustar el limite de recursion
import math # Para funciones matematicas
import matplotlib.pyplot as plt # Para graficos

# Aumentar el limite de recursión para Quicksort en arreglos grandes
try:
    # Este limite es crucial para N=100,000 en casos ordenados/inversos
    sys.setrecursionlimit(200000)
except Exception as e:
    print(f"Advertencia: No se pudo cambiar el límite de recursión. {e}")

#Algoritmos de Ordenamiento
# Lentos
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

# Rapidos
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        izq = arr[:mid]
        dere = arr[mid:]
        merge_sort(izq)
        merge_sort(dere)
        i = j = k = 0
        while i < len(izq) and j < len(dere):
            if izq[i] < dere[j]:
                arr[k] = izq[i]
                i += 1
            else:
                arr[k] = dere[j]
                j += 1
            k += 1
        while i < len(izq):
            arr[k] = izq[i]
            i += 1
            k += 1
        while j < len(dere):
            arr[k] = dere[j]
            j += 1
            k += 1
    return arr

def quicksort(arr):
    # Funcion interna para el Quicksort
    def _quicksort_internal(items, low, high):
        if low < high:
            # Pivote simple (ultimo elemento)
            pivot = items[high]
            i = low - 1
            for j in range(low, high):
                if items[j] <= pivot:
                    i += 1
                    items[i], items[j] = items[j], items[i]
            items[i + 1], items[high] = items[high], items[i + 1]
            pivot_index = i + 1
            
            _quicksort_internal(items, low, pivot_index - 1)
            _quicksort_internal(items, pivot_index + 1, high)

    _quicksort_internal(arr, 0, len(arr) - 1)
    return arr

def heap_sort(arr):
    n = len(arr)
    
    def heapify(arr, n, i):
        grande = i  # Inicializar el más grande como raíz
        izq = 2 * i + 1  # izquierda = 2*i + 1
        dere = 2 * i + 2  # derecha = 2*i + 2

        # Ver si el hijo izquierdo existe y es mayor que la raíz
        if izq < n and arr[i] < arr[izq]:
            grande = izq
        # Ver si el hijo derecho existe y es mayor que la raiz (o el izquierdo)
        if dere < n and arr[grande] < arr[dere]:
            grande = dere
        # Cambiar raiz si es necesario
        if grande != i:
            arr[i], arr[grande] = arr[grande], arr[i]
            heapify(arr, n, grande)

    # Construir un max-heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extraer elementos uno por uno
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # Mover la raiz actual al final
        heapify(arr, i, 0)  # llamar max heapify en el montículo reducido
    return arr

def shell_sort(arr):
    n = len(arr)
    gap = 1
    while gap < n / 3:
        gap = 3 * gap + 1
    
    while gap > 0:
        # Hacer un insertion sort con "gaps"
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        # Reducir el gap
        gap //= 3
    return arr

# No Comparacion
def aux_radix(arr, exp):
    """Función auxiliar para Radix Sort"""
    n = len(arr)
    output = [0] * n
    conteo = [0] * 10  # Contar dígitos del 0 al 9

    # Almacenar conteo de ocurrencias en conteo[]
    for i in range(n):
        index = (arr[i] // exp)
        conteo[index % 10] += 1

    # Conteo acumulativo
    for i in range(1, 10):
        conteo[i] += conteo[i - 1]

    # Construir el arreglo de salida
    i = n - 1
    while i >= 0:
        index = (arr[i] // exp)
        output[conteo[index % 10] - 1] = arr[i]
        conteo[index % 10] -= 1
        i -= 1

    # Copiar el arreglo de salida a arr[]
    for i in range(len(arr)):
        arr[i] = output[i]

def radix_sort(arr):
    """Implementación de Radix Sort para enteros positivos."""
    if not arr:
        return arr
    if len(arr) <= 1:
        return arr
    
    max_val = max(arr)
    
    exp = 1
    while max_val // exp > 0:
        aux_radix(arr, exp)
        exp *= 10
    return arr

def bucket_sort(arr):
    """Implementación de Bucket Sort para números distribuidos."""
    if not arr:
        return arr
    if len(arr) <= 1:
        return arr

    # Crear cubetas
    max_val = max(arr)
    min_val = min(arr)
    rango_val = max_val - min_val
    
    # Evitar división por cero si todos los elementos son iguales
    if rango_val == 0:
        return arr
        
    num_buckets = len(arr)
    buckets = [[] for _ in range(num_buckets)]

    # Distribuir elementos en las cubetas
    for num in arr:
        # Calcular índice de la cubeta
        idx = math.floor((num - min_val) / rango_val * (num_buckets - 1))
        buckets[idx].append(num)
    # Ordenar cada cubeta
    for i in range(num_buckets):
        insertion_sort(buckets[i])

    k = 0
    for i in range(num_buckets):
        for j in range(len(buckets[i])):
            arr[k] = buckets[i][j]
            k += 1
    return arr

def hash_sort(arr):
    if not arr:
        return arr
    if len(arr) <= 1:
        return arr
        
    max_val = max(arr)
    min_val = min(arr)
    rango = max_val - min_val + 1
    
    # 1. Crear el arreglo de conteo 
    conteo = [0] * rango
    
    # 2. Contar ocurrencias
    for num in arr:
        conteo[num - min_val] += 1
        
    # 3. Reconstruir el arreglo ordenado
    k = 0
    for i in range(rango):
        for _ in range(conteo[i]):
            arr[k] = i + min_val
            k += 1
    return arr

# Generacion de Arreglos 
def generar_arreglo(tamaño, estado):
    """Genera un arreglo de un tamaño y estado especifico."""
    if estado == "Ordenado":
        return list(range(tamaño))
    elif estado == "Inverso":
        return list(range(tamaño - 1, -1, -1)) 
    elif estado == "Mediamente Ordenado":
        arr = list(range(tamaño))
        random.shuffle(arr)
        return arr
    else:
        raise ValueError(f"Estado de arreglo desconocido: {estado}")

# 3. Funciones de Reporte y Graficos
def imprimir_resumen_por_metodo(resultados):
    """Imprime el resumen de resultados agrupados por metodo."""
    print("\n" + "="*40)
    print("  RESUMEN DE RESULTADOS POR METODO")
    print("="*40)
    
    for algo, tamaños in resultados.items():
        print(f"\n--- {algo} ---")
        for tamaño, estados in tamaños.items():
            for estado, tiempo in estados.items():
                if tiempo == float('inf') - 1:
                    tiempo_str = "Error de Recursion"
                else:
                    tiempo_str = f"{tiempo:10.6f} seg"
                print(f"  Tamaño {tamaño: <7} | Estado: {estado: <20} | Tiempo: {tiempo_str}")

def imprimir_resumen_por_escenario(resultados, tamaños_arr, estados_arr):
    """Imprime el resumen por escenario, ordenado de mejor a peor."""
    print("\n" + "="*50)
    print("  RESUMEN POR ESCENARIO (ORDENADO DE MEJOR A PEOR)")
    print("="*50)
    
    for tamaño in tamaños_arr:
        for estado in estados_arr:
            print(f"\n--- Escenario: {tamaño} elementos, {estado} ---")
            
            # Recopilar resultados para este escenario
            tiempos_escenario = []
            for algo, tamaños_data in resultados.items():
                tiempo = tamaños_data[tamaño][estado]
                tiempos_escenario.append((algo, tiempo))
            
            # Ordenar de mas rapid a mas lento
            tiempos_escenario.sort(key=lambda x: x[1])
            
            for i, (algo, tiempo) in enumerate(tiempos_escenario):
                if tiempo == float('inf') - 1:
                    tiempo_str = "Error de Recursión"
                else:
                    tiempo_str = f"{tiempo:10.6f} seg"
                print(f"  {i+1}. {algo: <25} | {tiempo_str}")

def graficar_resultados(resultados, tamaños_arr, estados_arr):
    """Genera un grafico por cada algoritmo mostrando su rendimiento."""
    print("\nGenerando graficos...")
    
    algoritmos_por_grafico = 12 
    n_algos = len(resultados)
    n_figs = math.ceil(n_algos / algoritmos_por_grafico)
    
    algos_lista = list(resultados.keys())

    for fig_idx in range(n_figs):
        
        # constrained_layout=True para que matplotlib ajuste todo
        fig, axes = plt.subplots(3, 4, figsize=(20, 15), constrained_layout=True) 
        
        fig.suptitle(f"Rendimiento de Algoritmos (Parte {fig_idx + 1}/{n_figs})", fontsize=16)
        axes = axes.flatten()
        
        algos_para_esta_fig = algos_lista[fig_idx*algoritmos_por_grafico : (fig_idx+1)*algoritmos_por_grafico]
        
        for i, algo in enumerate(algos_para_esta_fig):
            ax = axes[i]
            tamaños_data = resultados[algo]
            ax.set_title(f"Rendimiento de: {algo}")
            
            for estado in estados_arr:
                tiempos = []
                tamaños_plot = []
                for tamaño in tamaños_arr:
                    tiempo = tamaños_data[tamaño][estado]
                    if tiempo < float('inf') - 1: # Solo graficar datos válidos
                        tiempos.append(tiempo)
                        tamaños_plot.append(tamaño)
                
                if tiempos: # Solo graficar si hay datos
                    ax.plot(tamaños_plot, tiempos, marker='o', linestyle='-', label=estado)
            
            ax.set_xlabel("Tamaño del Arreglo (N)")
            ax.set_ylabel("Tiempo de Ejecución (segundos)")
            ax.set_xscale('log')
            ax.set_yscale('log')
            ax.legend()
            ax.grid(True, which="both", linestyle='--', linewidth=0.5)
            ax.set_xticks(tamaños_arr)
            ax.get_xaxis().set_major_formatter(plt.ScalarFormatter())

        # Ocultar ejes no usados
        for i in range(len(algos_para_esta_fig), len(axes)):
            axes[i].set_visible(False)

        plt.show()

# Funcion Principal de Ejecucion 
def ejecutar_benchmark():
    """Funcion principal que ejecuta todas las pruebas."""
    
    tamaños_arr = [100, 1000, 10000, 100000]
    estados_arr = ["Ordenado", "Inverso", "Mediamente Ordenado"]
    
    algoritmos = {
        #Lentos
        "Bubble Sort": bubble_sort,
        "Insertion Sort": insertion_sort,
        "Selection Sort": selection_sort,
        # Rápidos
        "Merge Sort": merge_sort,
        "Quicksort": quicksort,
        "Heap Sort": heap_sort,
        "Shell Sort": shell_sort,
        # No Comparacion
        "Radix Sort": radix_sort,
        "Bucket Sort": bucket_sort,
        "Hash Sort": hash_sort
    }
    
    #almacenar todos los resultados
    resultados = {algo: {tamaño: {} for tamaño in tamaños_arr} for algo in algoritmos}
    
    print("Iniciando Prueba Completa de Algoritmos de Ordenamiento...")
    print(f"Tamaños: {tamaños_arr}")
    print(f"Estados: {estados_arr}")
    
    for tamaño in tamaños_arr:
        for estado in estados_arr:
            print(f"\n--- Probando Escenario: {tamaño} elementos, {estado} ---")
            
            arreglo_base = generar_arreglo(tamaño, estado) 
            for algo_nombre, algo_func in algoritmos.items():
                
                # Crear una copia del arreglo base para cada algoritmo
                arreglo_copia = arreglo_base[:]
                
                try:
                    # Medir el tiempo
                    t_inicio = time.perf_counter()
                    print(f"  Ejecutando {algo_nombre: <25}...", end='', flush=True)
                    algo_func(arreglo_copia)
                    t_fin = time.perf_counter()
                    
                    duracion = t_fin - t_inicio
                    resultados[algo_nombre][tamaño][estado] = duracion
                    print(f" {duracion:10.6f} segundos")
                    
                    # Verificación de ordenamiento (opcional, útil para depurar)
                    # es_ordenado = True
                    # for i in range(len(arreglo_copia) - 1):
                    #     if arreglo_copia[i] > arreglo_copia[i+1]:
                    #         es_ordenado = False
                    #         break
                    # if not es_ordenado:
                    #    print(f"  ¡¡¡ERROR DE ORDENAMIENTO en {algo_nombre}!!!")
                        
                except RecursionError:
                    print(f" [ERROR] {algo_nombre} alcanzo el límite de recursión.")
                    resultados[algo_nombre][tamaño][estado] = float('inf') - 1 # Código especial
                except Exception as e:
                    print(f" [ERROR] {algo_nombre} falló: {e}")
                    resultados[algo_nombre][tamaño][estado] = float('inf') - 1
                    
    return resultados, tamaños_arr, estados_arr

# Ejecucion del Programa
if __name__ == "__main__":
    # Ejecutar las pruebas
    resultados_finales, tamaños, estados = ejecutar_benchmark()
    
    imprimir_resumen_por_metodo(resultados_finales)
    imprimir_resumen_por_escenario(resultados_finales, tamaños, estados)
    graficar_resultados(resultados_finales, tamaños, estados)
    
    print("\nPruebas de Metodos de Ordenamiento finalizado.")

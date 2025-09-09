function insertarDesplazar(nums, idx, val) {
    if (idx < 0 || idx >= nums.length) throw new Error("Índice fuera de rango");

    let res = nums.slice(0, idx);
    res.push(val);
    res = res.concat(nums.slice(idx, nums.length - 1));
    return res;
}

// Uso
const datos = [1,2,3,4,5,6,7,8,9,10];

console.log("Original:", datos);
console.log("Inserta 99 en índice 5");

try {
    const res = insertarDesplazar(datos, 5, 99);
    console.log("Resultado:", res);
} catch (e) {
    console.log("Error:", e.message);
}

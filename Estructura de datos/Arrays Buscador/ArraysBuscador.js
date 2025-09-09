function busca(nums, x) {
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] === x) return i;
    }
    return -1;
}

const datos = [5, 2, 8, 1, 9, 3];
const val = 8;

const pos = busca(datos, val);

if (pos !== -1)
    console.log(`Valor ${val} en pos ${pos}`);
else
    console.log(`Valor ${val} no hallado`);

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

vector<int> insertarDesplazar(const vector<int>& nums, int idx, int val) {
    if (idx < 0 || idx >= nums.size()) throw out_of_range("Índice fuera de rango");

    vector<int> res;
    for (int i = 0; i < idx; i++) res.push_back(nums[i]);
    res.push_back(val);
    for (int i = idx; i < nums.size() - 1; i++) res.push_back(nums[i]);
    return res;
}

int main() {
    vector<int> datos = {1,2,3,4,5,6,7,8,9,10};

    cout << "Original: ";
    for (int n : datos) cout << n << " ";
    cout << "\nInserta 99 en índice 5\n";

    try {
        vector<int> res = insertarDesplazar(datos, 5, 99);
        cout << "Resultado: ";
        for (int n : res) cout << n << " ";
        cout << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

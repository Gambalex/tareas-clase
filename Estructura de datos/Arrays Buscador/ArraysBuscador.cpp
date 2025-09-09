#include <iostream>
#include <vector>
using namespace std;

int busca(const vector<int>& v, int x) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == x) return i;
    }
    return -1;
}

int main() {
    vector<int> nums = {5, 2, 8, 1, 9, 3};
    int val = 8;

    int pos = busca(nums, val);

    if (pos != -1)
        cout << "Valor " << val << " en pos " << pos << endl;
    else
        cout << "Valor " << val << " no hallado" << endl;

    return 0;
}

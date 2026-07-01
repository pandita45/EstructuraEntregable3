#include <iostream>
#include <string>
#include "../Header/ht_abierto.h"
#include "../Header/ht_cerrado.h"

using namespace std;

int main() {
    cout << "=== Prueba de HashTableAbierto<string> ===" << endl;
    HashTableAbierto<string> hashAbierto(10);
    hashAbierto.insert("ana");
    hashAbierto.insert("ana");
    hashAbierto.insert("carlos");
    hashAbierto.insert("lucia");

    int valor = 0;
    if (hashAbierto.get("ana", valor)) {
        cout << "ana = " << valor << endl;
    }
    if (hashAbierto.get("carlos", valor)) {
        cout << "carlos = " << valor << endl;
    }
    if(hashAbierto.get("lucia", valor)) {
        cout << "lucia = " << valor << endl;
    }

    cout << endl;
    cout << "=== Prueba de HashTableCerrado<int> con LINEAR ===" << endl;
    HashTableCerrado<int> hashLineal(10, LINEAR);
    hashLineal.insert(10);
    hashLineal.insert(10);
    hashLineal.insert(21);
    hashLineal.insert(32);

    if (hashLineal.get(10, valor)) {
        cout << "10 = " << valor << endl;
    }
    if (hashLineal.get(21, valor)) {
        cout << "21 = " << valor << endl;
    }

    cout << endl;
    cout << "=== Prueba de HashTableCerrado<int> con QUADRATIC ===" << endl;
    HashTableCerrado<int> hashCuadratica(10, QUADRATIC);
    hashCuadratica.insert(10);
    hashCuadratica.insert(10);
    hashCuadratica.insert(21);
    hashCuadratica.insert(32);

    if (hashCuadratica.get(10, valor)) {
        cout << "10 = " << valor << endl;
    }
    if (hashCuadratica.get(32, valor)) {
        cout << "32 = " << valor << endl;
    }

    cout << endl;
    cout << "=== Prueba de HashTableCerrado<int> con DOUBLE_HASHING ===" << endl;
    HashTableCerrado<int> hashDoble(10, DOUBLE_HASHING);
    hashDoble.insert(10);
    hashDoble.insert(10);
    hashDoble.insert(21);
    hashDoble.insert(32);

    if (hashDoble.get(10, valor)) {
        cout << "10 = " << valor << endl;
    }
    if (hashDoble.get(21, valor)) {
        cout << "21 = " << valor << endl;
    }

    return 0;
}
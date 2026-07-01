#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum State { EMPTY, OCCUPIED, DELETED };

enum ProbeStrategy { LINEAR, QUADRATIC, DOUBLE_HASHING };

template <typename Key>
struct Entry {
    Key key;
    int value;
    State state;

    Entry() : key(0), value(0), state(EMPTY) {}
};



int h1(int k, int n) {
    return k % n;
}

int h2(int k, int n) {
    float a = (float)k * 0.618; 
    a -= (int)a;
    return n * a;
}

// Linear Probing
int linear_probing(int k, int n, int i) {
    return (h1(k, n) + i) % n;
}

// Quadratic Probing
int quadratic_probing(int k, int n, int i) {
    return (h1(k, n) + i + 2 * i * i) % n;
}

// Double Hashing
int double_hashing(int k, int n, int i) {
    return (h1(k, n) + i * h2(k, n)) % n;
}

template <typename Key>
class HashTable {
private:
    vector<Entry<Key>> table;
    int size;
    int elementos;
    int posicionPrimos;
    ProbeStrategy probeStrategy;

public:
    HashTable(int tableSize, ProbeStrategy strategy = LINEAR) : size(tableSize), elementos(0), posicionPrimos(0), probeStrategy(strategy) {
        table.resize(size);
    }

    int probe(int key, int i) {
        // Dependiendo de la estrategia de sondeo, llamamos a la función correspondiente
        switch (probeStrategy) {
            case LINEAR:
                return linear_probing(key, size, i);
            case QUADRATIC:
                return quadratic_probing(key, size, i);
            case DOUBLE_HASHING:
                return double_hashing(key, size, i);
            default:
                return linear_probing(key, size, i);
        }
    }

    void insert(Key key, int value) {
        if ((float)(elementos) / (float)size > 0.75f) {
            resize();
        }

        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            // Si encontramos un lugar vacío o eliminado, insertamos
            if (table[index].state == EMPTY || table[index].state == DELETED) {
                table[index].key = key;
                table[index].value = value;
                table[index].state = OCCUPIED;
                elementos++;
                return;
            }
            // Si ya existe, actualizar
            if (table[index].state == OCCUPIED && table[index].key == key) {
                table[index].value = value;
                return;
            }
        }

    }

    int get(Key key) {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (table[index].state == EMPTY) break; // ya no va a aparecer

            if (table[index].state == OCCUPIED && table[index].key == key) {
                return table[index].value;
            }
        }
        return -1; // Devolver un valor especial para indicar que no se encontró
    }

    void remove(Key key) {

        for (int i = 0; i < size; i++) {
            // Calculamos el índice usando la función de sondeo
            int index = probe(key, i);

            if (table[index].state == EMPTY) break; // Si encontramos un espacio vacío, la clave no está en la tabla

            // Si encontramos la clave, la marcamos como eliminada
            if (table[index].state == OCCUPIED && table[index].key == key) {
                table[index].state = DELETED;
                elementos--;
                return;
            }
        }
    }
    void resize(){
        // Lista de números primos para el tamaño de la tabla hash
        const int primos[] = {3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};
        int cantidadPrimos = primos[posicionPrimos++];
        int newsize;

        if (posicionPrimos >= cantidadPrimos) {
            newsize = size * 2 + 1; // Si nos quedamos sin primos, simplemente duplicamos el tamaño
        } else {
            newsize = primos[posicionPrimos++];
        }

        
        //se guarda la tabla vieja y se crea una nueva con el nuevo tamaño
        vector<Entry<Key>> oldTable = table;
        table.clear();
        table.resize(newsize);
        int oldSize = size;
        size = newsize;
        elementos = 0;

        //se reinsertan los elementos de la tabla vieja en la nueva
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i].state == OCCUPIED) {
                for (int j = 0; j < size; j++) {
                    int index = probe(oldTable[i].key, j);
                    if (table[index].state == EMPTY) {
                        table[index].key = oldTable[i].key;
                        table[index].value = oldTable[i].value;
                        table[index].state = OCCUPIED;
                        elementos++;
                        break;
                    }
                }
            }
        }

        
    }
};

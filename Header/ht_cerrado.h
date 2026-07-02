#ifndef HT_CERRADO
#define HT_CERRADO

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

using namespace std;

enum State { EMPTY, OCCUPIED, DELETED };

enum ProbeStrategy { LINEAR, QUADRATIC, DOUBLE_HASHING };

template <typename Key>
struct EntryCerrado {
    Key key;
    int value;
    State state;
    EntryCerrado() : key(), value(0), state(EMPTY) {}
};


template <typename Key>
class HashTableCerrado {
private:
    vector<EntryCerrado<Key>> table;
    int size;
    int elementos;
    int posicionPrimos;
    ProbeStrategy probeStrategy;

    // Convierte una clave a entero para usar en las funciones hash
    long long keyToInt(const Key &k) const {
        if constexpr (std::is_integral_v<Key>) {
            long long value = static_cast<long long>(k);
            if (value < 0) {
                value = -value;
            }
            return value;
        } else {
            long long suma = 0;
            for (char c : k) suma += static_cast<unsigned char>(c);
            return suma;
        }
    }
    //funcion 1
    int h1(long long k) const {
        long long value = k % size;
        if (value < 0) {
            value += size;
        }
        return static_cast<int>(value);
    }
    //funcion 2
    int h2(long long k) const {
        if (size <= 1) {
            return 1;
        }

        int value = static_cast<int>(k % (size - 1));
        if (value < 0) {
            value += (size - 1);
        }

        return 1 + value;
    }
    
    int linear_probing(const Key &k, int i) const {
        long long kk = keyToInt(k);
        return (h1(kk) + i) % size;
    }

    int quadratic_probing(const Key &k, int i) const {
        long long kk = keyToInt(k);
        long long offset = static_cast<long long>(i) + 2LL * i * i;
        long long index = (h1(kk) + offset) % size;
        if (index < 0) {
            index += size;
        }
        return static_cast<int>(index);
    }

    int double_hashing(const Key &k, int i) const {
        long long kk = keyToInt(k);
        long long offset = static_cast<long long>(i) * h2(kk);
        long long index = (h1(kk) + offset) % size;
        if (index < 0) {
            index += size;
        }
        return static_cast<int>(index);
    }

public:
    HashTableCerrado(int tableSize, ProbeStrategy strategy = LINEAR) : size(tableSize), elementos(0), posicionPrimos(0), probeStrategy(strategy) {
        table.resize(size);
    }

    int probe(const Key &key, int i) const {
        // Dependiendo de la estrategia de sondeo, llamamos a la función correspondiente
        switch (probeStrategy) {
            case LINEAR:
                return linear_probing(key, i);
            case QUADRATIC:
                return quadratic_probing(key, i);
            case DOUBLE_HASHING:
                return double_hashing(key, i);
            default:
                return linear_probing(key, i);
        }
    }

    void insert(const Key &key) {
        // Si la carga de la tabla supera el 75%, redimensionamos
        if ((float)(elementos) / (float)size > 0.75f) {
            resize();
        }
        // Insertamos el elemento usando la estrategia de sondeo
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            // Si encontramos un lugar vacío o eliminado, insertamos
            if (table[index].state == EMPTY || table[index].state == DELETED) {
                table[index].key = key;
                table[index].value = 1;
                table[index].state = OCCUPIED;
                elementos++;
                return;
            }
            // Si ya existe, actualizar
            if (table[index].state == OCCUPIED && table[index].key == key) {
                table[index].value += 1;
                return;
            }
        }

    }
    // Función para obtener el valor asociado a una clave, se guarda en result y devuelve true si se encontró, false si no
    bool get(const Key &key, int &result) const {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (table[index].state == EMPTY) break; // ya no va a aparecer

            if (table[index].state == OCCUPIED && table[index].key == key) {
                result = table[index].value;
                return true;
            }
        }
        return false;
    }
    // Función para eliminar una clave de la tabla hash
    void remove(const Key &key) {

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
    // Función para redimensionar la tabla hash cuando la carga supera el 75%
    void resize(){
        // Lista de números primos para el tamaño de la tabla hash
        const int primos[] = {3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};
        const int cantidadPrimos = static_cast<int>(sizeof(primos) / sizeof(primos[0]));

        while (posicionPrimos < cantidadPrimos && primos[posicionPrimos] <= size) {
            ++posicionPrimos;
        }

        int newsize = (posicionPrimos < cantidadPrimos) ? primos[posicionPrimos++] : size * 2 + 1;
        if (newsize <= size) {
            newsize = size * 2 + 1;
        }

        
        //se guarda la tabla vieja y se crea una nueva con el nuevo tamaño
        vector<EntryCerrado<Key>> oldTable = table;
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

#endif

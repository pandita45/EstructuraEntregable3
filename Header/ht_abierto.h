
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <type_traits>

using namespace std;


template <typename Key>
struct Entry {
    Key key;
    int value;

    Entry(Key k, int v) : key(k), value(v) {}
};

template <typename Key>
class HashTableAbierto {
private:
    int size;
    int elementos;
    vector<list<Entry<Key>>> table;

public:
    HashTableAbierto(int tableSize) : size(tableSize), elementos(0) {
        table.resize(size);
    }

    void insert(Key key) {
        int index = getIndex(key);
        /* se usa la implementación de la función:
        Dada la tabla hash H y dado el usuario con user_id k

        if(k está en H) H[k] = H[k] + 1
        else H[k] = 1

        */
        // Si la clave ya existe, actualizamos el valor
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                entry.value += 1;
                return;
            }
        }

        // Si no existe, la agregamos al final
        table[index].emplace_back(key, 1);
    }

    bool get(Key key, int& result) const {
        int index = getIndex(key);
        // Buscamos la clave en la lista correspondiente al índice
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                result = entry.value;
                return true;
            }
        }

        return false;
    }

    void remove(Key key) {
        int index = getIndex(key);
        // Buscamos la clave en la lista y la eliminamos si la encontramos
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                return;
            }
        }
    }
    int hashFunctionID(const Key& key) const {
        long long value = static_cast<long long>(key);
        if (value < 0) {
            value = -value;
        }

        return static_cast<int>(value % size);
    }
    int hashFunctionString(const string& key) const {
        long long suma = 0;
        for (const unsigned char c : key) {
            suma += static_cast<long long>(c);
        }

        long long index = suma % size;
        if (index < 0) {
            index += size;
        }

        return static_cast<int>(index);
    }
    //función que devuelve el índice de la tabla hash para una clave dada, dependiendo del tipo de clave (int o string)
    int getIndex(const Key& key) const {
        if constexpr (std::is_integral_v<Key>) {
            return hashFunctionID(key);
        } else if constexpr (std::is_same_v<Key, std::string>) {
            return hashFunctionString(key);
        } else {
            static_assert(std::is_integral_v<Key> || std::is_same_v<Key, std::string>, "HashTableAbierto solo soporta claves enteras o std::string");
            return 0;
        }
    }
};

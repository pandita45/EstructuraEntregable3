
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
                cout << "Se ha actualizado el valor de la clave: " << key << " a " << entry.value << endl;
                return;
            }
        }

        // Si no existe, la agregamos al final
        cout << "Se ha insertado la clave: " << key << " con valor 1" << endl;
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
    int hashFunctionID(Key key) const { //hash basica para int
        return key % size;
    }
    int hashFunctionString(const string& key) const {
        //transformar el string
        int suma = 0;
        for(const char& c : key) {
            //suma el valor ASCII de cada caracter
            suma += c; 
        }

        return suma % size;
    }
    //función que devuelve el índice de la tabla hash para una clave dada, dependiendo del tipo de clave (int o string)
    int getIndex(Key key) const {
        if constexpr (std::is_same_v<Key, int>) { // Si Key es int, usamos hashFunctionID
            return hashFunctionID(key);
        } else if constexpr (std::is_same_v<Key, std::string>) { // Si Key es string, usamos hashFunctionString
            return hashFunctionString(key);
        }
    }
};

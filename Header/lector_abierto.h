#ifndef LECTOR_ABIERTO
#define LECTOR_ABIERTO


#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include "ht_abierto.h"



enum class TypeId {ID, SCREEN_NAME};

template <typename Key>
class LectorAbierto {
public:
    HashTableAbierto<Key> lecturaArchivo(TypeId type){
        std::ifstream archivo("../Data/auspol2019.csv");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            exit(1);
        }

        std::string linea;
        HashTableAbierto<Key> hashTable(1000); // Tamaño inicial de la tabla hash
        std::getline(archivo, linea); // Leemos la primera línea (cabecera) y la ignoramos
        while(getline(archivo, linea)){
            std::stringstream ss(linea);
            std::string campo, basura;


            for (int i = 0; i < 8; ++i) {
                if constexpr (std::is_same_v<Key, int>) {
                    if (i == 5 && type == TypeId::ID) {
                        hashTable.insert(static_cast<Key>(std::stol(campo)));
                    }
                } else if constexpr (std::is_same_v<Key, std::string>) {
                    if (i == 7 && type == TypeId::SCREEN_NAME) {
                        hashTable.insert(static_cast<Key>(campo));
                    }
                } else {
                    std::getline(ss, basura, ','); // Leemos el campo y lo ignoramos
                }
            }
        }
        return hashTable;
    }
   
};

#endif

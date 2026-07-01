#ifndef LECTOR_CERRADO
#define LECTOR_CERRADO

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "ht_cerrado.h"

enum class ClosedTypeId { ID, SCREEN_NAME };
enum class ClosedHashType { LINEAR, QUADRATIC, DOUBLE_HASHING };

template <typename Key>
class LectorCerrado {
public:
    HashTableCerrado<Key> lecturaArchivo(ClosedTypeId type, ClosedHashType hashType) {
        std::ifstream archivo("../Data/auspol2019.csv");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            exit(1);
        }

        ProbeStrategy estrategia = LINEAR;
        if (hashType == ClosedHashType::QUADRATIC) {
            estrategia = QUADRATIC;
        } else if (hashType == ClosedHashType::DOUBLE_HASHING) {
            estrategia = DOUBLE_HASHING;
        }

        HashTableCerrado<Key> hashTable(1000, estrategia);
        std::string linea;
       

        std::getline(archivo, linea);
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string campo, basura;

            for (int i = 0; i < 8; i++){
                if constexpr (std::is_same_v<Key, int>) {
                    if (i == 5 && type == ClosedTypeId::ID) {
                        hashTable.insert(static_cast<Key>(std::stoll(campo)));
                    }
                } else if constexpr (std::is_same_v<Key, std::string>) {
                    if (i == 7 && type == ClosedTypeId::SCREEN_NAME) {
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

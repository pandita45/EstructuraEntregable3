#ifndef LECTOR_ABIERTO
#define LECTOR_ABIERTO


#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include "ht_abierto.h"
#include "csv_utils.h"



enum class TypeId {ID, SCREEN_NAME};

template <typename Key>
class LectorAbierto {
public:
    HashTableAbierto<Key> lecturaArchivo(TypeId type, const std::filesystem::path& datasetPath = resolveDatasetPath()){
        std::ifstream archivo(datasetPath);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            exit(1);
        }

        std::string linea;
        HashTableAbierto<Key> hashTable(1000); // Tamaño inicial de la tabla hash
        if (!readCsvRecord(archivo, linea)) {
            return hashTable;
        }

        while (readCsvRecord(archivo, linea)){
            const auto campos = splitCsvRecord(linea);
            if (type == TypeId::ID && campos.size() > 5) {
                hashTable.insert(parseCsvKey<Key>(campos[5]));
            } else if (type == TypeId::SCREEN_NAME && campos.size() > 6) {
                hashTable.insert(parseCsvKey<Key>(campos[6]));
            }
        }
        return hashTable;
    }
   
};

#endif

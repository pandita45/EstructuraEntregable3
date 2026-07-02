#ifndef LECTOR_UNORDERED
#define LECTOR_UNORDERED

#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <type_traits>

#include "csv_utils.h"

enum class UnorderedTypeId {ID, SCREEN_NAME};
template <typename Key>
class LectorUnordered {
public:
    std::unordered_map<Key, int> lecturaArchivo(UnorderedTypeId type, const std::filesystem::path& datasetPath = resolveDatasetPath()){
        std::ifstream archivo(datasetPath);
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            exit(1);
        }

        std::string linea;
        std::unordered_map<Key, int> hashTable;

        if (!readCsvRecord(archivo, linea)) {
            return hashTable;
        }

        while(readCsvRecord(archivo, linea)){
            const auto campos = splitCsvRecord(linea);
            if (type == UnorderedTypeId::ID && campos.size() > 5) {
                hashTable[parseCsvKey<Key>(campos[5])] += 1;
            } else if (type == UnorderedTypeId::SCREEN_NAME && campos.size() > 6) {
                hashTable[parseCsvKey<Key>(campos[6])] += 1;
            }
        }
        return hashTable;
    }

};


#endif
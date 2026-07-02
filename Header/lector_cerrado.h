#ifndef LECTOR_CERRADO
#define LECTOR_CERRADO

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#include "ht_cerrado.h"
#include "csv_utils.h"

enum class ClosedTypeId { ID, SCREEN_NAME };
enum class ClosedHashType { LINEAR, QUADRATIC, DOUBLE_HASHING };

template <typename Key>
class LectorCerrado {
public:
    HashTableCerrado<Key> lecturaArchivo(ClosedTypeId type, ClosedHashType hashType, const std::filesystem::path& datasetPath = resolveDatasetPath()) {
        std::ifstream archivo(datasetPath);
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
       

        if (!readCsvRecord(archivo, linea)) {
            return hashTable;
        }

        while (readCsvRecord(archivo, linea)) {
            const auto campos = splitCsvRecord(linea);

            if (type == ClosedTypeId::ID && campos.size() > 5) {
                hashTable.insert(parseCsvKey<Key>(campos[5]));
            } else if (type == ClosedTypeId::SCREEN_NAME && campos.size() > 6) {
                hashTable.insert(parseCsvKey<Key>(campos[6]));
            }
        }

        return hashTable;
    }
};

#endif

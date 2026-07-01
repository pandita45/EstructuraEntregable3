#ifndef LECTOR_UNORDERED
#define LECTOR_UNORDERED

#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

enum class UnorderedTypeId {ID, SCREEN_NAME};
class LectorUnordered {
public:
    std::unordered_map<std::string, int> lecturaArchivo(UnorderedTypeId type){
        std::ifstream archivo("../Data/auspol2019.csv");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            exit(1);
        }

        std::string linea;
        std::unordered_map<std::string, int> hashTable; // Tabla hash para almacenar los datos
        std::getline(archivo, linea);
        while(getline(archivo, linea)){
            std::stringstream ss(linea);
            std::string campo, basura;

            for (int i = 0; i < 8; ++i) {
                std::getline(ss, campo, ',');
                if (i == 5 && type == UnorderedTypeId::ID) {
                    hashTable[campo] += 1; // Incrementamos el contador para el ID
                } else if (i == 7 && type == UnorderedTypeId::SCREEN_NAME) {
                    hashTable[campo] += 1; // Incrementamos el contador para el SCREEN_NAME
                } else {
                    std::getline(ss, basura, ','); // Leemos el campo y lo ignoramos
                }
            }
        }
        return hashTable;
    }

};


#endif
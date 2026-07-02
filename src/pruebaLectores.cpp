#include <iostream>
#include <string>
#include <filesystem>

#include "../Header/lector_abierto.h"
#include "../Header/lector_cerrado.h"
#include "../Header/lector_unordered.h"

using namespace std;

template <typename Table, typename Key>
void imprimirValor(const string& titulo, const Table& tabla, const Key& clave) {
	int valor = 0;
	cout << titulo;
	if (tabla.get(clave, valor)) {
		cout << " encontrado con conteo = " << valor << endl;
	} else {
		cout << " no encontrado" << endl;
	}
}

int main() {

	cout << "=== Prueba de lectores sobre auspol2019.csv ===" << endl;

	LectorAbierto<long long> lectorAbiertoId;
	auto tablaAbiertaId = lectorAbiertoId.lecturaArchivo(TypeId::ID);
    cout << "HashTableAbierto<long long> creada" << endl;
	imprimirValor("HashTableAbierto<long long> para user_id 92484856", tablaAbiertaId, 92484856LL);

	LectorAbierto<string> lectorAbiertoNombre;
	auto tablaAbiertaNombre = lectorAbiertoNombre.lecturaArchivo(TypeId::SCREEN_NAME);
	imprimirValor("HashTableAbierto<string> para PIPELINEPETE", tablaAbiertaNombre, string("PIPELINEPETE"));

	LectorCerrado<long long> lectorCerradoId;
	auto tablaCerradaLineal = lectorCerradoId.lecturaArchivo(ClosedTypeId::ID, ClosedHashType::LINEAR);
	imprimirValor("HashTableCerrado<long long> LINEAR para user_id 92484856", tablaCerradaLineal, 92484856LL);

	LectorCerrado<string> lectorCerradoNombre;
	auto tablaCerradaCuadratica = lectorCerradoNombre.lecturaArchivo(ClosedTypeId::SCREEN_NAME, ClosedHashType::QUADRATIC);
	imprimirValor("HashTableCerrado<string> QUADRATIC para PIPELINEPETE", tablaCerradaCuadratica, string("PIPELINEPETE"));

	LectorUnordered<long long> lectorUnorderedIds;
	auto conteoIds = lectorUnorderedIds.lecturaArchivo(UnorderedTypeId::ID);
	LectorUnordered<string> lectorUnorderedNombres;
	auto conteoNombres = lectorUnorderedNombres.lecturaArchivo(UnorderedTypeId::SCREEN_NAME);

	cout << "unordered_map para user_id 92484856 = " << conteoIds[92484856LL] << endl;
	cout << "unordered_map para PIPELINEPETE = " << conteoNombres["PIPELINEPETE"] << endl;

	return 0;

}

#ifndef HASH_TABLE
#define HASH_TABLE


//entry representa un par clave-valor, donde la clave es de tipo Key y el valor es un entero
template <typename Key>
struct entry {
    Key key;
    int value;

    entry(Key k, int v) : key(k), value(v) {};
};

// HashTable es una clase abstracta que define la interfaz para una tabla hash
template <typename Key>
class HashTable {
    protected:
        int size;
        int elementos;

    public:
        HashTable(int s) : size(s), elementos(0) {};
        virtual ~HashTable() {};

        virtual void insert(Key key);
        virtual bool get(Key key);
        virtual void remove(Key key);
    };



#endif
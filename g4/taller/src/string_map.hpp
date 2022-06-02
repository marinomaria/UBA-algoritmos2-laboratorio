template <typename T>
string_map<T>::string_map() : raiz(nullptr), _size(0) {}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    _destroy(raiz);

    copiaRecursiva(raiz, d.raiz);
    _size = d.size();
    return *this;
}

template<typename T>
void string_map<T>::copiaRecursiva(Nodo*& destiny, Nodo* source) {
    if (source != nullptr) {
        destiny = new Nodo(source->definicion);
        for (int i = 0; i < 256; i++) {
            copiaRecursiva(destiny->siguientes[i], source->siguientes[i]);
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    _destroy(raiz);
}

template <typename T>
void string_map<T>::_destroy(Nodo* n){
    if (n != nullptr) {
        for (int i = 0; i < 256; i++) {
            _destroy(n->siguientes[i]);
        }
        delete n;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& p) {
    if (raiz == nullptr) {
        raiz = new Nodo();
    }
    Nodo* n = raiz;
    for (int i = 0; i < p.first.size(); i++) {
        // c es la rep numérica del iésimo caracter de la clave
        unsigned int c = int(p.first[i]);

        if (n->siguientes[c] == nullptr) {
            n->siguientes[c] = new Nodo();
        }

        if (i == p.first.size() - 1) {
            // Si ya hay una definición borro el puntero y libero la memoria
            if (n->siguientes[c]->definicion != nullptr) {
                delete n->siguientes[c]->definicion;
            }
            n->siguientes[c]->definicion = new T(p.second);
        }

        n = n->siguientes[c];
    }
    _size++;
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    if (raiz != nullptr) {
        Nodo* n = raiz;
        for (int i = 0; i < clave.size(); i++) {
            // c es la rep numérica del iésimo caracter de la clave
            unsigned int c = int(clave[i]);

            if (n->siguientes[c] != nullptr) {
                if (i == clave.size() - 1 && (n->siguientes[c])->definicion != nullptr) {
                    return 1;
                }
                n = n->siguientes[c];
            } else {
                return 0;
            }
        }
    } else {
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* n = raiz;
    for (char const &c : clave) {
        n = n->siguientes[int(c)];
    }

    return *(n->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* n = raiz;
    for (char const &c : clave) {
        n = n->siguientes[int(c)];
    }

    return *(n->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* u = raiz;
    Nodo* n = raiz;
    unsigned int j = 0;
    // Busco el último nodo útil
    for (int i = 0; i < clave.size(); i++) {
        if (std::count(n->siguientes.cbegin(), n->siguientes.cend(), nullptr) < 255 || n->definicion != nullptr || (i == clave.size() - 1 && std::count(n->siguientes.cbegin(), n->siguientes.cend(), nullptr) == 255)) {
            u = n;
            j = i;
        }

        n = n->siguientes[int(clave[i])];
    }

    if (u != n && std::count(n->siguientes.cbegin(), n->siguientes.cend(), nullptr) == 256) {
        _destroy(u->siguientes[int(clave[j])]);
        u->siguientes[int(clave[j])] = nullptr;
    } else {
        delete n->definicion;
        n->definicion = nullptr;
    }

    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return (_size == 0);
}

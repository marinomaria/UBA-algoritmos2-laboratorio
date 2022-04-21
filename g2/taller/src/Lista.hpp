#include "Lista.h"

Lista::Lista(): _primero(nullptr), _ultimo(nullptr), _longitud(0) {}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

void Lista::_destruir() {
    int l = _longitud;
  for(int i = 0; i < l; i++) {
        eliminar(0);
    }
}

Lista::~Lista() {
    // Completar
    _destruir();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar

    // Si la lista tiene algo, borro todos sus nodos
    _destruir();

    // Si la lista a copiar es vacía imito el comportamiento del constructor Lista()
    if (aCopiar.longitud() == 0) {
        _primero = nullptr;
        _ultimo = nullptr;
        _longitud = 0;
    }
    else {
        for (int i = 0; i < aCopiar.longitud(); i++) {
            agregarAtras(aCopiar.iesimo(i));
        }
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    nuevo->siguiente = _primero;
    _primero = nuevo;
    if (_longitud == 0) {
    // Si la lista estaba vacía tanto el _ultimo tiene que apuntar al mismo nodo que _primero
        _ultimo = nuevo;
    }
    _longitud++;
}

void Lista::agregarAtras(const int& elem) {
    // Completar
    if (_longitud == 0) {
    // Si la lista estaba vacía es lo mismo agregar adelante o atrás
        agregarAdelante(elem);
    }
    else {
        Nodo* nuevo = new Nodo(elem);
        _ultimo->siguiente = nuevo;
        nuevo->anterior = _ultimo;
        _ultimo = nuevo;
        _longitud++;
    }
}

void Lista::eliminar(Nat i) {
    // Completar

    // Busco que tmp apunte al iésimo nodo
    Nodo* tmp = _primero;
    int j = 0;
    while (tmp != nullptr && j < i) {
        tmp = tmp->siguiente;
        j++;
    }

    // Elimino el iésimo nodo y re-enlazo la lista
    if (i == 0) {
        _primero = tmp->siguiente;
    }
    else if (i == _longitud - 1) {
        _ultimo = tmp->anterior;
    }
    else {
        (tmp->anterior)->siguiente = tmp->siguiente;
        (tmp->siguiente)->anterior = tmp->anterior;
    }
    delete tmp;
    _longitud--;
}

int Lista::longitud() const {
    // Completar
    return _longitud;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* tmp = _primero;
    int j = 0;
    while (tmp != nullptr && j < i) {
        tmp = tmp->siguiente;
        j++;
    }
    return tmp->valor;
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* tmp = _primero;
    int j = 0;
    while (tmp != nullptr && j < i) {
        tmp = tmp->siguiente;
        j++;
    }
    return tmp->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}

Lista::Nodo::Nodo(const int& elem): valor(elem), siguiente(nullptr), anterior(nullptr) {};

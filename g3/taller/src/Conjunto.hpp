
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() : _raiz(nullptr) {}

template <class T>
void Conjunto<T>::_destruir(Nodo* n) {
    if (n != nullptr) {
        _destruir(n->izq);
        _destruir(n->der);
        delete n;
    }
}

template <class T>
Conjunto<T>::~Conjunto() {
    _destruir(_raiz);
}

template <class T>
bool Conjunto<T>::_perteneceAux(Nodo* n, const T& clave) const {
    if (n == nullptr) {
        return false;
    } else if (n->valor == clave) {
        return true;
    } else {
        return _perteneceAux(n->izq, clave) || _perteneceAux(n->der, clave);
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    return _perteneceAux(_raiz, clave);
}

template<class T>
void Conjunto<T>::_insertarAux(Conjunto::Nodo *n, const T &clave) {
    if (n->valor > clave) {
        if (n->izq == nullptr) {
            Nodo* c = new Nodo(clave);
            n->izq = c;
        } else {
            _insertarAux(n->izq, clave);
        }
    } else {
        if (n->der == nullptr) {
            Nodo* c = new Nodo(clave);
            n->der = c;
        } else {
            _insertarAux(n->der, clave);
        }
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (!(this->pertenece(clave))) {
        if (_raiz == nullptr) {
            Nodo* n = new Nodo(clave);
            _raiz = n;
        } else {
            _insertarAux(_raiz, clave);
        }
    }
}

template<class T>
void Conjunto<T>::_removerAux(Nodo *n, const T &clave, Nodo *p, std::string dir) {
    if (n->valor == clave) {
        if (n->izq == nullptr && n->der == nullptr) {
            if (dir == "izq") {
                p->izq = nullptr;
            } else {
                p->der = nullptr;
            }
            delete n;
        } else {
            if (n->der != nullptr) {
                n->valor = _minimoAux(n->der);
                _removerAux(n->der, n->valor, n, "der");
            } else {
                n->valor = _maximoAux(n->izq);
                _removerAux(n->izq, n->valor, n, "izq");
            }
        }
    } else if (n->valor > clave) {
        _removerAux(n->izq, clave, n, "izq");
    } else {
        _removerAux(n->der, clave, n, "der");
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (pertenece(clave)) {
        if (_contarNodos(_raiz) == 1) {
            delete _raiz;
            _raiz = nullptr;
        } else {
            _removerAux(_raiz, clave, nullptr, "");
        }
    }
}

template <class T>
const T& Conjunto<T>::_siguienteEnStack(const T &clave, std::vector<Nodo*> stack) const {
    for (int i = stack.size() - 1; i >= 0; i--) {
        if (stack[i]->valor > clave) {
            return stack[i]->valor;
        }
    }
}

template<class T>
const T &Conjunto<T>::_siguienteAux(Conjunto::Nodo *n, const T &clave, std::vector<Nodo*> stack) const {
    if (n->valor == clave) {
        if (n->der != nullptr) {
            return _minimoAux(n->der);
        } else {
            return _siguienteEnStack(clave, stack);
        }
    } else if (n->valor > clave) {
        stack.push_back(n);
        return _siguienteAux(n->izq, clave, stack);
    } else {
        stack.push_back(n);
        return _siguienteAux(n->der, clave, stack);
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    return _siguienteAux(_raiz, clave, {});
}

template<class T>
const T &Conjunto<T>::_minimoAux(Conjunto::Nodo *n) const {
    return n->izq == nullptr ? n->valor : _minimoAux(n->izq);
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return _minimoAux(_raiz);
}

template<class T>
const T &Conjunto<T>::_maximoAux(Conjunto::Nodo *n) const {
    return n->der == nullptr ? n->valor : _maximoAux(n->der);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return _maximoAux(_raiz);
}

template<class T>
unsigned int Conjunto<T>::_contarNodos(Nodo* n) const {
    if (n == nullptr) {
        return 0;
    } else {
        return _contarNodos(n->izq) + _contarNodos(n->der) + 1;
    }
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _contarNodos(_raiz);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}


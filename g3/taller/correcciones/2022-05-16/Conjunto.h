#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& clave);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:

        /**
         * Completar con lo que sea necesario...
         **/

        struct Nodo
        {
            // El constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v) : valor(v), izq(NULL), der(NULL) {};
            // El elemento al que representa el nodo.
            T valor;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der;
        };

        // Puntero a la raíz de nuestro árbol.
        Nodo* _raiz;

        void _destruir(Nodo* n);

        unsigned int _contarNodos(Nodo* n) const;

        bool _perteneceAux(Nodo* n, const T& clave) const;

        void _insertarAux(Nodo* n, const T& clave);

        const T& _minimoAux(Nodo* n) const;

        const T& _maximoAux(Nodo* n) const;

        const T& _siguienteAux(Nodo* n, const T& clave, std::vector<Nodo*> stack) const;

        const T& _siguienteEnStack(const T &clave, std::vector<Nodo*> stack) const;

        void _removerAux(Nodo *n, const T &clave, Nodo *p, std::string dir);

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_

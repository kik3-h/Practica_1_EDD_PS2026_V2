#pragma once

// implementacion propia de Pila (Stack asi en inglich) con punteros dinamicos
// TAD Stack<T>
//hice mucho comentario pq se que aca me van a chiquitiar

#include <stdexcept>

template<typename T>
class Stack {
private:
    // Nodo interno de la pila
    struct Nodo {
        T dato;
        Nodo* siguiente;
        explicit Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* cima_;     // puntero al tope de la pila
    int   tamanio_;  // cantidad de elementos

public:
    // constructor
    Stack() : cima_(nullptr), tamanio_(0) {}

    // dstructor que libera toda la memoria segun lo que se pide (como chinga inge :3)
    ~Stack() {
        while (!empty()) pop();
    }

    // prohibir copia manejo manual de memoria para evitar errores de doble liberación y fugas de memoria
    Stack(const Stack&)            = delete;
    Stack& operator=(const Stack&) = delete;

    
     //inserta un elemento en la cima
     // valor Elemento a insertar
     // Complejidad O(1) porque solo se manipulan punteros sin necesidad de recorrer la estructura
    
    void push(const T& valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cima_;
        cima_ = nuevo;
        ++tamanio_;
    }

    // Elimina el elemento de la cima
    // Complejidad: O(1) 
    
    void pop() {
        if (empty()) throw std::underflow_error("Stack::pop() - pila vacía");
        Nodo* tmp = cima_;
        cima_ = cima_->siguiente;
        delete tmp;
        --tamanio_;
    }

    // Retorna referencia al elemento de la cima
    // Complejidad O(1) y lanza excepción si la pila ests vacia
    
    T& top() {
        if (empty()) throw std::underflow_error("Stack::top() - pila vacía");
        return cima_->dato;
    }

    const T& top() const {
        if (empty()) throw std::underflow_error("Stack::top() - pila vacía");
        return cima_->dato;
    }

    // Retorna el numero de elementos segun la complejidad: O(1) porque se mantiene un contador actualizado en cada operación de push/pop
    int size() const { return tamanio_; }

// Verifica si la pila está vacia Complejidad: O(1) porque solo se verifica si el puntero cima_ es nulo o el contador de tamaño es cero
    bool empty() const { return tamanio_ == 0; }

// Transfiere todos los elementos a un arreglo temporal (para barajar) del arr Arreglo destino (debe tener tamanio_ espacios)
//  Complejidad O(n) porque se recorre toda la pila para copiar los elementos al arreglo
    void toArray(T* arr) {
        Nodo* actual = cima_;
        int i = 0;
        while (actual != nullptr) {
            arr[i++] = actual->dato;
            actual = actual->siguiente;
        }
    }
// Reconstruye la pila desde un arreglo (índice 0 queda al fondo)
     // Complejidad: O(n) porque se recorre todo el arreglo para insertar los elementos en la 
     //pila, ademas de vaciar la pila actual que tambien es O(n) en el peor caso 
     //(cuando la pila tiene muchos elementos)
     
    void fromArray(T* arr, int n) {
        while (!empty()) pop();
        for (int i = 0; i < n; ++i) push(arr[i]);
    }
};
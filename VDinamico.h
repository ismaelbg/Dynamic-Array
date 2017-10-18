#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <iostream>
#include "Palabra.h"
#include <cmath>
#include <climits>

template <class T>
class VDinamico {
public:
    VDinamico();
    VDinamico(const VDinamico& orig);
    virtual ~VDinamico();

    VDinamico(unsigned tam);
    VDinamico(const VDinamico& orig, unsigned inic, unsigned num);
    VDinamico &operator=(VDinamico &right);
    T &operator[](int i);
    void insertar(const T& dato, unsigned int pos = UINT_MAX);
    T borrar(int pos = UINT_MAX);
    void disminuye();
    unsigned int getTaml() const;
    long int busquedaBin(T& p);
    
private:
    int tamf;
    int taml;
    T *v;
};

template <class T>
VDinamico<T>::VDinamico():
    tamf(1),taml(0){
    v = new T [tamf];
}


template <class T>
VDinamico<T>::VDinamico(unsigned tam): taml(tam){
//    while (tamf < tam)
//        tamf *= 2;
    float x = log2(tam)/log2(2);
    int i = ceil(x);
    tamf = pow(2,i);
    v = new T[tamf];
}

template <class T>
VDinamico<T>::VDinamico(const VDinamico& orig):
    tamf(orig.tamf),
    taml(orig.taml){
    v = new T[tamf];
    for (int i = 0; i < taml;i++)
        v[i] = orig.v[i];
}

template <class T>
VDinamico<T>::VDinamico(const VDinamico& orig, unsigned inic, unsigned num):
    taml(num){
    float x = log2(taml)/log2(2);
    int i = ceil(x);
    tamf = pow(2,i);
    v = new T[tamf];
    int j = 0;
    for (unsigned int i = inic; i < (inic+num);i++){
        v[j] = orig.v[i];
        j++;
    }
}

template <class T>
VDinamico<T>& VDinamico<T>::operator=(VDinamico& right) {
    if (this == &right)
        return *this;
    tamf = right.tamf;
    taml = right.taml;
    delete []v;
    v = new T[tamf];
    for (unsigned int i = 0; i < taml;i++)
        v[i] = right.v[i];
    return *this;
}

template <class T>
T& VDinamico<T>::operator[](int i) {
    if ((i < 0) || (i > taml))
        throw std::invalid_argument("[VDinmico::operator[]]: acceso a posición no válida");
    return v[i];
}

template <class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos) {
    if (pos < 0)
        throw std::invalid_argument("[VDinamico::insertar]: posición invalida");
    if (taml == tamf){
        T *vaux;
        vaux = new T[tamf=tamf*2];
        for (int i = 0; i < taml; i++)
            vaux[i] = v[i];
        delete []v;
        v = vaux;
    }
    if (pos == UINT_MAX){
            v[taml] = dato;
            taml++;
    }
    else{
        if (taml != 0)
            for(unsigned int i=taml-1;i>=pos;i--)
                v[i+1] = v[i];
        v[pos] = dato;
        taml++;
    }
}

template <class T>
T VDinamico<T>::borrar(int pos) {
    if ((pos < 0) || (pos > taml))
        throw std::invalid_argument("[VDinamico::borrar] posición no válida");
    T aux = v[pos];
    if (pos == UINT_MAX)
        v[taml] = T();
    else{
        for ( int i = pos;i<taml;i++)
            v[i] = v[i+1];
    }
    taml--;
    VDinamico<T>::disminuye();
    return aux;
}

template <class T>
void VDinamico<T>::disminuye() {
    if (taml*3<tamf){
        tamf = tamf/2;
        T *vaux = new T[tamf];
        for (unsigned i = 0;i<taml;i++)
            vaux[i] = v[i];
        delete []v;
        v = vaux;
    }
}

template <class T>
unsigned int VDinamico<T>::getTaml() const {
    return taml;
}

template <class T>
long int VDinamico<T>::busquedaBin(T& p) {
    int inf = 0;
    int sup = taml - 1;
    int curIn;

    while (inf <= sup) {
        curIn = (inf + sup) / 2;
        if (v[curIn] == p)//if(v[curIn].GetTermino()==p.GetTermino())//obligatorio sobrecargar este operador
            return curIn;
        else if (v[curIn] < p) inf = curIn + 1; //(v[curIn].GetTermino()<p.GetTermino()) inf=curIn+1;//obligatorio sobrecargar este operador
        else sup = curIn - 1;
        
    }
    return -1;
}

template <class T>
VDinamico<T>::~VDinamico() {
    delete []v;
}

#endif /* VDINAMICO_H */

#include "Ruta.h"
#include <string>
#include <list>
#include <iostream>
#include "Punto.h"

using namespace std;


Ruta::Ruta(){}

void Ruta::Insertar (const Punto & n){

    puntos.push_back(n);

}

void Ruta::Borrar(const Punto & n){

    puntos.remove(n);

}

string Ruta::GetCode()const{

    return code;

}

void Ruta::SetCode(const string & code){

    this->code = code;

}

bool Ruta::operator==(const Ruta & R)const{

    return (puntos == R.puntos && code == R.code);
}

bool Ruta::operator<(const Ruta &R)const{

    return (puntos.size() < R.puntos.size());
}

Ruta::iterator Ruta::begin(){
    iterator it;
    it.p = puntos.begin();
    return it;
}  

Ruta::const_iterator Ruta::begin()const{
    const_iterator it;
    it.p = puntos.cbegin();
    return it;
}

Ruta::iterator Ruta::end(){
    iterator it;
    it.p = puntos.end();
    return it;
}
Ruta::const_iterator Ruta::end()const{
    const_iterator it;
    it.p = puntos.cend();
    return it;
}

Ruta::iterator Ruta::find(const Punto &p){
    
    iterator it;
    list<Punto>::iterator i;
    for (i=puntos.begin(); i!=puntos.end() && !((*i) == p); ++i);
        it.p=i;
    return it;
}

istream & operator>>(istream & is, Ruta & R){
    
    int numPuntos;
    is >> R.code;
    is >> numPuntos;

    for (int i=0; i<numPuntos; i++){
        Punto p_aux;
        is >> p_aux;
        R.puntos.emplace_back(p_aux);
    }
    
    return is;
}

ostream & operator<<(ostream & os, const Ruta &R){

    os << R.code << " " << R.puntos.size() << " ";

    Ruta::const_iterator it;
    for (it = R.begin(); it != R.end(); ++it){
        os << (*it);
        os << " ";
    }

    return os;

}
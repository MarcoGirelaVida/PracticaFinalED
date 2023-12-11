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
    // DESCONOZCO SI EL CODIGO ES ÚNICO
    // EN ESTE CODIGO SE SUPONE QUE SI

    return (puntos == R.puntos && code == R.code);
}

bool Ruta::operator<(const Ruta &R)const{
    // SE SUPONE Q UNA RUTA ES MAYOR QUE OTRA
    // SI TIENE MAS PUNTOS

    return (puntos.size() < R.puntos.size());
}

#include <iostream>
#include "Punto.h"
#include <cassert>

using namespace std;


double Punto::GetLatitud()const{
    return latitud;
}

double Punto::GetLongitud()const{
    return longitud;
}

void Punto::SetLatitud(double l){
    latitud = l;
}

void Punto::SetLongitud(double l){
    longitud = l;
}

bool Punto::operator<(const Punto &p)const{

    if (GetLatitud() < p.GetLatitud()) {
        return true;
    } else if (GetLatitud() == p.GetLatitud() && GetLongitud() < p.GetLongitud()) {
        return true;
    } else {
        return false;
    }

}

bool Punto::operator==(const Punto &p)const{

    return ((GetLatitud() == p.GetLatitud()) && GetLongitud() == p.GetLongitud()); 
        
}

istream & operator>>(istream & is, Punto &p){
    is >> p.latitud >> p.longitud;
}

ostream & operator<<(ostream & os, const Punto &p){
    os << p.GetLatitud() << p.GetLongitud() << endl;
}
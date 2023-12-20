
#include "Pais.h"
#include "Paises.h"
#include <unordered_set>
#include <vector>
using namespace std;


Paises::Paises(){}

void Paises::Insertar(const Pais &P){
    datos.emplace(make_pair(P.GetPunto().GetLatitud(),P.GetPunto().GetLongitud()),P);
}
void Paises::Borrar(const Pais &P){
    datos.erase(make_pair(P.GetPunto().GetLatitud(),P.GetPunto().GetLongitud()));
}


Paises::iterator Paises::begin(){
    iterator it;
    it.p = datos.begin();
    return it;
}  

Paises::const_iterator Paises::begin()const{
    const_iterator it;
    it.p = datos.cbegin();
    return it;
}

Paises::iterator Paises::end(){
    iterator it;
    it.p = datos.end();
    return it;
}
Paises::const_iterator Paises::end()const{
    const_iterator it;
    it.p = datos.cend();
    return it;
}

Paises::iterator Paises::find(const Pais &p){
    iterator it = find(p.GetPunto());
    return it;
}

Paises::iterator Paises::find(const Punto &p){
    
    iterator it;
    unordered_map<pair<double,double>,Pais>::iterator i;
    for (i=datos.begin(); i!=datos.end() && !(i->first.first == p.GetLatitud() && i->first.second == p.GetLongitud()); ++i);
        it.p=i;
    return it;
}

istream & operator>>(istream & is, Paises & R){
    Paises rlocal;
    //leemos el comentario
    if (is.peek()=='#'){
        string a;
        getline(is,a);
    }	
    
    Pais P;
    while (is>>P){
    rlocal.Insertar(P);
    
    }
    
    R=rlocal;
    return is;
}

ostream & operator<<(ostream & os, const Paises &R){
    Paises::const_iterator it;
    for (it=R.begin(); it!=R.end(); ++it){
        os<<*it<<"\t";
    }
    return os;
}

<<<<<<< HEAD
#include <iostream>
#include "Almacen_Rutas.h"

using namespace std;

=======
#include "Almacen_Rutas.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;


Almacen_Rutas::Almacen_Rutas(){}

>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
void Almacen_Rutas::Insertar(const Ruta & R){

    rutas.emplace(R.GetCode(),R);

}

<<<<<<< HEAD
void Almacen_Rutas::Borrar(const Ruta & R){
=======
void Almacen_Rutas::Insertar(const Ruta & R){
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727

    rutas.erase(R.GetCode());

}

<<<<<<< HEAD

Ruta Almacen_Rutas::GetRuta(const string & a){

    map<string,Ruta>::iterator it;
=======
Ruta Almacen_Rutas::GetRuta(const string & a){

    unordered_map<string,Ruta>::iterator it;
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
    it = rutas.find(a);

    return it->second;
}


Almacen_Rutas::iterator Almacen_Rutas::begin(){
    iterator it;
    it.p = rutas.begin();
    return it;
}  

Almacen_Rutas::const_iterator Almacen_Rutas::begin()const{
    const_iterator it;
    it.p = rutas.cbegin();
    return it;
}

Almacen_Rutas::iterator Almacen_Rutas::end(){
    iterator it;
    it.p = rutas.end();
    return it;
}

Almacen_Rutas::const_iterator Almacen_Rutas::end()const{
    const_iterator it;
    it.p = rutas.cend();
    return it;
}

istream & operator >> (istream & is, Almacen_Rutas & AR){

    //leemos el comentario
    if (is.peek()=='#'){
        string a;
        getline(is,a);
    }	
    
    Ruta R;
    while (is>>R){
        AR.Insertar(R);
    }
    
    return is;
}

ostream & operator << (ostream & os, const Almacen_Rutas &AR){

    Almacen_Rutas::const_iterator it;

    os << "#Rutas" << endl;
    for (it=AR.begin(); it!=AR.end(); ++it){
        os<<*it<<endl;
    }
    return os;
}
<<<<<<< HEAD
#include "Pais.h"

=======
#include "Punto.h"
#include "Pais.h"

    Pais::Pais(){}
    
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
    Punto Pais::GetPunto()const {
        return p;
    }
    string Pais::GetPais()const{
        return pais;
    }
    string Pais::GetBandera()const{
        return bandera;
    }
    
    bool Pais::operator<(const Pais &P)const{
        return GetPunto() < P.GetPunto();
    }	
    bool Pais::operator==(const Pais &P)const{
        return GetPunto() == P.GetPunto();
    }
     bool Pais::operator==(const Punto &P)const{
        return GetPunto() == P;
    }
    istream & operator>>(istream & is, Pais & P){
        double lat,lng;
	
	    is>>lat>>lng>>P.pais>>P.bandera;
	
	    P.p=Punto(lat,lng);
	    return is;
    }

    ostream & operator<<(ostream & os, const Pais &P){
	    os<<P.p<<" "<<P.pais<<" "<<P.bandera<<endl;
	    return os;
    }
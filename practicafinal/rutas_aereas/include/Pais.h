
#include "Punto.h"



class Pais{
  private:
    Punto p;
    string pais;
    string bandera;
    
  public:
    Pais();
    Punto GetPunto()const;
    string GetPais()const;
    string GetBandera()const;
    
    bool operator<(const Pais &P)const;

    bool operator==(const Pais &P)const;

     bool operator==(const Punto &P)const;

    friend istream & operator>>(istream & is, Pais & P);

    friend ostream & operator<<(ostream & os, const Pais &P);

};
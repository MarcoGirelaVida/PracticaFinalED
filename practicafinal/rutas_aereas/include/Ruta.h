#include <string>
#include <list>
#include <iostream>
#include "Punto.h"
#include "imagen.h"
#include "Paises.h"


#ifndef RUTA
#define RUTA

using namespace std;

class Ruta{

    private:
        list<Punto> puntos;
        string code;
    public:
        Ruta();
        void Insertar (const Punto & n);
        void Borrar (const Punto & n);
        string GetCode()const;
        Imagen PintarRuta(const Imagen & mapa, Paises & paises, const char * FlagPath, const Imagen & avion);

                iterator(){}
                bool operator == (const iterator &i){return p == i.p;}  
                bool operator != (const iterator &i){return p != i.p;}
                iterator & operator++(){
                    ++p;
                    return *this;
                }
                iterator& operator--(){
                    --p;
                    return *this;
                }

                Punto & operator*(){
                    return *p;
                }
                
            friend class Ruta;
            friend class const_iterator;
	    }; 

        class const_iterator{
            private:
                list<Punto>::const_iterator p;
            public:
                const_iterator(){}
                bool operator == (const const_iterator &i){return p == i.p;}
                bool operator != (const const_iterator &i){return p != i.p;}
                const_iterator & operator++(){
                    ++p;
                    return *this;		
                }
                const_iterator & operator--(){
                    --p;
                    return *this;
                }
                
                const Punto & operator*()const{
                    return *p;
                }

                friend class Ruta;
            
        };

        iterator begin();
        const_iterator begin()const;
        iterator end();
        const_iterator end()const;

        iterator find(const Punto &p);

        friend istream & operator>>(istream & is, Ruta & R);
        friend ostream & operator<<(ostream & os, const Ruta &R);
};

#endif
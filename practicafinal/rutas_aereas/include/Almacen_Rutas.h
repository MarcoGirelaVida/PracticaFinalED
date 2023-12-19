#include <string>
#include <unordered_map>
#include <iostream>
#include "Ruta.h"
#include "imagen.h"

#ifndef ALMACEN_RUTAS
#define ALMACEN_RUTAS

class Almacen_Rutas{


    private:
        unordered_map<string,Ruta> rutas;
    public:
        Almacen_Rutas();
        void Insertar(const Ruta & R);
        void Borrar(const Ruta & R);
        Ruta GetRuta(const string & a);
        Imagen PintarRuta(const Imagen & mapa, const Ruta & R);



        class iterator{
            private:
                unordered_map<string,Ruta>::iterator p;
            public:
                iterator(){}
                bool operator == (const iterator &i){return p == i.p;}  
                bool operator != (const iterator &i){return p != i.p;}
                iterator & operator++(){
                    ++p;
                    return *this;
                }

                Ruta & operator*(){
                    return p->second;
                }
                
            friend class Almacen_Rutas;
            friend class const_iterator;
        };

        class const_iterator{
            private:
                unordered_map<string,Ruta>::const_iterator p;
            public:
                const_iterator(){}
                bool operator == (const const_iterator &i){return p == i.p;}  
                bool operator != (const const_iterator &i){return p != i.p;}
                const_iterator & operator++(){
                    ++p;
                    return *this;
                }

                const Ruta & operator*()const{
                    return p->second;
                }
                
            friend class Almacen_Rutas;
        };

        iterator begin();
        const_iterator begin()const;
        iterator end();
        const_iterator end()const;

        friend istream & operator >> (istream & is, Almacen_Rutas & AR);
        friend ostream & operator <<(ostream & os, const Almacen_Rutas &R);


};

#endif
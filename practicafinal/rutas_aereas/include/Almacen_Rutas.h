#include <string>
<<<<<<< HEAD
#include <map>
=======
#include <unordered_map>
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
#include <iostream>
#include "Ruta.h"
#include "imagen.h"

#ifndef ALMACEN_RUTAS
#define ALMACEN_RUTAS

class Almacen_Rutas{


    private:
<<<<<<< HEAD
        map<string,Ruta> rutas;
    public:
        Almacen_Rutas(){};
        void Insertar(const Ruta & R);
        void Borrar(const Ruta & R);
        Ruta GetRuta(const string & a);

        class iterator{
            private:
                map<string,Ruta>::iterator p;
=======
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
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
            public:
                iterator(){}
                bool operator == (const iterator &i){return p == i.p;}  
                bool operator != (const iterator &i){return p != i.p;}
                iterator & operator++(){
                    ++p;
                    return *this;
                }

<<<<<<< HEAD
                iterator & operator--(){
                    --p;
                    return *this;
                }

=======
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
                Ruta & operator*(){
                    return p->second;
                }
                
            friend class Almacen_Rutas;
            friend class const_iterator;
        };

        class const_iterator{
            private:
<<<<<<< HEAD
                map<string,Ruta>::const_iterator p;
=======
                unordered_map<string,Ruta>::const_iterator p;
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
            public:
                const_iterator(){}
                bool operator == (const const_iterator &i){return p == i.p;}  
                bool operator != (const const_iterator &i){return p != i.p;}
                const_iterator & operator++(){
                    ++p;
                    return *this;
                }

<<<<<<< HEAD
                const_iterator & operator--(){
                    --p;
                    return *this;
                }

=======
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727
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
<<<<<<< HEAD
        friend ostream & operator <<(ostream & os, const Almacen_Rutas &AR);
=======
        friend ostream & operator <<(ostream & os, const Almacen_Rutas &R);
>>>>>>> 5bae131a539d3d157aaa1d5f80d687cb53872727


};

#endif
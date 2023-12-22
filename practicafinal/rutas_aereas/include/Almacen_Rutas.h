/*!
 * @file Almacen_Rutas.h
 * @brief Cabecera para la clase Almacen de Rutas
 */


#include <string>
#include <map>
#include <iostream>
#include "Ruta.h"
#include "imagen.h"

#ifndef ALMACEN_RUTAS
#define ALMACEN_RUTAS


/**
 * @brief T.D.A Almacen de Rutas 
 * 
 * Una instancia del tipo de dato abstracto Almacen de Rutas nos permite
 * almacenar una colección de rutas y acceder a ellos con facilidad
 * mediante el uso de identificadores de ruta guardados como clave
 * 
 * El TDA proporciona herramientas para su manipulación y uso
 * 
 * Para poder usar el TDA Paises hay que incluir el fichero
 * 
 * \#include <Almacen_Rutas.h>
 * 
 * TIPO DE REPRESENTACIÓN:
 * 
 * Colección de claves con objetos asociados en los que la claves son
 * string y los objetos asociados son objetos de la clase Ruta.
 * 
 * La relación entre clave y objeto es la siguiente:
 * 
 * String = Ruta.GetCode
 */

class Almacen_Rutas{


    private:

        /**
         *@brief Conjunto ordenado de Rutas
         */
       map<string,Ruta> rutas;
    public:

        /**
         * @brief Constructor por defecto
         * @post Genera una instancia de Almacen_Rutas sin datos inicializados
         * @return Almacen_Rutas, el objeto creado
         */
        Almacen_Rutas(){};

        /**
         * @brief Inserción de una ruta en el conjunto
         * @param R Ruta que se va a insertar en el conjunto de rutas
         * @pre R es una Ruta inicializada correctamente
         * @post La ruta no se modifica. El conjunto es modificado añadiendo
         * la nueva Ruta
         */
        void Insertar(const Ruta & R);
        
        /**
         * @brief Borrado de una ruta del conjunto
         * @param R Ruta que se va a borrar del conjunto de rutas
         * @pre R es una Ruta inicializada correctamente
         * @post La ruta no se modifica. El conjunto es modificado eliminando
         * la Ruta R
         */
        void Borrar(const Ruta & R);

        /** @brief Ruta con número identificatorio concreto
         *  @param a Código identificatorio de la Ruta que se busca
         *  @post La colección no se modifica
         *  @return La ruta cuyo codigo coincide con el codigo a
         */
        Ruta GetRuta(const string & a);

        class iterator{
            private:
                map<string,Ruta>::iterator p;
            public:
                iterator(){}
                bool operator == (const iterator &i){return p == i.p;}  
                bool operator != (const iterator &i){return p != i.p;}
                iterator & operator++(){
                    ++p;
                    return *this;
                }

                iterator & operator--(){
                    --p;
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
                map<string,Ruta>::const_iterator p;
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

                const Ruta & operator*()const{
                    return p->second;
                }
                
            friend class Almacen_Rutas;
        };

        /**
         * @brief Inicio de la colección de Rutas
         * @post La colección no se ve modificada
         * @return Iterador que apunta a la primera Ruta de la colección
         */
        iterator begin();
        /**
         * @brief Inicio de la colección de Rutas
         * @post La colección no se ve modificada
         * @return Const_iterator que apunta a la primera Ruta de la colección
         */
        const_iterator begin()const;
        /**
         * @brief Final de la colección de Rutas
         * @post La colección no se ve modificada
         * @return Iterador que apunta a la ultima Ruta de la colección
         */
        iterator end();

        /**
         * @brief Final de la colección de Rutas
         * @post La colección no se ve modificada
         * @return Const_iterator que apunta a la ultima Ruta de la colección
         */
        const_iterator end()const;

        friend istream & operator >> (istream & is, Almacen_Rutas & AR);
        friend ostream & operator <<(ostream & os, const Almacen_Rutas &AR);


};

#endif
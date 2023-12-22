/*!
 * @file Ruta.h
 * @brief Cabecera para la clase Ruta
 */

#include <string>
#include <list>
#include <iostream>
#include "Punto.h"
#include "imagen.h"
#include "Paises.h"


#ifndef RUTA
#define RUTA


/**
 *@brief T.D.A Ruta 
 * 
 * Una instancia del tipo de dato Abstracto Ruta nos permite
 * almacenar datos sobre un conjunto de Puntos que forman una
 * Ruta y ponerle un código identificatorio
 *  
 * Cada punto es un objeto de la clase Punto
 * 
 * El TDA también proporciona herramientas para su manipulación y uso
 * 
 * Para poder usar el TDA Ruta hay que incluir el fichero
 * 
 * \#include <Ruta.h>
 * 
 * 
 * TIPO DE REPRESENTACIÓN:
 *  Conjunto formado por una colección de puntos geográficos y un string que
 *  representa el recorrido de la ruta en un mapa y su identificador
 *  respectivamente.
 * 
 *  FUNCION DE ABSTRACCIÓN:
 * 
 * 
 */
class Ruta{

    private:

        /**
         * @brief Colección de puntos geográficos 
         */
        list<Punto> puntos;

        /**
         *@brief Identificador de la ruta 
         */
        string code;

    public:

        /**
         * @brief Constructor por defecto
         * @post Genera una instancia de Ruta sin datos inicializados
         * @return Ruta, el objeto creado
         */
        Ruta(){};



        /**
         * @brief Inserción de un pais en el conjunto
         * @param n Punto que se va a insertar en la Ruta
         * @pre n es un Punto inicializado correctamente
         * @post El punto no se modifica. El conjunto es modificado
         * añadiendo el nuevo pais
         */
        void Insertar (const Punto & n);
        /**
         * @brief Borrado de un Punto del conjunto
         * @param n Punto que se va a borrar de la Ruta
         * @pre n es un Punto inicialiado correctamente
         * @post El Punto no se modifica. El conjunto es modificado
         * eliminando el nuevo pais
         */
        void Borrar (const Punto & n);
        /**
         * @brief Código identificatorio de la ruta
         * @return Código de la ruta en forma de string
         * @post La ruta no se modifica
         */
        string GetCode()const;

        /**
         * @brief Pintado de Aviones entre dos puntos de una ruta
         * @param f1 Coordenada X del primer punto
         * @param f2 Coordenada X del segundo punto
         * @param c1 Coordenada Y del primer punto
         * @param c2 Coordenada Y del segundo punto
         * @param I Imagen del Mapa donde se van a pintar los aviones
         * @param avion Imagen del avión que se va a usar para pintar
         * @param mindisf Mínimo de filas
         * @param mindisc Mínimo de columnas
         */
        void PintarAviones(int f1,int f2,int c1,int c2,Imagen &I, const Imagen &avion,int mindisf,int mindisc);
        Imagen PintarRuta(const Imagen & mapa, Paises & paises, const string FlagPath, const Imagen & avion);

        void SetCode(const string & code);
        bool operator==(const Ruta & R)const;
        bool operator<(const Ruta &R)const;

        class iterator{
            private:
                list<Punto>::iterator p;
            public:
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
/*!
 * @file Paises.h
 * @brief Cabecera para la clase Paises
 */ 

#include "Pais.h"
#include "Punto.h"
#include <map>
using namespace std;

#ifndef PAISES
#define PAISES


/**
 * @brief T.D.A Paises
 * 
 * Una instancia del tipo de dato Abstracto Paises nos permite almacenar
 * una colección de paises y acceder a ellos con facilidad
 * 
 * EL TDA proporciona herramientas para su manipulación y uso
 * 
 * Para poder usar el TDA Paises hay que incluir el fichero
 * 
 * \#include <Paises.h>
 * 
 * TIPO DE REPRESENTACIÓN:
 * 
 * Colección de claves con objetos asociados en los que las claves son
 * objetos de la clase Punto y los objetos asociados son objetos de la
 * clase Pais. La relación entre clave y objeto es la siguiente:
 * 
 * Punto(clave) = Pais.getPunto()
 * 
 * 
 * 
 */

class Paises{
  private:

	/**
	 * @brief Conjunto ordenado de países
	 */
    map<Punto,Pais> datos;
  public:
	
	/**
	 * @brief Constructor por defecto
	 * @post Genera una instancia de Paises sin datos inicializados
	 * @return Paises, el objeto creado
	 */

    Paises(){};

	/**
	 * @brief Inserción de un pais en el conjunto
	 * @param P Pais que se va a insertar en el conjunto de paises
	 * @pre p es un Pais inicializado correctamente
	 * @post El Pais no se modifica. El conjunto es modificado añadiendo
	 * el nuevo pais
	 */
    void Insertar(const Pais &P);


	/**
	 * @brief Borrado de un pais del conjunto
	 * @param P Pais que se va a borrar del conjunto de paises
	 * @pre p es un Pais inicializado correctamente
	 * @post El pais no se modifica. Se elimina el Pais del conjunto, modificandolo
	 */
    void Borrar(const Pais &P);
      
	class iterator{
	private:
	    map<Punto,Pais>::iterator p;
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
		
		const Pais & operator*()const{
			return p->second;
		}
		
	    friend class Paises;
	    friend class const_iterator;
	};    

	class const_iterator{
	private:
	    map<Punto,Pais>::const_iterator p;
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

		const Pais & operator*()const{
			return p->second;
		}

	    friend class Paises;
	   
	};


	/**
	 * @brief Inicio de la colección de Paises 
	 * @post La colección no se ve modificada
	 * @return Iterador que apunta al primer pais de la colección
	 */
	iterator begin();

	/**
	 * @brief Inicio de la colección de Paises 
	 * @post La colección no se ve modificada
	 * @return Const_iterator que apunta al primer pais de la colección
	 */
	const_iterator begin()const;
	/**
	 * @brief Final de la colección de Paises 
	 * @post La colección no se ve modificada
	 * @return Iterador que apunta al ultimo pais de la colección
	 */
	iterator end();

	/**
	 * @brief Final de la colección de Paises 
	 * @post La colección no se ve modificada
	 * @return Const_iterator que apunta al ultimo pais de la colección
	 */
	const_iterator end()const;



	/**
	 * @brief Búsqueda de un Pais en la colección
	 * @param p Pais a buscar en la colección
	 * @pre p es un Pais inicializado correctamente
	 * @post La colección no se ve modificada
	 * @return iterador que apunta al Pais encontrado
	 */
	iterator find(const Pais &p);

	/**
	 * @brief Búsqueda de un Pais en la colección
	 * @param p Punto del pais a buscar en la colección
	 * @pre p es un Punto inicializado correctamente
	 * @post La coleccion no se ve modificada
	 * @return iterador que apunta al Pais encontrado
	 */
	iterator find(const Punto &p);

    /**
     * @brief Sobrecarga del flujo de entrada
     * @param is flujo de entrada a leer
     * @param R Objeto de la clase Países donde se almacenarán los Paises leidos de @p is  
     * @pre @p R es un conjunto vacío (o no) de Paises inicializado correctamente
     * @post Se rellenan los datos del conjunto de Paises @p R con los Paises leidos del flujo
     * @p is
     */
	friend istream & operator>>(istream & is, Paises & R);

	/**
     * @brief Sobrecarga del flujo de salida
     * @param is flujo de salida donde se escribirán datos
     * @param R Objeto de la clase Paises de donde se extraerán los datos a almacenar en @p is  
     * @pre @p R es un conjunto de Países inicializado correctamente
     * @post Se leen los datos del conjunto de Paises @p R y se escriben en el flujo @p os
     */
	friend ostream & operator<<(ostream & os, const Paises &R);
};


#endif
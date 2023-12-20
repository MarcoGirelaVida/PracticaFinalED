/*!
 * @file Paises.h
 * @brief Cabecera para la clase Paises
 */ 

#include "Pais.h"
#include <unordered_map>
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
 * 
 * 
 * 
 */

class Paises{
  private:

	/**
	 * @brief Conjunto ordenado de países
	 */
    unordered_map<pair<double,double>,Pais> datos;
  public:
	
	/**
	 * @brief Constructor por defecto
	 * @post Genera una instancia de Paises sin datos inicializados
	 * @return Paises, el objeto creado
	 */

    Paises();

	/**
	 * @brief Inserción de un pais en el conjunto
	 * @param P Pais que se va a insertar en el conjunto de paises
	 * @pre p es un Pais inicializado correctamente
	 * @post El Pais no se modifica. El conjunto es modificado añadiendo
	 * el nuevo pais
	 */
    void Insertar(const Pais &P);


	/**
	 * @brief Borrado de un pais en el conjunto
	 * @param P Pais que se va a borrar del conjunto de paises
	 * @pre p es un Pais inicializado correctamente
	 * @post EL pais no se modifica. Se elimina el Pais del conjunto, modificandolo
	 */
    void Borrar(const Pais &P);
      
	class iterator{
	private:
	    unordered_map<pair<double,double>,Pais>::iterator p;

	public:
	    iterator(){}
		bool operator == (const iterator &i){return p == i.p;}  
		bool operator != (const iterator &i){return p != i.p;}
		iterator & operator++(){
			++p;
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
	    unordered_map<pair<double,double>,Pais>::const_iterator p;
	public:
		const_iterator(){}
		bool operator == (const const_iterator &i){return p == i.p;}
		bool operator != (const const_iterator &i){return p != i.p;}
		const_iterator & operator++(){
			++p;
			return *this;		
		}

		const Pais & operator*()const{
			return p->second;
		}

	    friend class Paises;
	   
	};
	/**
	 * @brief Función begin
	 * @return iterador de Paises apuntando 
	 * 
	 * 
	 * 
	 * 
	 */


#endif
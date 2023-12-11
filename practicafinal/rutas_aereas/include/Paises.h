
#include "Pais.h"
#include <set>
using namespace std;


class Paises{
  private:
    set<Pais> datos;
  public:
    Paises(){}
    void Insertar(const Pais &P);
    void Borrar(const Pais &P);
      
	class iterator{
	private:
	    set<Pais>::iterator p;
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
			return *p;
		}
		
	    friend class Paises;
	    friend class const_iterator;
	};    

	class const_iterator{
	private:
	    set<Pais>::const_iterator p;
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
			return *p;
		}

	    friend class Paises;
	   
	};

	iterator begin();
	const_iterator begin()const;
	iterator end();
	const_iterator end()const;

	iterator find(const Pais &p);
	iterator find(const Punto &p);

	friend istream & operator>>(istream & is, Paises & R);
	friend ostream & operator<<(ostream & os, const Paises &R);
};

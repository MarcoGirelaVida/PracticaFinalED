#include <iostream>
using namespace std;

#ifndef _IMAGEN_H_
#define _IMAGEN_H_


enum Tipo_Pegado {OPACO, BLENDING};
using namespace std;
struct Pixel{
  unsigned char r,g,b;
  unsigned char transp; //0 no 255 si
};  

class Imagen{
  private:
    Pixel ** data;
    int nf,nc;
    void Borrar();
    void Copiar(const Imagen & I);

  public:
   Imagen();
   
   Imagen(int f,int c);
   
   Imagen(const Imagen & I);
   
   Imagen & operator=(const Imagen & I);
   
   ~Imagen();
   
   //set y get
   Pixel & operator ()(int i,int j);
   
   const Pixel & operator ()(int i,int j)const;
   
   void EscribirImagen(const char * nombre, bool getMascara);
   
   void LeerImagen (const char *nombre,const string &nombremascara="");
   void LimpiarTransp();
   int num_filas()const{return nf;}
   int num_cols()const{return nc;}
   void PutImagen(int posi,int posj, const Imagen &I,Tipo_Pegado tippegado=OPACO);
   Imagen ExtraeImagen(int posi,int posj,int dimi,int dimj);
   void Rota(const Imagen & Io,double angulo);
};   


#endif
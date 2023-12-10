#include "imagenES.h"
#include "imagen.h"
#include <iostream>
#include <cassert>
using namespace std;


  void Imagen::Borrar(){

    nf = 0;
    nc = 0;
    delete[] data;
    data = nullptr;
  }


  void Imagen::Copiar(const Imagen & I){

    nf = I.nf;
    nc = I.nc;

    data = new Pixel*[nf];
    for (int i=0;i<nf;i++){
      data[i]=new Pixel[nc];
      for (int j=0;j<nc;j++){
        data[i][j].r=I.data[i][j].r;
        data[i][j].g=I.data[i][j].g;
        data[i][j].b=I.data[i][j].b;
        data[i][j].transp=I.data[i][j].transp;
      }
    }
  }

  Imagen::Imagen(){

    nf = 0;
    nc = 0;
    data = nullptr;

  }





  Imagen::Imagen(int f,int c){
    nf = f;
    nc = c;
    data = new Pixel*[nf];
    for (int i=0;i<nf;i++){
      data[i]=new Pixel[nc];
      for (int j=0;j<nc;j++){
        data[i][j].r=255;
        data[i][j].g=255;
        data[i][j].b=255;
        data[i][j].transp=255;
      }
    }  
  }


  Imagen::Imagen(const Imagen & I){

    // Constructor de copia

    //Copio filas y columnas
    nf = I.num_filas();
    nc = I.num_cols();


    // Reservo memoria y copio los datos
    data = new Pixel*[nf];
      for (int i=0;i<nf;i++){
        data[i]=new Pixel[nc];
    }

    Copiar(I);

  }



 Imagen & Imagen::operator=(const Imagen & I){

      if (this != &I) { // Evita la autoasignación
          // Libero la memoria actual
          Borrar();
          Copiar(I);
      }
      return *this; // Permite encadenar asignaciones (a = b = c)
  }

  Imagen::~Imagen(){

    for (size_t i = 0; i < nf; i++)
      delete[] data[i];

    delete[] data;

  }
  /**********************************************/
  Pixel & Imagen::operator()(int i,int j){
    assert(i>=0 && i<nf && j>=0 && j<nc);
    return data[i][j];
  }

  /**********************************************/
  const Pixel & Imagen::operator()(int i,int j)const{
    assert(i>=0 && i<nf && j>=0 && j<nc);
    return data[i][j];
  }

  /***********************************************/

  void Imagen::EscribirImagen(const char * nombre){
        unsigned char * aux = new unsigned char [nf*nc*3];
        unsigned char * m = new unsigned char [nf*nc];
        
        int total = nf*nc*3;
        for (int i=0;i<total;i+=3){
          int posi = i /(nc*3);
          int posj = (i%(nc*3))/3;
          
          aux[i]=data[posi][posj].r;
          aux[i+1]=data[posi][posj].g;
          aux[i+2]=data[posi][posj].b;
          m[i/3]=data[posi][posj].transp;
        
        }    
    
        if (!EscribirImagenPPM (nombre, aux,nf,nc)){
          cerr<<"Ha habido un problema en la escritura de "<<nombre<<endl;
        }	  
        delete[]aux;
        string n_aux = "mascara_";
        n_aux =n_aux+nombre;
        std::size_t found =n_aux.find(".ppm");
        if (found!=std::string::npos){
          n_aux =n_aux.substr(0,found);
        }
        n_aux =n_aux+".pgm";

        
        if (!EscribirImagenPGM (n_aux.c_str(), m,nf,nc)){
          cerr<<"Ha habido un problema en la escritura de "<<n_aux<<endl;
        }	    
        delete []m;
    
  }  
  /*********************************/
void Imagen::LeerImagen(const char * nombre,const string &nombremascara){
      int f,c;
      unsigned char * aux,*aux_mask ;
      
      LeerTipoImagen(nombre, f, c);
      aux = new unsigned char [f*c*3];
      LeerImagenPPM (nombre, f,c,aux);
      if (nombremascara!=""){
        int fm,cm;
        LeerTipoImagen(nombremascara.c_str(), fm, cm);
        aux_mask = new unsigned char [fm*cm];
        LeerImagenPGM(nombremascara.c_str(), fm,cm,aux_mask);
      }
      else{
	      aux_mask=0;
      }	
      
      
      Imagen I(f,c);
      int total = f*c*3;
      for (int i=0;i<total;i+=3){
        int posi = i /(c*3);
        int posj = (i%(c*3))/3;
      //   cout<<posi<<" " <<posj<<endl;
          I.data[posi][posj].r=aux[i];
          I.data[posi][posj].g=aux[i+1];
          I.data[posi][posj].b=aux[i+2];
          if (aux_mask!=0)
            I.data[posi][posj].transp=aux_mask[i/3];
          else  
            I.data[posi][posj].transp=255;
	    }
 
      *this = I;

      if (aux_mask!=0) delete[]aux_mask;
      delete []aux;

      
}	


  /*********************************/
  void Imagen::LimpiarTransp(){


  
  
  
  // No se usa, no es necesario implementarlo
  
  
  
  
  }
 /*********************************/

  void Imagen::PutImagen(int posi,int posj, const Imagen &I,Tipo_Pegado tippegado){
      assert(nf>=posi+I.nf && nc>=posj+I.nc);
      
      for (int i=0;i<I.nf;i++)
        for (int j=0;j<I.nc;j++)
          if (i+posi>=0 && i+posi<nf && j+posj>=0 && j+posj<nc){
            if (I.data[i][j].transp!=0){
              if (tippegado==OPACO)
                data[i+posi][j+posj]=I.data[i][j];
              else{
                data[i+posi][j+posj].r=(data[i+posi][j+posj].r+I.data[i][j].r)/2;
                data[i+posi][j+posj].g=(data[i+posi][j+posj].r+I.data[i][j].g)/2;
                data[i+posi][j+posj].b=(data[i+posi][j+posj].r+I.data[i][j].b)/2;
              }  
            }  
          }	
        
  }

 /*********************************/
 Imagen Imagen::ExtraeImagen(int posi, int posj, int dimi,int dimj){

  
  Imagen aux = Imagen(dimi, dimj);

  for (int i=posi; i<dimi; i++){
    for (int j=posj; j<dimj; j++){
      aux.data[i-posi][j-posj].r = data[i][j].r;
      aux.data[i-posi][j-posj].g = data[i][j].g;
      aux.data[i-posi][j-posj].b = data[i][j].b;
      aux.data[i-posi][j-posj].transp = data[i][j].transp;
    }
  }

  return aux;
 }
  /*********************************/

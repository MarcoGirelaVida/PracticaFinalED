 /**
  * @file imageIO.cpp
  * @brief Fichero con definiciones para la E/S de imágenes
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */
#include <string>
#include <iostream>
#include <fstream>
#include "imageIO.h"
using namespace std;

ImageKind ReadKind(ifstream& f){
  char c1,c2;
  ImageKind res= IMG_UNKNOWN;

  if (f){
    c1=f.get();
    c2=f.get();
    if (f && c1=='P')
      switch (c2) {
        case '5': res= IMG_PGM; break;
        case '6': res= IMG_PPM; break;
        default: res= IMG_UNKNOWN;
      }
  }
  return res;
}

// _____________________________________________________________________________

ImageKind ReadImageKind(const char *pathname){
  ifstream f(pathname);
  return ReadKind(f);
}


// _____________________________________________________________________________

char SkipWhitespaces (ifstream& f){
  char c;
  do{
    c= f.get();
  } while (isspace(c));
  f.putback(c);
  return c;
}

// _____________________________________________________________________________

bool ReadHeader (ifstream& f, int& rows, int& cols){
    int maxvalue;
    string linea;

    // Salta los comentarios
    while (SkipWhitespaces(f) == '#')
      getline(f,linea);

    //Lee las dimensiones y el maxvalor
    f >> cols >> rows >> maxvalue;
    
    // No sé qué hace
    if (/*str &&*/ f && rows>0 && rows<5000 && cols>0 && cols<5000){
        f.get(); // Saltamos separador
        return true;
    }
    else 
      return false;
}


// _____________________________________________________________________________

unsigned char *ReadPPMImage (const char pathname[], int& rows, int& cols)
{
  bool success = false;
  rows=0;
  cols=0;
  ifstream f(pathname);
  
  if (ReadKind(f)==IMG_PPM)
    if (ReadHeader (f, rows, cols))
	if (f.read(reinterpret_cast<char *>(buffer),rows*cols*3))
	  success = true;
  
  return success;
}

// _____________________________________________________________________________

unsigned char *ReadPGMImage (const char *path, int& rows, int& cols){
  unsigned char *res=0;
  rows=0;
  cols=0;
  ifstream f(path);
  
  if (ReadKind(f) == IMG_PGM){
    if (ReadHeader(f, rows, cols)){
      res= new unsigned char[rows*cols];
      f.read(reinterpret_cast<char *>(res),rows*cols);
      if (!f){
        delete[] res;
        res= 0;
      }
    }
  }
  return res;
}

// _____________________________________________________________________________

bool WritePGMImage (const char * pathname, const unsigned char * img, const int rows, const int cols){
  ofstream f(pathname);
  bool res= true;
  
  if (f){
    f << "P5" << endl;
    f << cols << ' ' << rows << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(img),rows*cols);
    if (!f)
      res=false;
  }
  return res;
}

// _____________________________________________________________________________

bool WritePPMImage (const char pathname[], const unsigned char img[], int rows, int cols)
{
  ofstream f(pathname);
  bool res= true;
  
  if (f) {
    f << "P6" << endl;
    f << cols << ' ' << rows << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(img),rows*cols*3);
    if (!f) res=false;
  }
  return res;
}
/* Fin Fichero: imagenES.cpp */


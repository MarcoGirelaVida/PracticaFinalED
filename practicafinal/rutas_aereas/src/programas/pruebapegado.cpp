#include "image.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 8)
  {
    cout << "Los parametros son :" << endl;
    cout << "\t1.-La Image de fondo" << endl;
    cout << "\t2.-La Image a pegar" << endl;
    cout << "\t3.-La máscara de la Image a pegar" << endl;
    cout << "\t4.-El nombre de la Image de salida" << endl;
    cout << "\t5.-La fila donde pegar" << endl;
    cout << "\t6.-La columna donde pegar" << endl;
    cout << "\t7.- 0: Pegado Opaco 1: Pegado Blending" << endl;
    return 0;
  }
  Image base_image, image_to_paste;
  if (!base_image.Load(argv[1]))
  {
    cerr << "ERROR AL CARGAR IMAGEN" << endl;
    exit(EXIT_FAILURE);
  }
  
  image_to_paste.Load(argv[2], argv[3]);

  int paste_row, paste_col;
  paste_row = atoi(argv[5]);
  paste_col = atoi(argv[6]);

  PasttingType pastting_type = OPAQUE; // variable de tipo Tipo_Pegado que es un enumerado con los valores OPACO y 	BLENDING
  //int au = atoi(argv[7]);
  if (atoi(argv[7]))
    pastting_type = BLENDING;

  base_image.Paste(paste_row, paste_col, image_to_paste, pastting_type);
  base_image.Save(argv[4]);
}
#include "image.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

Image Rotate(const Image & Io,double angulo){
  double rads=angulo;
  double coseno = cos(angulo);
  double seno = sin(angulo);
  //Para obtener las dimensiones de la Image
  int rcorners[4],ccorners[4];
  int newimgrows,newimgcols;
  double new_row_min,new_col_min,new_row_max,new_col_max;
  double inter,inter1;
  rcorners[0]=0;
  rcorners[1]=0;
  ccorners[0]=0;
  ccorners[2]=0;
  rcorners[2]=Io.get_rows()-1;
  rcorners[3]=Io.get_rows()-1;
  ccorners[1]=Io.get_cols()-1;
  ccorners[3]=Io.get_cols()-1;
  new_row_min=0;
  new_col_min=0;
  new_row_max=0;
  new_col_max=0;
  newimgrows=0;
  newimgcols=0;
  for(int count=0;count<4;count++)
  {
    inter=rcorners[count]*coseno+ccorners[count]*seno;
    
    if(inter<new_row_min)
      new_row_min=inter;
    if(inter>new_row_max)
      new_row_max=inter;
    inter1=-rcorners[count]*seno+ccorners[count]*coseno;
    
    if(inter1<new_col_min)
      new_col_min=inter1;	
    if(inter1>new_col_max)
      new_col_max=inter1;
  }

  newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
  newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);

  Image Iout(newimgrows, newimgcols);
  for(int rows=0; rows<newimgrows; rows++)
  {
    for(int cols=0; cols < newimgcols; cols++)
    {
      float oldrowcos=((float)rows+new_row_min)*cos(-rads);
      float oldrowsin=((float)rows+new_row_min)*sin(-rads);
      float oldcolcos=((float)cols+new_col_min)*cos(-rads);
      float oldcolsin=((float)cols+new_col_min)*sin(-rads);
      float old_row=oldrowcos+oldcolsin;
      float old_col=-oldrowsin+oldcolcos;
      old_row=ceil((double)old_row);
      old_col=ceil((double)old_col);

      if((old_row >= 0) && (old_row < Io.get_rows()) && (old_col >= 0) && (old_col < Io.get_cols()))
      {
          Iout(rows,cols) = Io(old_row,old_col);
      }
      else
        Iout(rows,cols).red = Iout(rows,cols).green = Iout(rows,cols).blue = 255;
    }
  }
  return Iout;
	  
}



int main(int argc, char * argv[]){
  if (argc!=4){
    cout<<"Los parametros son :"<<endl;
    cout<<"1.-La Image de entrada"<<endl;
    cout<<"2.-El angulo de rotación"<<endl;
    cout<<"3.-El nombre de la Image de salida"<<endl;
    return 0;
  }

  Image I;
  I.Load(argv[1]);
  double angulo=atof(argv[2]);
  angulo = angulo*(M_PI)/180;
  Image Iout = Rotate(I,angulo);
  Iout.Save(argv[3]);
  
}  
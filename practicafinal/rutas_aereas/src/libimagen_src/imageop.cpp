/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>
#include <cassert>
using namespace std;

bool Image::ValidSection(const int nrow, const int ncol, const int height, const int width) const
{
    return ValidRow(nrow) && ValidCol(ncol) && ValidRow(nrow+height-1) && ValidRow(ncol+width-1);
}

// IMPORTANTE: No funciona si se pone un nrow/ncol negativo y un height/width > max_row/col_valid
// Lo arreglaría pero es un coñazo y no me parece tan importante :(
bool Image::ValidSectionSmart(int &nrow, int &ncol, int &height, int &width) const
{
    bool isValid = ValidSection(nrow, ncol, height, width);
    const int max_col_valid = get_cols() - 1;
    const int max_row_valid = get_rows() - 1;
    const int min_valid = 0;

    //DEBUG
    /*
    cerr << "PREPROCESADO" << endl;
    cerr << "Max row: " << get_rows() - 1 << endl;
    cerr << "Max col: " << get_cols() - 1 << endl;
    cerr << "Nrow: " << nrow << endl;
    cerr << "Ncol: " << ncol << endl;
    cerr << "Height: " << height << endl;
    cerr << "Width: " << width << endl;
    */

    if (!isValid)
    {
        if (!ValidRow(nrow))
            nrow = (nrow < 0) ? min_valid : max_row_valid;
        else
            height = max_row_valid - nrow + 1;

        if (!ValidCol(ncol))
            ncol = (ncol < 0) ? min_valid : max_col_valid;
        else
            width = max_row_valid - ncol + 1; 
    }
    
    // Si la sección sigue siendo erronea avisa y proporciona los valores por los que es erronea
    if (!ValidSection(nrow, ncol, height, width))
    {
        cerr << "IRREPARABLE INVALID SECTION" << endl;
        cerr << "Max row: " << get_rows() - 1 << endl;
        cerr << "Max col: " << get_cols() - 1 << endl;
        cerr << "Nrow: " << nrow << endl;
        cerr << "Ncol: " << ncol << endl;
        cerr << "Height: " << height << endl;
        cerr << "Width: " << width << endl;
    }
    
    return ValidSection(nrow, ncol, height, width);
}

// 1. Genera una subimagen
Image Image::Crop(int nrow, int ncol, int height, int width) const
{
    //---Calculo las dimensiones que tendrá la imagen resultado---
    assert (ValidSectionSmart(nrow, ncol, height, width));

    // Creamos una imagen auxiliar donde alojaremos la imagen recortada
    Image aux = Image(height, width, 0);

    for (int i=0; i < height; i++)
        for (int j=0; j < width; j++)
            aux.set_pixel(i,j,get_pixel(nrow+i,ncol+j));

    return aux;

}

void Image::Paste(const int paste_row, const int paste_col, const Image image_to_paste, const PasttingType passting_type)
{
    assert(ValidSectionSmart(paste_row, paste_col, image_to_paste.get_rows, image_to_paste.get_cols));
    
    for (int i = 0; i < image_to_paste.get_rows(); i++)
        for (int j = 0; j < image_to_paste.get_cols(); j++)
                if (image_to_paste(i, j).trasnparency != BLACK)
                {
                    pixel & to_change_pixel = this->(i + paste_row, j + paste_col);

                    if (passting_type == OPAQUE)
                        to_change_pixel = image_to_paste(i, j);
                    else
                    {
                        to_change_pixel.red = (to_change_pixel.red + image_to_paste(i, j).red) / 2;
                        to_change_pixel.green = (to_change_pixel.green + image_to_paste(i, j).green) / 2;
                        to_change_pixel.blue = (to_change_pixel.blue + image_to_paste(i, j).blue) / 2;
                    }
                }  

}
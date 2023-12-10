/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>

#include "image.h"

using namespace std;

/********************************
      FUNCIONES PRIVADAS
********************************/
void Image::AllocatePGM(int nrows, int ncols, pixel * buffer){
    rows = nrows;
    cols = ncols;

// TIPO REP 2
    img = new pixel*[rows];

    for (size_t i = 0; i < rows; i++)
    {
        img[i] = new pixel[cols];
    }

    if (buffer != 0)
    {
        for (size_t i = 0; i < rows*cols; i++)
            img[i/cols][i%cols] = buffer[i];
    }
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image::InitializePGM(int nrows, int ncols, pixel * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen
bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image::Destroy(){
    /* TIPO REP 1
    if (!Empty()){
        delete [] img[0];
        delete [] img;
    }
    */
    for (size_t i = 0; i < rows; i++)
        delete[] img[i];

    delete[] img;
}

LoadResult Image::LoadFromPGM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PGM)
        return LoadResult::NOT_PGM;

    pixel * buffer = ReadPGMImage(file_path, rows, cols);
    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}

LoadResult Image::LoadFromPPM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PPM)
        return LoadResult::NOT_PPM;

    pixel * buffer = ReadPPMImage(file_path, rows, cols);

    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}
/********************************
       FUNCIONES PÚBLICAS
********************************/

// Constructor por defecto

Image::Image(){
    Initialize();
}

// Constructores con parámetros
Image::Image (int nrows, int ncols, pixel value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++)
        set_pixel(k,value);
}

bool Image::Load (const char * file_path) {
    Destroy();
    return LoadFromPPM(file_path) == LoadResult::SUCCESS;
}

bool Image::Load (const char * image_file_path, const char * mask_file_path)
{   
    bool result;
    if (mask_file_path = "")
    {
        result = LoadFromPPM(image_file_path);
        Image mask(get_rows(), get_cols(), 255);
    }
    else
    {
        result = LoadFromPPM(mask_file_path);
        Image mask(*this);
        result = result && Load(image_file_path);
    }
    

    if (result && (mask.get_rows() == get_rows()) && (mask.get_cols() == get_cols()))
        for (size_t k = 0; k < size(); k++)
            if (mask(k).trasnparency == BLACK)
                set_pixel(k, '255');
    else
        result = false;
        //cerr << "ERROR, MASCARA CON TAMAÑO INCORRECTO" << endl;
        //exit(EXIT_FAILURE);

    return result;
}

// Constructor de copias

Image::Image (const Image & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image::~Image(){
    Destroy();
}

// Operador de Asignación

Image & Image::operator= (const Image & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image::get_rows() const {
    return rows;
}

int Image::get_cols() const {
    return cols;
}

int Image::size() const{
    return get_rows()*get_cols();
}

// Métodos básicos de edición de imágenes
void Image::set_pixel (int i, int j, pixel value) {
    img[i][j] = value;
}

pixel Image::get_pixel (int i, int j) const
{
    return this->(i, j);
}

pixel & Image::operator()(int i, int j)
{
    return img[i][j];
}

const pixel & Image::operator()(int i, int j) const
{
    return img[i][j];
}

pixel & Image::operator()(int k)
{
    int i = k / get_cols();
    int j = k % get_cols();
    return this->(i, j);
}

const pixel & Image::operator()(int k) const
{
    int i = k / get_cols();
    int j = k % get_cols();
    return this->(i, j);
}

void Image::set_pixel (int k, pixel value) {
    int i = k / get_cols();
    int j = k % get_cols();
    return set_pixel(i, j, value);
}

pixel Image::get_pixel (int k) const
{
    return this->(k);
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    pixel * p = new pixel[size()];

    cerr << "For_Save" << endl;
    for (size_t i = 0; i < size(); i++)
        p[i] = get_pixel(i);
    cerr << "/For_Save" << endl << endl;
    cerr << "WritePGMImage" << endl;
    bool success = WritePGMImage(file_path, p, rows, cols);
    cerr << "/WritePGMImage" << endl << endl;

    delete[] p;

    return success;
}


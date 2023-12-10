/**
 * @file image.h
 * @brief Cabecera para la clase Image  
 */

#ifndef _IMAGEN_H_
#define _IMAGEN_H_


#include <cstdlib>
#include "imageIO.h"


/**
 * @brief Tipo de dato "byte" compuesto por un tipo de dato 'char'
*/
typedef unsigned char pixel;

/**
 * @brief Struct que determina el resultado de una lectura de una imagen PGM
*/
enum LoadResult: unsigned char {
    SUCCESS,
    NOT_PGM,
    NOT_PPM,
    READING_ERROR
};

/**
 * @brief Struct que determina el tipo de pegado deseado
 * @param OPAQUE Opaco
 * @param BLENDING Se hace promedio entre la imagen fondo y la imagen a pegar
*/
enum PasttingType : bool
{
  OPAQUE = false,
  BLENDING = true
};

/**
 * @brief Byte a color
 * @param red Intensidad del color rojo
 * @param green Intensidad del color verde
 * @param blue Intensidad del color azul
 * @pre 0 <= @p red , @p green , @p blue <= 255
*/
struct RgbPixel
{
  pixel red;
  pixel green;
  pixel blue;
  WhiteBlackPixel trasnparency;
};

/**
 * @brief Pixel blaco o negro
 * @param black El pixel es negro
 * @param white El pixel es blaco
*/
enum WhiteBlackPixel : pixel
{
  WHITE = 255,
  BLACK = 0
};

/**
  @brief T.D.A. Imagen

  Una instancia del tipo de dato abstracto Imagen nos permite almacenar imágenes de intensidades.

  El TDA Imagen proporciona además distintas herramientas para la manipulación de dichas imágenes.

  Para poder usar el TDA Imagen se debe incluir el fichero

  \#include <Imagen.h>

  @author Javier Abad
  @author Guillermo Gómez
  @date Septiembre 2021

**/

class Image{

    /**
         @page page_repImagen Representación del TDA Imagen

         @section sec_Image_A Representación Tipo 1 (Actual)
          Dada una imagen de f filas y c columnas, está representada por:
         - _byte ** img_: Un puntero a un vector de punteros (Representa a la imagen completa)
         - _byte * filas[f]_ : Un vector con f punteros a bytes
         - _byte * m[f*c]_ : Un macro vector que almacena todos los bytes de la imagen secuencialmente

         Esta representación es preferible en aquellos casos en los que necesitamos operaciones que se apliquen secuencialmente sobre todos los píxeles de una imagen.
         @image html rep1.png "Rep 1"

         @section sec_Image_B Representación Tipo 2 (ej Barajar)
          Dada una imagen de f filas y c columnas, está representada por:
         - _byte ** img_ : Un puntero a un vector de punteros (La imagen completa)
         - _byte * filas[f]_ : Un vector con f punteros a vectores de píxeles (bytes)
         - _f byte * col[c]_ : f vectores de píxeles (bytes) con tamaño c (esto será cada columna)

         Esta representación es preferible en aquellos casos en los que hagamos operaciones directas sobre el orden de las filas de la imagen.
         @image html rep2.png "Rep 2"

       **/

private :

    /**
      @brief Puntero a la imagen almacenada

      img apunta a un array-2D dinámico de bytes que contiene la imagen en sí. Almacena tantos bytes como pixeles tenga la imagen.

    **/
    pixel **img;

    /**
      @brief Número de filas de la imagen.
    **/
    int rows;


    /**
      @brief Número de columnas de la imagen.
    **/
    int cols;


    /**
      @brief Initialize una imagen.
      @param nrows Número de filas que tendrá la imagen. Por defecto, 0
      @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre filas >= O y columnas >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
    void Initialize (int nrows= 0, int ncols= 0, pixel *buffer= 0);

    /**
      @brief Lee una imagen PGM desde un archivo.
      @param file_path Ruta del archivo a leer
      @return LoadResult
    **/
    LoadResult LoadFromPGM(const char * file_path);

    /**
      @brief Lee una imagen PPM desde un archivo.
      @param file_path Ruta del archivo a leer
      @return LoadResult
    **/
    LoadResult LoadFromPPM(const char * file_path);

    /**
      @brief Copy una imagen .
      @param orig Referencia a la imagen original que vamos a copiar
      @pre Asume que no hay memoria reservada o se ha llamado antes a Destroy()
      @pre Asume this != &orig
    **/
    void Copy(const Image &orig);

    /**
      @brief Reserva o copia en memoria una imagen.
      @param nrows Número de filas que tendrá la imagen.
      @param ncols Número de colwnnas que tendrá la imagen.
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre nrows >= O y ncols >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
    void Allocate(int nrows, int ncols, pixel * buffer = 0);

    /**
      * @brief Destroy una imagen
      *
      * Libera la memoria reservada en la que se almacenaba la imagen que llama a la función.
      * Si la imagen estaba vacía no hace nada .
      */
    void Destroy();

public :

    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase Imagen con O filas y O colunmas.
      * @return Imagen, el objeto imagen creado.
      */
    Image();

    /**
      * @brief Constructor con parámetros.
      * @param nrows Número de filas de la imagen.
      * @param ncols Número de columnas de la imagen.
      * @param value defecto Valor con el que inicializar los píxeles de la imagen . Por defecto O.
      * @pre n fils > O Y n_cols > O
      * @post La imagen creada es de n_fils y n_cols columnas. Estará inicializada al valor por defecto.
      * @return Imagen, el objeto imagen creado.
      */
    Image(int nrows, int ncols, pixel value=0);

    /**
      * @brief Constructor de copias.
      * @param orig Referencia a la imagen original que se quiere copiar.
      * @return Imagen, el objeto imagen creado.
      */
    Image (const Image & orig);

    /**
      * @brief Oper ador de tipo destructor.
      * @return void
      * @post El objeto Imagen destruido no puede usarse salvo que se haga sobre él una operacion Imagen().
      */
    ~Image() ;

    /**
      * @brief Carga en memoria una imagen de disco .
      * @param file_path Ruta donde se encuentra el archivo desde el que cargar la imagen.
      * @pre @p file_path debe ser una ruta válida que contenga un fichero . pgm
      * @return Devuelve @b true si la imagen se carga con éxito y @b false en caso contrario.
      * @post La imagen previamente almacenada en el objeto que llama a la función se destruye.
      */
    bool Load (const char * file_path);

    /**
      * @brief Carga en memoria una imagen de disco con la máscara especificada
      * @param file_path Ruta donde se encuentra el archivo desde el que cargar la imagen.
      * @param mask Es una imagen unicamente en blaco y negro donde los pixeles negros indican que se procesar procesar dicho pixel de la imagen original y el blanco que no.
      * @pre @p file_path debe ser una ruta válida que contenga un fichero . pgm
      * @pre @p mask debe tener las mismas dimesiones que la imagen base
      * @return Devuelve @b true si la imagen se carga con éxito y @b false en caso contrario.
      * @post La imagen previamente almacenada en el objeto que llama a la función se destruye.
      */
    bool Load (const char * iamge_file_path, const char * mask_file_path = "");

    /**
      * @brief Operador de asignación .
      * @param orig Referencia a la imagen original que desea copiarse.
      * @return Una referencia al objeto imagen modificado.
      * @post Destroy cualquier información que contuviera previamente la imagen que llama al operador de asignación.
      */
    Image & operator= (const Image & orig);

    /**
      * @brief Funcion para conocer si una imagen está vacía.
      * @return Si la imagene está vacía
      * @post la imagen no se modifica.
      */
    bool Empty() const;

    /**
      * @brief Filas de la imagen .
      * @return El número de filas de la i magen.
      * @post la imagen no se modifica.
      */
    int get_rows() const;

    /**
      * @brief Columnas de la imagen.
      * @return El número de columnas de la imagen.
      * @post la imagen no se modifica.
      */
    int get_cols() const;

    /**
      * @brief Devuelve el número de píxeles de la imagen.
      * @return número de píxeles de la imagen.
      * @post la imagen no se modifica.
      */
    int size() const;

    /**
    * @brief Asigna el valor valor al píxel ( @p i, @p j) de la imagen.
    * @param i Fila de la imagen en la que se encuentra el píxel a escribir .
    * @param j Columna de la imagen en la que se encuentra el píxel a escribir.
    * @param value Valor que se escribirá en el píxel ( @p i, @p j) .
    * @pre O <= @p i < get_rows()
    * @pre O <= @p j < get_cols()
    * @pre O <= @p value <= 255
    * @post El píxel ( @p i, @p j) de la imagen se modificará y contendrá valor @p value.
    * Los demás píxeles permanecerán iguales.
    */
    void set_pixel (int i, int j, pixel value);

    /**
      * @brief Consulta el valor del píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a consultar.
      * @param j Columna de la imagen en la que se encuentra el píxel a consultar.
      * @pre O <= fil < I.Num_ Filas() II O <= col < I.Num Columnas()
      * @return el valor del píxel contenido en (fil,col)
      * @post La imagen no se modifica.
      * @post Si el pixel solicitado está fuera de rango se proporciona el pixel de la imagen más cercano disponible
      */
    pixel get_pixel (int i, int j) const;

    /**
      * @brief Consulta el valor del píxel k de la imagen desenrrollada.
      * @param k Índice del píxel
      * @pre 0 <= k < filas*columnas
      * @return el valor del píxel contenido en (k/filas,k%filas)
      * @post La imagen no se modifica.
      */
    pixel get_pixel (int k) const;

    /**
      * @brief Consulta el valor del píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a consultar.
      * @param j Columna de la imagen en la que se encuentra el píxel a consultar.
      * @pre O <= fil < I.Num_ Filas() II O <= col < I.Num Columnas()
      * @return referencia al píxel contenido en (fil,col)
      * @post La imagen no se modifica pero se puede modificar a través de la referencia
      * @post Si el pixel solicitado está fuera de rango se proporciona el pixel de la imagen más cercano disponible
    */
    pixel & operator()(int i,int j);

    /**
      * @brief Consulta el valor del píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a consultar.
      * @param j Columna de la imagen en la que se encuentra el píxel a consultar.
      * @pre O <= fil < I.Num_ Filas() II O <= col < I.Num Columnas()
      * @return referencia al píxel contenido en (fil,col)
      * @post La imagen no se modifica y no se puede modificar a través de la referencia
      * @post Si el pixel solicitado está fuera de rango se proporciona el pixel de la imagen más cercano disponible
    */
    const pixel & operator()(int i, int j) const;
    
    /**
      * @brief Consulta el valor del píxel k de la imagen desenrrollada.
      * @param k Índice del píxel
      * @pre 0 <= k < filas*columnas
      * @return referencia al píxel contenido en (k/filas,k%filas)
      * @post La imagen no se modifica pero se puede modificar a través de la referencia
      */
    pixel & Image::operator()(int k);

    /**
      * @brief Consulta el valor del píxel k de la imagen desenrrollada.
      * @param k Índice del píxel
      * @pre 0 <= k < filas*columnas
      * @return referencia al píxel contenido en (k/filas,k%filas)
      * @post La imagen no se modifica y no se puede modificar a través de la referencia
      */
    const pixel & Image::operator()(int k) const;

    /**
      * @brief Asigna el valor valor al píxel k de la imagen desenrollada.
      * @param k Índice del píxel a escribir .
      * @param value Valor que se escribirá en el píxel k.
      * @pre 0 <= k < filas*columnas && O <= valor <= 255
      * @post El píxel k se modificará con el valor de value.
      */
    void set_pixel (int k, pixel value);

    /**
      * @brief Almacena imágenes en disco.
      * @param file_path Ruta donde se almacenará la imagen.
      * @pre file path debe ser una ruta válida donde almacenar el fichero de salida.
      * @return Devuelve true si la imagen se almacenó con éxito y false en caso contrario.
      * @post La imagen no se modifica.
      */
    bool Save (const char * file_path) const;


    // Recorre una imagen y aplica una operación sobre la misma
    //void GoAcrossAndOperate(void (*func)(int ));

    /**
     * @brief Comprueba la validez de una fila dada
     * @param nrow Fila de la que se quiere comprobar la validez
     * @return @p true si la fila dada está dentro de la imagen, @p false en caso contrario
    */
    bool ValidRow(const int nrow) const{ return (0 <= nrow && nrow < get_rows()); }

    /**
     * @brief Comprueba la validez de una columna dada
     * @param ncol Columna de la que se quiere comprobar la validez
     * @return @p true si la columna dada está dentro de la imagen, @p false en caso contrario
    */
    bool ValidCol(const int ncol) const{ return (0 <= ncol && ncol < get_cols()); }

    /**
     * @brief Comprueba que la sección proporcionada se encuentra dentro de la imagen
     * @param nrow Fila inicial para recortar
     * @param ncol Columna inicial para recortar
     * @param height Número de filas
     * @param width Número de columnas
     * @return True si la sección entra dentro de la imagen
    */
    bool ValidSection(const int nrow, const int ncol, const int height, const int width) const;

    /**
     * @brief Comprueba que la sección proporcionada se encuentra dentro de la imagen y si no lo está, a ser posible, los modificará para que lo estén
     * @param nrow Referencia a la variable que almacena la fila inicial para recortar
     * @param ncol Referencia a la variable que almacena la columna inicial para recortar
     * @param height Referencia a la variable que almacena el número de filas
     * @param width Referencia a la variable que almacena el número de columnas
     * @retval True si la sección era válida o si ha sido posible modificar los valores para que lo sea.
     * @retval False si la sección es inválida y no ha sido posible modificarla para deje de serlo.
     * @post Si @p nrow > filas --> @p nrow = filas
     * @post Si @p height + @p nrow > filas -> @p height = filas-nrow
     * @post Si @p ncol > columnas --> @p ncol = columnas
     * @post Si @p width + @p ncol > columnas -->  @p width = columnas-ncol
     * @note No será capaz de arreglar la sección si @p nrow && @p height son valores inválidos ( @ref ValidRow "ValidRow") o @p ncol && @p width son valores inválidos ( @ref ValidCol "ValidCol")
    */
    bool ValidSectionSmart(int &nrow, int &ncol, int &height, int &width) const;

    /**
     * @brief Genera una subimagen
     * @param nrow Fila inicial para recortar
     * @param ncol Columna inicial para recortar
     * @param height Número de filas
     * @param width Número de columnas
     * @pre 0 <= @p nrow < filas
     * @pre 0 <= @p ncol < columnas
     * @pre 0 <= @p height and @p height + @p nrow <= filas
     * @pre 0 <= @p width and @p width + @p ncol <= columnas
     * @note Si uno o varios parámetros no cumplen los requisitos se modificarán conforme la función @ref ValidSectionSmart "ValidSectionSmart"
     * @return Imagen con el recorte
     * @post El objeto que llama a la función no se modifica
    */
    Image Crop(int nrow, int ncol, int height, int width) const;

    /**
     * @brief Pega la imagen proporcionada en la fila y columa especificada de la imagen donde se aplica el método
     * @param paste_row Fila donde se desea que se pegue la imagen
     * @param paste_col Columna donde se desea que se pegue la imagen
     * @param image_to_paste Imagen que se desea pegar
     * @param passting_type Tipo de pegado que se desea (0: OPACO, 1: BLENDING)
     * @pre 0 <= @p nrow < filas
     * @pre 0 <= @p ncol < columnas
     * @post La imagen donde se aplica la función queda modificada.
     * @note Si el tamaño de la función a pegar supera las dimensiones de la imagen base solo se pegará lo que quepa en la sección solicitada
    */
    void Paste(const int paste_row, const int paste_col, const Image image_to_paste, const PasttingType passting_type);
};


#endif // _IMAGEN_H_


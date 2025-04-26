/*
 * Programa demostrativo de manipulaciónprocesamiento de imágenes BMP en C++ usando Qt.
 *
 * Descripción:
 * Este programa realiza las siguientes tareas:
 * 1. Carga una imagen BMP desde un archivo (formato RGB sin usar estructuras ni STL).
 * 2. Modifica los valores RGB de los píxeles asignando un degradado artificial basado en su posición.
 * 3. Exporta la imagen modificada a un nuevo archivo BMP.
 * 4. Carga un archivo de texto que contiene una semilla (offset) y los resultados del enmascaramiento
 *    aplicados a una versión transformada de la imagen, en forma de tripletas RGB.
 * 5. Muestra en consola los valores cargados desde el archivo de enmascaramiento.
 * 6. Gestiona la memoria dinámicamente, liberando los recursos utilizados.
 *
 * Entradas:
 * - Archivo de imagen BMP de entrada ("I_O.bmp").
 * - Archivo de salida para guardar la imagen modificada ("I_D.bmp").
 * - Archivo de texto ("M1.txt") que contiene:
 *     • Una línea con la semilla inicial (offset).
 *     • Varias líneas con tripletas RGB resultantes del enmascaramiento.
 *
 * Salidas:
 * - Imagen BMP modificada ("I_D.bmp").
 * - Datos RGB leídos desde el archivo de enmascaramiento impresos por consola.
 *
 * Requiere:
 * - Librerías Qt para manejo de imágenes (QImage, QString).
 * - No utiliza estructuras ni STL. Solo arreglos dinámicos y memoria básica de C++.
 *
 * Autores: Augusto Salazar Y Aníbal Guerra
 * Fecha: 06/04/2025
 * Asistencia de ChatGPT para mejorar la forma y presentación del código fuente
 */

#include <fstream>
#include <iostream>
#include <QCoreApplication>
#include <QImage>

using namespace std;
unsigned char* loadPixels(QString input, int &width, int &height);
bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida);
unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);
//Firmas de funciones creadas
unsigned char* funcXor(unsigned char* img1, unsigned char* img2, int &width, int &height);
unsigned char* Desenmascar(unsigned int* datostxt, unsigned char* mascara, int &seed, int &widthM,int &heightM,int &n_pixels);
unsigned char* rotacionInversa(unsigned char* imagen, int &ancho, int &alto);

int main()
{
    // Definición de rutas de archivo de entrada (imagen original) y salida (imagen modificada)
    QString archivoEntrada = "Caso 1/P3.bmp";
    QString archivoSalida = "Caso 1/I_D.bmp";
    QString archivoEntrada1 = "Caso 1/I_M.bmp";

    // Variables para almacenar las dimensiones de la imagen
    int height = 0;
    int width = 0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto

    unsigned char *pixelData = loadPixels(archivoEntrada, width, height);
    unsigned char *dataimgIM = loadPixels(archivoEntrada1,width,height);

    //OPeracion XOR Ultima Imagen e Imagen Mascara

    cout<<width<<","<<height<<endl;
    unsigned char *resultado = funcXor(pixelData,dataimgIM,width,height);

    // Simula una modificación de la imagen asignando valores RGB incrementales
    // (Esto es solo un ejemplo de manipulación artificial)

   /* for (int i = 0; i < width * height * 3; i += 3) {
        pixelData[i] = i;     // Canal rojo
        pixelData[i + 1] = i; // Canal verde
        pixelData[i + 2] = i; // Canal azul
    }
*/
    // Exporta la imagen modificada a un nuevo archivo BMP
    bool exportI = exportImage(resultado, width, height, archivoSalida);

    // Muestra si la exportación fue exitosa (true o false)
    cout << exportI << endl;

    // Libera la memoria usada para los píxeles
    delete[] pixelData;
    pixelData = nullptr;

    delete[] dataimgIM;
    dataimgIM = nullptr;

    delete[] resultado;
    resultado = nullptr;

    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento

    int seed = 0;
    int n_pixels = 0;
    int widthM = 0;
    int heightM =0;

    //Archivos de entrada y salida
    QString archivoEntrada2= "Caso 1/M.bmp";
    QString archivoSalida2= "Caso 1/I_D2.bmp";

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    unsigned int *maskingData = loadSeedMasking("Caso 1/M2.txt", seed, n_pixels);

   /* // Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    for (int i = 0; i < n_pixels * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << maskingData[i] << ", "
             << maskingData[i + 1] << ", "
             << maskingData[i + 2] << ")" << endl;
    }
*/
    //Carga de la mascara.bmp
    unsigned char *mascara = loadPixels(archivoEntrada2,widthM,heightM);

    //Funcion Desenmascarar
    unsigned char *Desenmascaramiento2=Desenmascar(maskingData,mascara,seed,widthM,heightM,n_pixels);

     //Funcion Exportar Imagen

    bool ExportII = exportImage(Desenmascaramiento2,width,height,archivoSalida2);
                   cout<<ExportII<<endl;

    // Libera la memoria usada para los datos de enmascaramiento
    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }

delete[] mascara;
    mascara = nullptr;

delete[] Desenmascaramiento2;
    Desenmascaramiento2 = nullptr;

//Archivo de entrada

    QString archivoEntrada3 = "Caso 1/I_D2.bmp";
    QString archivoSalida3 ="Caso 1/I_D3.bmp";

    //Carga de Imagen D2

    unsigned char *imgI_D2 = loadPixels(archivoEntrada3,width,height);

//Operacion de 3 bits ala izquierda

    unsigned char *resultado3Bits = rotacionInversa(imgI_D2,width,height);
//Exportar Imagen rotada

    bool ExportIII = exportImage(resultado3Bits,width,height,archivoSalida3);
    cout<<ExportIII<<endl;

    //Limpiar memoria dinamica

    delete[] imgI_D2;
    imgI_D2 = nullptr;

    delete[] resultado3Bits;
    resultado3Bits = nullptr;
    //Variables semilla y numero

    int seed1 = 0;
    int n_pixels1 = 0;

    //Archivos de entrada y salida
    QString archivoEntrada4 ="Caso 1/M.bmp";
    QString archivoSalida4 = "Caso 1/I_D4.bmp";

    //Carga de la mascara.bmp
    unsigned char *mascara1 = loadPixels(archivoEntrada4,widthM,heightM);


    //Carga de archivo enmascaramiento1

        unsigned int *m1Txt = loadSeedMasking("Caso 1/M1.txt",seed1,n_pixels1);

    //Operacion desenmascarar

    unsigned char *Desenmascaramiento1 = Desenmascar(m1Txt,mascara1,seed1,widthM,heightM,n_pixels1);

    //Exportar archivo D4

    bool ExportIIII = exportImage(Desenmascaramiento1,width,height,archivoSalida4);
    cout<<ExportIIII<<endl;

    delete[] mascara1;
    mascara1 = nullptr;

    delete[] m1Txt;
    m1Txt = nullptr;

    delete[]Desenmascaramiento1;
    Desenmascaramiento1 = nullptr;

   // Rutas de archivo de entrada  y salida
    QString archivoEntrada5 = "Caso 1/I_D4.bmp";
    QString archivoSalida5 = "Caso 1/I_D5.bmp";
    QString archivoEntrada6 = "Caso 1/I_M.bmp";


    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto

    unsigned char *imgI_M = loadPixels(archivoEntrada6,width,height);
    unsigned char *imgD4 =loadPixels(archivoEntrada5,width,height);

    //Operacion XOR primer Imagen e Imagen Mascara

    unsigned char *resultadoFinal = funcXor(imgD4,imgI_M,width,height);


    // Exporta la imagen D5
    bool exportIIIII= exportImage(resultadoFinal, width, height, archivoSalida5);

    // Muestra si la exportación fue exitosa (true o false)
    cout << exportIIIII << endl;

    delete[]imgD4;
    imgD4 = nullptr;

    delete[]imgI_M;
    imgI_M = nullptr;

    delete[] resultadoFinal;
    resultadoFinal = nullptr;


    return 0; // Fin del programa
}


unsigned char* loadPixels(QString input, int &width, int &height){
/*
 * @brief Carga una imagen BMP desde un archivo y extrae los datos de píxeles en formato RGB.
 *
 * Esta función utiliza la clase QImage de Qt para abrir una imagen en formato BMP, convertirla al
 * formato RGB888 (24 bits: 8 bits por canal), y copiar sus datos de píxeles a un arreglo dinámico
 * de tipo unsigned char. El arreglo contendrá los valores de los canales Rojo, Verde y Azul (R, G, B)
 * de cada píxel de la imagen, sin rellenos (padding).
 *
 * @param input Ruta del archivo de imagen BMP a cargar (tipo QString).
 * @param width Parámetro de salida que contendrá el ancho de la imagen cargada (en píxeles).
 * @param height Parámetro de salida que contendrá la altura de la imagen cargada (en píxeles).
 * @return Puntero a un arreglo dinámico que contiene los datos de los píxeles en formato RGB.
 *         Devuelve nullptr si la imagen no pudo cargarse.
 *
 * @note Es responsabilidad del usuario liberar la memoria asignada al arreglo devuelto usando `delete[]`.
 */

    // Cargar la imagen BMP desde el archivo especificado (usando Qt)
    QImage imagen(input);

    // Verifica si la imagen fue cargada correctamente
    if (imagen.isNull()) {
        cout << "Error: No se pudo cargar la imagen BMP." << std::endl;
        return nullptr; // Retorna un puntero nulo si la carga falló
    }

    // Convierte la imagen al formato RGB888 (3 canales de 8 bits sin transparencia)
    imagen = imagen.convertToFormat(QImage::Format_RGB888);

    // Obtiene el ancho y el alto de la imagen cargada
    width = imagen.width();
    height = imagen.height();

    // Calcula el tamaño total de datos (3 bytes por píxel: R, G, B)
    int dataSize = width * height * 3;

    // Reserva memoria dinámica para almacenar los valores RGB de cada píxel
    unsigned char* pixelData = new unsigned char[dataSize];

    // Copia cada línea de píxeles de la imagen Qt a nuestro arreglo lineal
    for (int y = 0; y < height; ++y) {
        const uchar* srcLine = imagen.scanLine(y);              // Línea original de la imagen con posible padding
        unsigned char* dstLine = pixelData + y * width * 3;     // Línea destino en el arreglo lineal sin padding
        memcpy(dstLine, srcLine, width * 3);                    // Copia los píxeles RGB de esa línea (sin padding)
    }

    // Retorna el puntero al arreglo de datos de píxeles cargado en memoria
    return pixelData;
}

bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida){
/*
 * @brief Exporta una imagen en formato BMP a partir de un arreglo de píxeles en formato RGB.
 *
 * Esta función crea una imagen de tipo QImage utilizando los datos contenidos en el arreglo dinámico
 * `pixelData`, que debe representar una imagen en formato RGB888 (3 bytes por píxel, sin padding).
 * A continuación, copia los datos línea por línea a la imagen de salida y guarda el archivo resultante
 * en formato BMP en la ruta especificada.
 *
 * @param pixelData Puntero a un arreglo de bytes que contiene los datos RGB de la imagen a exportar.
 *                  El tamaño debe ser igual a width * height * 3 bytes.
 * @param width Ancho de la imagen en píxeles.
 * @param height Alto de la imagen en píxeles.
 * @param archivoSalida Ruta y nombre del archivo de salida en el que se guardará la imagen BMP (QString).
 *
 * @return true si la imagen se guardó exitosamente; false si ocurrió un error durante el proceso.
 *
 * @note La función no libera la memoria del arreglo pixelData; esta responsabilidad recae en el usuario.
 */

    // Crear una nueva imagen de salida con el mismo tamaño que la original
    // usando el formato RGB888 (3 bytes por píxel, sin canal alfa)
    QImage outputImage(width, height, QImage::Format_RGB888);

    // Copiar los datos de píxeles desde el buffer al objeto QImage
    for (int y = 0; y < height; ++y) {
        // outputImage.scanLine(y) devuelve un puntero a la línea y-ésima de píxeles en la imagen
        // pixelData + y * width * 3 apunta al inicio de la línea y-ésima en el buffer (sin padding)
        // width * 3 son los bytes a copiar (3 por píxel)
        memcpy(outputImage.scanLine(y), pixelData + y * width * 3, width * 3);
    }

    // Guardar la imagen en disco como archivo BMP
    if (!outputImage.save(archivoSalida, "BMP")) {
        // Si hubo un error al guardar, mostrar mensaje de error
        cout << "Error: No se pudo guardar la imagen BMP modificada.";
        return false; // Indica que la operación falló
    } else {
        // Si la imagen fue guardada correctamente, mostrar mensaje de éxito
        cout << "Imagen BMP modificada guardada como " << archivoSalida.toStdString() << endl;
        return true; // Indica éxito
    }

}

unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels){
/*
 * @brief Carga la semilla y los resultados del enmascaramiento desde un archivo de texto.
 *
 * Esta función abre un archivo de texto que contiene una semilla en la primera línea y,
 * a continuación, una lista de valores RGB resultantes del proceso de enmascaramiento.
 * Primero cuenta cuántos tripletes de píxeles hay, luego reserva memoria dinámica
 * y finalmente carga los valores en un arreglo de enteros.
 *
 * @param nombreArchivo Ruta del archivo de texto que contiene la semilla y los valores RGB.
 * @param seed Variable de referencia donde se almacenará el valor entero de la semilla.
 * @param n_pixels Variable de referencia donde se almacenará la cantidad de píxeles leídos
 *                 (equivalente al número de líneas después de la semilla).
 *
 * @return Puntero a un arreglo dinámico de enteros que contiene los valores RGB
 *         en orden secuencial (R, G, B, R, G, B, ...). Devuelve nullptr si ocurre un error al abrir el archivo.
 *
 * @note Es responsabilidad del usuario liberar la memoria reservada con delete[].
 */

    // Abrir el archivo que contiene la semilla y los valores RGB
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        // Verificar si el archivo pudo abrirse correctamente
        cout << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }

    // Leer la semilla desde la primera línea del archivo
    archivo >> seed;

    int r, g, b;

    // Contar cuántos grupos de valores RGB hay en el archivo
    // Se asume que cada línea después de la semilla tiene tres valores (r, g, b)
    while (archivo >> r >> g >> b) {
        n_pixels++;  // Contamos la cantidad de píxeles
    }

    // Cerrar el archivo para volver a abrirlo desde el inicio
    archivo.close();
    archivo.open(nombreArchivo);

    // Verificar que se pudo reabrir el archivo correctamente
    if (!archivo.is_open()) {
        cout << "Error al reabrir el archivo." << endl;
        return nullptr;
    }

    // Reservar memoria dinámica para guardar todos los valores RGB
    // Cada píxel tiene 3 componentes: R, G y B
    unsigned int* RGB = new unsigned int[n_pixels * 3];

    // Leer nuevamente la semilla desde el archivo (se descarta su valor porque ya se cargó antes)
    archivo >> seed;

    // Leer y almacenar los valores RGB uno por uno en el arreglo dinámico
    for (int i = 0; i < n_pixels * 3; i += 3) {
        archivo >> r >> g >> b;
        RGB[i] = r;
        RGB[i + 1] = g;
        RGB[i + 2] = b;
    }

    // Cerrar el archivo después de terminar la lectura
    archivo.close();

    // Mostrar información de control en consola
    cout << "Semilla: " << seed << endl;
    cout << "Cantidad de píxeles leídos: " << n_pixels << endl;

    // Retornar el puntero al arreglo con los datos RGB
    return RGB;
}


unsigned char* funcXor(unsigned char* img1, unsigned char* img2, int &width, int &height){
   int size= width * height * 3;
    unsigned char *resultado = new unsigned char[size];
    for (int u = 0; u <= size; ++u) {
     resultado[u] = img1[u] ^ img2[u];

    }
    return resultado;
}


unsigned char* Desenmascar(unsigned int* datostxt, unsigned char* mascara, int &seed, int &widthM,int &heightM,int &n_pixels) {
    unsigned char* imagenDesenmascarada = new unsigned char[n_pixels];
    n_pixels = widthM * heightM;
    for (int u = 0; u < n_pixels; ++u) {
        int posicion = u + seed;
        if (posicion < n_pixels) {
            int valor = (int)(datostxt[u]) - (int)(mascara[u]);

            if (valor < 0) valor = 0;
            if (valor > 255) valor = 255;

            imagenDesenmascarada[posicion] = (unsigned char)(valor);
        }
    }

    return imagenDesenmascarada;
}


unsigned char* rotacionInversa(unsigned char* imagen, int &ancho, int &alto) {
    int totalPixeles = ancho * alto * 3;
    unsigned char* resultado = new unsigned char[totalPixeles];

    for (int i = 0; i < totalPixeles; ++i) {
        unsigned char byte = imagen[i];
        // Rotación de 3 bits a la izquierda
        resultado[i] = (byte << 3) | (byte >> (8 - 3));
    }

    return resultado;
}







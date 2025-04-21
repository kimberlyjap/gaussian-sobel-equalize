# 🎨 Filtros de Imagen con OpenCV / Image Filters with OpenCV

Este proyecto fue realizado como parte de un **examen práctico de Visión Artificial**. Utiliza OpenCV para aplicar procesos clásicos de procesamiento de imágenes, como:

This project was created as part of a **practical exam for a Computer Vision course**. It uses OpenCV to apply classic image processing techniques such as:

- Conversión a escala de grises / Grayscale conversion  
- Filtro Gaussiano / Gaussian filter  
- Ecualización de histograma / Histogram equalization  
- Filtro de Sobel / Sobel filter  

---

## 🖼️ Imagen de entrada / Input image

Se utiliza la clásica imagen de Lena: `lenahermosa.jpg`.  
This project uses the classic Lena image: `lenahermosa.jpg`.

*Asegúrate de tenerla en la ruta correcta si deseas probar el programa.*  
*Make sure it’s in the correct path if you want to run the program.*

---

## 📦 Requisitos / Requirements

- C++
- OpenCV (recomendado 3.4 o superior / recommended 3.4+)

---

## 🧠 Funcionalidad principal / Main features

1. **Lectura de imagen / Image reading**  
   Se carga una imagen en color desde disco.  
   Loads a color image from disk.

2. **Conversión a escala de grises / Grayscale conversion**  
   Transformación de RGB a escala de grises.  
   Converts RGB image to grayscale.

3. **Generación de kernel gaussiano / Gaussian kernel generation**  
   Se genera un kernel 2D en base a `sigma` y tamaño definido por el usuario.  
   Generates a 2D Gaussian kernel based on `sigma` and a user-defined size.

4. **Filtro Gaussiano / Gaussian filter**  
   Se aplica el kernel a la imagen con `filter2D`.  
   Applies the kernel to the image using `filter2D`.

5. **Ecualización de histograma / Histogram equalization**  
   Mejora el contraste con `equalizeHist`.  
   Enhances contrast with `equalizeHist`.

6. **Filtro Sobel / Sobel filter**  
   Detecta bordes usando gradientes horizontales y verticales.  
   Detects edges using horizontal and vertical gradients.

---

## 🔧 Uso / Usage

1. Compilar el archivo fuente:  
   Compile the source file:

```bash
g++ fileGrey.cpp -o filtro `pkg-config --cflags --libs opencv4`

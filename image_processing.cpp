#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#define PI 3.141592653589

using namespace cv;
using namespace std;

// Mostrar la imagen original
void mostrarOriginal(Mat imagen) {
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    waitKey(0);
}

// Mostrar cualquier imagen
void mostrarImagen(Mat imagen, string titulo) {
    namedWindow(titulo, WINDOW_AUTOSIZE);
    imshow(titulo, imagen);
    waitKey(0);
}

// Crear kernel gaussiano 2D
Mat generarKernelGaussiano(int kernelSize, double sigma) {
    Mat kernel(kernelSize, kernelSize, CV_64F);
    int centro = kernelSize / 2;
    double suma = 0.0;

    for (int i = 0; i < kernelSize; i++) {
        for (int j = 0; j < kernelSize; j++) {
            int x = i - centro;
            int y = j - centro;
            double valor = exp(-(x * x + y * y) / (2 * sigma * sigma));
            valor /= (2 * PI * sigma * sigma);
            kernel.at<double>(i, j) = valor;
            suma += valor;
        }
    }

    // Normalizar el kernel
    kernel /= suma;
    return kernel;
}

// Aplicar el kernel gaussiano a la imagen
Mat aplicarFiltroGaussiano(Mat imagen, Mat kernel) {
    Mat imagenGris, resultado;
    cvtColor(imagen, imagenGris, COLOR_BGR2GRAY);
    filter2D(imagenGris, resultado, -1, kernel);
    return resultado;
}

// Ecualización de histograma
Mat ecualizar(Mat imagen) {
    Mat gris, histEq;
    cvtColor(imagen, gris, COLOR_BGR2GRAY);
    equalizeHist(gris, histEq);
    return histEq;
}

// Aplicar filtro Sobel
Mat aplicarSobel(Mat imagen) {
    Mat gris, gradX, gradY, sobel;
    cvtColor(imagen, gris, COLOR_BGR2GRAY);
    Sobel(gris, gradX, CV_16S, 1, 0);
    Sobel(gris, gradY, CV_16S, 0, 1);
    Mat absX, absY;
    convertScaleAbs(gradX, absX);
    convertScaleAbs(gradY, absY);
    addWeighted(absX, 0.5, absY, 0.5, 0, sobel);
    return sobel;
}

int main() {
    Mat imagen = imread("C:/Users/kpi00/Downloads/lenahermosa.jpg");

    if (imagen.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return -1;
    }

    mostrarOriginal(imagen);

    int sigma, kernelSize;
    cout << "Elige el valor de sigma: ";
    cin >> sigma;
    cout << "Elige un tamaño impar para el kernel: ";
    cin >> kernelSize;
    while (kernelSize < 1 || kernelSize % 2 == 0) {
        cout << "Error. Debe ser impar. Intenta de nuevo: ";
        cin >> kernelSize;
    }

    Mat kernelGauss = generarKernelGaussiano(kernelSize, sigma);
    Mat imagenSuavizada = aplicarFiltroGaussiano(imagen, kernelGauss);
    mostrarImagen(imagenSuavizada, "Imagen Suavizada");

    Mat imagenEcualizada = ecualizar(imagen);
    mostrarImagen(imagenEcualizada, "Imagen Ecualizada");

    Mat imagenSobel = aplicarSobel(imagen);
    mostrarImagen(imagenSobel, "Filtro Sobel");

    return 0;
}

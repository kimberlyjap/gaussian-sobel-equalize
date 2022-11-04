//  Kimberly Jovana Almeraya Pineda
//  04/11/2022
//  Primer Examen Práctico
//  Visión Artificial

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <opencv2/imgproc/imgproc.hpp>
#define PI 3.141592653589

using namespace cv;
using namespace std;

//Función para ver la imagen Original
void mostrarOriginal(Mat imagen) { 
	
	int fila_original = imagen.rows;//Leer el número de filas
	int columna_original = imagen.cols;//Leer el de número columnas

	cout << "filas: " << fila_original << endl;
	cout << "columnas: " << columna_original << endl;

	namedWindow("Original", WINDOW_AUTOSIZE);//Crear de una ventana
	imshow("Original", imagen);//Mostrar la imagen original


	waitKey(0); //Esperar con la ventana abierta
}

//Funcion para ver la imagen del resultado del Kernel en Escala de Grises
void mostrarImagen(Mat imagen) {
	int fila_original = imagen.rows;
	int columna_original = imagen.cols;//Lectura de cuantas columnas

	cout << "filas: " << fila_original << endl;
	cout << "columnas: " << columna_original << endl;

	namedWindow("Filtro", WINDOW_AUTOSIZE);//Crear una ventana para la imagen del filtro en escala de grises
	imshow("Filtro", imagen);//Mostrar la imagen del filtro en escala de grises

	waitKey(0); //Esperar con la ventana abierta

}

//Función para ver la imagen ecualizada
void mostrarEcualizada(Mat imagen) {
	Mat original;//Declaramos una matriz de la original
	original = imread("lenahermosa.jpg");//Accesar a la ubicación de la imagen
	Mat gray;//Declarar una matriz para la imagen en escala de grises
	cvtColor(original, gray, COLOR_BGR2GRAY);//Función de opencv para transformar la original a escala de grises
	Mat hist;//Declarar una matriz para la imagen resultado del histograma
	cv::equalizeHist(gray, hist);//Función de opencv para realizar la imagen en histograma ecualizado
	namedWindow("Histograma");//Crear una ventana para la imagen ecualizada
	imshow("Histograma", hist);//Mostrar la imagen ecualizada
	waitKey(0);//Esperar con la ventana abierta
}

//Función para el filtro Sobel
void mostrarSobel(Mat imagen) {

}

//Proceso para la generación del Kernel
double** generacionKernel(int sigma, int kernel) { //Recibe la variable sigma y kernel
	//Mat matriz; que recibe, transforma y devuelve el kernel
	Mat matriz(kernel, kernel, CV_8UC1);
	int centro = (kernel - 1) / 2;//Se encuentra el centro del Kernel dentro de la matriz Kernel

	double** matrizprueba = new double* [kernel];

	//Ciclo para el Kernel
	for (int i = 0; i < kernel; i++) {
		matrizprueba[i] = new double[kernel];
		for (int j = 0; j < kernel; j++) {
			int posx = i - centro;
			int posy = (j - centro) * -1;

			double valor = 1 / (2 * PI * sigma * sigma);
			valor = valor * exp(-(pow(posx, 2) + pow(posy, 2)) / 2 * pow(sigma, 2));
			matrizprueba[i][j] = valor;

			cout << valor << "\t";

		}
		cout << "\n";
	}

	return matrizprueba;
}
//Se procesa con el Kernel la imagen original con esta funcion
void procesarMatriz(Mat imagen, int kernel, int sigma) {//Por eso recibe la original, el kernel y el sigma
	int rows = imagen.rows;//Obtener la información de la imagen en filas y columnas
	int cols = imagen.cols;
	int exceso = (kernel - 1) / 2;//Revisamos si hay un exceso, es decir, sobresale el Kernel para ajustarlo

	Mat grises(rows + exceso, cols + exceso, CV_8UC1);
	Mat grande(rows + exceso, cols + exceso, CV_8UC1);

	cvtColor(imagen, grises, COLOR_BGR2GRAY);//Funcion de openCV para transformar la imagen original a escala de grises

	double rojo, azul, verde, gris_p;//Recibirán la información de la imagen en sus tres canales  y la info resultado de la escala de grises

	for (int i = 0; i < rows + exceso; i++) {
		for (int j = 0; j < cols + exceso; j++) {

			if (i >= rows || i < exceso) { // 
				grande.at<uchar>(Point(j, i)) = uchar(0);
				//cout << "entra\n";
			}
			else if (j >= cols || j < exceso) {  //>=, Porque se toma en cuenta el 0
				grande.at<uchar>(Point(j, i)) = uchar(0);
				//cout << "entra\n";
			}
			else {
				azul = imagen.at<Vec3b>(Point(j - exceso, i - exceso)).val[0];
				//verde la segunda
				verde = imagen.at<Vec3b>(Point(j - exceso, i - exceso)).val[1];
				//roja la tercera
				rojo = imagen.at<Vec3b>(Point(j - exceso, i - exceso)).val[2];

				//El valor de gris promediado lo obtenemos sumando cada valor de 
				//rojo, verde y azul dividido entre 3
				gris_p = (azul + verde + rojo) / 3;

				grande.at<uchar>(Point(j, i)) = uchar(gris_p);
			}
			// azul la primer declaración
			//azul = image.at<Vec3b>(Point(j, i)).val[0];
			//verde la segunda declaración
			//verde = image.at<Vec3b>(Point(j, i)).val[1];
			//roja la tercer declaración
			//rojo = image.at<Vec3b>(Point(j, i)).val[2];

			//grande.at<uchar>(Point(j, i)) = uchar(gris_p); //uchar es un valor de 8 bits

		}
	}
	mostrarImagen(grande);//Llamada a la función para ver el resultado de la imagen procesada con un Kernel

}

int main() {

	// Matriz que contiene nuestra imagen sin importar el formato
	// Matriz de la imagen
// Leer imagen
	cv::Mat imagen = cv::imread("lenahermosa.jpg");// Matriz que contiene nuestra imagen sin tomar en cuenta el formato

	//Validación de la imagen
	if (!imagen.data)
	{
		cout << "Error al cargar la imagen: " << imagen << endl;
		exit(1);
	}
	//Llamada a la función para ver la imagen original
	mostrarOriginal(imagen);
	
	int sigma;//Declaración de la variable sigma int

	cout << "Elige el valor de sigma: ";//Obtener el valor de sigma por el usuario
	cin >> sigma;//Guardar el valor de sigma en la variable

	int kernel;//Declaración de la variable Kernel
	cout << "Elige un tamanio para kernel: "; //Obtener el valor de kernel por el usuario

	cin >> kernel;//Guardar el valor de Kernel en la variable
	while (kernel < 1 || kernel % 2 == 0) {//Validación de que el Kernel sea un número Impar
		cout << "Error! Elige in kernel de tamanio impar ";

		cin >> kernel;
	}

	//Llamado a funciones de procesos:
	//Kernel,ecualizacion y sobel
	double** matriz_kernel = generacionKernel(sigma, kernel);
	procesarMatriz(imagen, kernel, sigma);
	mostrarEcualizada(imagen);
	mostrarSobel(imagen);

	return 0;//Ejecución sin errores
}
/*
 * pantalla.h
 *
 *  Created on: 6 oct. 2020
 *      Author: leo
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

#define TRUE 1
#define FALSE 0
#define SIZE_NOMBRE 50
#define SIZE_DIRECCION 90
#define QTY_ENTIDAD 5
#define MIN 1
#define MAX 100

typedef struct
{
	int id;
	int isEmpty;
	char nombre[SIZE_NOMBRE];
	int tipoDePantalla;
	float precioXDia;
	char direccion[SIZE_DIRECCION];

}Pantalla;

int pant_initArray(Pantalla* pArray, int limite);

int pant_alta(Pantalla* pArray,int limite);
int pant_altaConIndice(Pantalla* pArray,int limite,int indice);
int pant_modificar(Pantalla* pArray,int limite);
int pant_baja(Pantalla* pArray,int limite);

int pant_imprimir(Pantalla* pArray, int limite);
int pant_imprimirPorID(Pantalla* pArray, int limite, int index);

int pant_buscarId(Pantalla* pArray, int limite, int* pIndex, int id);
int pant_buscarLibreRef(Pantalla* pArray, int limite, int *pIndex);
int pant_buscarLibreValor(Pantalla* pArray, int limite);

int pant_ordenarAlfabeticamente(Pantalla* pArray, int limite, int orden);
int pant_ordenarAlfaX2Criterios(Pantalla* pArray, int limite);

#endif /* PANTALLA_H_ */

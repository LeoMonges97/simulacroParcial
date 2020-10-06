/*
 * pantalla.c
 *
 *  Created on: 6 oct. 2020
 *      Author: leo
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "pantalla.h"

// Modificar variables genericas: Pantalla - cadena - entero
// pant_alta
// pant_altaConIndice
// pant_modificar
// pant_imprimir
// pant_imprimirPorID
// pant_ordenarAlfabeticampante
// pant_ordenarAlfaX2Criterios

static int generarIdNuevo(void);

/**@brief generarIdNuevo(): Cada vez que la llamo, me devuelve un ID nuevo que nunca me devolvio antes.
 */
static int generarIdNuevo(void)
{
	static int id = 0; // es global para solo la fn puede usarla

	//guardar el ultimo que asigne (ultimo que devolvi)
	//para devolver 1+
	id = id + 1;
	return id;
}

/**@brief pant_initArray(): Inicializa el array.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int pant_initArray(Pantalla* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i=0;i<limite;i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief pant_alta(): Realiza el alta de una entidad solo si el indice que se busca corresponde en Empty.
 * @param Pantalla* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int pant_alta(Pantalla* pArray,int limite)
{
	int retorno = -1;
	int indice;
	Pantalla buffer;

	if(	pArray != NULL && limite > 0)
	{
		if(pant_buscarLibreRef(pArray, limite,&indice) == 0) // Busca un lugar libre
		{
			if(	utn_getNombre("\n . Nombre: ","\n > Error!",buffer.nombre,2,SIZE_NOMBRE) == 0 &&
				utn_getInt("\n . Tipo de Pantalla: ","\n > Error!",&(buffer.tipoDePantalla),2,MIN,MAX) == 0
			  )
			{
				//buffer.isEmpty = FALSE;
				buffer.id = generarIdNuevo();
				pArray[indice] = buffer;
				pArray[indice].isEmpty = FALSE;

				retorno = 0;
			}
			else
			{
				printf("\n Error en la carga de datos!\n");
			}
		}
		else
		{
			printf("\n Lo sentimos, no hay posiciones libres!\n");
		}
	}
	return retorno;
}

/**@brief pant_altaConIndice(): Realiza el alta de una entidad solo si el indice que le paso corresponde a un Empty.
 * @param Pantalla* pArray, Es el puntero al array de enteros.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el ent.
 * @return (-1) Error / (0) Ok
 */
int pant_altaConIndice(Pantalla* pArray,int limite,int indice)
{
	int retorno = -1;
	Pantalla buffer;

	if(	pArray != NULL && limite > 0 &&
			indice >=0 &&
			indice < limite &&
			pArray[indice].isEmpty == TRUE)
	{
		if(	utn_getInt("\n . tipoDePantalla: ","\nError",&buffer.tipoDePantalla,2,MIN,MAX) == 0 &&
				utn_getNombre("\n . Cadena: ","\nError",buffer.nombre,2,SIZE_NOMBRE) == 0)
		{
			//buffer.isEmpty = FALSE;
			buffer.id = generarIdNuevo();
			pArray[indice] = buffer;
			pArray[indice].isEmpty = FALSE;

			retorno = 0;
		}
	}
	return retorno;
}

/**@brief pant_modificar(): Modifica los datos de un ent solo si el indice corresponde a un NO Empty.
 * @param Pantalla* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int pant_modificar(Pantalla* pArray,int limite)
{
	int retorno = -1;
	int idModificar;
	int indice;
	Pantalla buffer;

	if(utn_getInt(" . Ingrese el ID a modificar:"," Error!", &idModificar,5,1,1000) == 0)
	{
		if(pant_buscarId(pArray, limite, &indice, idModificar) == 0)
		{
			if(	pArray != NULL && limite > 0 && indice >= 0 && indice < limite &&
					pArray[indice].isEmpty == FALSE)
			{
				if(	utn_getInt("\n . tipoDePantalla: ","\nError",&buffer.tipoDePantalla,2,MIN,MAX) == 0 &&
						utn_getNombre("\n . Cadena: ","\nError",buffer.nombre,2,SIZE_NOMBRE) == 0)
				{
					//buffer.isEmpty = FALSE;
					buffer.id = pArray[indice].id; //generarIdNuevo(); // NOOOOOOOOO
					// Al entrar ne la funcion, no puede tocar el campo de id.
					// Es por eso que antes de que se modifiquen todos los campos,
					// le asigno nuevamente el id que ya traia.
					// Es el unico dato que puede cambiar nunca.
					// Si se modificara el id, se estaria llamando a eliminar
					// y daria de alta uno de nuevo.
					pArray[indice] = buffer;
					pArray[indice].isEmpty = FALSE;

					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

/**@brief pant_baja(): Realiza la baja de una entidad dando el ID correpondiente.
 * @param Pantalla* pArray, Es el puntero al array.
 * @param int limite, es el limite de array.
 * @param int indice, es el indice donde se cargara el dato.
 * @return (-1) Error / (0) Ok
 */
int pant_baja(Pantalla* pArray,int limite)
{
	// Tipo de baja: Logica
	int retorno = -1;
	int idBajar;
	int indice;

	if(utn_getInt(" . Ingrese el ID a bajar:"," Error! ", &idBajar,2,1,1000) == 0)
	{
		if(pant_buscarId(pArray, limite, &indice, idBajar) == 0)
		{
			if(	pArray != NULL && limite > 0 && indice >= 0 && indice < limite &&
					pArray[indice].isEmpty == FALSE)
			{
				pArray[indice].isEmpty = TRUE;
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**@brief pant_imprimir(): Imprime las entidades cargadas.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int pant_imprimir(Pantalla* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i=0;i<limite;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("\nID:%d - Cadena: %s - tipoDePantalla: %d",
						pArray[i].id,
						pArray[i].nombre,
						pArray[i].tipoDePantalla);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**@brief pant_imprimirPorID(): Imprime el ID de alguna entidad que se quiera buscar.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es el indice a imprimir.
 * @return (-1) Error / (0) Ok
 */
int pant_imprimirPorID(Pantalla* pArray, int limite, int index)
{
	int retorno = -1;

	if(pArray != NULL && limite > 0 && index < limite)
	{
		if(pArray[index].isEmpty == FALSE)
		{
			printf("\nCadena: %s - tipoDePantalla: %d\n\n",
					pArray[index].nombre,
					pArray[index].tipoDePantalla);
			retorno = 0;
		}
	}
	return retorno;
}

/**
 * Como lo implemento?
 * int posicionLibre;
 * if(pant_buscarLibre(ent,QTY_ALUMNOS,&posicionLibre) == 0)
 * {
 *   posicionLibre -> alta
 * }
 */
/**@brief pant_buscarLibreRef(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por referencia.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int *pIndex, es la varible en donde se guardara esa posicion vacia o disponible.
 * @return (-1) Error / (0) Ok
 */
int pant_buscarLibreRef(Pantalla* pArray, int limite, int *pIndex)
{
	int retornar = -1;
	if(pArray != NULL && pIndex != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				*pIndex = i;
				retornar = 0;
				break;
			}
		}
	}
	return retornar;
}

/**
 * Como lo implemento?
 * int posicionLibre;
 * posicionLibre = pant_buscarLibre(ent,QTY_ALUMNOS);
 * if(posicionLibre >=0)
 * {
 *   posicionLibre -> alta
 * }
 */
/**@brief pant_buscarLibreValor(): Busca un espacio libre en el array y retorna la posicion mediante pasaje por valor.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int pant_buscarLibreValor(Pantalla* pArray, int limite)
{
	int retornar = -1;
	if(pArray != NULL && limite > 0)
	{
		for(int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retornar = i;
				break;
			}
		}
	}
	return retornar;
}

/**@brief pant_buscarId(): Busca el ID de una entidad.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int index, es la varible en donde se guardara la posicion del ID.
 * @param int id, es el identificador que quiero comparar y buscar.
 * @return (-1) Error / (0) Ok
 */
int pant_buscarId(Pantalla* pArray, int limite, int* pIndex, int id)
{
	int retorno = -1;
	//*pIndex = -1;
	if (pArray != NULL && limite > 0 && id >= 0)
	{
		for (int i = 0; i < limite; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].id == id)
				{
					*pIndex = i;
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

/**@brief ent_ordenarAlfabeticamente(): Ordena alfabeticamente las cadenas de caracteres (ascendente & descendente).
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @param int orden, es el criterio de ordenamiento a elegir (1 = a-z || 0 = z-a).
 * @return (-1) Error / (0) Ok
 */
int pant_ordenarAlfabeticamente(Pantalla* pArray, int limite, int orden)
{
	int retorno = -1;
	int flagSwap;
	Pantalla buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE

	if(pArray != NULL && limite > 0 && (orden == 0 || orden == 1))
	{
		do
		{
			flagSwap = 0;
			for(int i = 0; i < limite-1;i++)
			{
				if((orden == 1 && strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) > 0) ||
				   (orden == 0 && strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) < 0)
				)
				{
					buffer = pArray[i];
					pArray[i] = pArray[i+1];
					pArray[i+1] = buffer;
					flagSwap = 1;
					retorno = 0;
				}
			}
		}while(flagSwap);
	}
	return retorno;
}

/**@brief pant_ordenarAlfaX2Criterios(): Ordena alfabeticamente las cadenas de caracteres incluyendo otro campo para "desempatar",
 *        en caso de ser iguales las cadenas.
 * @param Pantalla* pArray, Es el puntero al array al tipo de datos.
 * @param int limite, es el limite de array.
 * @return (-1) Error / (0) Ok
 */
int pant_ordenarAlfaX2Criterios(Pantalla* pArray, int limite)
{
	int retorno = -1;
	int flagSwap;
	Pantalla buffer;

	//if(pArray[i].isEmpty == FALSE && pArray[i+1].isEmpty == FALSE
	do
	{
		flagSwap = 0;
		for(int i = 0; i < limite-1;i++)
		{
			if(strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) > 0 ||
					(strncmp(pArray[i].nombre,pArray[i+1].nombre,SIZE_NOMBRE) == 0
							&& pArray[i].tipoDePantalla > pArray[i+1].tipoDePantalla))
			{
				buffer = pArray[i];
				pArray[i] = pArray[i+1];
				pArray[i+1] = buffer;
				flagSwap = 1;
				retorno = 0;
			}
		}
	}while(flagSwap);

	return retorno;
}


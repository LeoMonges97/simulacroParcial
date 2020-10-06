/*
 * utn.c
 *
 *  Created on: 11 sep. 2020
 *      Author: Leo
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"

static int myGets(char* cadena, int longitud);
static int esNombreValido(char* cadena,int limite);
static int getInt(int* pResultado);
static int esNumerica(char* cadena);
static int getFloat(float* pResultado);
static int esFlotante(char* cadena);

/**@brief myGets(): Recibe un string con limite.
 * @param char* cadena: Cadena donde dejo la informacion.
 * @param int longitud: Cuantos caracteres quiero leer.
 * @return 0
 */
static int myGets(char* cadena, int longitud)
{
	__fpurge(stdin);
	fgets(cadena,longitud,stdin);
	cadena[strlen(cadena)-1] = '\0';
	return 0;
}

/**@brief utn_getInt(): Verifica si la cadena ingresada es entero.
 * @param int* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @return
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[64];
	//scanf("%s",buffer);
	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer) == 1)
		{
			*pResultado = atoi(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

/**@brief esNumerica(): Verifica si la cadena/buffer son solo numeros enteros.
 *                      (Se incluyen valores negativos).
 * @param char* cadena: Cadena de caracteres a ser analizada.
 * @return (1) OK / (0) Error
 */
static int esNumerica(char* cadena)
{
	int retorno = 1;
	int i = 0;
	if(cadena[i] == '-')
	{
		i = 1;
	}
	for( ; cadena[i] != '\0'; i++)
	{
		if(cadena[0] == '-')
		{

		}
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/**@brief utn_getInt(): Verifica si la cadena ingresada es flotante.
 * @param float* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @return
 */
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[64];
	if(pResultado != NULL)
	{
		if(myGets(buffer, sizeof(buffer)) == 0 && esFlotante(buffer) == 1)
		{
			*pResultado = atof(buffer);
			retorno = 0;
		}
	}
	return retorno;
}

/**@brief esFlotante(): Verifica si la cadena/buffer son solo numeros flotantes
 *                      (Se incluyen ejemplos como:
 *                       3.14 +3.14 -3.14 .314 +.314 -.314 314. +314. -314.)
 * @param char* cadena: Cadena de caracteres a ser analizada.
 * @return (1) OK / (0) Error
 */
static int esFlotante(char* cadena)
{
	int retorno = 1;
	int i = 0;
	int contadorPuntos = 0; //No tiene que haber mas de 2 puntos.

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i = 0; cadena[i] != '\0'; i++)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}



/**@brief utn_getInt(): Solicita un numero entero al usuario.
 * @param char* mensaje: Es el mensaje a ser mostrado al usuario.
 * @param char* mensajeError: Es el mensaje de error a ser mostrado al usuario.
 * @param int* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @param int reintentos: Cantidad de oportunidades para ingresar el dato.
 * @param int maximo: Valor maximo admitido.
 * @param int minimo: Valor minimo admitido.
 * @return (-1) Error / (0) Ok
 */
int utn_getInt(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int minimo,int maximo)
{
	int retorno = -1;
	int bufferInt;
	//int resultadoScanf;
	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			maximo >= minimo)
	{
		do
		{
			printf("%s",mensaje);
			__fpurge(stdin);
			//resultadoScanf = scanf("%d" , &bufferInt);
			if( getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
				retorno = 0;
				*pResultado = bufferInt;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**@brief utn_getFloat(): Solicita un numero flotante al usuario.
 * @param char* mensaje: Es el mensaje a ser mostrado al usuario.
 * @param char* mensajeError: Es el mensaje de error a ser mostrado al usuario.
 * @param int* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @param int reintentos: Cantidad de oportunidades para ingresar el dato.
 * @param int maximo: Valor maximo admitido.
 * @param int minimo: Valor minimo admitido.
 * @return (-1) Error / (0) Ok
 */
int utn_getFloat(char* mensaje, char* mensajeError, float* pResultado,int reintentos,float minimo,float maximo)
{
	int retorno = -1;
	float bufferFloat;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			maximo >= minimo)
	{
		do
		{
			printf("%s",mensaje);
			__fpurge(stdin);

			if(getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
			{
				retorno = 0;
				*pResultado = bufferFloat;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**@brief utn_getChar(): Solicita un caracter char al usuario.
 * @param char* mensaje: Es el mensaje a ser mostrado al usuario.
 * @param char* mensajeError: Es el mensaje de error a ser mostrado al usuario.
 * @param char* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @param int reintentos: Cantidad de oportunidades para ingresar el dato.
 * @param int maximo: Valor maximo admitido.
 * @param int minimo: Valor minimo admitido.
 * @return (-1) Error / (0) Ok
 */
int utn_getChar(char* mensaje, char* mensajeError, char* pResultado,int reintentos,int rangoInicial,int rangoFinal)
{
	int retorno = -1;
	char bufferChar;
	int resultadoScanf;
	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			rangoFinal >= rangoInicial)
	{
		do
		{
			printf("%s",mensaje);
			__fpurge(stdin);
			resultadoScanf = scanf("%c" , &bufferChar);
			if(resultadoScanf == 1 && bufferChar >= rangoInicial && bufferChar <= rangoFinal)
			{
				retorno = 0;
				*pResultado = bufferChar;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**@brief utn_getString(): Solicita un texto/cadena al usuario.
 * @param char* mensaje: Es el mensaje a ser mostrado al usuario.
 * @param char* mensajeError: Es el mensaje de error a ser mostrado al usuario.
 * @param char* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @param int reintentos: Cantidad de oportunidades para ingresar el dato.
 * @param int limite: Indica la cantidad de letras maxima del nombre.
 * @return (-1) Error / (0) Ok
 */
int utn_getString(char* mensaje,char* mensajeError,char* pResultado,int reintentos,int limite)
{
	int retorno = -1;
	char bufferString[4096];

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if(myGets(bufferString,sizeof(bufferString)-1) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1) <= limite)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**@brief utn_getNombre(): Solicita un nombre al usuario.
 * @param char* mensaje: Es el mensaje a ser mostrado al usuario.
 * @param char* mensajeError: Es el mensaje de error a ser mostrado al usuario.
 * @param char* pResultado: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @param int reintentos: Cantidad de oportunidades para ingresar el dato.
 * @param int limite: Indica la cantidad de letras maxima del nombre.
 * @return (-1) Error / (0) Ok
 */
int utn_getNombre(char* mensaje,char* mensajeError,char* pResultado,int reintentos,int limite)
{
	int retorno = -1;
	char bufferString[4096];
	//int resultadoScanf;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			//__fpurge(stdin);
			//resultadoScanf = scanf("%s",&bufferString);
			//resultadoScanf == 1
			if(myGets(bufferString,sizeof(bufferString)-1) == 0 &&
					strnlen(bufferString,sizeof(bufferString)-1) <= limite &&
					esNombreValido(bufferString,limite) != 0)
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/**@brief normalizarNombre(): Une en una sola variable el apellido y nombre.
 * @param char* nombre: Puntero al espacio de memoria donde se dejara el valor obtenido de nombre.
 * @param char* apellido: Puntero al espacio de memoria donde se dejara el valor obtenido de apellido.
 * @param char* nombreCompleto: Puntero al espacio de memoria donde se dejara el valor obtenido.
 * @return (-1) Error / (0) Ok
 */
int utn_normalizarNombre(char* nombre, char* apellido,char* nombreCompleto)
{
	int retorno = -1;

	if(nombre != NULL && apellido != NULL && nombreCompleto != NULL)
	{
		strlwr(nombre);
		nombre[0] = toupper(nombre[0]);
		strlwr(apellido);
		apellido[0] = toupper(apellido[0]);
		sprintf(nombreCompleto,"\n .Nombre completo: %s, %s",apellido,nombre);
		retorno = 0;
	}

	return retorno;
}

/**@brief esNombre(): Verifica una cadena recibida como parametro para
 *                    determinar si es un nombre valido.
 * @param char* cadena: Cadena a analizar.
 * @param int limite: Indica la cantidad de letras maxima de la cadena.
 * @return   (0)  Indica que no es un nombre valido.
 *         (0!/1) Indica que es un nombre valido.
 */
static int esNombreValido(char* cadena,int limite)
{
	int respuesta = 1; //TODO OK

	for(int i = 0;i <= limite && cadena[i] != '\0' ;i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
				(cadena[i] < 'a' || cadena[i] > 'z') &&
				cadena[i] != '.')
		{
			respuesta = 0;
			break;
		}
	}
	/*For:
	. 1 parte que se ejecuta una vez.
	. 1 parte que condiciona o no volver a entrar o no al for.
	. Algo que se va ejecutar en cada vuelta.
	 */
	return respuesta;
}

/**@brief strupr(): Covierte toda la cadena en mayuscula (Para Linux).
 * @param char* cadena, es la cadena a utilizar.
 */
void strupr(char* cadena)
{
	if(cadena != NULL)
	{
		while(*cadena)
		{
			*cadena = toupper(*cadena);
			cadena++;
		}
	}
}

/**@brief strlwr(): Covierte toda la cadena en minuscula (Para Linux).
 * @param char* cadena, es la cadena a utilizar.
 */
void strlwr(char* cadena)
{
	if(cadena != NULL)
	{
		while(*cadena)
		{
			*cadena = tolower(*cadena);
			cadena++;
		}
	}
	/* Otra variante:
	int retorno = -1;
	int i = 0;

	if(str != NULL)
	{
		while(str[i] != '\0')
		{
			str[i] = tolower(str[i]);
			i++;
		}
		retorno = 0;
	}
	return retorno;
	 */
}

/**@brief pause(): Comando de pausa para consola Linux.
 */
void pause()
{
	char tmp;
	__fpurge(stdin);
	do
	{
		tmp = getchar();
	}while(tmp != '\n' && tmp != EOF);

	return;
}

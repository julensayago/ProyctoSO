//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	
	// Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char nombre[20];
	int ID;
	char consulta [80];
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) 
	{
		printf ("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		
		exit (1);
	}
	//inicializar la conexion, indicando nuestras claves de acceso al servidor de BBDD
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "juego", 0, NULL,0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		
		exit (1);
	}
	
		
		// Ahora vamos a buscar el nombre de la persona cuyo nombre es uno
		// dado por el usuario
		printf ("Dame el nombre del usuario:\n");
		scanf ("%s", nombre);
		// construimos la consulta SQL
		strcpy (consulta,"SELECT partidas.fecha_hora FROM jugadores,partidas WHERE jugadores.nombre = '");
		strcat (consulta, nombre);
		strcat (consulta, "'AND jugadores.nombre = partidas.ganador");
		
		// hacemos la consulta
		err=mysql_query (conn, consulta);
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
			
			exit (1);
		}

		//recogemos el resultado de la consulta
		resultado = mysql_store_result (conn);
		row = mysql_fetch_row (resultado);

		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else
			while (row !=NULL) {
			// El resultado debe ser una matriz con una sola fila
			// y una columna que contiene el nombre
				printf ("%s jugo una partida el dia y hora: %s\n",nombre, row[0]);
				row = mysql_fetch_row (resultado);
			}
		
		// cerrar la conexion con el servidor MYSQL
		mysql_close (conn);
		exit(0);


	
}

#include "testing.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int cmp (const void* a,const void *b){
	return strcmp(a,b);
}

typedef struct pruebas{
	void* elementos;
}pruebas_t;


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void pruebas_crear_heap_vacio(){
	heap_t* heap = heap_crear(cmp);
	print_test("Heap vacio creado",heap != NULL);
	print_test("Heap desencolar es NULL",heap_desencolar(heap) == NULL);
	print_test("Heap ver max es NULL", heap_ver_max(heap) == NULL);
	print_test("Heap encolar elmento nulo es falso",heap_encolar(heap,NULL) == false);
	print_test("Heap esta vacio es true", heap_esta_vacio(heap) == true);
	print_test("Heap cantidad es 0", heap_cantidad(heap) == 0);
	heap_destruir(heap,NULL);
	print_test("Heap destruido correctamente",true);
}

static void pruebas_heap_encolar_desencolar(){
	int datos[] = {7,2,1,8};
	heap_t* heap = heap_crear(cmp);
	print_test("Heap vacio creado", heap != NULL);
	print_test("Heap encolar 7 es true",heap_encolar(heap,&datos[0]) == true);
	print_test("Heap ver maximo es 7",heap_ver_max(heap) == &datos[0]);
	print_test("Heap esta vacio es falso",heap_esta_vacio(heap) == false);
	print_test("heap cantidad es 1",heap_cantidad(heap) == 1);
	
	print_test("Heap encolar 2 es true",heap_encolar(heap,&datos[1]) == true);
	print_test("Heap ver maximo es 7",heap_ver_max(heap) == &datos[0]);
	print_test("heap cantidad es 2",heap_cantidad(heap) == 2);

	print_test("Heap encolar 1 es true",heap_encolar(heap,&datos[2]) == true);
	print_test("Heap ver maximo es 7",heap_ver_max(heap) == &datos[0]);
	print_test("heap cantidad es 1",heap_cantidad(heap) == 3);

	print_test("Heap encolar 8 es true",heap_encolar(heap,&datos[3]) == true);
	print_test("Heap ver maximo es 8",heap_ver_max(heap) == &datos[3]);
	print_test("heap cantidad es 4",heap_cantidad(heap) == 4);

	print_test("heap desencolar ", heap_desencolar(heap) == &datos[3]);
	print_test("Heap ver maximo es 7",heap_ver_max(heap) == &datos[0]);
	print_test("Heap cantidad es 3", heap_cantidad(heap) == 3);

	print_test("Heap desencolar", heap_desencolar(heap) == &datos[0]);
	print_test("Heap ver maximo es 2", heap_ver_max(heap) == &datos[1]);
	print_test("heap cantidad es 2",heap_cantidad(heap) == 2);

	print_test("Heap desencolar", heap_desencolar(heap) == &datos[1]);
	print_test("Heap ver maximo es 1", heap_ver_max(heap) == &datos[2]);
	print_test("Heap cantidad es 1", heap_cantidad(heap) == 1);

	print_test("Heap desencolar", heap_desencolar(heap) == &datos[2]);
	print_test("Heap ver maximo es nulo", heap_ver_max(heap) == NULL);
	print_test("Heap cantidad es 0", heap_cantidad(heap) == 0);
	print_test("Heap esta vacio es true", heap_esta_vacio(heap) == true);
	print_test("Heap desencolar es NULL", heap_desencolar(heap) == NULL);

	heap_destruir(heap,NULL);
	print_test("Heap destruido correctamente",true);
}

static void pruebas_crear_arr_heapify(){
	void** elementos = malloc(sizeof(void*) * 4);
	char* nombres[] = {"Gonzalo","Lucia","Ana","Sebastian"};
	elementos[0]=nombres[0];
	elementos[1]=nombres[1];
	elementos[2]=nombres[2];
	elementos[3]=nombres[3];
	heap_t* heap = heap_crear_arr(elementos,4,cmp);
	print_test("Heap creado correctamente", heap != NULL);
	print_test("Heap cantidad es 4", heap_cantidad(heap) == 4);
	print_test("Heap ver maximo es Sebastian", heap_ver_max(heap) == elementos[3]);
	print_test("Heap desencolar", heap_desencolar(heap) == elementos[3]);
	print_test("Heap ver maximo es Lucia", heap_ver_max(heap) == elementos[1]);
	print_test("Heap cantidad es 3",heap_cantidad(heap) == 3);
	print_test("Heap desencolar", heap_desencolar(heap) == elementos[1]);
	print_test("Heap ver maximo es Gonzalo",heap_ver_max(heap) == elementos[0]);
	print_test("Heap cantidad es 2", heap_cantidad(heap) == 2);

	free(elementos);
	heap_destruir(heap,NULL);
	print_test("Heap destruido correctamente",true);
}

void pruebas_heap_alumno (){
	pruebas_crear_heap_vacio();
	pruebas_heap_encolar_desencolar();
	pruebas_crear_arr_heapify();
}
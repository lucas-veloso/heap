#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_INICIAL 199

// Definicion de heap
struct heap{
	cmp_func_t comparar;
	void** datos;
	size_t cantidad;
	size_t tamanio;
};

/* *****************************************************************
 *                    AUXILIARES DEL HEAP                          *
 * *****************************************************************/

bool heap_redimensionar(heap_t* heap, size_t tamanio_nuevo) {
    void* datos_nuevo = realloc(heap->datos, tamanio_nuevo * sizeof(void*));
    if (tamanio_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }
    heap->datos = datos_nuevo;
    heap->tamanio = tamanio_nuevo;
    return true;
}

void swap (void** dato1, void** dato2){
	void* auxiliar = *dato1;
	*dato1 = *dato2;
	*dato2 = auxiliar;
	return;
}

void upheap (void *arreglo[], size_t pos){
	if (pos == 0) return;
	size_t padre = (pos-1)/2;
	if (arreglo[padre] < arreglo [pos]){
		swap(&arreglo[padre],&arreglo[pos]);
		upheap(arreglo,padre);
	}
}

void downheap (void *arreglo[], size_t n, size_t pos){
	if (pos>=n) return;
	size_t max = pos;
	size_t hijo_izq = (2*pos) +1;
	size_t hijo_der = (2*pos) +2;
	if (hijo_izq <n && arreglo[hijo_izq] > arreglo[max]) max = hijo_izq;
	if (hijo_der <n && arreglo[hijo_der] > arreglo[max]) max = hijo_der;
	if (max!= pos){
		swap(&arreglo[max],&arreglo[pos]);
		downheap(arreglo,n,max);
	}
}

void heapify(heap_t* heap){
	size_t pos = heap->cantidad-1;
	while (pos != 0){
		downheap(heap->datos,heap->cantidad,pos);
		pos--;
	}
}

/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP                          *
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	void* datos = malloc (sizeof(void*) * TAM_INICIAL);
	if (!datos){
		free(heap);
		return NULL;
	}
	heap->comparar = cmp;
	heap->datos = datos;
	heap->cantidad = 0;
	heap->tamanio = TAM_INICIAL;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = heap_crear(cmp);
	if (!heap) return NULL;
	if (n >= (heap->tamanio * 0.7)) heap_redimensionar(heap,heap->tamanio *2);
	for (int i = 0; i<n; i++){
		heap->datos[i] = arreglo [i];
		heap->cantidad++;
	}
	heapify(heap); 
	return heap;                                                                                                                                  
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e));

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	if (heap_cantidad(heap) == 0) return true;
	return false;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem);

void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap);
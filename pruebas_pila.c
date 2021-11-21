#include "pila.h"
#include "testing.h"
#include <stdio.h>


static void prueba_pila_vacia(void) {
    pila_t* pila = pila_crear();
    print_test("Prueba pila vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
}

static void prueba_invariante(void){
	pila_t* pila = pila_crear();

	bool apilar = true;
	bool desapilar = true;
	bool tope = true;

	int arreglo[] = {1, 2, 3};

	for (int i = 0; i < 3; i++){
		apilar &= pila_apilar(pila, &arreglo[i]);
		tope &= pila_ver_tope(pila) == &arreglo[i];
	}

	print_test("Apilar varios elementos linealmente", apilar);
	print_test("Ver tope al apilar elementos linealmente", tope);

	for (int i = 2; i >= 0 ; i--){
		tope &= pila_ver_tope(pila) == &arreglo[i];
		desapilar &= pila_desapilar(pila) == &arreglo[i];
	}
	print_test("Desapilar varios elementos linealmente", desapilar);
	print_test("Ver tope al desapilar elementos linealmente", tope);


	//Realizo distintas combinaciones de operaciones con la pila

	print_test("Apilar el elemento A", pila_apilar(pila, &arreglo[0]));
	print_test("Apilar el elemento B", pila_apilar(pila, &arreglo[1]));
	print_test("Al desapilar se recibio el elemento B", pila_desapilar(pila) == &arreglo[1]);
	print_test("Apilar el elemento C", pila_apilar(pila, &arreglo[2]));
	print_test("Al ver tope se recibio el elemento C", pila_ver_tope(pila) == &arreglo[2]);
	print_test("Al desapilar se recibio el elemento C", pila_desapilar(pila) == &arreglo[2]);
	print_test("Apilar elemento C", pila_apilar(pila, &arreglo[2]));
	print_test("Apilar elemento B", pila_apilar(pila, &arreglo[1]));
	print_test("Al desapilar se recibio el elemento B", pila_desapilar(pila) == &arreglo[1]);
	print_test("Al desapilar se recibio el elemento C", pila_desapilar(pila) == &arreglo[2]);
	print_test("Al desapilar se recibio el elemento A", pila_desapilar(pila) == &arreglo[0]);

	pila_destruir(pila);
}

static void prueba_volumen(void){
	bool apilar = true;
	bool desapilar = true;
	bool tope = true;
	int arreglo[1000];

	pila_t* pila = pila_crear();

	//Apilo 1000 elementos
	for (int i = 0; i < 1000; i++){
		apilar &= pila_apilar(pila, &arreglo[i]);
		tope &= pila_ver_tope(pila) == &arreglo[i];
	}

	print_test("Apilar 1000 elementos", apilar);
	print_test("Al ver tope apilando recibo el elemento esperado las 1000 veces", tope);

	//Verifico que conservan el orden al desapilarlos
	for (int i = 999; i >= 0; i--){
		tope &= pila_ver_tope(pila) == &arreglo[i];
		desapilar &= pila_desapilar(pila) == &arreglo[i];
	}

	print_test("Los 1000 elementos conservan el orden al desapilar", desapilar);
	print_test("Al ver tope desapilando recibo el elemento esperado las 1000 veces", tope);

	pila_destruir(pila);
}

static void prueba_apilar_NULL(void){
	void* a = NULL;

	pila_t* pila = pila_crear();

	print_test("Se pudo apilar NULL", pila_apilar(pila, &a));
	print_test("Al ver tope recibo el puntero a NULL que apile", pila_ver_tope(pila) == &a);
	print_test("Al desapilar recibo el puntero a NULL que apile", pila_desapilar(pila) == &a);

	pila_destruir(pila);
}

static void prueba_vaciar_pila(void){
	pila_t* pila = pila_crear();

	int a = 1;
	//apilo y desapilo a
	print_test("Apilo un elemento", pila_apilar(pila, &a));
	print_test("Al desapilar recibo el elemento", pila_desapilar(pila) == &a);

	//reviso si se comporta como recien creada.
	//O sea, esta vacia y puedo apilar elementos.
	print_test("La pila esta vacia despues de vaciarla", pila_esta_vacia(pila));

	print_test("Puedo apilar elementos despues de vaciarla", pila_apilar(pila, &a));

	print_test("Al desapilar recibo el elemento que apile despues de vaciarla", pila_desapilar(pila) == &a);

	pila_destruir(pila);
}

static void prueba_desapilar_y_ver_tope_invalidas(void){
	pila_t* pila = pila_crear();

	print_test("Desapilar invalida en pila vacia", pila_desapilar(pila) == NULL);
	print_test("Ver tope invalida en pila vacia", pila_ver_tope(pila) == NULL);

	pila_destruir(pila);
}

static void prueba_desapilar_y_ver_tope_invalidas_redimensionada(void){
	bool apilar = true;
	bool desapilar = true;
	bool tope = true;
	int arreglo[1000];

	pila_t* pila = pila_crear();

	//Apilo 1000 elementos
	for (int i = 0; i < 1000; i++){
		apilar &= pila_apilar(pila, &arreglo[i]);
		tope &= pila_ver_tope(pila) == &arreglo[i];
	}

	print_test("Apilar 1000 elementos", apilar);
	print_test("Al ver tope apilando recibo el elemento esperado las 1000 veces", tope);

	//Verifico que conservan el orden al desapilarlos
	for (int i = 999; i >= 0; i--){
		tope &= pila_ver_tope(pila) == &arreglo[i];
		desapilar &= pila_desapilar(pila) == &arreglo[i];
	}

	print_test("Los 1000 elementos conservan el orden al desapilar", desapilar);
	print_test("Al ver tope desapilando recibo el elemento esperado las 1000 veces", tope);


	//Intento utilizar desapilar y ver_tope

	print_test("Al desapilar vacia redimensionada recibo NULL", pila_desapilar(pila) == NULL);
	print_test("Al ver tope vacia redimensionada recibo NULL", pila_ver_tope(pila) == NULL);

	pila_destruir(pila);
}




void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_invariante();
    prueba_volumen();
    prueba_apilar_NULL();
    prueba_vaciar_pila();
    prueba_desapilar_y_ver_tope_invalidas();
    prueba_desapilar_y_ver_tope_invalidas_redimensionada();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif

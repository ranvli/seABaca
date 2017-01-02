// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
#pragma once
#include <iostream>
using namespace std;

// TODO: mencionar aquí los encabezados adicionales que el programa necesita
class nodo {

public:
	nodo(nodo *val, nodo *der, bool dibr)
	{
		dibujado = dibr;
		ndato = val;
		derecha = der;
	}
	nodo(nodo *val, nodo *izq, nodo *der, bool dibr)
	{
		dibujado = dibr;
		ndato = val;
		derecha = der;
		izquierda = izq;
	}
	nodo(int val, nodo *izq, nodo *der, int posXr, int posYr)
	{
		dato = val;

		derecha = der;
		izquierda = izq;
		
		posX = posXr;
		posY = posYr;
		FB = 0;

		acomodado = false;
	}
	int dato;
private:
	
	int posX;
	int posY;
	int FB;

	bool dibujado;
	bool acomodado;

	nodo *ndato;
	nodo *izquierda;
	nodo *derecha;
	nodo *raiz;

	friend class nodo;
	friend class AB;
	friend class util;
	friend class listaDoble;
	
};

class listaDoble{

public:
	listaDoble() { primerNodo = NULL; };
	void borra();

	bool ListaVacia() { return primerNodo == NULL; } 
	void borraAlInicio();
	void borraAlFinal();
	void borraPos(int pos);
	void invertirApartirDe(int pos, listaDoble &destino);
	int cantidadDeNodos();
	int getDatoEnPos(int pos);
	void insertaAlFinal(nodo * val);
	void muestraLista();
	void borraPosImpares();
	void actualizaValor(int vBus, int vNueX, int vNueY);

private:
	nodo * primerNodo;
	friend class util;
	friend class AB;
	friend class nodo;


};




//class lista{
//
//public:
//	lista() { primerNodo = NULL; }
//
//	void muestraLista();
//	bool ListaVacia() { return primerNodo == NULL; } 
//	void insertaAlFinal(nodo * val);
//	//void actualizaValor(int vBus, int vNueX, int vNueY);
//	int cantidadDeNodos();
//	
//private:
//	nodo * primerNodo;
//
//	friend class nodo;
//	friend class AB;
//	friend class util;
//	friend class lista;
//
//};



public class util{

public:
	//void reAcomoda(nodo * nodo, lista &cacheNodos, System::Windows::Forms::Panel^ p1);
	void reAcomodaRaiz(nodo * actual, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1, bool der);
	void dibujaNodo(int valor, int posX, int posY, System::Windows::Forms::Panel^ p1, System::Drawing::Pen^ pcolor);
	void dibujaArista(int x1, int y1, int x2, int y2, bool ladoDerecho, System::Windows::Forms::Panel^ p1);
	void borraNodo(int valor, int posX, int posY, System::Windows::Forms::Panel^ p1);
	void mueveNodo(int valor, int posXini, int posYini, int posXfin, int posYfin, System::Windows::Forms::Panel^ p1, listaDoble &cacheNodos);
	void dibujaCache(listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1);
	void setNoDibujado(int val, listaDoble &cacheNodos);
	void setDibujado(int val, listaDoble &cacheNodos);
	void dibujaFB(nodo * actual, System::Windows::Forms::Panel^ p1);
	//void verificaPosiciones(nodo * nuevo, lista &cacheNodos, System::Windows::Forms::Panel^ p1, bool der);
	//void reOrdena(nodo * actref, lista &cacheNodos, System::Windows::Forms::Panel^ p1);
	void reOrdena(bool lado, int vS, nodo * actref, nodo * arriba, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1);
	void reOrdena2(int dX, int dY, int inX, bool der, int inY, nodo * raiz, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1);
	void reOrdenaBorrado(int dX, int dY, int inX, bool der, int inY, nodo * raiz, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1);
	void chequeaInterPos(listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1);
	int CalculAlturArbol(AB &ArbolB, System::Windows::Forms::Panel ^p1);
	int infoNodo(AB &ArbolB, System::String^ tipo);
	nodo * util::buscaNodoMenor(nodo * nodoAc, nodo * menor);
	void refrescaPD(listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1, int delay);

	friend class nodo;
	friend class AB;
	friend class util;
	friend class listaDoble;

};

class AB{

public:
	listaDoble nueva;
	AB() : cacheNodos(nueva) { raiz = NULL;	};
	bool estaVacio(){ return raiz == NULL; };
	void insertar(int val, System::Windows::Forms::Panel^ p1);
	void InOrden(nodo * nodo, System::Windows::Forms::Panel^ p1, System::Drawing::Pen^ pcolor, listaDoble &cacheNodos, int retraso);
	void RecorreInOrden(System::Windows::Forms::Panel^ p1, int retraso);
	void PreOrden(nodo * nodo, System::Windows::Forms::Panel^ p1, System::Drawing::Pen^ pcolor, listaDoble &cacheNodos, int retraso);
	void RecorrePreOrden(System::Windows::Forms::Panel^ p1, int retraso);
	void PostOrden(nodo * nodo, System::Windows::Forms::Panel^ p1, System::Drawing::Pen^ pcolor, listaDoble &cacheNodos, int retraso);
	void RecorrePostOrden(System::Windows::Forms::Panel^ p1, int retraso);
	void setDibujado(int val);
	int calculAltura(nodo * nodo);
	void borraOrdenado(int val, System::Windows::Forms::Panel^ p1);
	void checkAVL(nodo * nodo);
	void aplicaRotacionSimple(int val, System::Windows::Forms::Panel^ p1, int delay);
	void aplicaRotacionDoble(int val, System::Windows::Forms::Panel^ p1, int delay);
	
	nodo * raiz;

private:
	
	listaDoble &cacheNodos;

	friend class nodo;
	friend class AB;
	friend class util;
	friend class listaDoble;

};


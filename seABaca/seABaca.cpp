// seABaca.cpp: archivo de proyecto principal.
#include "stdafx.h"
#include "Form1.h"

using namespace seABaca;

void AB::InOrden(nodo * nodo, Windows::Forms::Panel^ p1, Pen^ pcolor, listaDoble &cacheNodos, int retraso){


	if(nodo == NULL){
		return;
	}
	else
	{
		InOrden(nodo->izquierda, p1, pcolor, cacheNodos, retraso);
		
		Graphics^ g = p1->CreateGraphics();

		g->FillEllipse(gcnew SolidBrush(Color::Yellow), nodo->posX +1, nodo->posY +1, 24, 24);
		g->DrawString(nodo->dato.ToString(), gcnew Font("Arial", 8), gcnew SolidBrush(Color::Red), nodo->posX+5, nodo->posY+5);

		System::Threading::Thread::Sleep(retraso);
		System::Windows::Forms::Application::DoEvents();
		

		InOrden(nodo->derecha, p1, pcolor, cacheNodos, retraso);
	}

}

int util::CalculAlturArbol(AB &ArbolB, System::Windows::Forms::Panel ^p1){

	
	Graphics^ g = p1->CreateGraphics();
	g->Clear(System::Drawing::Color::DarkSeaGreen);


	util util;

	int Alt = ArbolB.calculAltura(ArbolB.raiz);

	util.dibujaCache(ArbolB.cacheNodos, p1);


	return Alt;
	
	

}

void AB::checkAVL(nodo * nac){


	nodo * ini = nac;

	if(ini == NULL){
		return;
	}
	else{
		checkAVL(ini->izquierda);
		checkAVL(ini->derecha);

		if(ini->FB < -1 || ini->FB > 1){
			
			if(ini->FB > 1) {
				String^ RL;
				if(ini->izquierda->FB >= 0) RL = "Se recomienda rotación simple";
				if(ini->izquierda->FB < 0) RL = "Se recomienda rotación doble";
				MessageBox::Show("Nodo desbalanceado hacia la izquierda : " + ini->dato.ToString() + ". " + RL);
			}

			if(ini->FB < 1){
				String^ RL;
				if(ini->derecha->FB <= 0) RL = "Se recomienda rotación simple";
				if(ini->derecha->FB > 0) RL = "Se recomienda rotación doble";
				MessageBox::Show("Nodo desbalanceado hacia la derecha : " + ini->dato.ToString() +  ". " + RL);
			}			

		}

	}


};


void AB::aplicaRotacionDoble(int val, System::Windows::Forms::Panel ^ p1, int delay){


	util util;

	//busca el nodo con el valor
	nodo * actualC = cacheNodos.primerNodo;
	while(actualC != NULL){
		if(actualC->ndato->dato == val) break;
		actualC = actualC->derecha;
	}

	if(actualC == NULL) return;
	nodo * actual = actualC->ndato;
	
	//averigua si a la derecha o izquierda
	bool der;
	if(actual->FB > 0) der = true;
	if(actual->FB < 0) der = false;

	if(actual->FB == 1 || actual->FB == 0 || actual->FB == -1){
		MessageBox::Show("No es necesario aplicar rotación a este nodo, el FB está dentro del rango permitido.");
		return;
	}

	if(der){

		if((actual->FB > 0 && actual->izquierda->FB > 0) || (actual->FB < 0 && actual->izquierda->FB < 0) ) {
			MessageBox::Show("Está tratando de aplicar una rotación doble en donde se recomienda rotación simple, cancelando");
			return;
		}

		nodo * izq = actual->izquierda;
		nodo * izqDer = actual->izquierda->derecha;

		nodo * alaIzq = izqDer->izquierda;
		nodo * alaDer = izqDer->derecha;

		if(actual != raiz && actual->raiz->derecha == actual) actual->raiz->derecha = izqDer;
		if(actual != raiz && actual->raiz->izquierda == actual) actual->raiz->izquierda = izqDer;
		if(actual == raiz) {
			raiz = izqDer;
		}

		util.refrescaPD(cacheNodos, p1, delay);

		izqDer->raiz = actual->raiz;
		util.refrescaPD(cacheNodos, p1, delay);


		int antPAX = actual->posX;
		int antPAY = actual->posY;

		//mueve nodos a nuevas posiciones
		util.setNoDibujado(actual->dato, cacheNodos);
		util.mueveNodo(actual->dato, actual->posX, actual->posY, actual->posX + 25, actual->posY + 50, p1, cacheNodos);
		util.setDibujado(actual->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(actual->dato, actual->posX + 25, actual->posY + 50);

		//mueve nodos a nuevas posiciones
		util.setNoDibujado(izqDer->dato, cacheNodos);
		util.mueveNodo(izqDer->dato, izqDer->posX, izqDer->posY, antPAX, antPAY, p1, cacheNodos);
		util.setDibujado(izqDer->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(izqDer->dato, antPAX, antPAY);
	

		izqDer->derecha = actual;
		util.refrescaPD(cacheNodos, p1, delay);


		actual->raiz = izqDer;
		util.refrescaPD(cacheNodos, p1, delay);

		izq->raiz = izqDer;
		util.refrescaPD(cacheNodos, p1, delay);

		izqDer->izquierda = izq;
		util.refrescaPD(cacheNodos, p1, delay);

		izq->derecha = alaIzq;
		if(alaIzq != NULL) alaIzq->raiz = izq;
		util.refrescaPD(cacheNodos, p1, delay);

		actual->izquierda = alaDer;
		if(alaDer != NULL) alaDer->raiz = actual;
		util.refrescaPD(cacheNodos, p1, delay);

		//acomodar el eje de las abcisas(Y) por si quedo algun nodo mas alto que su padre
		if(actual->derecha != NULL){
			if(actual->derecha->posY <= actual->posY) util.reAcomodaRaiz(actual->derecha, cacheNodos, p1, true);
		}

		if(actual->izquierda != NULL){
			if(actual->izquierda->posY <= actual->posY) util.reAcomodaRaiz(actual->izquierda, cacheNodos, p1, true);
		}

		util.reOrdenaBorrado(25, 0, actual->posX, true, actual->posY, actual, cacheNodos, p1);

		util.refrescaPD(cacheNodos, p1, 0);

		util.chequeaInterPos(cacheNodos, p1);

	}

	if(!der){

		if((actual->FB > 0 && actual->derecha->FB > 0) || (actual->FB < 0 && actual->derecha->FB < 0) ) {
			MessageBox::Show("Está tratando de aplicar una rotación doble en donde se recomienda rotación simple, cancelando");
			return;
		}

		nodo * der = actual->derecha;
		nodo * derIzq = actual->derecha->izquierda;

		nodo * alaIzq = derIzq->izquierda;
		nodo * alaDer = derIzq->derecha;

		if(actual != raiz && actual->raiz->derecha == actual) actual->raiz->derecha = derIzq;
		if(actual != raiz && actual->raiz->izquierda == actual) actual->raiz->izquierda = derIzq;
		if(actual == raiz) {
			raiz = derIzq;
		}

		util.refrescaPD(cacheNodos, p1, delay);

		derIzq->raiz = actual->raiz;
		util.refrescaPD(cacheNodos, p1, delay);


		int antPAX = actual->posX;
		int antPAY = actual->posY;

		//mueve nodos a nuevas posiciones
		util.setNoDibujado(actual->dato, cacheNodos);
		util.mueveNodo(actual->dato, actual->posX, actual->posY, actual->posX - 25, actual->posY + 50, p1, cacheNodos);
		util.setDibujado(actual->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(actual->dato, actual->posX - 25, actual->posY + 50);

		//mueve nodos a nuevas posiciones
		util.setNoDibujado(derIzq->dato, cacheNodos);
		util.mueveNodo(derIzq->dato, derIzq->posX, derIzq->posY, antPAX, antPAY, p1, cacheNodos);
		util.setDibujado(derIzq->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(derIzq->dato, antPAX, antPAY);
	

		derIzq->izquierda = actual;
		util.refrescaPD(cacheNodos, p1, delay);


		actual->raiz = derIzq;
		util.refrescaPD(cacheNodos, p1, delay);

		der->raiz = derIzq;
		util.refrescaPD(cacheNodos, p1, delay);

		derIzq->derecha = der;
		util.refrescaPD(cacheNodos, p1, delay);

		der->izquierda = alaDer;
		if(alaIzq != NULL) alaIzq->raiz = der;
		util.refrescaPD(cacheNodos, p1, delay);

		actual->derecha = alaIzq;
		if(alaDer != NULL) alaDer->raiz = actual;
		util.refrescaPD(cacheNodos, p1, delay);

		//acomodar el eje de las abcisas(Y) por si quedo algun nodo mas alto que su padre
		if(actual->derecha != NULL){
			if(actual->derecha->posY <= actual->posY) util.reAcomodaRaiz(actual->derecha, cacheNodos, p1, true);
		}

		if(actual->izquierda != NULL){
			if(actual->izquierda->posY <= actual->posY) util.reAcomodaRaiz(actual->izquierda, cacheNodos, p1, true);
		}

		util.reOrdenaBorrado(25, 0, actual->posX, true, actual->posY, actual, cacheNodos, p1);

		util.refrescaPD(cacheNodos, p1, 0);

		util.chequeaInterPos(cacheNodos, p1);
	}



};

void AB::aplicaRotacionSimple(int val, System::Windows::Forms::Panel ^ p1, int delay){



	util util;

	//busca el nodo con el valor
	nodo * actualC = cacheNodos.primerNodo;
	while(actualC != NULL){
		if(actualC->ndato->dato == val) break;
		actualC = actualC->derecha;
	}

	if(actualC == NULL) return;

	nodo * actual = actualC->ndato;
	
	//averigua si a la derecha o izquierda
	bool der;
	if(actual->FB > 0) der = true;
	if(actual->FB < 0) der = false;

	if(actual->FB == 1 || actual->FB == 0 || actual->FB == -1){
		MessageBox::Show("No es necesario aplicar rotación a este nodo, el FB está dentro del rango permitido.");
		return;
	}

	if(der){

		if((actual->FB > 0 && actual->izquierda->FB < 0) || (actual->FB < 0 && actual->izquierda->FB > 0) ) {
			MessageBox::Show("Está tratando de aplicar una rotación simple en donde se recomienda rotación doble, cancelando");
			return;
		}


		nodo * izq = actual->izquierda;
		nodo * izqDer = actual->izquierda->derecha;

		//actualiza Referencias
		//asigna al nodo  desbalanceado lo ke tenga la derecha de su izquierda
		izq->raiz = actual->raiz;
		util.refrescaPD(cacheNodos, p1, delay);

		
		if(actual != raiz && actual->raiz->izquierda == actual) actual->raiz->izquierda = izq;
		if(actual != raiz && actual->raiz->derecha == actual) actual->raiz->derecha = izq;
		if(actual == raiz) {
			raiz = izq;
		}
		util.refrescaPD(cacheNodos, p1, delay);

		actual->izquierda = izqDer;
		if (izqDer != NULL) izqDer->raiz = actual;
		util.refrescaPD(cacheNodos, p1, delay);

		//asigna a la raiz de la izquierda del nodo desbalanceao su raiz
		izq->derecha = actual;
		util.refrescaPD(cacheNodos, p1, delay);

		actual->raiz = izq;
		util.refrescaPD(cacheNodos, p1, delay);


		//mueve nodos a nuevas posiciones
		util.setNoDibujado(actual->dato, cacheNodos);
		util.mueveNodo(actual->dato, actual->posX, actual->posY, actual->posX + 25, actual->posY + 50, p1, cacheNodos);
		util.setDibujado(actual->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(actual->dato, actual->posX + 25, actual->posY + 50);
	
		util.setNoDibujado(izq->dato, cacheNodos);
		util.mueveNodo(izq->dato, izq->posX, izq->posY, izq->posX + 25, actual->posY - 50, p1, cacheNodos);
		util.setDibujado(izq->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(izq->dato, izq->posX + 25, izq->posY - 50);
		//util.reOrdena2(25, -50, izq->posX + 25, der, izq->posY, izq, cacheNodos, p1);

		//if(actual->derecha != NULL) util.reOrdenaBorrado(25, (actual->posY - actual->derecha->posY) + 25, actual->derecha->posX, der, actual->derecha->posY , actual, cacheNodos, p1);
		//if(actual->izquierda != NULL) util.reOrdenaBorrado(25, (actual->posY - actual->izquierda->posY) + 25, actual->izquierda->posX, der, actual->izquierda->posY + ((actual->posY - actual->izquierda->posY) + 25), actual->izquierda, cacheNodos, p1);

		//acomodar el eje de las abcisas(Y) por si quedo algun nodo mas alto que su padre
		if(actual->derecha != NULL){
			if(actual->derecha->posY <= actual->posY) util.reAcomodaRaiz(actual->derecha, cacheNodos, p1, true);
		}

		if(actual->izquierda != NULL){
			if(actual->izquierda->posY <= actual->posY) util.reAcomodaRaiz(actual->izquierda, cacheNodos, p1, true);
		}

		util.reOrdenaBorrado(25, 0, actual->posX, true, actual->posY, actual, cacheNodos, p1);

		util.refrescaPD(cacheNodos, p1, 0);
	
		util.chequeaInterPos(cacheNodos, p1);
	}


	if(!der){

		
		if((actual->FB > 0 && actual->derecha->FB < 0) || (actual->FB < 0 && actual->derecha->FB > 0) ) {
			MessageBox::Show("Está tratando de aplicar una rotación simple en donde se recomienda rotación doble, cancelando");
			return;
		}

		nodo * der = actual->derecha;
		nodo * derIzq = actual->derecha->izquierda;

		//actualiza Referencias
		//asigna al nodo  desbalanceado lo ke tenga la derecha de su izquierda
		der->raiz = actual->raiz;
		util.refrescaPD(cacheNodos, p1, delay);

		if(actual != raiz && actual->raiz->izquierda == actual) actual->raiz->izquierda = der;
		if(actual != raiz && actual->raiz->derecha == actual) actual->raiz->derecha = der;
		
		if(actual == raiz) {
			raiz = der;
		}

		util.refrescaPD(cacheNodos, p1, delay);

		actual->derecha = derIzq;
		if (derIzq != NULL) derIzq->raiz = actual;
		util.refrescaPD(cacheNodos, p1, delay);

		//asigna a la raiz de la izquierda del nodo desbalanceao su raiz
		der->izquierda = actual;
		util.refrescaPD(cacheNodos, p1, delay);

		actual->raiz = der;
		util.refrescaPD(cacheNodos, p1, delay);


		//mueve nodos a nuevas posiciones
		util.setNoDibujado(actual->dato, cacheNodos);
		util.mueveNodo(actual->dato, actual->posX, actual->posY, actual->posX - 25, actual->posY + 50, p1, cacheNodos);
		util.setDibujado(actual->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(actual->dato, actual->posX - 25, actual->posY + 50);
	
		util.setNoDibujado(der->dato, cacheNodos);
		util.mueveNodo(der->dato, der->posX, der->posY, der->posX - 25, actual->posY - 50, p1, cacheNodos);
		util.setDibujado(der->dato, cacheNodos);
		//actualiza posicion
		cacheNodos.actualizaValor(der->dato, der->posX - 25, der->posY - 50);
		//util.reOrdena2(25, -50, izq->posX + 25, der, izq->posY, izq, cacheNodos, p1);

		//if(actual->derecha != NULL) util.reOrdenaBorrado(25, (actual->posY - actual->derecha->posY) + 25, actual->derecha->posX, der, actual->derecha->posY , actual, cacheNodos, p1);
		//if(actual->izquierda != NULL) util.reOrdenaBorrado(25, (actual->posY - actual->izquierda->posY) + 25, actual->izquierda->posX, der, actual->izquierda->posY + ((actual->posY - actual->izquierda->posY) + 25), actual->izquierda, cacheNodos, p1);

		//acomodar el eje de las abcisas(Y) por si quedo algun nodo mas alto que su padre
		if(actual->derecha != NULL){
			if(actual->derecha->posY <= actual->posY) util.reAcomodaRaiz(actual->derecha, cacheNodos, p1, true);
		}

		if(actual->izquierda != NULL){
			if(actual->izquierda->posY <= actual->posY) util.reAcomodaRaiz(actual->izquierda, cacheNodos, p1, true);
		}

		util.reOrdenaBorrado(25, 0, actual->posX, false, actual->posY, actual, cacheNodos, p1);

		util.refrescaPD(cacheNodos, p1, 0);
	
		util.chequeaInterPos(cacheNodos, p1);
	}



};

void util::refrescaPD(listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1, int delay){


	System::Threading::Thread::Sleep(delay);

	util util;

	//refresca panel dibujo
	Graphics^ g = p1->CreateGraphics();
	g->Clear(System::Drawing::Color::DarkSeaGreen);
	util.dibujaCache(cacheNodos, p1);

};

int AB::calculAltura(nodo * nodo){


	int alt1;
	int alt2;
	int altM;

	if(nodo == NULL){
		return 0;
	}
	else
	{
		alt1 = calculAltura(nodo->izquierda);	
		alt2 = calculAltura(nodo->derecha);
		
		if(alt1 > alt2) altM = alt1;
		if(alt2 >= alt1) altM = alt2;

		nodo->FB = (alt1 + 1) - (alt2 + 1);

		return altM +1;
		
	}


};

int util::infoNodo(AB &ArbolB, String^ tipo){

	int hojas = 0;
	int nodos = 0;

	nodo * actual = ArbolB.cacheNodos.primerNodo;

	while(actual != NULL){
		if(actual->ndato->derecha == NULL && actual->ndato->izquierda == NULL) hojas++;
		nodos++;
		actual = actual->derecha;
	}
	
	if(tipo->Equals("nodos")){
		return nodos;
	}
	
	if(tipo->Equals("hojas")){
		return hojas;
	}

	return 0;

};

void AB::borraOrdenado(int val, System::Windows::Forms::Panel^ p1){

	
	nodo * actual = cacheNodos.primerNodo;

	//int pos = 1;

	util util;

	while(actual != NULL)
	{
		if(actual->ndato->dato == val)
		{
			
			//si es null ambos solo borrarlo **************************************************************
			if((actual->ndato->derecha == NULL) & (actual->ndato->izquierda == NULL))
			{
				if(actual->ndato->raiz->derecha == actual->ndato)
				{
					actual->ndato->raiz->derecha = NULL;
					//delete actual->ndato;
				}
				if(actual->ndato->raiz->izquierda == actual->ndato)
				{
					actual->ndato->raiz->izquierda = NULL;
					//delete actual->ndato;
				}

				if(val == raiz->dato) raiz = NULL;
				cacheNodos.borraPos(val);
				break;
			}
			
			//2do caso **************************************************************
			//si es null uno solo borrarlo y pasar el donde no es null.
			if((actual->ndato->derecha == NULL) && (actual->ndato->izquierda != NULL))
			{
				if(actual->ndato->raiz != NULL){
					if(actual->ndato->raiz->derecha == actual->ndato)
					{
						actual->ndato->raiz->derecha = actual->ndato->izquierda;
						actual->ndato->izquierda->raiz = actual->ndato->raiz;
					}
					if(actual->ndato->raiz->izquierda == actual->ndato)
					{
						actual->ndato->raiz->izquierda = actual->ndato->izquierda;
						actual->ndato->izquierda->raiz = actual->ndato->raiz;
					}
					util.reOrdenaBorrado(25, -25, actual->ndato->posX, true, actual->ndato->posY, actual->ndato->izquierda, cacheNodos, p1);
				}

				//si es la raiz, indicar nueva raiz
				if(val == raiz->dato) raiz = actual->ndato->izquierda;

				cacheNodos.borraPos(val);
				util.chequeaInterPos(cacheNodos, p1);
				break;
			}
			if((actual->ndato->derecha != NULL) && (actual->ndato->izquierda == NULL))
			{
				if(actual->ndato->raiz != NULL){
					if(actual->ndato->raiz->derecha == actual->ndato)
					{
						actual->ndato->raiz->derecha = actual->ndato->derecha;
						actual->ndato->derecha->raiz = actual->ndato->raiz;
						//delete actual->ndato;
					}
					if(actual->ndato->raiz->izquierda == actual->ndato)
					{
						actual->ndato->raiz->izquierda = actual->ndato->derecha;
						actual->ndato->derecha->raiz = actual->ndato->raiz;
						//delete actual->ndato;
					}
					//(margen X, margen Y, nueva pos
				}
				util.reOrdenaBorrado(25, -25, actual->ndato->posX, false, actual->ndato->posY, actual->ndato->derecha, cacheNodos, p1);
				//si es la raiz, indicar nueva raiz
				if(val == raiz->dato) raiz = actual->ndato->derecha;

				cacheNodos.borraPos(val);
				util.chequeaInterPos(cacheNodos, p1);
				break;
			}
	

			//3do caso **************************************************************
			//busca el menor de los mayores o  el mayor de los menores 
			if((actual->ndato->derecha != NULL) && (actual->ndato->izquierda != NULL))
			{
				nodo * menor = util.buscaNodoMenor(actual->ndato->derecha, actual->ndato->derecha);
				
				//MessageBox::Show(menor->dato.ToString());

				util.mueveNodo(menor->dato, menor->posX, menor->posY, actual->ndato->posX, actual->ndato->posY, p1, cacheNodos);
				cacheNodos.actualizaValor(menor->dato, actual->ndato->posX, actual->ndato->posY);

				nodo * tmpD = actual->ndato->derecha;
				nodo * tmpI = actual->ndato->izquierda;
				nodo * tmpR = actual->ndato->raiz;
				

				//la raiz del ke se borra tiene ke saber quien va a ser su nueva derecha o izquierda
				if(tmpR != NULL){
					if(tmpR->derecha == actual->ndato) {
						tmpR->derecha = menor;
					}
					if(tmpR->izquierda == actual->ndato) {
						tmpR->izquierda = menor;
					}
				}
				
				//la raiz del menor de los mayores tiene ke ser lo ke haya abajo del menor
				if(menor->raiz->derecha == menor && menor->raiz != actual->ndato) {
					menor->raiz->derecha = NULL;
					if(menor->derecha != NULL){
						menor->raiz->derecha = menor->derecha;
						menor->derecha->raiz = menor->raiz;
					}
					if(menor->izquierda != NULL) {
						menor->raiz->derecha = menor->izquierda;
						menor->izquierda->raiz = menor->raiz;
					}
				}
				if(menor->raiz->izquierda == menor && menor->raiz != actual->ndato) {
					menor->raiz->izquierda = NULL;
					if(menor->derecha != NULL){
						menor->raiz->izquierda = menor->derecha;
						menor->derecha->raiz = menor->raiz;
					}
					if(menor->izquierda != NULL){
						menor->raiz->izquierda = menor->izquierda;
						menor->izquierda->raiz = menor->raiz;
					}
				}

				//la nueva derecha e izquierda del menor
				//si no era el unico nodo a la derecha entonces asignar el nuevo
				if(tmpD != menor){
					menor->derecha = tmpD;
					tmpD->raiz = menor;
				}

				if(tmpI != menor){
					menor->izquierda = tmpI;
					tmpI->raiz = menor;
				}

				//si era el unico entonces a lado der o izq no queda el mismo..
				if(tmpD == menor) {
					if(tmpD->derecha != NULL) menor->derecha = tmpD->derecha;
					else menor->derecha = NULL;
				}

				if(tmpI == menor) {
					if(tmpI->izquierda != NULL) menor->izquierda = tmpI->izquierda;
					else menor->izquierda = NULL;
				}

				menor->raiz = tmpR;
				
				//si es la raiz, indicar nueva raiz
				if(val == raiz->dato) raiz = menor;

				cacheNodos.borraPos(val);
				util.chequeaInterPos(cacheNodos, p1);
				break;
				
			}
		
			
		}
	
		
		//pos++;
		actual = actual->derecha;
	}

	util.refrescaPD(cacheNodos, p1, 0);


};

nodo * util::buscaNodoMenor(nodo * nodoAc, nodo * menor){


	if(nodoAc == NULL){
		return menor;
	}
	else{
		menor = buscaNodoMenor(nodoAc->izquierda, menor);
		menor = buscaNodoMenor(nodoAc->derecha, menor);
		
		if(nodoAc->dato <= menor->dato) return nodoAc; 
		if(nodoAc->dato > menor->dato) return menor;
		
		
	}


}


void AB::PreOrden(nodo * nodo, Windows::Forms::Panel^ p1, Pen^ pcolor, listaDoble &cacheNodos, int retraso){


	if(nodo == NULL){
		return;
	}
	else
	{
		Graphics^ g = p1->CreateGraphics();

		g->FillEllipse(gcnew SolidBrush(Color::Yellow), nodo->posX +1, nodo->posY +1, 24, 24);
		g->DrawString(nodo->dato.ToString(), gcnew Font("Arial", 8), gcnew SolidBrush(Color::Red), nodo->posX+5, nodo->posY+5);

		System::Threading::Thread::Sleep(retraso);
		System::Windows::Forms::Application::DoEvents();
		

		PreOrden(nodo->izquierda, p1, pcolor, cacheNodos, retraso);		
		PreOrden(nodo->derecha, p1, pcolor, cacheNodos, retraso);
	}

}

void AB::PostOrden(nodo * nodo, Windows::Forms::Panel^ p1, Pen^ pcolor, listaDoble &cacheNodos, int retraso){


	

	if(nodo == NULL){
		return;
	}
	else
	{
		PostOrden(nodo->izquierda, p1, pcolor, cacheNodos, retraso);
		PostOrden(nodo->derecha, p1, pcolor, cacheNodos, retraso);

		Graphics^ g = p1->CreateGraphics();

		g->FillEllipse(gcnew SolidBrush(Color::Yellow), nodo->posX +1, nodo->posY +1, 24, 24);
		g->DrawString(nodo->dato.ToString(), gcnew Font("Arial", 8), gcnew SolidBrush(Color::Red), nodo->posX+5, nodo->posY+5);

		System::Threading::Thread::Sleep(retraso);
		System::Windows::Forms::Application::DoEvents();
		
	}

}


void AB::setDibujado(int val){


		//set nodo dibujado en el cache
		
		nodo * tmpA = cacheNodos.primerNodo;
		
		while(tmpA != NULL){
			if(tmpA->ndato->dato == val){
				tmpA->dibujado = true;
				break;
			}
			tmpA = tmpA->derecha;
		}


};



void util::setNoDibujado(int val, listaDoble &cacheNodos){


		//set nodo dibujado en el cache
		
		nodo * tmpA = cacheNodos.primerNodo;
		
		while(tmpA != NULL){
			if(tmpA->ndato->dato == val){
				tmpA->dibujado = false;
				break;
			}
			tmpA = tmpA->derecha;
		}


};

void util::setDibujado(int val, listaDoble &cacheNodos){


		//set nodo dibujado en el cache
		
		nodo * tmpA = cacheNodos.primerNodo;
		
		while(tmpA != NULL){
			if(tmpA->ndato->dato == val){
				tmpA->dibujado = true;
				break;
			}
			tmpA = tmpA->derecha;
		}


};

void AB::RecorreInOrden(System::Windows::Forms::Panel^ p, int retraso){

	
	util util;
	Graphics^ g = p->CreateGraphics();
	g->Clear(System::Drawing::Color::DarkSeaGreen);

	util.dibujaCache(cacheNodos, p);

	InOrden(raiz, p, gcnew Pen(System::Drawing::Color::Black), cacheNodos, retraso);

}

void AB::RecorrePreOrden(System::Windows::Forms::Panel^ p, int retraso){

	util util;
	Graphics^ g = p->CreateGraphics();
	g->Clear(System::Drawing::Color::DarkSeaGreen);

	util.dibujaCache(cacheNodos, p);

	PreOrden(raiz, p, gcnew Pen(System::Drawing::Color::Black), cacheNodos, retraso);

}

void AB::RecorrePostOrden(System::Windows::Forms::Panel^ p, int retraso){

	util util;
	Graphics^ g = p->CreateGraphics();
	g->Clear(System::Drawing::Color::DarkSeaGreen);

	util.dibujaCache(cacheNodos, p);

	PostOrden(raiz, p, gcnew Pen(System::Drawing::Color::Black), cacheNodos, retraso);

}

void util::chequeaInterPos(listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1){


			util util;
			bool dirDer = true;
			nodo * actCache;
			nodo * actualCache;

			//aqiu prueba aqui
			actualCache = cacheNodos.primerNodo;
			while(true){
				
				if(dirDer) actCache = cacheNodos.primerNodo;
				if(!dirDer){
					nodo * tmp = cacheNodos.primerNodo;
					while(tmp->derecha != NULL){
						tmp = tmp->derecha;
					}
					actCache = tmp;
				}
					
				while(true){
						
					if(actCache->ndato->posX >= actualCache->ndato->posX-35 && actCache->ndato->posX <= actualCache->ndato->posX+35 && actCache->ndato->posY == actualCache->ndato->posY && actCache->ndato != actualCache->ndato){
							
						//MessageBox::Show("Detectado al lado derecho : inX : " + Convert::ToString(inX) + " *** actCache->ndato->posX-24 : " + Convert::ToString(actCache->ndato->posX-24) + " ** actCache->ndato->posX+24 : " + Convert::ToString(actCache->ndato->posX+24));

						if(actCache->ndato->raiz->derecha == actCache->ndato){						
							nodo * rtmp = actCache->ndato->raiz;
							while(rtmp->raiz->derecha == rtmp){
								rtmp = rtmp->raiz;
								if(rtmp->raiz == NULL) break;
							}
							util.reOrdena2(25, 0, rtmp->posX - 50, false, rtmp->posY, rtmp, cacheNodos, p1);
						}
						if(actCache->ndato->raiz->izquierda == actCache->ndato){
							nodo * rtmp = actCache->ndato->raiz;
							while(rtmp->raiz->izquierda == rtmp){
								rtmp = rtmp->raiz;
								if(rtmp->raiz == NULL) break;
							}
							util.reOrdena2(25, 0, rtmp->posX + 50, true, rtmp->posY, rtmp, cacheNodos, p1);
						}
							
						//invierte la lista para evitar loops
						dirDer = !dirDer;
						
						//aqui volver a repasar todos
						if(dirDer){
							actualCache = cacheNodos.primerNodo;
							actCache = cacheNodos.primerNodo;
						}
						if(!dirDer){
							nodo * tmp = cacheNodos.primerNodo;
							while(tmp->derecha != NULL){
								tmp = tmp->derecha;
							}
							actualCache = tmp;
							actCache = tmp;
						}
					}
					if(dirDer) {
						actCache = actCache->derecha;
						if(actCache == NULL) break;
					}
					if(!dirDer){
						actCache = actCache->izquierda;
						if(actCache == cacheNodos.primerNodo) break;
					}
				}
				if(dirDer) {
					actualCache = actualCache->derecha;
					if(actualCache == NULL) break;
				}
				if(!dirDer){
					actualCache = actualCache->izquierda;
					if(actualCache  == cacheNodos.primerNodo) break;
				}
			}
			//fin prueba aqui

};

void listaDoble::borra(){

	nodo * actual = primerNodo;
	nodo * aux;

	while(actual != NULL){
		aux = actual;
		actual = actual->derecha;
		aux->derecha = NULL;
		aux->izquierda = NULL;
	}

	primerNodo = NULL;


};

void listaDoble::invertirApartirDe(int pos, listaDoble &destino){


	if (ListaVacia()){
		return;
	}
	else{
		
		nodo * actual = primerNodo;
		nodo * pas;
		int pac = 1;

		while(pac != pos){
			pac++;
			actual = actual->derecha;
		}


		destino.insertaAlFinal(actual);

		while(actual != primerNodo){
			actual = actual->izquierda;
			destino.insertaAlFinal(actual);
		}

	}


};

void AB::insertar(int val, System::Windows::Forms::Panel^ p1){


	nodo * actCheck = cacheNodos.primerNodo;

	while(actCheck != NULL){
		if(val == actCheck->ndato->dato){
			MessageBox::Show("Dato ya existe en el árbol");
			return;
		}
		actCheck = actCheck->derecha;
	}



	util util;
	int inX = 425;
    int inY = 25;

	int iniX = 350;
    int iniY = 25;

	if(estaVacio()){
		//inX-= 50;
		raiz = new nodo(val, NULL, NULL, inX, inY);
		raiz->raiz = NULL;
		//inY+= 50;
		cacheNodos.insertaAlFinal(raiz);

		util.mueveNodo(val, inX, inY, inX, inY, p1, cacheNodos);
		setDibujado(val);
	}
	else
	{
		nodo * actual = raiz;

		int inX = raiz->posX;
	    int inY = raiz->posY;


		while(true)
		{

			if(val > actual->dato)
			{
				if (actual->derecha == NULL)
				{
					inX+= 25;
                    inY+= 50;

					nodo * nuevo = new nodo(val, NULL, NULL, inX, inY);
					cacheNodos.insertaAlFinal(nuevo);					

					util.mueveNodo(val, inX-25, inY-50, inX, inY, p1, cacheNodos);
					setDibujado(nuevo->dato);

					actual->derecha = nuevo;
					actual->derecha->raiz = actual;

	
					util.reOrdena(false, 1, nuevo, nuevo->raiz->raiz, cacheNodos, p1);
				
					util.chequeaInterPos(cacheNodos, p1);

					util.dibujaCache(cacheNodos, p1);


					break;
				}
				
				int inxp = actual->posX;
				int inyp = actual->posY;

				actual = actual->derecha;
				
				inX+= actual->posX - inxp;
				inY+= actual->posY - inyp;
			
				util.mueveNodo(val, inxp, inyp, inX, inY, p1, cacheNodos);


			}
			
			if(val < actual->dato){
				if (actual->izquierda == NULL){

					inX-= 25;
                    inY+= 50;


					//agrega nuevo nodo
					nodo * nuevo = new nodo(val, NULL, NULL, inX, inY);
					//aqui agrega al cache
					cacheNodos.insertaAlFinal(nuevo);

					//animacion
					util.mueveNodo(val, inX+25, inY-50, inX, inY, p1, cacheNodos);
					setDibujado(nuevo->dato);

					actual->izquierda = nuevo;
					actual->izquierda->raiz = actual;

					//fin agrega
					
					util.reOrdena(true, 1, nuevo, nuevo->raiz->raiz, cacheNodos, p1);

					util.chequeaInterPos(cacheNodos, p1);
					
					util.dibujaCache(cacheNodos, p1);

					
					break;
				}
				

				int inxp = actual->posX;
				int inyp = actual->posY;

				actual = actual->izquierda;
				 
				inX-= inxp - actual->posX;
				inY+= actual->posY - inyp;
			
				util.mueveNodo(val, inxp, inyp, inX, inY, p1, cacheNodos);

			}

			//

		} //end while

	}


};

void util::reOrdena(bool derr, int vS, nodo * actref, nodo * arriba, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1){


	bool der = derr;
	if(arriba == NULL){
		return;
	}

	nodo * nuevo = actref;
	nodo * baja;

	//if(arriba->derecha != NULL){
	//	if(arriba->derecha->derecha == nuevo){
	//		return;
	//	}
	//}

	//if(arriba->izquierda != NULL){
	//	if(arriba->izquierda->izquierda == nuevo){
	//		return;
	//	}
	//}

	if(der) baja = arriba->derecha;
	if(!der) baja = arriba->izquierda;

	if(baja == NULL){
		vS++;
		reOrdena(der, vS, nuevo, arriba->raiz, cacheNodos, p1);
		return;
	}



	for(int v = vS; v > 0; v--){
		if(baja == NULL) return;	
		if(der) baja = baja->izquierda;
		if(baja == NULL) return;	
		if(!der) baja = baja->derecha;
	}


	if(baja == NULL){
		//es as:
		//x
		//  x
		//    x
		//o viceversa
		return;
	}
	
	
	if(nuevo != baja){
		//MessageBox::Show("No puede ser, error, jamas, imposible de llegar aqui.");
		//Application::Exit();
		return;
	}

	if(nuevo == baja){
		if(nuevo->posX <= arriba->posX){
			if (der) cacheNodos.actualizaValor(arriba->derecha->dato, arriba->derecha->posX +25, arriba->derecha->posY);
			if (der) reOrdena2(25, 0, arriba->derecha->posX + (25), true, arriba->derecha->posY, arriba->derecha, cacheNodos, p1);
			if (!der) cacheNodos.actualizaValor(arriba->izquierda->dato, arriba->izquierda->posX -25, arriba->izquierda->posY);
			if (!der) reOrdena2(25, 0, arriba->izquierda->posX - (25), false, arriba->izquierda->posY, arriba->izquierda, cacheNodos, p1);
			return;
		}
	}






	//if(nuevo->raiz != NULL){
	//	if(nuevo->raiz->raiz != NULL){
	//		
	//		//  x
	//		//      x
	//		//  x
	//		if(nuevo->raiz->raiz->derecha != NULL){
	//			if(nuevo->raiz->raiz->derecha->izquierda == nuevo){
	//				if(nuevo->posX <= nuevo->raiz->raiz->posX){
	//					reOrdena2(nuevo->raiz->posX +25, true, nuevo->raiz->posY, nuevo->raiz, cacheNodos, p1);
	//				}
	//			}
	//		}

	//		//      x
	//		//  x
	//		//      x		
	//		if(nuevo->raiz->raiz->izquierda != NULL){
	//			if(nuevo->raiz->raiz->izquierda->derecha == nuevo){
	//				if(nuevo->posX >= nuevo->raiz->raiz->posX){
	//					reOrdena2(nuevo->raiz->posX -25, false, nuevo->raiz->posY, nuevo->raiz, cacheNodos, p1);
	//				}
	//			}
	//		}

	//		reOrdena(nuevo->raiz, cacheNodos, p1);
	//	}
	//}



}
void util::reOrdenaBorrado(int dX, int dY, int inX, bool der, int inY, nodo * actref, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1){

	util util;
	nodo * actual;
	actual = actref;
	
	if(actual == NULL){
		return;
	}
	else{

		int posXa = actual->posX;
		int posYa = actual->posY;
		
		actual->posX = inX;
		actual->posY = inY;

		Graphics^ g = p1->CreateGraphics();
		g->Clear(System::Drawing::Color::DarkSeaGreen);

		setNoDibujado(actual->dato, cacheNodos);
		mueveNodo(actual->dato, posXa, posYa, actual->posX, actual->posY, p1, cacheNodos);
		setDibujado(actual->dato, cacheNodos);
		
		if(der){
			if(actual->izquierda != NULL) {
				cacheNodos.actualizaValor(actual->izquierda->dato, actual->izquierda->posX + dX, actual->izquierda->posY  + dY);
				reOrdenaBorrado(dX, dY, actual->posX - dX, der, actual->izquierda->posY + dY, actual->izquierda, cacheNodos, p1);
				util.reOrdena(der, 1, actual->izquierda, actual->raiz, cacheNodos, p1);
			}
			if(actual->derecha != NULL) {
				cacheNodos.actualizaValor(actual->derecha->dato, actual->derecha->posX + dX, actual->derecha->posY  + dY);
				reOrdenaBorrado(dX, dY, actual->posX + dX, der, actual->derecha->posY + dY, actual->derecha, cacheNodos, p1);
				util.reOrdena(der, 1, actual->derecha, actual->raiz, cacheNodos, p1);
			}
		}

		if(!der){
			if(actual->izquierda != NULL) {
				cacheNodos.actualizaValor(actual->izquierda->dato, actual->izquierda->posX - dX, actual->izquierda->posY  + dY);
				reOrdenaBorrado(dX, dY, actual->posX - dX, der, actual->izquierda->posY + dY, actual->izquierda, cacheNodos, p1);
				util.reOrdena(der, 1, actual->izquierda, actual->raiz, cacheNodos, p1);
			}
			if(actual->derecha != NULL) {
				cacheNodos.actualizaValor(actual->derecha->dato, actual->derecha->posX - dX, actual->derecha->posY + dY);
				reOrdenaBorrado(dX, dY, actual->posX + dX, der, actual->derecha->posY + dY, actual->derecha, cacheNodos, p1);
				util.reOrdena(der, 1, actual->derecha, actual->raiz, cacheNodos, p1);
			}
		}
	
	}

	

};

void util::reOrdena2(int dX, int dY, int inX, bool der, int inY, nodo * actref, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1){

	nodo * actual;
	actual = actref;
	
	if(actual == NULL){
		return;
	}
	else{

		int posXa = actual->posX;
		int posYa = actual->posY;
		
		actual->posX = inX;
		actual->posY = inY;

		Graphics^ g = p1->CreateGraphics();
		g->Clear(System::Drawing::Color::DarkSeaGreen);

		setNoDibujado(actual->dato, cacheNodos);
		mueveNodo(actual->dato, posXa, posYa, actual->posX, actual->posY, p1, cacheNodos);
		setDibujado(actual->dato, cacheNodos);
		
		if(der){
			if(actual->izquierda != NULL) {
				cacheNodos.actualizaValor(actual->izquierda->dato, actual->izquierda->posX + dX, actual->izquierda->posY  + dY);
				reOrdena2(dX, dY, actual->izquierda->posX + dX, der, actual->izquierda->posY + dY, actual->izquierda, cacheNodos, p1);
			}
			if(actual->derecha != NULL) {
				cacheNodos.actualizaValor(actual->derecha->dato, actual->derecha->posX + dX, actual->derecha->posY  + dY);
				reOrdena2(dX, dY, actual->derecha->posX + dX, der, actual->derecha->posY + dY, actual->derecha, cacheNodos, p1);
			}
		}

		if(!der){
			if(actual->izquierda != NULL) {
				cacheNodos.actualizaValor(actual->izquierda->dato, actual->izquierda->posX - dX, actual->izquierda->posY  + dY);
				reOrdena2(dX, dY, actual->izquierda->posX - dX, der, actual->izquierda->posY + dY, actual->izquierda, cacheNodos, p1);
			}
			if(actual->derecha != NULL) {
				cacheNodos.actualizaValor(actual->derecha->dato, actual->derecha->posX - dX, actual->derecha->posY + dY);
				reOrdena2(dX, dY, actual->derecha->posX - dX, der, actual->derecha->posY + dY, actual->derecha, cacheNodos, p1);
			}
		}
	
	}

	

};



void util::reAcomodaRaiz(nodo * actual, listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1, bool der){

	
	if(actual != NULL){

		util util;
		Graphics^ g = p1->CreateGraphics();
				
		int incX = 0;
		int incY = 50;

		if(der){
			g->Clear(System::Drawing::Color::DarkSeaGreen);
			
			actual->posX+= incX;
			actual->posY+= incY;
			util.setNoDibujado(actual->dato, cacheNodos);
			util.mueveNodo(actual->dato, actual->posX-incX, actual->posY-incY, actual->posX, actual->posY, p1, cacheNodos);
			util.setDibujado(actual->dato, cacheNodos);
			
			util.reAcomodaRaiz(actual->izquierda, cacheNodos, p1, true);
			util.reAcomodaRaiz(actual->derecha, cacheNodos, p1, true);
			
		}	
		if(!der ){
			g->Clear(System::Drawing::Color::DarkSeaGreen);

			actual->posX-= incX;
			actual->posY+= incY;					
			util.setNoDibujado(actual->dato, cacheNodos);
			util.mueveNodo(actual->dato, actual->posX+incX, actual->posY-incY, actual->posX, actual->posY, p1, cacheNodos);
			util.setDibujado(actual->dato, cacheNodos);

			util.reAcomodaRaiz(actual->izquierda, cacheNodos, p1, false);
			util.reAcomodaRaiz(actual->derecha, cacheNodos, p1, false);
		}	

		//actualiza cache
		cacheNodos.actualizaValor(actual->dato, actual->posX, actual->posY);
	}
						

}
//void util::reAcomoda(nodo * actual, lista &cacheNodos, System::Windows::Forms::Panel^ p1){
//
//		
//		util util;
//
//		
//		if(actual->raiz != NULL)
//		{
//			if(actual->raiz->raiz != NULL)
//			{
//			
//				if(actual->raiz->raiz->izquierda != NULL){
////					if(actual->raiz->raiz->izquierda->izquierda != NULL){
//
//						if(actual->raiz->izquierda == actual && actual->raiz->raiz->izquierda->izquierda != actual)
//						{
//							if(actual->raiz->raiz->izquierda->derecha != NULL)
//							{
//								//significa que es del lado izquierdo y hay ke restar x para correrlo a la izquierda
//								util.reAcomodaRaiz(actual->raiz, cacheNodos, p1, true);
//							}
//						}
//
////					}
//				}
//
//				if(actual->raiz->raiz->derecha != NULL){
////					if(actual->raiz->raiz->derecha->derecha != NULL){
//
//						if(actual->raiz->derecha == actual && actual->raiz->raiz->derecha->derecha != actual)
//						{
//							if(actual->raiz->raiz->derecha->izquierda != NULL)
//							{
//								//significa que es del lado derech y hay ke sumar x para correrlo a la derech
//								util.reAcomodaRaiz(actual->raiz, cacheNodos, p1, false);
//							}
//						}
////					}
//				}
//			}
//		
//			reAcomoda(actual->raiz, cacheNodos, p1);
//		}
//};

void util::dibujaNodo(int valor, int posX, int posY, System::Windows::Forms::Panel^ p1, Pen^ pcolor){
			 
	Graphics^ g = p1->CreateGraphics();
				 
	//x,y, ancho, alto
	

	g->DrawEllipse(pcolor, posX, posY, 25, 25);
	g->DrawString(Convert::ToString(valor), gcnew Font("Arial", 8), gcnew SolidBrush(Color::Black), posX+5, posY+5);

	


};

void util::dibujaCache(listaDoble &cacheNodos, System::Windows::Forms::Panel^ p1){


	nodo * actual = cacheNodos.primerNodo;
	util util;

	while(actual != NULL){
		if(actual->dibujado == true){
			//nodo
			util.dibujaNodo(actual->ndato->dato, actual->ndato->posX, actual->ndato->posY, p1, gcnew Pen(System::Drawing::Color::Black));
			
			//FB
			util.dibujaFB(actual, p1);

			//Aristas
			if(actual->ndato->derecha != NULL){
				util.dibujaArista(actual->ndato->posX, actual->ndato->posY, actual->ndato->derecha->posX, actual->ndato->derecha->posY, true, p1);
			}
			if(actual->ndato->izquierda != NULL){
				util.dibujaArista(actual->ndato->posX, actual->ndato->posY, actual->ndato->izquierda->posX, actual->ndato->izquierda->posY, false, p1);
			}
		}
		actual = actual->derecha;
	}


};

void util::dibujaFB(nodo * nodoA, System::Windows::Forms::Panel^ p1){


	nodo * actual = nodoA;
	
	Graphics^ g = p1->CreateGraphics();
	
	Color sem;

	if(actual->ndato->FB >= -1 && actual->ndato->FB <= 1){
		sem = Color::Blue;
	}
	if(actual->ndato->FB < -1 || actual->ndato->FB > 1){
		sem = Color::Red;
	}

	g->DrawString(actual->ndato->FB.ToString(), gcnew Font("Arial", 8), gcnew SolidBrush(sem), actual->ndato->posX + 25, actual->ndato->posY -15);



};

void util::dibujaArista(int x1, int y1, int x2, int y2, bool ladoDerecho, System::Windows::Forms::Panel^ p1){

    Graphics^ g = p1->CreateGraphics();
	Pen^ cpen = gcnew Pen(System::Drawing::Color::Red);

    if(ladoDerecho){
		g->DrawLine(cpen, x1 + 20, y1 + 25, x2 + 12, y2);
    }

    if(!ladoDerecho){
		g->DrawLine(cpen, x1 + 5, y1 + 25, x2 + 12, y2);
    }
        

};


void util::borraNodo(int valor, int posX, int posY, Windows::Forms::Panel^ p1){
			 
	Graphics^ g = p1->CreateGraphics();
	
	//x,y, ancho, alto
	g->FillEllipse(gcnew SolidBrush(Color::DarkSeaGreen), posX-1, posY-1, 27, 27);
	
};

void util::mueveNodo(int valor, int posXini, int posYini, int posXfin, int posYfin, System::Windows::Forms::Panel^ p1, listaDoble &cacheNodos){

	int xInc = posXini;
	int yInc = posYini;

	util util;
	
	do{
		//dibuja el nodo
		dibujaNodo(valor, xInc, yInc, p1, gcnew Pen(Color::Black));
		
		//espera delay
		System::Threading::Thread::Sleep(50);
		System::Windows::Forms::Application::DoEvents();
		
		//boorra el nodo
		borraNodo(valor, xInc, yInc, p1);

		
		//nuevas coordenadas
		if(xInc < posXfin) xInc+=5;
		if(xInc > posXfin) xInc-=5;

		if(yInc < posYfin) yInc+=5;
		if(yInc > posYfin) yInc-=5;

		util.dibujaCache(cacheNodos, p1);
		
	}while(xInc != posXfin || yInc != posYfin);

	dibujaNodo(valor, xInc, yInc, p1, gcnew Pen(Color::Black));
		
	//MessageBox::Show("Animaci'on completada");


};

void listaDoble::actualizaValor(int vBus, int vNueX, int vNueY){

	nodo * actual = primerNodo;

	while(actual != NULL){
		if(actual->ndato->dato == vBus) {
			actual->ndato->posX = vNueX;
			actual->ndato->posY = vNueY;
			break;
		}
		actual = actual->derecha;
	}


};

//void lista::insertaAlFinal(nodo * val){
//
//	if (ListaVacia()){
//		primerNodo = new nodo(val, NULL, false);
//	}
//	else{
//		nodo * actual = primerNodo;
//		while(actual->derecha != NULL){ actual = actual->derecha; };
//		actual->derecha = new nodo(val, NULL, false);
//	}
//
//};

int listaDoble::getDatoEnPos(int pos){


	if (ListaVacia()){
		return NULL;
	}
	else{
		
		nodo * actual = primerNodo;
		int pac = 1;

		while(pac != pos){
			pac++;
			actual = actual->derecha;
		}

		if(actual != NULL) { return actual->dato; };
		if(actual == NULL) { return NULL; };
	}

	return 0;

}
int listaDoble::cantidadDeNodos(){

	nodo * actual = primerNodo;
	int cant = 1;

	if (ListaVacia()) return 0;

	while(actual->derecha != NULL) {
		actual = actual->derecha;
		cant++;
	}

	return cant;

}
void listaDoble::borraPos(int pos){

	if (ListaVacia()){
		return;
	}
	else{
		
		/*if(pos == 1){
			borraAlInicio();
			return;
		}*/

		nodo * actual = primerNodo;
		nodo * pas = NULL;
		//int pac = 1;

		if(actual->ndato->dato == pos){
			primerNodo = actual->derecha;
			delete actual;
			return;
		}

		while(actual->ndato->dato != pos){
			//pac++;
			pas = actual;
			actual = actual->derecha;
		}

		pas->derecha = actual->derecha;
		if(actual->derecha != NULL) actual->derecha->izquierda = pas;
 		delete actual;
		
	}


}
void listaDoble::borraAlInicio(){

	if(ListaVacia()){
		return;
	}
	else{
		nodo * tmp = primerNodo;
		primerNodo = primerNodo->derecha;
		primerNodo->izquierda = NULL;
		delete tmp;
	}


}
void listaDoble::borraAlFinal(){

	if(ListaVacia()){
		return;
	}
	else{
		nodo * actual = primerNodo;

		while(actual->derecha != NULL){
			actual = actual->derecha;
		}
		
		actual->izquierda->derecha = NULL;
		delete actual;

	}


}



void listaDoble::muestraLista(){

	nodo * actual = primerNodo;

	while(actual != NULL){
		cout << "Dato : " << actual->dato << endl;
		actual = actual->derecha;
	}


}

void listaDoble::insertaAlFinal(nodo * val){


	if (ListaVacia()){
		primerNodo = new nodo(val, NULL, false);
	}
	else{
		
		nodo * actual = primerNodo;

		while(actual->derecha != NULL){
			actual = actual->derecha;
		}

		actual->derecha = new nodo(val, actual, NULL, false);
	}







}




//void lista::muestraLista(){
//
//	nodo * actual = primerNodo;
//
//	while(actual != NULL){
//		cout << "Dato : " << actual->dato << endl;
//		actual = actual->derecha;
//	}
//
//
//};

//int lista::cantidadDeNodos(){
//
//	nodo * actual = primerNodo;
//	int cant = 1;
//
//	if (ListaVacia()) return 0;
//
//	while(actual->derecha != NULL) {
//		actual = actual->derecha;
//		cant++;
//	}
//
//	return cant;
//
//};



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Habilitar los efectos visuales de Windows XP antes de crear ningún control
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Crear la ventana principal y ejecutarla
	Application::Run(gcnew Form1());
	return 0;
}




#include "gtest/gtest.h"
#include "../HUFFMAN.h"


namespace std{
TEST(HUFFMANtest, generarCodigos) {
	list<NodoArbol*> hojas;
		Arbol * huff = new Arbol();
		Caracter chars[256];

		for (int i = 0 ; i < 256 ; i++){
			chars[i].longitud = 0;
		}

		for(int i = 65 ; i < 95 ; i++){
			NodoArbol * nuevoNodo = new NodoArbol(i*3,i);

			hojas.push_back(nuevoNodo);
		}

		 for (std::list<NodoArbol*>::iterator it=hojas.begin(); it != hojas.end(); ++it)
		    std::cout << ' ' << (*it)->getPeso();

		 huff->ArmarArbol(hojas);

		 huff->generarCodigos(chars);

		 cout << endl;
		 for (int i = 0 ; i < 256 ; i++){
			 if(chars[i].longitud != 0 ){
				cout << (char)i << " Codigo: ";
		 		for (int j = 0 ; j < chars[i].longitud ; j++)
		 			cout << chars[i].cod[j];
		 		cout << endl;
			 }
		 }
}
}

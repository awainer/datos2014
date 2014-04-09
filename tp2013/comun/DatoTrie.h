#ifndef DATOTRIE_H
#define DATOTRIE_H

class NodoTrie;

class DatoTrie {
private:
	char caracter;
	NodoTrie * ptrNodoHijo;	

public:
	DatoTrie(const char caracter, NodoTrie * ptrNodoHijo);
	char getCaracter();
	NodoTrie * getPtrNodoHijo();	
	~DatoTrie();

};

#endif // DATOTRIE_H

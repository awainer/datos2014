#ifndef MIPARSER_H
#define MIPARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>

class MiParser {
private:
	std::string MiBuffer;
	std::set<char> delimitadores;
	
	//metodos privados
	std::string obtenerTerminoParcial(bool & hayDelimitadores, unsigned & longCad);
	
public:
	MiParser(std::string configParser);
	
	void parsearBuffer(std::string buffer, std::list<std::string>& terminos);
	std::string getResto();
	void vaciarBuffer();
	
	~MiParser();

};

#endif // MIPARSER_H

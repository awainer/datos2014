#include "MiParser.h"
#define NULLCHAR ' '

MiParser::MiParser(std::string configParser) {
	std::ifstream fdDelim(configParser.data(), std::ifstream::in);
	
	if (fdDelim.good()) {
		char unChar;
		while ((unChar = fdDelim.get()) && (fdDelim.good()))
			delimitadores.insert(unChar);
		fdDelim.close();
	} else 
		std::cout << "Error: Archivo " << configParser << " no encontrado.\n";
}

void MiParser::parsearBuffer(std::string buffer, std::list<std::string>& terminos) {
	MiBuffer.append(buffer);
	bool hayDelimitadores = true;
	
	while (!MiBuffer.empty() && hayDelimitadores) {
		unsigned longCad = 0;
		std::string cadena(obtenerTerminoParcial(hayDelimitadores, longCad));
		
		if (hayDelimitadores) {
			// agrego el termino solo si es completo
			terminos.push_back(cadena);
			unsigned longBuff = MiBuffer.length();
			
			//elimino la cadena agregada del buffer
			if (longCad <= longBuff) 
				MiBuffer.assign(MiBuffer.substr(longCad, longBuff - longCad));
		}
	}
}

std::string MiParser::getResto() {
	return MiBuffer;
}

void MiParser::vaciarBuffer() {
	MiBuffer.clear();
}

MiParser::~MiParser() {
	MiBuffer.clear();
	delimitadores.clear();
}

// metodos privados
std::string MiParser::obtenerTerminoParcial(bool & hayDelimitadores, unsigned & longCad) {
	char caracter;
	std::string cadena;
	bool esFinCadena = false;
	
	unsigned cursor = 0;
	while ((cursor < MiBuffer.length()) && (!esFinCadena)) {
		caracter = MiBuffer.at(cursor);
		
		if ((delimitadores.find(caracter) != delimitadores.end()) ||		
			(caracter < NULLCHAR)) {
			// esto es por si hay dos delimitadores juntos
			if (!cadena.empty())
				esFinCadena = true;
		} else
			cadena.append(1, caracter);
		
		++cursor;
	}
	
	if (!esFinCadena)
		hayDelimitadores = false;
	
	longCad = cursor;
	return cadena;
}

#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <cstdio>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#define NULLCHAR ' '

// para que cargue todos los archivos sin importar la extension ".*"
inline void recolectarRutasArch(std::string path, std::string ext, std::list<std::string>& dirs) {
	DIR * directorio;
	static struct dirent * miDirent;
	if ((directorio = opendir(path.c_str())) != NULL) {
		while ((miDirent = readdir(directorio)) != NULL) {
			if (std::string(miDirent->d_name) != "." &&
				std::string(miDirent->d_name) != "..") {
				std::string ruta(path + miDirent->d_name);
				struct stat structura;
				if (stat(ruta.c_str(), &structura) >= 0) {
					if (!S_ISDIR(structura.st_mode)) {
						if ((ext.compare(".*") == 0) ||
							(ruta.find(ext, 0) != std::string::npos))
							dirs.push_back(ruta);
					} else
						recolectarRutasArch(std::string(ruta + '/'), ext, dirs);
				}
			}
		}
		closedir(directorio);
	}
}

inline std::string getNombreArchivo(std::string dirDoc) {
	unsigned a = dirDoc.find_last_of("/") + 1;
	return dirDoc.substr(a, dirDoc.find_last_of(".") - a);
}

inline std::string getTime() {
	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo = localtime(&rawtime);
	return std::string(asctime(timeinfo));
}

// elimina el archivo indicado
inline void eliminarArchivo(std::string archivo) {
	if (std::remove(archivo.data()) != 0)
		std::cout << "Error al eliminar archivo " << archivo << std::endl;
}

// elimina todos los archivos de una carpeta
inline void eliminarArchivosDe(std::string dir) {
	std::list<std::string> directorios;
	recolectarRutasArch(dir, ".*",directorios);
	std::list<std::string>::iterator itDirs = directorios.begin();
	for (; itDirs != directorios.end(); itDirs++)
		eliminarArchivo((*itDirs));
}

// crea una carpeta en el directorio actual
inline std::string crearCarpeta(std::string nombreCarpeta) {
	std::string carpeta("./");
	carpeta.append(nombreCarpeta);
	if (mkdir(carpeta.data(), 0755) != 0)
		std::cout << "Aviso: El directorio " << carpeta << " ya existe.\n";
	carpeta.append("/");
	return carpeta;
}

inline std::string numeroACadena(unsigned numero) {
	char cadena[10];
	memset(cadena, '\0', 10);
	sprintf(cadena,"%u",numero);
	return std::string(cadena);
}

inline std::string formarPath(std::string path, std::string nombre,
unsigned var, std::string ext) {
	std::string directorio(path);
	directorio.append(nombre);
	directorio.append("[");
	directorio.append(numeroACadena(var));
	directorio.append("]");
	directorio.append(ext);
	return directorio;
}

inline std::string formarPath(std::string path, std::string nombre,
std::string ext) {
	std::string directorio(path);
	directorio.append(nombre);
	directorio.append(ext);
	return directorio;
}

inline bool esNumerico(std::string & numero) {
	bool numerico = false;
	if (!numero.empty()) {
		numerico = true;
		unsigned x = 0;
		while ((x < numero.length()) && (numerico)) {
			if ((numero.at(x) < '0') ||
				(numero.at(x) > '9'))
				numerico = false;
			++x;
		}
	}
	return numerico;
}

inline std::string pasarAMinusculas(std::string & palabra) {
	std::string enMinusculas;
	unsigned index = 0;
	while (index < palabra.length()) {
		enMinusculas.append(1, palabra.at(index));
		if ((palabra.at(index) >= 'A') && (palabra.at(index) <= 'Z'))
			enMinusculas.replace(index, 1, 1, palabra.at(index) + ' ');
		++index;
	}
	
	return enMinusculas;
}


/*inline bool compOrdenAlfa(std::string s1, std::string s2) {
	unsigned x = 0;
	if (s1.length() > s2.length()) {
		while (x < s2.length() && s1.at(x) == s2.at(x)) {x++;}
	} else {
		while (x < s1.length() && s1.at(x) == s2.at(x)) {x++;}
	}
	if (x < s1.length() && x < s2.length())
		return s1.at(x) < s2.at(x);
	else
		return true;
}*/

#endif // UTILS_H

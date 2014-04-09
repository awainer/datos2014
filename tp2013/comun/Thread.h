#ifndef THREAD_H
#define THREAD_H
#include <iostream>
#include <pthread.h>

class Thread {
private:
    pthread_t ptrThread;
    
	// debe implementarse para indicar la accion a realizar por la clase 
	// concreta de thread
    virtual void ejecutarThread() = 0;
	
	// metodo static para la creacion del thread
    static void * accionThread(void * ptrParametro) {
        Thread * ptrThread = (Thread *) ptrParametro;
        ptrThread -> ejecutarThread();
        return ptrThread;
    }
        
public:
	// permite iniciar el thread para realizar la accion descrita en ejecutar
    int iniciarThread();

	// finaliza el thread esperando que el mismo termine
    virtual void finalizarThread();
	
	// devuelve el thread
    pthread_t getPtrThread();
};

#endif // THREAD_H


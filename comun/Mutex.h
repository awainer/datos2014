#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>

class Mutex {
private:
    pthread_mutex_t mutex;
	
public:
	// crea una instancia mutex
    Mutex();
	
	// permite el lock del mutex 
	void lockMutex();
	
	// permite quitar el lock del mutex
	void unlockMutex();
	
	// elimina la instancia de mutex
    ~Mutex();
};

#endif // MUTEX_H

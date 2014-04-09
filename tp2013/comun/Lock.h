#ifndef LOCK_H
#define LOCK_H
#include "Mutex.h"

class Lock {
private:
    Mutex & mutex;
	
public:
	// realiza la funcion lock del mutex indicado
    Lock(Mutex & mutex);
	
	// libera el mutex lockeado en el constructor
    ~Lock();
};

#endif // LOCK_H

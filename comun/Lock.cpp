#include "Lock.h"

Lock::Lock(Mutex & mutex) : mutex(mutex) {
	mutex.lockMutex();
}

Lock::~Lock() {
	mutex.unlockMutex();
}

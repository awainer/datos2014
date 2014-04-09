#include "Mutex.h"

Mutex::Mutex() {
	pthread_mutex_init(&mutex, NULL);
}

void Mutex::lockMutex() {
	pthread_mutex_lock(&mutex);
}

void Mutex::unlockMutex() {
	pthread_mutex_unlock(&mutex);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&mutex);
}

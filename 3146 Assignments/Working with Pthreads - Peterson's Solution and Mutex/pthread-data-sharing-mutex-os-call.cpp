#include <iostream>
#include <pthread.h>
#include <stdlib.h>

#define TOTAL_THREADS 4

int count;
pthread_mutex_t mutex; // Mutex variable

void *myFunction(void *arg) {
    int actual_arg = *((int *)arg);

    for (unsigned int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex); // Acquire the lock

        // Beginning of the critical region
        count++;
        std::cout << "Thread #" << actual_arg << " count = " << count << std::endl;
        // End of the critical region

        pthread_mutex_unlock(&mutex); // Release the lock

        // Random wait - This code is just to ensure that the threads
        // show data sharing problems
        int max = rand() % 100000;
        for (int x = 0; x < max; x++)
            ;

        // End of random wait code
    }

    pthread_exit(NULL);
}

int main() {
    int rc[TOTAL_THREADS];
    pthread_t ids[TOTAL_THREADS];
    int args[TOTAL_THREADS];

    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    count = 0;
    for (unsigned int i = 0; i < TOTAL_THREADS; ++i) {
        args[i] = i;
        rc[i] = pthread_create(&ids[i], NULL, myFunction, (void *)&args[i]);
    }

    for (unsigned int i = 0; i < TOTAL_THREADS; ++i) {
        pthread_join(ids[i], NULL);
    }

    std::cout << "Final count = " << count << std::endl;

    pthread_mutex_destroy(&mutex); // Destroy the mutex

    pthread_exit(NULL);
}

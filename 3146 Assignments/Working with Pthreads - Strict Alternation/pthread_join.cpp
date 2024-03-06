#include <iostream>
#include <pthread.h>

int count = 0;

// This function implements the code that is
// executed by the thread.
void* myFunction(void* arg) {
    int actual_arg = *((int*) arg);
    
    for(unsigned int i = 0; i < 10; ++i) {
        count++;
        std::cout << "Thread #" << actual_arg << " count = " << count << std::endl;
    }
    
    pthread_exit(NULL);
}

// This program creates one thread, waits for it
// to finish its job and exits.
int main() {
    int rc;
    pthread_t the_thread;
    int arg = 1;   // Data being passed to the thread

    // Create a new thread
    rc = pthread_create(&the_thread, NULL, myFunction, (void*) &arg);
    
    // Check if thread creation was successful
    if (rc) {
        std::cerr << "Error: Unable to create thread, " << rc << std::endl;
        exit(-1);
    }

    // Wait for the thread to finish its job
    rc = pthread_join(the_thread, NULL);
    if (rc) {
        std::cerr << "Error: Unable to join thread, " << rc << std::endl;
        exit(-1);
    }

    std::cout << "Thread #" << arg << " done!" << std::endl;
    std::cout << "Final count = " << count << std::endl;
   
    return 0;
}

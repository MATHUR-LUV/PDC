#include <stdio.h>
#include <pthread.h>


void *myThread(void *arg){
    printf("thread is running");
    pthread_exit((void*) "Thread finished");
    
}
int main(){
    pthread_t thread;

    void * exit_status;

    pthread_create(&thread, NULL, myThread, Null);
    pthread_join(thread, &exit_status);

    printf("Thread exited with message %s \n", (char*)exit_status);
    return 0;
}

// gcc -lpthread q2.c
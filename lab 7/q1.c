#include <stdio.h>
#include <pthread.h>


void *myThread(void *arg){
    printf("Hello from new thread");
    return NULL;
}
int main(){
    pthread_t thread;
    pthread_create(&thread, NULL, myThread, Null);
    pthread_join(thread, NULL);

    return 0;
}

// gcc -lpthread q1.c
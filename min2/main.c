// This is a program that uses threads to calculate the sum of all the numbers stored in a 3d array. It uses semopheres for the threads
//to take turns as sum is a shared varaible. Without the use of semopheres the sum is different each time we run the program.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //library that allows us to use threads 

int number_of_threads = 5; 
long sum=0;
pthread_mutex_t wait; //when waiting its down when you are done its up

int ar[100][100][20];

//this is a function to fill the 3d array. 
void fill_ar (){
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            for(int k=0; k<20; k++){
                ar[i][j][k]=i+j+k;
            }
        }
    }

}

// this is the sumfunction that calculates the sum of the array 
void *sum_ig (void *tid)
{
    long ti; 
    ti= (long) tid; //turning it back to an long 
    for(int i=(ti)*20; i<(ti+1)*20-1; i++){
          for(int j=0; j<100; j++){
                for(int k=0; k<20; k++){
                    pthread_mutex_lock(&wait); //checks if any other thread is using thread 
                    sum=ar[i][j][k]+sum; // addingg the values of the array
                    pthread_mutex_unlock(&wait); //imdicates sum is free to be used 
                }
          }

    }

}

int main()
{
    fill_ar();
    pthread_t threads[number_of_threads]; //creating 5 threads
    pthread_mutex_init(&wait,0); //
    int status;
    long i;
    //loop to create 5 threads 
    for (i=0; i< number_of_threads; i++){
        printf("main here. creating threads %ld \n",i);
        status= pthread_create(&threads[i], NULL, sum_ig, (void*)i);

        if (status != 0){
            printf("Oops, pthread_create returned error code %d \n", status);
            exit(-1);
        }
    }
    
    //loops to see if all threads are done finished 
    for (long i = 0; i < number_of_threads; i++) {
        pthread_join(threads[i], NULL); //waits for all the threads to complete their addition 
    }
    pthread_mutex_destroy(&wait);
    printf("\n sum= %ld \n", sum); //prints the final sum


}
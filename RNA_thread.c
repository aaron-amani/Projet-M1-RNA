#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include "perceptron.h"


/**
 * RNA_thread.c
 * Fichier qui execute deux RNA de fonction différente avec des threads concurrentes
 * auteur : Aaron Amani et Wilhem Liban
 */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int x[4][2] = {{0,0},{0,1},{1,0},{1,1}};
double w[4][2];
double b[4];
int m = 2;
double pas = 0.01;


void initPoid(){
    // Initialisation en mettant des poid et biais aléatoire entre 0 et 1
    srand( time( NULL ) );
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 2; j++){
            
            w[i][j]= rand() % 100;
        }
    }
    for (int i = 0; i < 4; i++){
        
        b[i] = rand() % 100;
    }
}

void traitement(int y[4]){

    double sommeL=0;

    printf("Input :");

    for (int i = 0; i < 4 ; i++) {
        printf("[");
        for (int j = 0; j < 2 ; j++) {
            printf(" %d ",x[i][j]);
        }
        printf("] ");
    }
    printf("\n");

    printf("Output : [");
    for (int i = 0; i < 4 ; i++) {
        int *sortie=perceptron(x[i],w[i],&b[i],y[i],pas);
        int y = sortie[0];
        printf(" %d ",y);
        sommeL += sortie[1];
        }
    printf("]\n");

    printf("nb iterations  = %f \n",sommeL);
    printf("nb iterations en moyenne par perceptrons  = %f \n",sommeL/4);

}

int test(int y[4],int nbtest){

    int x1; //variable aléatoire entre 0 ou 1
    int x2; //variable aléatoire entre 0 ou 1
    int i; // indice sauvegardé pour selectionné les bon poids et biais 
    int valid=0;
    int testok=0; //valeur determinant des test validé

    // on va effectuer une certain nombre de test et afficher si on a validé ou pas 
    for (int j = 0; j < nbtest; j++){
        
        x1 = rand() % 2; 
        x2 = rand() % 2; 
        printf("  Valeur de x1 : %d\n",x1);
        printf("  Valeur de x2 : %d\n",x2);
        
        while(valid!=1){
            for (i = 0; i < 4 || valid!=1 ; i++){
                if(x1==x[i][0] && x2==x[i][1]){
                    valid=1;
                    break;
                }
            }
        }

        double y_pred = propagation(x[i],w[i],b[i]);

        printf("  Valeur du y predi : %f\n",y_pred);
        printf("  Valeur du y attendu : %d\n",y[i]);

        if(y_pred == y[i]){
            printf("  Test Reussi\n\n");
            testok++;
        }
        else{
            printf("  Test Non Reussi\n\n");
        }
    }
    return testok;
}

/**
 * @brief Fonction qui simule une RNA implementant la fonction AND
 * donc il y 4 perceptron retournant les valeur de y attendues avec la moyenne des Log loss
 * 
 * @param arg 
 * @return void*
 */
void* RNA_AND();

/**
 * @brief Fonction qui simule une RNA implementant la fonction XOR
 * donc il y 4 perceptron retournant les valeur de y attendues avec la moyenne des Log loss
 * 
 * @param arg 
 * @return void* 
 */
void* RNA_XOR();

int main(int argc, char* argv []) {
    void * tabFx[2];
    tabFx[0]= RNA_AND;
    tabFx[1]= RNA_XOR;

    pthread_t fils1,fils2; 
    
    if ( pthread_create ( &fils1 , NULL , tabFx[0] , NULL )) {
        perror ( " pthread_create RNA AND  ") ; 
    }
    
    if ( pthread_create ( &fils2 , NULL , tabFx[1] , NULL )) { 
        perror ( " pthread_create RNA_XOR ") ; 
    }

    if ( pthread_join (fils1, NULL )) {
        perror ( " pthread_join RNA AND ") ;
        return EXIT_FAILURE;
    }

    if (pthread_join(fils2,NULL)) { 
        perror("pthread_join RNA_XOR ");
        return EXIT_FAILURE;
    } 

    printf ( " Sortie du main \n") ; 
    pthread_exit (0) ;  
} 

/**
 * @brief Fonction qui simule une RNA implementant la fonction AND
 * donc il y 4 perceptron retournant les valeur de y attendues avec la moyenne des Log loss
 * 
 */
void* RNA_AND(){
    pthread_mutex_lock(&mutex);


    int y[4] = {0,0,0,1};
    initPoid();
    printf("------------------------\n");
    printf("-- RNA AND --\n\n");
    printf("RNA AND : Apprentissage En Cours.. \n");
    traitement(y);
    printf("RNA AND : Apprentissage FINI \n\n");
    printf("RNA AND : Test En Cours.. \n");
    if (test(y,4)==4)
        printf("RNA AND : Testé et Validé \n\n");
    else
        printf("RNA AND : Testé et Non Validé \n\n");
    printf("RNA AND : Test FINI \n");
    printf("------------------------\n");


    pthread_mutex_unlock(&mutex);

    pthread_exit(0); 
}

/**
 * @brief Fonction qui simule une RNA implementant la fonction XOR
 * donc il y 4 perceptron retournant les valeur de y attendues avec la moyenne des Log loss
 * 
 */
void* RNA_XOR(){
    pthread_mutex_lock(&mutex);


    int y[4] = {0,1,1,0};
    initPoid();
    printf("------------------------\n");
    printf("-- RNA XOR --\n\n");
    printf("RNA XOR : Apprentissage En Cours.. \n");
    traitement(y);
    printf("RNA XOR : Apprentissage FINI \n\n");
    printf("RNA XOR : Test En Cours.. \n");
    if (test(y,4)==4)
        printf("RNA XOR : Testé et Validé \n\n");
    else
        printf("RNA XOR : Testé et Non Validé \n\n");
    printf("RNA XOR : Test FINI \n");
    printf("------------------------\n");


    pthread_mutex_unlock(&mutex);

    pthread_exit(0); 
}



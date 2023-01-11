#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include "perceptron.h"


/**
 * Perceptron.c
 * auteur : Aaron Amani et Wilhem Liban
 */

/**
 * @brief Fonction Linéaire 
 * 
 * @param x : int tableau d'entrée
 * @param w : double tableau des poids
 * @param b : double valeur du biais
 * @return double sortie z 
 */
double fonction_lineaire(int x[2],double w[2],double b){
    return (w[0]*x[0])+(w[1]*x[1])+b;
}

/**
 * @brief Fonction Sigmoïde qui determinera la frontiere de décision 
 * 
 * @param z : double (sera la sortie de la fonction linéaire)
 * @return : double y 
 */
double fonction_sigmoide(double z){
    return (1/(1 + exp(-z))) ;
}

/**
 * @brief Dans la propagation, nous allons determiné la valeur a predire :
 * On prend la valeur de fonction liénaire, on le met a l'entrée de la fonction sigmoïde, 
 * en fonction de la sortie nous retournont soit 1 ou 0
 * 
 * @param x : tableau d'entrée
 * @param w : tableau des poids
 * @param b : valeur du biais
 * @return valeur a prédire (y)
 */
double propagation(int x[2],double w[2],double b){
    double z = fonction_lineaire(x,w,b);

    if (fonction_sigmoide(z) > 0)
        return 1;
    else 
        return 0;
}

/**
 * @brief Fonction cout: permet de quantifier les erreurs effectuées par le perceptron
 * 
 * @param y 
 * @return double 
 */
double fonction_cout(double y, int x[2],double *w, double b){

    double z = fonction_lineaire(x,w,b);
    double a = fonction_sigmoide(z);
  
    return -((y*log(a))+((1-y)*log(1-a)));
}

/**
 * @brief fonction qui fait la déscente de gradient pour les poids
 * 
 * @param w poid 
 * @param pas pas d'apprentissage 
 * @param x entrée 
 * @param y_pred sortie predit 
 * @param y sortie attendu
 * @return nouveaux poids
 */
void update_w(double *w, double pas, double x, double y_pred, double y){
    *w = *w + (y-y_pred)*pas*x ;
}

/**
 * @brief fonction qui fait la déscente de gradient pour b
 * 
 * @param b biais
 * @param pas pas d'apprentissage 
 * @param y_pred sortie predit 
 * @param y sortie attendu
 * @return nouveaux poids
 */
void update_b(double *b, double pas, double y_pred, double y){
    *b = *b + (y-y_pred)*pas ;
}

/**
 * @brief fonction qui effectue les traitement du perceptron
 * 
 * @param x entrée
 * @param w poids
 * @param b biais 
 * @param y sortie attendu
 * @param pas pas d'apprentissage
 * @return pointeur contenent l'adresse d'un tableau afin de sortir la sortie trouvé et sortir la valeur du log loss
 */
int *perceptron(int x[2],double *w, double *b, int y, double pas){

    int *sortie=malloc(2*sizeof(int));
    sortie[1]=0;
    int erreur=0;
    double z=0;
    double a=0;
    int y_pred = 0;

    //on effectue le model et si la sortie n'est pas celle qu'on attend on fait la descente de gradient et on re-itere
          
    do{

        z = fonction_lineaire(x,w,*b);
        a = fonction_sigmoide(z);
        y_pred = propagation(x,w,*b);


        if(y_pred != y){
            erreur++;
            // Decente de gradient de w
            for (int i = 0; i < 2; i++){
                update_w((w+i),pas,x[i],y_pred,y);
                //printf("w = %lf \n",w[i]); 
            }
            update_b(b,pas,y_pred,y);
            //printf("b = %lf \n",b); 
        }
        
    }while(y_pred != y);

    //printf("L = %f \n",L);
    sortie[1]=erreur;
    sortie[0]=y_pred;
    return sortie;
}

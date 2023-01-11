
#ifndef PERCEPTRON_H_ /* L'écriture ici présente n'est pas universelle */
#define PERCEPTRON_H_ /* Edit suite aux corrections des posts suivants -> */
/*Il est conseillé d'utiliser MON_FICHIER : pas de underscore au début */
 
 /**
 * Perceptron.h
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
double fonction_lineaire(int x[2],double w[2],double b);
/**
 * @brief Fonction Sigmoïde qui determinera la frontiere de décision 
 * 
 * @param z : double (sera la sortie de la fonction linéaire)
 * @return : double y 
 */
double fonction_sigmoide(double z);
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
double propagation(int x[2],double w[2],double b);
/**
 * @brief Fonction cout: permet de quantifier les erreurs effectuées par le perceptron
 * 
 * @param y 
 * @return double 
 */
double fonction_cout(double y, int x[2],double w[2], double b);
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
void update_w(double *w, double pas, double x, double y_pred, double y);
/**
 * @brief fonction qui fait la déscente de gradient pour b
 * 
 * @param b biais
 * @param pas pas d'apprentissage 
 * @param y_pred sortie predit 
 * @param y sortie attendu
 * @return nouveaux poids
 */
void update_b(double *b, double pas, double y_pred, double y);
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
int *perceptron(int x[2],double *w, double *b, int y, double pas);

#endif
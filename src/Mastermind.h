#define SIZE 4 							//Taille des tableaux pour le joueur et la combinaison à trouver 
#include <stdio.h>						//Inclusion des librairies necessaires
#include <time.h>
#include <stdlib.h>
#include <string.h>
//#include "Mastermind.h"

struct Plateau  						//Declaration d'une structure representant le jeu
{    
     char combinaison_rand[SIZE] ;		//Tableau contenant la combinaison aléatoire des 4 lettres
     int tentatives_max ;				//Nombres de tentaives maximales (10)
     signed int resultat ;				//Resultat correspondant au joueur (Gagné ou perdu)
     int nb_tentatives ;				//Variable stockant le nombre d'essais effectués par le joueur
     int coups_restants;				//Variable stockant le nombre de coups restants de l'utilisateur
     int Partie_gagnee;					//Declaration de la variable Partie Gagnee 0 : Partie non gagnee, 1 : Partie gagnee
};

typedef struct Plateau plateau ; 

struct Joueur							//Declaration d'une structure representant le joueur
{
    char combinaison_joueur[SIZE] ;		//Tableau contenant les proposition du joueur		
    int nb_bien_places ;				//Variable stockant le nombre de lettre bien placées
    int nb_mal_places ;					//Variable stokant le nombre de lettres mal placées
    FILE *fichier;
};

typedef struct Joueur joueur ; 


void Saisie_Joueur(joueur *p_joueur);												//Prototype de la fonction de saisie par le joueur
void Combi_Secrete(plateau *p_plateau, int taille, char min, char max); 			//Prototype de la fonction créant la combinaison secrète 
int Comparaison_Combinaison(joueur *p_joueur, plateau *p_plateau, int taille);  	//Prototype de la fonction comparant la combinaison secrete à la combinaison entree par le joueur
int Saisie_Securisee(joueur *p_joueur, int taille);									//Protoype de la fonction permettant une saisie securisee par le joueur
void Affichage_Fin_Partie(plateau *p_plateau);										//Prototype de la fonction permettant l'affichage de fin de partie
void Jeu(plateau p_plateau,joueur p_joueur,FILE *fichier);									//Prototype de la fonction lancant le jeu et regroupant les fonction precedentes
int Menu(void);																		//Prototype de la fonction affichant le menu
void Regles(void);																	//Prototype de la fonction affichant les regles du Mastermind
void Quitter_Jeu(void);																//Prototype de la fonction permettant de quitter le jeu
void Sauvegarde_Jeu(FILE *file);
void Sauvegarde_Combinaison_Joueur(FILE *file,joueur *p_joueur);
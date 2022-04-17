
#include <stdio.h>						//Inclusion des librairies necessaires
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Mastermind.h"



#define SIZE 4 							//Taille des tableaux pour le joueur et la combinaison à trouver 


int main(int argc, char const *argv[])
{
	srand(time(NULL));																			//Initialise le module permettant degenerer les combinaisons aleatoires
	joueur p_joueur;																			//Declaration du pointeur de structre
	plateau p_plateau;																			//Declaration du pointeur de structre

	int etat = 0;	

    FILE* fichier = NULL;
 
    fichier = fopen(argv[1], "w");
 
    if (fichier != NULL)
    {
        // On demande l'âge
        printf("Quel age avez-vous ? ");
       
 
        // On l'écrit dans le fichier
        //fprintf(fichier, "Le Monsieur qui utilise le programme, il a 21101 ans");
        //fclose(fichier);

    }
 
    

	while(1){																					//Se repete en boucle

        etat = Menu();																			//La valeur etat prend la valeaur saisie par l'utilisateur dans la fonction Menu() : 1,2 ou 3

        switch(etat)																			//Changement d'etat en fonction de etat
        {	
            case 1:																				//etat = 1
                Jeu(p_plateau,p_joueur,fichier);														//Appel de la fonction Jeu()
            break;


            case 2:																				//etat = 2
                Regles();																		//Appel de la fonction Regles()
            break;


            case 3:																				//etat = 3
            	Quitter_Jeu();																	//Appel de la fonction Quitter_Jeu()
            break;	
        }
    }

	return 0;
}


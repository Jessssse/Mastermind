#include "Mastermind.h"





void Jeu(plateau p_plateau,joueur p_joueur,FILE *fichier)
{




	p_plateau.tentatives_max = 10;																		//Initialise le nombre de coups
	p_plateau.coups_restants = p_plateau.tentatives_max;												//Affecte au nombre de coups restants le nombre de coups maximum
	p_plateau.nb_tentatives = 1;																		//Passe à 1 le nombre de tentatives

	Combi_Secrete(&p_plateau, SIZE, 'A', 'F');															//Genere une combinaison secrete
	//Aff_tab_int(p_plateau.combinaison_rand,SIZE);							

	while(p_plateau.Partie_gagnee == 0 && p_plateau.coups_restants > 0)											//Tant que la partie n'est pas gagnee ou que le joueur a des coups restants
	{

		do
		{
			Saisie_Joueur(&p_joueur);																	//Demander au joueur de saisir une combinaison 
		}
		while(Saisie_Securisee(&p_joueur,SIZE) == 0);													//Tant que la combinaison ne respecte pas le format du type AAAA

		
		Sauvegarde_Combinaison_Joueur(fichier,&p_joueur);


		p_plateau.Partie_gagnee = Comparaison_Combinaison(&p_joueur, &p_plateau,SIZE);							//Compare la combinaison du joueur à la combinaison secrete

	}

	Affichage_Fin_Partie(&p_plateau);														//Appelle la fonction d'affichage de fin de partie 
}



void Affichage_Fin_Partie(plateau *p_plateau)										//Focntion permettant l'affichage à la fin de la partie
{

	int choix = 0;

	if(p_plateau -> Partie_gagnee == 1)																				//Si la partie est gagnee, affiche la victoire et le nombre de coups
	{
		printf("Bravo ! Vous avez gagne en %d coup(s)\n",p_plateau -> nb_tentatives);
		printf("Entrez (0) pour revenir au menu principale\n" );										//Demande à l'utilisateur d'entrer 0 pour revenir au menu
    	scanf("%d", &choix);																			//Attente du 0
	}
	else if(p_plateau -> coups_restants == 0)															//S'il ne reste plus de coups -> partie perdue
	{
		printf("Dommage, vous avez perdu\n"																//Affiche la defaite de l'utilisateur et la combinaison secrete
			   "La solution etait : %s\n",p_plateau -> combinaison_rand);
		printf("Entrez (0) pour revenir au menu principale\n" );										//Demande à l'utilisateur d'entrer 0 pour revenir au menu
    	scanf("%d", &choix);																			//Attente du 0
	}
}



int Saisie_Securisee(joueur *p_joueur,int taille)														//Fonction permettant la saisie securisée
{			

	int nb_carac = 0;																					//Declaration du nombre de caractere contenu dans le tableau saisie joueur 
	int i = 0;																							//Declaration de la variable i pour le parcour de tableau
	int etat = 1;																						//Declaration de l'etat : 1 si la saisie ets bonne, 0 si la saisie n'est pas bonne 
	int nb_mauvaise_lettres = 0;

	nb_carac = strlen(p_joueur -> combinaison_joueur);													//Comptage du nombre de caractere du tableau combinaison joueur

	if(nb_carac != 4)																					//Test du nombre de caratctere, si different de 4
	{
		printf("Veuillez entrer entre 1 et 4 caracteres\n\n");											//Demande au joueur une autre cominaison 
		etat = 0;																						//Passe etat à 0
	}
	else
	{

	for(i = 0;i<taille;i++)																				//Boucle for parcourant le tableau
	{
		if((p_joueur -> combinaison_joueur[i] < 'A') || (p_joueur -> combinaison_joueur[i] > 'F'))		//Teste de chaque caractere du tableau, si different ne va pas de A à F
		{
			nb_mauvaise_lettres++;																		//Increment le nombre de mauvaise lettre
			etat = 0;																					//Passe etat à 0
		}

	}

	if(nb_mauvaise_lettres > 0)																			//S'il y au moins une mauvaise lettre
	{
		printf("Veuillez entrer des lettres entre A et F\n\n");											//Demande au joueur une autre cominaison
	}

	}
	return etat;																						//Retourne etat : 0 ou 1
}



void Combi_Secrete(plateau *p_plateau, int taille, char min, char max)			//Fonction créant la combinaison secrete
{

	int i ;																		//Declaration de l'element d'incrementation du tableau

	for (i = 0; i < taille; i++)												//Boucle for parcourant le tableau
	{												
    	p_plateau->combinaison_rand[i] = ((rand() % (max - min + 1)) + min) ;	//Attribution des valeurs dans la structure Plateau, dans le tableau combinaison_rand
    																			//Calcul permettant d'obtenir des lettres entre A et F
	}
}



void Saisie_Joueur(joueur *p_joueur)											//Fonction pour la saisie du joueur
{
    	printf("Veuillez entrer une combinaison de lettres\n");					//Demande au joueur de saisir une combinaison
    	scanf("%s",p_joueur->combinaison_joueur);								//Stocke la combinaison dans la structure joueur, dans le tableau combinaison_joueur
    	printf("\n");
    	
}



int Comparaison_Combinaison(joueur *p_joueur, plateau *p_plateau, int taille)
{

    int i, j ;																			//Declaration des elements d'incrementation des tableaux
    char copie_combinaison_secrete[taille];												//Declaration d'un tableau permettant de copier d'autres tableaux
    char copie_combinaison_joueur[taille];												//Declaration d'un tableau permettant de copier d'autres tableaux

    p_joueur -> nb_mal_places = 0;
    p_joueur -> nb_bien_places = 0;


    // Creation de la copie du tableau //
    for (i = 0 ; i < taille ; i++)														//Boucle for parcourant le tableau
    {
   	 copie_combinaison_secrete[i] = p_plateau -> combinaison_rand[i]; 					//Copie des tableaux contenus dans les structures
   	 copie_combinaison_joueur[i] = p_joueur -> combinaison_joueur[i];					//Copie des tableaux contenus dans les structures
    }


    // Verification des lettres bien placées //
    for (i = 0 ; i < taille; i++){														//Boucles for parcourant les deux tableaux
	   	 for (j = 0; j < taille; j++)
	   	 {
		   	if((copie_combinaison_joueur[i] == copie_combinaison_secrete[j]) && (i==j)) //Test des lettres bien placées Si les emplacements contiennent les memes lettres et que les emplacements sont les memes
		   	{
		   		(p_joueur -> nb_bien_places)++;											//Incrementation du nombre de lettres bien placées
		   		copie_combinaison_secrete[j] = 1;										//Passage des lettres à 1 pour eviter les repetitions par la suite
		   		copie_combinaison_joueur[i] = 0;										//Passage des lettres à 0 pour éviter les repetitions par la suite
			}
		 }
  	}


  	//Verification de la victoire du joueur//
	if((p_joueur -> nb_bien_places) == taille)											//Test du nombre de lettres bien placées, Si nombre de lettres bien placees == taille 
	{
	   	return 1;  																		//Partie gagnee
	}
	else
	{
	// Verification des lettres mal placées //
    for (i=0; i < taille; i++)															//Boucles for parcourant les deux tableaux
    {
		for (j=0; j < taille; j++)
		{
			if(copie_combinaison_joueur[j] == copie_combinaison_secrete[i])				//Test du nombre de lettres mal placées, Si les emplacements contiennent les memes lettres
			{
				(p_joueur -> nb_mal_places)++;											//Incrementation du nombre de lettres mal placées
				copie_combinaison_secrete[i] = 1 ;										//Passage des lettres à 1 pour eviter les repetitions par la suite
				copie_combinaison_joueur[j] = 0 ;										//Passage des lettres à 0 pour éviter les repetitions par la suite
			}
		}
	}

	p_plateau -> coups_restants = (p_plateau -> tentatives_max) - (p_plateau -> nb_tentatives++); //Affecte au nombre de coups restants le nombre de coups maximums moins le nombre de tentatives

	printf("Nombre de coups restants : %d\n",p_plateau -> coups_restants);
	printf("Nombre de lettres mal placees : %d\n",p_joueur -> nb_mal_places);			//Affichage du nombre de lettres mal placées
	printf("Nombre de lettres bien placees : %d\n\n",p_joueur -> nb_bien_places);		//Affichage du nombre de lettres bien placées

	return 0;																			//Partie non gagnée 
	}																		
}



void Quitter_Jeu(void)																		//Fonction permettant de quitter le Terminal
{
	system("osascript -e 'tell application \"Terminal\" to quit' &");					//Commande permettant de quitter le Terminal
}



int Menu(void)																				//Fonction pour l'affichage du menu
{
         int choix = 0;
       
         system("clear" ); 																// Nettoyer la console
         printf("======== MENU ========\n\n" );
         printf("(1) : Jouer\n" );
         printf("(2) : Regles du jeu\n" );
         printf("(3) : Quitter\n\n" );
         printf("======================\n\n\n" );
         printf("Que voulez vous faire ?\n\n" );
         scanf("%d", &choix);															//Attend que le joueur entre 0 pour revenir au menu principal
       
         return choix;
}


	
void Regles(void)																				//Fonction pour l'affichage des regles du Mastermind
{
    int choix = 0;
    system("clear" ); 																		//Nettoyer la console
   
    																						
    printf("***********************\n" );													//Affichage des règles du Mastermind
    printf("*REGLES DU MASTERMIND:*\n" );
    printf("***********************\n" );
   
    printf("\nLe programme choisit une combinaison de 4 lettres au hasard\n" );
    printf("parmi 6 lettres disponibles : A,B,C,D,E et F.\n" );
    printf("Cette combinaison de lettre peut contenir plusieurs fois la meme lettre.\n" );
    printf("L utilisateur essaie de la deviner en proposant au maximum dix combinaisons.\n" );
    printf("Pour chaque tentative le programme indique le nombre de lettres bien placees\n" );
    printf("et le nombre de couleurs mal placees\n" );
    printf("Si le nombre maximal d essais est atteint,\n" );
    printf("le programme indique au joueur qu il a perdu et donne la combinaison.\n\n" );
    printf("------------------------------------------------------------------------------\n\n" );
    printf("Entrez (0) pour revenir au menu principale\n" );
    scanf("%d", &choix);																	//Attend que le joueur entre 0 pour revenir au menu principal
}


void Sauvegarde_Combinaison_Joueur(FILE *fichier,joueur *p_joueur){

	fprintf(fichier, "%s",p_joueur -> combinaison_joueur);
	//fclose(fichier);
}






void Sauvegarde_Jeu(FILE *file){



}



























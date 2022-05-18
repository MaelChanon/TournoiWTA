#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include<locale.h>
#pragma warning(disable: 4996)

//constantes
#define maxTournois 10
#define nbMatchTournoi 127
#define maxjoueusesTournoi 128
#define lgMot 30
#define nbTournoisComptes 4


//profile joueuse
typedef struct {
	char nom[lgMot + 1];
	unsigned int points;
} Joueuse;

//résultat d'un match

typedef struct {
	unsigned int idxGagnante; //index de la gagnante dans datajoueuse 
	unsigned int idxPerdante; //index de la perdante dans datajoueuse
}Match;

//tournois

typedef struct {
	char nom[lgMot + 1];
	char date[lgMot + 1];
	Match dataMatch[nbMatchTournoi]; //tous les match du tournois 
} Tournoi;

//saison

typedef struct {
	Tournoi dataTournois[maxTournois]; //tous les tournois de la saison
	Joueuse dataJoueuses[maxTournois * maxjoueusesTournoi]; //toutes les joueuses ayant participé à au moins un tournoi

	unsigned int NOMBRETOURNOIS;
	unsigned int NombreActuelTournois;
	unsigned int NombreActuelJoueuse;
} TournoiWTA;




/*renvoie le nombre de tournois max lu au clavier si le nombre est vérifié
* [return] si la valeur est suppéreieure à 0 et inférieur à 10
*/
short definir_nombre_tournois();

/*enregistre le tournoi(nom prenom et les résultats des matchs e
t joueuses ayant participé
* [in] ins1 : pointe sur les données du championnat
* [int-out] ins1 : pointe sur les données du championnat
*/
void enregistrement_tournoi(TournoiWTA* ins1);

/*renvoie l'index de la joueuse si elle existe, sinon enregister le nom à la
dernière place du tableau
* [in] ins1: pointe sur les données du championnat
* [in] nom[] : nom de la joueuse
* [out] index de la joueuse
*/
int estJoueuse(TournoiWTA* ins, char nom[]);

/*Affiche tous les matchs d'un tournoi, si il n'est pas affiché dans la liste,
affiche que le tournoi est inconnu
* [in] ins1 : pointe sur les données du championnat
*/
void affichage_matchs_tournoi(const TournoiWTA* ins);

/*Affiche tous les matchs d'une d'une joueuse
* [in] ins1 : pointe sur les données du championnat
*/
void afficher_matchs_joueuse(const TournoiWTA* ins1);

/*Affiche toutes les joueuses d'un tournoi par ordre alphabetique
si la joueuse ne participe pas au tournoi, affiche que la joueuse est inconnue
* [in] ins1 : pointe sur les données du championnat
*/
void affichage_joueuses_tournoi(const TournoiWTA* ins1);

/*affiche le classement des joueuses selon ses points puis dans l'ordre alphabetique
* [in] ins1 : pointe sur les données du championnat
*/
void afficher_classement(const TournoiWTA* ins1);

int main() {

	char mot[lgMot + 1];
	TournoiWTA ins;


	ins.NombreActuelTournois = 0;
	ins.NombreActuelJoueuse = 0;

	while (1) {

		scanf("%s", mot);
		if (strcmp(mot, "exit") == 0) {
			exit(0);
		}
		if (strcmp(mot, "definir_nombre_tournois") == 0) {
			ins.NOMBRETOURNOIS = definir_nombre_tournois();
		}
		if (strcmp(mot, "enregistrement_tournoi") == 0) {
			assert(ins.NombreActuelTournois <= ins.NOMBRETOURNOIS);
			enregistrement_tournoi(&ins);

		}
		if (strcmp(mot, "affichage_matchs_tournoi") == 0) {
			affichage_matchs_tournoi(&ins);

		}
		if (strcmp(mot, "afficher_matchs_joueuse") == 0) {
			afficher_matchs_joueuse(&ins);
		}
		if (strcmp(mot, "affichage_joueuses_tournoi") == 0) {
			affichage_joueuses_tournoi(&ins);
		}
		if (strcmp(mot, "afficher_classement") == 0) {
			afficher_classement(&ins);
		}
	}
	return 0;
}

short definir_nombre_tournois() {

	short nbt;
	scanf("%hd", &nbt);
	assert(nbt >= 1 && nbt <= maxTournois); //si le nombre de tournois est supérieure ou egalà 1 ou inférieur au nombre maximum de tournois
	return nbt;
}


void enregistrement_tournoi(TournoiWTA* ins1) {

	unsigned int i = 0;
	Match idxMatch;

	char nomTournoi[lgMot + 1]; //nom du tournoi
	char date[lgMot + 1]; //date du tournois


	char win[lgMot + 1]; //nom de la gagnante et de la perdante
	char loose[lgMot + 1];

	scanf("%s", nomTournoi);
	scanf("%s", date);

	for (i = 0; i < ins1->NOMBRETOURNOIS; ++i) { //parcour tous les tournois et cause une erreur si le tournoi a deja été enregistré
		assert((strcmp(ins1->dataTournois[i].nom, nomTournoi) != 0)
		|| (strcmp(ins1->dataTournois[i].date, date) != 0));
	}


	strcpy(ins1->dataTournois[ins1->NombreActuelTournois].date, date);
	strcpy(ins1->dataTournois[ins1->NombreActuelTournois].nom, nomTournoi);


	for (i = 0; i < nbMatchTournoi; ++i) { //scanf des résultats de tous les matchs

		scanf("%s", win);
		scanf("%s", loose);
		ins1->dataTournois[ins1->NombreActuelTournois].dataMatch[i].idxGagnante
		= estJoueuse(ins1, win); //definit le resultat des match dans le tableau qui stoque tous les matchs du tournois
		ins1->dataTournois[ins1->NombreActuelTournois].dataMatch[i].idxPerdante
		= estJoueuse(ins1, loose);
		idxMatch = ins1->dataTournois[ins1->NombreActuelTournois].dataMatch[i];

		if (i >= 0 && i < 64) { //Attribution des points selon la sortie de de tournoi du joueur 
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 10;
			continue;
		}
		if (i >= 64 && i < 96) {
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 45;
			continue;
		}
		if (i >= 96 && i < 112) {
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 90;
			continue;
		}
		if (i >= 112 && i < 120) {
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 180;
			continue;
		}
		if (i >= 120 && i < 124) {
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 360;
			continue;
		}
		if (i >= 124 && i < 126) {
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 720;
			continue;
		}
		if (i == 126) {
			ins1->dataJoueuses[idxMatch.idxPerdante].points += 1200;
			ins1->dataJoueuses[idxMatch.idxGagnante].points += 2000;
			continue;
		}
	}

	ins1->NombreActuelTournois += 1;
	if (ins1->NombreActuelTournois > nbTournoisComptes) {
		for (i = 0; i < nbMatchTournoi; ++i) { //scanf des résultats de tous les matchs
			idxMatch = ins1->dataTournois[ins1->NombreActuelTournois 
			- (nbTournoisComptes+1)].dataMatch[i];


			if (i >= 0 && i < 64) { //Attribution des points selon la sortie de de tournoi du joueur 
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 10;
				continue;
			}
			if (i >= 64 && i < 96) {
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 45;
				continue;
			}
			if (i >= 96 && i < 112) {
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 90;
				continue;
			}
			if (i >= 112 && i < 120) {
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 180;
				continue;
			}
			if (i >= 120 && i < 124) {
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 360;
				continue;
			}
			if (i >= 124 && i < 126) {
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 720;
				continue;
			}
			if (i == 126) {
				ins1->dataJoueuses[idxMatch.idxPerdante].points -= 1200;
				ins1->dataJoueuses[idxMatch.idxGagnante].points -= 2000;
				continue;
			}
		}
	}
}

int estJoueuse(TournoiWTA* ins1, char nom[]) {
	unsigned int i;
	for (i = 0; i < ins1->NombreActuelJoueuse; ++i) {
		if (strcmp(ins1->dataJoueuses[i].nom, nom) == 0) { //si la joueuse est trouvée renvoie son index		
			return i;
		}
	}
	strcpy(ins1->dataJoueuses[ins1->NombreActuelJoueuse].nom, nom); //sinon l'enregistrer après la dernière joueuse avec 0 points 
	ins1->dataJoueuses[ins1->NombreActuelJoueuse].points = 0;
	ins1->NombreActuelJoueuse += 1;
	return ins1->NombreActuelJoueuse - 1;
}

void affichage_matchs_tournoi(const TournoiWTA* ins1) {
	unsigned int i = 0;
	unsigned int o = 0;

	char nom[lgMot + 1]; //nom et date du tournoi
	char date[lgMot + 1];


	scanf("%s", &nom);
	scanf("%s", &date);

	for (; i < ins1->NOMBRETOURNOIS; ++i) { //parcourir tous les tournois
		if ((strcmp(ins1->dataTournois[i].nom, nom) == 0) 
		&& (strcmp(ins1->dataTournois[i].date, date) == 0)) { //si on trouve un nom et une date correspondante
			printf("%s %s\n", nom, date);
			break;
		}
	}
	if (i == ins1->NOMBRETOURNOIS) { //sinon revoie que le tournoi est inconnu
		printf("tournoifefefefe inconnu");
		return;
	}

	for (; o < nbMatchTournoi; ++o) {
		switch (o) {
		case 0:
			printf("64emes de finale\n");
			break;
		case 64:
			printf("32emes de finale\n");
			break;
		case 96:
			printf("16emes de finale\n");
			break;
		case 112:
			printf("8emes de finale\n");
			break;
		case 120:
			printf("quarts de finale\n");
			break;
		case 124:
			printf("demi-finales\n");
			break;
		case 126:
			printf("finale\n");
			break;
		default:
			break;
		}
		//affiche nom de la joueuse gagngante et celle de la joueuse perdante
	
		printf("%s %s\n", 
		ins1->dataJoueuses[ins1->dataTournois[i].dataMatch[o].idxGagnante].nom, 
		ins1->dataJoueuses[ins1->dataTournois[i].dataMatch[o].idxPerdante].nom);
	}
}

void afficher_matchs_joueuse(const TournoiWTA* ins1) {

	//pour les for()
	unsigned int i = 0;
	unsigned int b = 0;
	unsigned int o = 0;

	int idxG;
	int idxP;
	char nomTournoi[lgMot + 1]; //nom et date du tournoi
	char date[lgMot + 1];
	char nomJoueuse[lgMot + 1];

	scanf("%s", &nomTournoi);
	scanf("%s", &date);
	scanf("%s", &nomJoueuse);

	for (; i < ins1->NOMBRETOURNOIS; i++) { //Cherche le tournoi indiqué dans la liste
		if ((strcmp(ins1->dataTournois[i].nom, nomTournoi) == 0) 
		&& (strcmp(ins1->dataTournois[i].date, date) == 0)) {
			break;
		}
		if (i == ins1->NOMBRETOURNOIS - 1) {
			printf("tournoi inconnu");
			return;
		}
	}
	for (b = 0; b < ins1->NombreActuelJoueuse; ++b) {
		if (strcmp(ins1->dataJoueuses[b].nom, nomJoueuse) == 0) { //si la joueuse est trouvée b = son index sinon imprimer que la joueuse est inconnu
			break;
		}
		if (b == ins1->NombreActuelJoueuse - 1) {
			printf("joueuse inconnue");
			return;
		}
	}
	for (; o < nbMatchTournoi; o++) {
		idxG = ins1->dataTournois[i].dataMatch[o].idxGagnante;
		idxP = ins1->dataTournois[i].dataMatch[o].idxPerdante;

		if (idxG == b || idxP == b) {  //si la joueuse est trouvée dans un des match imprimé le match
			printf("%s %s\n",
			ins1->dataJoueuses[ins1->dataTournois[i].dataMatch[o].idxGagnante].nom, 
			ins1->dataJoueuses[ins1->dataTournois[i].dataMatch[o].idxPerdante].nom);
			if (idxP == b) { //si la joueuse est eliminée arret de la fonction
				return;
			}
		}
	}

}

void affichage_joueuses_tournoi(const TournoiWTA* ins1) {
	unsigned int i = 0;
	unsigned int o = 0;

	unsigned int retenue[2] = { 0,0 };

	int Joueuse[maxjoueusesTournoi][2];
	int pluspetit = 0;

	char nom[lgMot + 1]; //nom et date du tournoi
	char date[lgMot + 1];

	scanf("%s", &nom);
	scanf("%s", &date);
	for (o = 0; o < ins1->NOMBRETOURNOIS; ++o) { //cherche les tournois 

		if ((strcmp(ins1->dataTournois[o].nom, nom) == 0)
		&& (strcmp(ins1->dataTournois[o].date, date) == 0)) { //si on trouve un nom et une date correspondante

			printf("%s %s\n", nom, date);
			break;
		}
	}
	if (i == ins1->NOMBRETOURNOIS) {
		printf("tournoi inconnu");
		return;
	}
	for (i = 0; i < nbMatchTournoi; ++i) {
		Joueuse[i][0] = ins1->dataTournois[o].dataMatch[i].idxPerdante; //stoquer toutes les joueuses d'un tournoi et les points gagnées 
		if (i >= 0 && i < 64) {
			Joueuse[i][1] = 10;
			continue;
		}
		if (i >= 64 && i < 96) {
			Joueuse[i][1] = 45;
			continue;
		}
		if (i >= 96 && i < 112) {
			Joueuse[i][1] = 90;
			continue;
		}
		if (i >= 112 && i < 120) {
			Joueuse[i][1] = 180;
			continue;
		}
		if (i >= 120 && i < 124) {
			Joueuse[i][1] = 360;
			continue;
		}
		if (i >= 124 && i < 126) {
			Joueuse[i][1] = 720;
			continue;
		}
		if (i == 126) {
			Joueuse[i][1] = 1200;
			Joueuse[i + 1][0] = ins1->dataTournois[o].dataMatch[i].idxGagnante;
			Joueuse[i + 1][1] = 2000;
			continue;
		}
	}
	//recherche du nombre le plus petit à chaque tours(pas le plus efficace)
	for (i = 0; i < maxjoueusesTournoi; ++i) { //on met en comparaison l'index i du tableau
		pluspetit = i;
		for (o = i; o < maxjoueusesTournoi; ++o) {
			if (strcmp(ins1->dataJoueuses[Joueuse[o][0]].nom,
			ins1->dataJoueuses[Joueuse[pluspetit][0]].nom) < 1) { //en parcourant tout le tableau, si le nom de la joueuse du rang o est plus petit son index devient le plus petit
				pluspetit = o;
			}
		}
		retenue[0] = Joueuse[i][0]; //on stoque temporairement l'index du joueur et ses temps dans retenue 
		retenue[1] = Joueuse[i][1];

		Joueuse[i][0] = Joueuse[pluspetit][0]; //on echange les valeurs des index
		Joueuse[i][1] = Joueuse[pluspetit][1];

		Joueuse[pluspetit][0] = retenue[0];
		Joueuse[pluspetit][1] = retenue[1];
	}
	for (i = 0; i < maxjoueusesTournoi; ++i) {
		printf("%s %d\n",ins1->dataJoueuses[Joueuse[i][0]].nom, Joueuse[i][1]); //imprimer les tableaux triés 
	}
}

void afficher_classement(const TournoiWTA* ins1) {
	unsigned int i = 0;

	unsigned int v = 0;
	unsigned int j = 0;
	int Joueuse[maxjoueusesTournoi * maxTournois];

	for (; i < ins1->NombreActuelJoueuse; ++i) {
		Joueuse[i] = i;
	}
	//algo de trie par selection
	for (i = 1; i < ins1->NombreActuelJoueuse; ++i) {
		v = Joueuse[i];
		j = i;
		//tant  que j>0 et qu'on ne tombe pas sur une nombre plus petit on décale toute la liste de i à ...
		while (j > 0 && ins1->dataJoueuses[Joueuse[j - 1]].points
		<= ins1->dataJoueuses[v].points) {
			Joueuse[j] = Joueuse[j - 1];
			if (ins1->dataJoueuses[Joueuse[j]].points == ins1->dataJoueuses[v].points 
			&& strcmp(ins1->dataJoueuses[Joueuse[j - 1]].nom, ins1->dataJoueuses[v].nom) < 1){
				break;
			}
			j = j - 1;
		}
			Joueuse[j] = v;
	}
	for (i = 0; i < ins1->NombreActuelJoueuse; ++i) {
		if (ins1->dataJoueuses[Joueuse[i]].points != 0) {
			printf("%s %d\n", ins1->dataJoueuses[Joueuse[i]].nom, ins1->dataJoueuses[Joueuse[i]].points);
		}
	}
}




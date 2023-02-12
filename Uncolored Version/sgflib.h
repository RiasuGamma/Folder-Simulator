#ifndef SGFLIB_H_INCLUDED
#define SGFLIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/*-------------------------------------*/

/*
  ---------------------------------------|
  -------------LES TYPES-----------------|
  ---------------------------------------|
*/
/*-------------CHEMIN--------------------*/
typedef struct noeudCh* TChemin;
struct noeudCh{
    char Nom[16];
    struct noeudCh* Suivant;
};

/*-------------ARBRE BINAIR--------------*/
typedef struct noeudArb* Tsysteme;
struct noeudArb{
    char Nom[16];
    int Rep;       //1 repertoire et 0 pour fichier
    int Taille;
    struct noeudArb* Fils;
    struct noeudArb* Frere;
};

/*
  ---------------------------------------|
  -------------LES FONCTIONS-------------|
  ---------------------------------------|
*/
    //pour le chemin
TChemin get_last(TChemin p );
TChemin insert_queue(TChemin l, char str[]);
TChemin insert_head(TChemin path, char nom[]);
TChemin store_path(TChemin l, char path[]);
TChemin store_file(TChemin l, char path[]);
void show_path(TChemin l);
TChemin get_pre_last(TChemin p);
void Cut(char str[],char cmd[],char path[], char f_name[], char corbille[]);
void cut2(char str[],char cmd[],char path[], char f_name[], char corbille[]);
int compare_cmd(char in[], char comp[]);
int check(char cmd[], char path[], char f_name[]);

/*-------------------------------------*/

    //pour l'arbre
Tsysteme createbase(Tsysteme Base);
void parcours(Tsysteme Base, char level[]);
Tsysteme ajouter_RF(Tsysteme fichier,char Nom[],int Type,int ftaille);
int get_size(Tsysteme Base);
void parcours_arbre(Tsysteme *temp,TChemin path,char buffer[],int *boolean);
int serch_for_file(Tsysteme *dossier, char nom[]);
int serch_for_dir(Tsysteme *dossier, char nom[]);
int existe(Tsysteme dossier,char nom[],int type);
void ls(Tsysteme dossier);
void rm(Tsysteme *file,Tsysteme *pre);
Tsysteme pastefile(Tsysteme file,Tsysteme copier);
Tsysteme cpdir(Tsysteme dossier);
void vider(Tsysteme *file);
void viderfils(Tsysteme *file);
void get_pre(Tsysteme base, Tsysteme *pre, Tsysteme file);
int exist_tp(char nom[], TChemin *path, Tsysteme *arbre);
void rm_apres_exist(Tsysteme *file,Tsysteme *pre);


/*-------------------------------------*/

#endif // SGFLIB_H_INCLUDED

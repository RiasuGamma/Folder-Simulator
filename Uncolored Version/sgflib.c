#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgflib.h"

Tsysteme createbase(Tsysteme Base){
    Tsysteme first=malloc(sizeof(struct noeudArb));
    Tsysteme bin=malloc(sizeof(struct noeudArb));
    Tsysteme home=malloc(sizeof(struct noeudArb));
    Tsysteme root=malloc(sizeof(struct noeudArb));
    Tsysteme run=malloc(sizeof(struct noeudArb));
    Tsysteme Univ8mai1945=malloc(sizeof(struct noeudArb));
    Tsysteme Bureau=malloc(sizeof(struct noeudArb));
    Tsysteme Documents=malloc(sizeof(struct noeudArb));
    Tsysteme Telechargements=malloc(sizeof(struct noeudArb));
        //The Root
                                strcpy(first->Nom,"/");
                                first->Rep=1;
                                first->Taille=0;
                                first->Frere=NULL;
                                first->Fils=bin;

            strcpy(bin->Nom,"bin");
            bin->Rep=1;
            bin->Taille=0;
            bin->Frere=home;
            bin->Fils=NULL;
                            strcpy(home->Nom,"home");
                            home->Rep=1;
                            home->Taille=0;
                            home->Frere=root;
                            home->Fils=Univ8mai1945;

            strcpy(Univ8mai1945->Nom,"Univ8mai1945");       strcpy(root->Nom,"root");
            Univ8mai1945->Rep=1;                            root->Rep=1;
            Univ8mai1945->Taille=0;                         root->Taille=0;
            Univ8mai1945->Fils=Bureau;                      root->Fils=NULL;
            Univ8mai1945->Frere=NULL;                       root->Frere=run;


    strcpy(Bureau->Nom,"Bureau");                                       strcpy(run->Nom,"run");
    Bureau->Rep=1;                                                      run->Rep=1;
    Bureau->Taille=0;                                                   run->Taille=0;
    Bureau->Fils=NULL;                                                  run->Fils=NULL;
    Bureau->Frere=Documents;                                            run->Frere=NULL;
                    strcpy(Documents->Nom,"Documents");
                    Documents->Rep=1;
                    Documents->Taille=0;
                    Documents->Fils=NULL;
                    Documents->Frere=Telechargements;
                                        strcpy(Telechargements->Nom,"Telechargements");
                                        Telechargements->Rep=1;
                                        Telechargements->Taille=0;
                                        Telechargements->Fils=NULL;
                                        Telechargements->Frere=NULL;
    return first;
}

/*-------------------------------------*/

void parcours_arbre(Tsysteme *Arbre, TChemin path, char buffer[],int *boolean){
    *boolean=1;
    int tr=0;
    Tsysteme temp=*Arbre;
    while (path!=NULL && temp !=NULL){
        tr=0;
        if(strcmp(path->Nom,temp->Nom)==0 && temp->Rep == 1){
            *Arbre= temp;
            sprintf(buffer,"%s->",temp->Nom);
            path=path->Suivant;
            temp=temp->Fils;
        }
        else{
            while(tr==0 && temp->Frere!=NULL){
                temp=temp->Frere;
                if(strcmp(path->Nom,temp->Nom)==0 && temp->Rep == 1){
                    *Arbre= temp;
                    sprintf(buffer,"%s->",temp->Nom);
                    path=path->Suivant;
                    temp=temp->Fils;
                    tr= 1;
                }
            }
            if(tr==0){
                *boolean=0;
                //printf("\n>>Path invalide\n");
                break;
            }
        }
    }
    if(path != NULL) {
            *boolean=0;
            printf("\n>> Path invalide\n");
    }
}

/*-------------------------------------*/
int serch_for_file(Tsysteme *dossier, char nom[]){
    Tsysteme temp = *dossier;
    if(temp->Fils == NULL) return 0;
    else{
        temp = temp->Fils;
        while(temp != NULL){
            if(strcmp(temp->Nom, nom) == 0 && temp->Rep == 0){
                *dossier = temp;
                return 1;
            }
            temp = temp->Frere;
        }
        return 0;
    }
}

/*-------------------------------------*/

int serch_for_dir(Tsysteme *dossier, char nom[]){
    Tsysteme temp = *dossier;
    if(temp->Fils == NULL) return 0;
    else{
        temp = temp->Fils;
        while(temp != NULL){
            if(strcmp(temp->Nom, nom) == 0 && temp->Rep == 1){
                *dossier = temp;
                return 1;
            }
            temp = temp->Frere;
        }
        return 0;
    }
}

/*-------------------------------------*/

void get_pre(Tsysteme base, Tsysteme *pre, Tsysteme file){
    Tsysteme temp= base;
    if(temp != NULL){
        if(temp->Fils == file || temp->Frere == file) *pre= temp;
        else{
            get_pre(temp->Fils, pre, file);
            get_pre(temp->Frere, pre, file);
        }
    }
}

/*-------------------------------------*/

void parcours(Tsysteme Base, char level[]){
    char temp[200];
    strcpy(temp, level);
    if (Base!=NULL){
            if(Base->Rep == 1 ){
                printf("%s",level);
                printf("%s [%03d] (D)\n",Base->Nom, get_size(Base->Fils));
            }
            else {
                printf("%s",level);
                printf("%s [%03d] (F)\n",Base->Nom, Base->Taille);

            }
            if(Base->Fils != NULL) strcat(temp, "|   ");
            parcours(Base->Fils, temp);
            strcpy(temp, level);
            parcours(Base->Frere, temp);


    }
}
/*-------------------------------------*/

int get_size(Tsysteme Base){
    if(Base==NULL) return 0;
    else{
        return Base->Taille + get_size(Base->Frere) + get_size(Base->Fils);
    }
}

/*-------------------------------------*/

Tsysteme ajouter_RF(Tsysteme fichier,char Nom[],int Type,int ftaille){
    Tsysteme temp=fichier;
    Tsysteme newRF=malloc(sizeof(struct noeudArb));
    newRF->Fils=NULL;
    newRF->Frere=NULL;
    strcpy(newRF->Nom, Nom);
    if (Type==1){
        newRF->Rep=1;
        newRF->Taille=0;
    }
    else {
        newRF->Rep=0;
        newRF->Taille=ftaille;
    }
    if(fichier->Fils==NULL){
        fichier->Fils=newRF;
    }
    else{
        temp=temp->Fils;
        while(temp->Frere!=NULL){
            temp=temp->Frere;
        }
        temp->Frere=newRF;
    }
return fichier;
}

/*-------------------------------------*/

Tsysteme cpdir(Tsysteme dossier){
    if(dossier!=NULL){
        Tsysteme T=malloc(sizeof(struct noeudArb));
        T->Rep=dossier->Rep;
        strcpy(T->Nom,dossier->Nom);
        T->Taille=dossier->Taille;
        T->Fils=cpdir(dossier->Fils);
        T->Frere=cpdir(dossier->Frere);
        return T;
    }
    else{
        return NULL;
    }
}

/*-------------------------------------*/

Tsysteme pastefile(Tsysteme file,Tsysteme copier){
    Tsysteme temp=file;
    if(temp->Fils==NULL){
        temp->Fils=copier;
    }
    else{
        temp=temp->Fils;
        while(temp->Frere !=NULL){
            temp=temp->Frere;
        }
        temp->Frere=copier;
    }
    return file;
}

/*-------------------------------------*/

void vider(Tsysteme *file){
    if (*file!=NULL){
        vider(&(*file)->Frere);
        vider(&(*file)->Fils);
        free(*file);
        *file=NULL;
    }
}
void viderfils(Tsysteme *file){
    if(*file != NULL){
        vider(&(*file)->Fils);
        free(*file);
        *file=NULL;
    }
}

/*-------------------------------------*/

void rm(Tsysteme *file,Tsysteme *pre){
    if((*pre)->Fils==*file){
        (*pre)->Fils=(*file)->Frere;
        viderfils(file);
    }
    else{
        if((*pre)->Frere==*file){
            (*pre)->Frere=(*file)->Frere;
            viderfils(file);
        }
    }
}

/*-------------------------------------*/

void ls(Tsysteme dossier){
    dossier=dossier->Fils;
    if(dossier==NULL){
        printf("\n>> Empty Directory");
    }
    else{
        printf("\n>>\n");
        while(dossier!=NULL){
            if(dossier->Rep==1){
                printf("    %s [%03d] (D) \n",dossier->Nom, get_size(dossier->Fils));
            }
            else{
                printf("    %s (%03d) (F) \n",dossier->Nom,dossier->Taille);
            }
            dossier=dossier->Frere;
         }
    }
}

/*-------------------------------------*/

TChemin insert_queue(TChemin l, char str[]){
    TChemin temp= l;
    if(l == NULL){
        TChemin e=malloc(sizeof(struct noeudCh));
        strcpy(e->Nom, str);
        e->Suivant=NULL;
        return e;
    }
    else{
        TChemin e=malloc(sizeof(struct noeudCh));
        strcpy(e->Nom, str);
        e->Suivant=NULL;

        while(temp->Suivant != NULL){
            temp=temp->Suivant;
        }
        temp->Suivant=e;
        return l;
    }
}

/*-------------------------------------*/

void cut(char str[],char cmd[],char path[], char f_name[], char corbille[]){    //split the typed string;
    int i=0; int k=0;
    if(str[k] != '\0'){
        while(str[k] == ' '){
            k++;
        }
        //cmd
        while(str[k] != '\0'){
            if(str[k] == ' ') break;
            cmd[i]=str[k];
            i++;
            k++;
        }
        cmd[i]='\0';     //cmd is filled
        //
        while(str[k] == ' '){
            k++;
        }
        //path
        i=0;
        while(str[k] != '\0'){
            if(str[k] == ' ') break;
            path[i]=str[k];
            i++;
            k++;
        }
        path[i]='\0';     //cmd is filled

        //
        while(str[k] == ' '){
            k++;
        }
        //file name
        i=0;
        while(str[k] != '\0'){
            if(str[k] == ' ') break;
            f_name[i]=str[k];
            i++;
            k++;
        }
        f_name[i]='\0';     //cmd is filled
        i=0;

        //
        while(str[k] == ' '){
            k++;
        }
        //Erro
        corbille[0]= str[k];
    }
    else{
        printf("\n");
    }
}
void cut2(char str[],char cmd[],char path[], char f_name[], char corbille[]){    //split the typed string;
    int i=0; int k=0;
    if(str[k] != '\0'){
        while(str[k] == ' '){
            k++;
        }
        //cmd
        while(str[k] != '\0'){
            if(str[k] == ' ') break;
            cmd[i]=str[k];
            i++;
            k++;
        }
        cmd[i]='\0';     //cmd is filled
        //
        while(str[k] == ' '){
            k++;
        }
        //path
        i=0;
        while(str[k] != '\0'){
            if(str[k] == ' ') break;
            path[i]=str[k];
            i++;
            k++;
        }
        path[i]='\0';     //cmd is filled

        //
        while(str[k] == ' '){
            k++;
        }
        //file name
        i=0;
        while(str[k] != '\0'){
            f_name[i]=str[k];
            i++;
            k++;
        }
        f_name[i]='\0';     //cmd is filled
        i=0;

        //
        while(str[k] == ' '){
            k++;
        }
        //Erro
        corbille[0]= str[k];
    }
    else{
        printf("\n");
    }
}
/*-------------------------------------*/

TChemin store_path(TChemin l, char path[]){
    TChemin temp=l;
    int i=0, k=0;
    char sub_char[16];
    if(path[k] == '\0'){           //if the path is null;
        printf(">> Error.");
        return NULL;
    }
    if(path[k] == '/'){           //if the path start wirh a "/";
        temp= insert_queue(temp, "/");
        k++;
        if(path[k] == '/'){        //if the path start with a "//" or only "/" -> "error";
            temp= insert_queue(temp, "/");
            printf(">> Error//.");
            return NULL;
        }
    }
    while(path[k] != '\0'){
        if(path[k] != '/'){       //fill a word from the path in sab_char;
            sub_char[i]=path[k];
            i++;
            k++;

        }
        else{
            sub_char[i]='\0';
            temp= insert_queue(temp, sub_char);
            //printf("%s, ", sub_char);
            strcpy(sub_char, "\0");
            i=0;
            k++;
            if(path[k]=='/' /*||path[k]=='\0'*/){      //if it is "//"
                printf(">> Error.");
                return NULL;
            }
            if(path[k]=='\0') return temp;
        }
    }
    sub_char[i]='\0';
    if(k > 1) temp= insert_queue(temp, sub_char);
    return temp;
}

/*-------------------------------------*/

TChemin store_file(TChemin l, char path[]){
    TChemin temp=l;
    int i=0, k=0;
    char sub_char[16];


    while(path[k] != '\0'){
        if(path[k] != ' '){       //fill a word from the path in sab_char;
            sub_char[i]=path[k];
            i++;
            k++;

        }
        else{
            sub_char[i]='\0';
            temp= insert_queue(temp, sub_char);
            strcpy(sub_char, "\0");
            i=0;
            while(path[k] == ' ') k++;

            if(path[k]== '\0') return temp;
        }
    }
    sub_char[i]='\0';
    if(k > 1) temp= insert_queue(temp, sub_char);
    return temp;
}

/*-------------------------------------*/

void show_path(TChemin l){
    printf("\n%c",175);
    TChemin temp= l;
    while(temp != NULL){
        if(temp->Suivant != NULL){
            if(strcmp(temp->Nom, "/") == 0) strcpy(temp->Nom, " ");
            printf("%s/", temp->Nom);
            temp=temp->Suivant;
        }
        else{
            if(strcmp(temp->Nom, "/") == 0) strcpy(temp->Nom, " ");
            printf("%s/", temp->Nom);
            temp=temp->Suivant;
        }
    }
}

/*-------------------------------------*/

int check(char cmd[], char path[], char *f_name){
    int i=0;
    if(cmd[0]=='\0' || path[0]=='\0'){       //if the input start with a space;
        return 0;
    }
    else {
        while(*f_name != '\0'){
            if(*f_name == '/'){
                return 0;
            }
            f_name++;
            i++;
        }
        i=0;
        while(path[i] != '\0'){
            if(path[i] == '/' && path[i+1]== '/') return 0; //if there is two '/' returns error
            i++;
        }
        return 1;
    }
}

/*-------------------------------------*/

int existe(Tsysteme dossier,char nom[],int type){
    if(dossier->Fils==NULL){
        return 0;
    }
    else{
        dossier=dossier->Fils;
        while(dossier!=NULL){
            if(strcmp(dossier->Nom,nom)==0 && type==dossier->Rep){
                return 1;
            }
            dossier=dossier->Frere;
        }
        return 0;
    }
}

/*-------------------------------------*/

int compare_cmd(char *in, char comp[]){
    int i=0;
    while(*in == ' '){
            in++;
            i++;
        }

    if(strcmp(in,comp)==0) return 1;
    else{
        return 0;
    }
}

/*-------------------------------------*/


int exist_tp(char nom[], TChemin *path, Tsysteme *arbre){
    Tsysteme temp = *arbre, temp2 = temp;

    if(temp == NULL) return 0;
    else{
        if(strcmp((temp)->Nom, nom) == 0){
            strcat(temp->Nom, " ");//----------------ESPACE POUR "VISIEE"
            //*arbre= temp;
            return 1;
        }
        else{
            if(exist_tp(nom, path, &(temp)->Fils) == 1){
                *path= insert_head(*path, temp->Nom);
                //*arbre= temp->Fils;
                return 1;
            }
            else{
                //*arbre= temp->Frere;
                return exist_tp(nom, path, &(temp)->Frere);
            }
        }
    }
}
TChemin insert_head(TChemin path, char nom[]){
    TChemin element = malloc(sizeof(struct noeudCh));
    strcpy(element->Nom, nom);
    element->Suivant = path;

    return element;
}
TChemin get_pre_last(TChemin p){
    TChemin temp= p;
    while(temp->Suivant != NULL) temp = temp->Suivant;
    strcpy(temp->Nom,"\b");
    return temp;
}


void rm_apres_exist(Tsysteme *file,Tsysteme *pre){
    if((*pre)->Fils==*file){
        (*pre)->Fils=(*file)->Frere;
        free(*file);
    }
    else{
        if((*pre)->Frere==*file){
            (*pre)->Frere=(*file)->Frere;
            free(*file);
        }
    }
}

TChemin get_last(TChemin p ){
    TChemin temp=p;
    while(temp->Suivant!=NULL){
        temp=temp->Suivant;
    }
    return temp;
}



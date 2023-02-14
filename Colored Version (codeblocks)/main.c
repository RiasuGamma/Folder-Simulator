//if you are reading this, do 20 pull ups rn
#include <stdio.h>
#include <string.h>
#include "sgflib.h"

int main()
{
    SetColor(255);
/*
  ---------------------------------------|
  -------------DECLARATION---------------|
  ---------------------------------------|
*/
    int compteur;
    int taille;
    int size;
    int filesize;
    int boolean1;//----------------------POUR TESTER EST CE QUE LE CHEMIN VRAIS OU NON

    Tsysteme base =NULL;
    base = createbase(base);
    Tsysteme copier =NULL;
    Tsysteme copier2 =NULL;
    Tsysteme temp = base;
    Tsysteme temp2 = NULL;
    Tsysteme pre = base;
    TChemin p = NULL;
    TChemin file = NULL;
    TChemin p_temp = NULL;

    char path[100];
    char path_temp[100];
    char exist_path[100];
    char cmd[16];
    char f_name[200];
    char str[200];
    char corbeille[100];
    char buffer[100];
    char unite[10];
    char level[200];
    char rm_type;
/*
  ---------------------------------------|
  -------------LA TAILLE-----------------|
  ---------------------------------------|
*/
    printf(">> Enter Storage size: ");
    SetColor(3);
    scanf(" %d",&taille);
    SetColor(255);
    while(taille <= 0){
        gets(corbeille);
        SetColor(4);
        printf(">> Error.\n");
        SetColor(255);
        printf(">> Tapez la taille de l'espace de stockage: ");
        SetColor(3);
        scanf("%d", &taille);
        SetColor(255);
    }
    gets(unite);//---------------------------------CORBEILLE (ou l'unité de la taille)
    SetColor(3);
    printf("\n>> Use Command");
    SetColor(13);
    printf(" [help] ");
    SetColor(3);
    printf("For Instructions\n");
    SetColor(255);

/*
  ---------------------------------------|
  -------------MAIN LOOP-----------------|
  ---------------------------------------|
*/

    while(1)
    {
        retour:
        memset(str,0,sizeof(str));
        memset(buffer,0,sizeof(buffer));
        memset(path,0,sizeof(path));
        memset(path_temp,0,sizeof(path_temp));
        memset(cmd,0,sizeof(cmd));
        memset(f_name,0,sizeof(f_name));

        f_name[0]='\0';
        corbeille[0]='\0';
        exist_path[0]='\0';
        level[0]='\0';
        rm_type = '\0';

        copier = NULL;
        copier2 = NULL;
        temp = base;
        temp2 = NULL;
        pre = base;
        p = NULL;
        file = NULL;

        filesize = -1;
/*--------------------------------------*/

        size= taille - get_size(base);
        printf("\n>> ");

        SetColor(11);
        gets(str);
        SetColor(255);

/*
  ---------------------------------------|
  -------------LES COMMANDES-------------|
  ---------------------------------------|
*/

/*-------------------------------------*/
        if(compare_cmd(str, "exit")) {
                return 0;
        }
/*-------------------------------------*/
        else {
            if(compare_cmd(str, "help")){
                printf("\n>> Commands That Need A Path Are Written In These Formats: \n     'CMD' '/PATH' 'FILE_NAME'      Or     'CMD' '/PATH/FILE_NAME'\n          %c__Spaces In Between Each One",24);
                printf("\n\n%c%c  LIST OF COMMANDS:\n    [exit]: end programme\n    [show]: show the path as a tree(yellow is directory, green is file)\n    [cls]: clear the window",175,175);
                printf("\n%c Commands That Need A Path:\n    [mkfile]: make a file    [mkdir]: make a directory    [cpfile]: copy a file",175);
                printf("\n      %c______________          %c                            __%c\n                    |These Three Work Only With First Format|",24,24,24);
                printf("\n    [cpdir]: copy a directory\n    [rm]: remove a file or a directory\n    [ls]: show inside current directory");
                printf("\n%c Special Case For This Command ,Only Needs The File Name Without A Path:\n   [exist]: show all the paths of the file name ",175);
                printf("\n\n%c An Exemple Of How To Work With A Command That Requires A Path(Both Formats):\n   First Format('CMD' '/PATH' 'FILE_NAME') %c mkfile /bin file01",175,16);
                printf("\n   Second Format('CMD' '/PATH/FILE_NAME')  %c ls /bin\n",16);
                goto retour;
            }
/*-------------------------------------*/
            if(compare_cmd(str, "show")) {
                parcours(temp, level);
                goto retour;
            }
/*-------------------------------------*/
            if (compare_cmd(str, "special")){
                printf("--------------------Î-------------------Î\n                    |                   |\n                    |   Amir Et Islam   |\n                    |                   |\n                    Î-------------------Î");
                goto retour;
            }
/*-------------------------------------*/
            if (compare_cmd(str,"storage")){
                SetColor(14);
                printf("\n>> Space left: [%03d]%s (use [help] command)\n", size, unite);
                SetColor(255);
                goto retour;
            }
/*-------------------------------------*/

            if(compare_cmd(str, "cls")) {
                    system("cls");
                    SetColor(3);
                    printf("\n>> Use Command");
                    SetColor(13);
                    printf(" [help] ");
                    SetColor(3);
                    printf("For Instructions\n");
                    SetColor(255);

            }
/*-------------------------------------*/

            else{
                cut2(str, cmd, path, f_name, corbeille);

/*-------------------------------------*/ //--------------TESTER SI IL Y A PLUS DE 3 ENTRES
                if(corbeille[0]!='\0'){
                    SetColor(4);
                    printf("\n>> Error.\n\n");
                    SetColor(255);
                    goto retour;
                }

                if(check(cmd, path, f_name)){
                    p = store_path(p, path);
                    file = store_file(file, f_name);

/*-------------------------------------*/
                    if(strcmp(cmd,"mkfile") == 0){
                        if(file != NULL){
                            if(file->Suivant != NULL){
                                printf("\n\n>> Warning: ");
                                SetColor(14);
                                printf("Too many Unnecessary Arguments\n");
                                SetColor(255);
                            }
                            printf("\n>> Enter File Size: ");
                            SetColor(3);
                            scanf("%d",&filesize);
                            SetColor(255);

                            while(filesize<=0){
                                    gets(corbeille);
                                    SetColor(4);
                                    printf(">> Error.\n");
                                    SetColor(255);
                                    printf("\n>>Enter File Size: ");
                                    SetColor(3);
                                    scanf("%d",&filesize);
                                    SetColor(255);
                            }
                            if(filesize < size){
                                gets(corbeille);
                                parcours_arbre(&temp ,p,buffer,&boolean1);
                                if(existe(temp,file->Nom,0)==0 && boolean1==1 ){
                                    if(temp->Rep==1){
                                        temp= ajouter_RF(temp, file->Nom, 0, filesize);
                                        printf(">> %s",buffer);
                                        printf(" (%s)", file->Nom);
                                    }
                                    else{
                                        printf("\n>> (%s) is not a directory",temp->Nom);
                                    }
                                }
                                else{
                                    if(existe(temp,file->Nom,0)==1){
                                        printf("\n>> File Already exists");
                                        printf(" (%s)", file->Nom);
                                    }
                                }
                            }
                            else{
                                gets(corbeille);
                                SetColor(4);
                                printf("\n>> Not Enough Space");
                                SetColor(255);
                            }
                        }
                        else printf(">>Empty file name.");

                    }
/*-------------------------------------*/

                    if(compare_cmd(cmd,"mkdir")){
                        if(*f_name != '\0'){
                            if(file->Suivant != NULL){
                                printf("\n\n>> Warning: ");
                                SetColor(14);
                                printf("Too many Unnecessary Arguments\n");
                                SetColor(255);
                            }
                            parcours_arbre(&temp ,p,buffer,&boolean1);
                            if(existe(temp,file->Nom,1)==0 && boolean1==1){
                                if(temp->Rep==1){
                                    temp= ajouter_RF(temp, file->Nom, 1, 0);
                                    printf("\n>> %s",buffer);
                                    printf(" (%s)", file->Nom);
                                }
                                else{
                                    printf("\n>> (%s) is not a directory",temp->Nom);
                                }
                            }
                            else{
                                if(existe(temp,file->Nom,1)==1){
                                    printf("\n>> Directory Already exists");
                                    printf(" (%s)", file->Nom);
                                }
                            }
                        }
                        else printf(">> Empty directory name.");
                    }

/*-------------------------------------*/
                    if(compare_cmd(cmd,"ls")){
                        if(f_name[0] != '\0'){
                            p=insert_queue(p, file->Nom);//----SI ON PEUT ECRIT A LA FORME: (OPERATION)(CHEMIN)(DOSSIER OU FICHIER)
                            if(file->Suivant != NULL){
                                printf("\n\n>> Warning: ");
                                SetColor(14);
                                printf("Too many Unnecessary Arguments\n");
                                SetColor(255);
                            }
                        }
                        parcours_arbre(&temp ,p,buffer,&boolean1);
                        if(boolean1==1){
                            if(temp->Rep==1){
                               ls(temp);
                            }
                            else{
                                printf("\n>> (%s) is not a directory",temp->Nom);
                            }
                        }
                    }

/*-------------------------------------*/
                    if(compare_cmd(cmd,"cpfile")){
                        if(file == NULL){
                            SetColor(4);
                            printf("\n>> Empty File Name\n");
                            SetColor(255);
                        }
                        else{
                            while(file != NULL){
                                temp = base;
                                parcours_arbre(&temp ,p,buffer,&boolean1);
                                if(serch_for_file(&temp, file->Nom)){
                                    copier=cpdir(temp);
                                    vider(&(copier)->Frere); //-------------Pour eviter de copier les frêres
                                    if(copier->Taille < size){
                                        temp=base;
                                        if(boolean1==1 && copier->Rep==0){
                                            p= NULL;
                                            printf("\n>> Enter Path Desired for (%s) : ",file->Nom);
                                            SetColor(3);
                                            scanf("%s",&path_temp);
                                            SetColor(255);
                                            gets(corbeille);
                                            p= store_path(p, path_temp);
                                            parcours_arbre(&temp ,p,buffer,&boolean1);
                                            if(existe(temp,copier->Nom,0)==0 && boolean1==1){
                                                if(temp->Rep==1){
                                                    temp=pastefile(temp,copier);
                                                    SetColor(2);
                                                    printf("\n>> File got pasted successfully\n");
                                                    SetColor(255);
                                                }
                                                else{
                                                    printf("\n>> Path Desired To Paste In Is Not A Directory");
                                                }
                                            }
                                            else{
                                                if(existe(temp,copier->Nom,0)==1 && boolean1 == 1){
                                                    printf("\n>> File Already exists");
                                                    printf(" (%s)\n", copier->Nom);
                                                }
                                            }
                                        }
                                        if(boolean1==1 && copier->Rep==1){
                                            printf("\n>> Object Desired To Copy Is Not A File");
                                        }
                                    }
                                    else{
                                        SetColor(4);
                                        printf("\n>> Not Enough Space");
                                        SetColor(255);
                                    }
                                }
                                else{
                                    SetColor(4);
                                    printf("\n>> The File ");
                                    SetColor(13);
                                    printf("'%s' ", file->Nom);
                                    SetColor(4);
                                    printf("Does not exist");
                                    SetColor(255);
                                }
                                file = file->Suivant;
                                temp = base;
                                p = NULL;
                                p = store_path(p, path);
                            }

                        }
                    }

/*-------------------------------------*/
                    if(compare_cmd(cmd,"cpdir")){
                        while(file != NULL){
                            p=insert_queue(p, file->Nom);//----SI ON PEUT ECRIT A LA FORME: (OPERATION)(CHEMIN)(DOSSIER OU FICHIER)
                            parcours_arbre(&temp ,p,buffer,&boolean1);
                            copier=cpdir(temp);
                            vider(&(copier)->Frere);//--------------Pour eviter de copier les frêres
                            if(get_size(copier) < size){
                                temp=base;
                                if(boolean1==1 && copier->Rep==1){
                                    p= NULL;
                                    printf("\n>> Enter Path Desired For [%s] : ", file->Nom);
                                    SetColor(3);
                                    scanf("%s",&path_temp);
                                    SetColor(255);
                                    gets(corbeille);
                                    p= store_path(p, path_temp);
                                    parcours_arbre(&temp ,p,buffer,&boolean1);
                                    if(existe(temp,copier->Nom,1)==0 && boolean1==1){
                                        if(temp->Rep==1){
                                            temp=pastefile(temp,copier);
                                            SetColor(2);
                                            printf("\n>> Directory got pasted successfully\n");
                                            SetColor(255);
                                        }
                                        else{
                                            printf("\n>> Path Desired To Paste In Is Not A Directory");
                                        }
                                    }
                                    else{
                                        if(existe(temp,copier->Nom,1)==1 && boolean1 == 1){
                                            printf("\n>> Directory already exists");
                                            printf(" [%s] \n", copier->Nom);
                                        }
                                    }
                                }
                                if(boolean1==1 && copier->Rep==0){
                                    printf("\n>> Object Desired To Copy Is Not A Directory");
                                }
                            }
                            else{
                                SetColor(4);
                                printf("\n>> Not Enough Space");
                                SetColor(255);
                            }
                            file= file->Suivant;
                            p = NULL;
                            p = store_path(p, path);
                            temp = base;
                        }
                        /*-------------------*///copier le contenu de l'adress
                        if(f_name[0] == '\0'){
                            parcours_arbre(&temp ,p,buffer,&boolean1);
                            if(boolean1 == 1){
                                if(temp->Fils == NULL){
                                    SetColor(4);
                                    printf("\n>> Empty Empty Directory");
                                    SetColor(255);
                                }
                                else{
                                    temp = temp->Fils;
                                    printf("\n>> Enter Path Desired: ");
                                    SetColor(3);
                                    scanf("%s",&path_temp);
                                    SetColor(255);
                                    gets(corbeille);
                                    p = NULL;
                                    p = store_path(p, path_temp);
                                    temp2 = base;
                                    parcours_arbre(&temp2 ,p,buffer,&boolean1);
                                    copier2 = cpdir(temp2->Fils);
                                    if(boolean1 == 1){
                                        while(temp != NULL){
                                            copier = cpdir(temp);
                                            vider(&(copier)->Frere);//--------------Pour eviter de copier les frêres
                                            if(strcmp(copier->Nom, temp2->Nom) == 0){
                                                vider(&(copier)->Fils);//--------------Pour eviter de copier les Fils deja copiee si le repertoire est le meme
                                                copier->Fils = copier2;
                                            }
                                            if(get_size(copier) > size){
                                                SetColor(4);
                                                printf("\n>> Not Enough Space");
                                                SetColor(255);
                                            }
                                            else{
                                                if(existe(temp2,copier->Nom,copier->Rep) == 1){
                                                    printf("\n>> ");
                                                    SetColor(4);
                                                    if(copier->Rep == 1) printf("Directory already exists");
                                                    else printf("File already exists");
                                                    SetColor(14);
                                                    printf(" (%s)", copier->Nom);
                                                    SetColor(255);
                                                }
                                                else{
                                                    temp2 = pastefile(temp2,copier);
                                                    if(copier->Rep == 1) printf("\n>> The Directory '%s' Has been pasted successfully", copier->Nom);
                                                    else printf("\n>> The File '%s' Has been pasted successfully", copier->Nom);
                                                }
                                            }
                                            temp = temp->Frere;
                                        }
                                    }
                                }
                            }
                        }
                    }

/*-------------------------------------*/
//

/*-------------------------------------*/

                        if(compare_cmd(cmd,"rm")){
                            if(f_name[0] != '\0'){
                                while(file != NULL){
                                    parcours_arbre(&temp ,p,buffer,&boolean1);
                                    temp2 = temp;
                                    if(existe(temp, file->Nom, 0) && existe(temp, file->Nom, 1) == 0){//----file
                                        rmfile://------------------label
                                        serch_for_file(&temp, file->Nom);
                                        get_pre(base, &pre, temp);
                                        if(boolean1 == 1){
                                            if (strcmp(path,"/")==0 && f_name[0] == '\0'){
                                                SetColor(4);
                                                printf("\n>> Directory Cant Be Removed\n");
                                                SetColor(255);
                                            }
                                            else {
                                                rm(&temp, &pre);
                                                printf("\n>> The File '%s' Have Been Removed Successfully", file->Nom);
                                            }
                                        }
                                        if(rm_type == 'b') {
                                            temp = temp2;
                                            goto rmdir;
                                        }
                                    }
                                    else{
                                        if(existe(temp, file->Nom, 1) && existe(temp, file->Nom, 0) == 0){//---dir
                                            rmdir:
                                            serch_for_dir(&temp, file->Nom);
                                            get_pre(base, &pre, temp);
                                            if(boolean1 == 1){
                                                if (strcmp(path,"/")==0 && f_name[0] == '\0'){
                                                    SetColor(4);
                                                    printf("\n>> Directory Cant Be Removed\n");
                                                    SetColor(255);
                                                }
                                                else {
                                                    rm(&temp, &pre);
                                                    printf("\n>> The Directory '%s' Have Been Removed Successfully", file->Nom);
                                                }
                                            }
                                        }
                                        else{
                                            if(existe(temp, file->Nom, 1) && existe(temp, file->Nom, 0)){
                                                printf("\n\n>> There are a FILE and a DIRECTORY with the same name '%s'", file->Nom);
                                                repeat:
                                                printf("\n   Press 'f' to remove the file\n   press 'd' to remove the directory\n   press 'b' to remove both\n>> ");
                                                scanf("%c", &rm_type);
                                                gets(corbeille);

                                                switch (rm_type){
                                                    case 'f':
                                                        goto rmfile;
                                                        break;
                                                    case 'd':
                                                        goto rmdir;
                                                        break;
                                                    case 'b':
                                                        goto rmfile;
                                                        break;
                                                    default:
                                                        SetColor(4);
                                                        printf("\n>> Wrong input");
                                                        SetColor(255);
                                                        goto repeat;
                                                }
                                            }
                                            else{
                                                SetColor(4);
                                                printf("\n>> 'File/Directory' Does Not Exist\n");
                                                SetColor(255);
                                            }
                                        }
                                    }
                                    file = file->Suivant;
                                    pre = base;
                                    temp = base;
                                    p = NULL;
                                    p = store_path(p, path);
                                }
                            }
                            else{
                                parcours_arbre(&temp ,p,buffer,&boolean1);
                                if(boolean1  == 1){
                                    if(temp->Fils == NULL){
                                        SetColor(4);
                                        printf("\n>> Empty Directory");
                                        SetColor(255);
                                    }
                                    else {
                                        printf("\n>> The folder '%s' has been emptied ", temp->Nom);
                                        vider(&(temp)->Fils);
                                    }
                                }
                            }
                        }

/*-------------------------------------*/

                        if(compare_cmd(cmd,"exist")){
                            file = insert_head(file, path);
                            while(file != NULL){
                                p= NULL;
                                temp= cpdir(base);
                                temp2= temp;
                                if(exist_tp(file->Nom, &p, &temp2)){
                                    show_path(p);
                                    printf(" %c%c%c  '%s'",205,205,16, file->Nom);
                                    //else printf(":             '%s' [%03d] (File)", temp2->Nom, temp2->Taille);
                                    p= NULL;
                                    temp2= temp;
                                    while(exist_tp(file->Nom, &p, &temp2)){
                                        show_path(p);
                                        printf(" %c%c%c  '%s'",205,205,16, file->Nom);
                                        //else printf(":             '%s' [%03d] (File)", temp2->Nom, temp2->Taille);
                                        p= NULL;
                                        temp2= temp;
                                    }
                                }
                                else{
                                    SetColor(4);
                                    printf("\n>> File or directory '%s' does not exist\n", file->Nom);
                                    SetColor(255);
                                }
                                file = file->Suivant;
                            }
                        }
/*-------------------------------------*/
                       else{
                            if(compare_cmd(cmd,"ls")==0 && compare_cmd(cmd,"mkfile")==0 && compare_cmd(cmd,"mkdir")==0 && compare_cmd(cmd,"cpfile")==0 && compare_cmd(cmd,"cpdir")==0 && compare_cmd(cmd,"rm")==0 && compare_cmd(cmd,"exist")==0){
                                SetColor(4);
                                printf("\n>> Invalide Command\n");
                                SetColor(255);
                            }
                        }

/*-------------------------------------*/
                printf("\n");
                }
                else{
                    SetColor(4);
                    printf("\n>> Invalide Command\n");
                    SetColor(255);
                }
            }
         }
   }
}

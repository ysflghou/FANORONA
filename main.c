#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


typedef struct chemsuiv{ // contient l'historique du chemin d'un pion
    int mat[20];
    int z;
}chemsuiv;

void initialiser_chemsuiv(chemsuiv* a){
    int i;
    for(i=0;i<20;i++){
        a->mat[i]=100;
    }
    a->z=0;
}

typedef struct pion{
    int i;  // (i,j) les coordonnées du pion
    int j;
    int curseur; // le curseur sur le pion à déplacer
    char genre; // son genre : blanc, noir ,ou vide
    int chem; // nombre de 8 chiffres qui va expliciter les positions de déplacements possibles
}pion;

typedef struct plateau{
    pion Mat[5][9]; // les pions
    int pn; //nombre de pions noirs
    int pb; // nombre de pions blancs
}plateau;

void initialiser(plateau* P){ // initialisation du plateau et le nombre de pions
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<9;j++)
        {
            pion p={i,j,0,'B',0};
            P->Mat[i][j]=p;
        }
    }
    pion p0={2,0,0,'N',0};
    P->Mat[2][0]=p0;
    pion p1={2,2,0,'N',0};
    P->Mat[2][2]=p1;
    pion p2={2,4,0,' ',0};
    P->Mat[2][4]=p2;
    pion p3={2,5,0,'N',0};
    P->Mat[2][5]=p3;
    pion p4={2,7,0,'N',0};
    P->Mat[2][7]=p4;
    for(i=3;i<5;i++)
    {
        for(j=0;j<9;j++)
        {
            pion p={i,j,0,'N',0};
            P->Mat[i][j]=p;
        }
    }
    P->pb=22;
    P->pn=22;
}

void print_pion(plateau P,int i,int j){ // definir la couleur des pions et du curseur
    if(P.Mat[i][j].genre==' ') {printf("   "); return;}
    if(P.Mat[i][j].curseur==1) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10); printf("<"); } // curseur
    else if(P.Mat[i][j].curseur==2) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); printf("<"); } // selectionnée
    else printf(" ");
    if(P.Mat[i][j].genre=='B') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);  // pion blanc
    else if(P.Mat[i][j].genre=='N') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);  // pion noir
    printf("O");
    if(P.Mat[i][j].curseur==1) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10); printf(">"); } // curseur
    else if(P.Mat[i][j].curseur==2) {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12); printf(">"); } // selectionnée
    else printf(" ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void print_chemin(plateau P,int i,int j,int c){ // les directions et leurs couleurs
    if(c==3){
        if(((P.Mat[i][j].chem)%1000)/100==1 || ((P.Mat[i][j+1].chem)%10000000)/1000000==1)
            {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); printf("---");}
        else printf("---");
    }
    if(c==1){
        if(((P.Mat[i][j].chem)%100000)/10000==1 || ((P.Mat[i+1][j].chem)%10)/1==1)
            {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); printf(" | ");}
        else printf(" | ");
    }
    if(c/10==2){
        if(((P.Mat[i][j].chem)%1000000)/100000==1 || ((P.Mat[i+1][j-1].chem)%100)/10==1)
            {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); if(c%10==1) printf(" / "); else printf("/  "); }
        else{if(c%10==1) printf(" / "); else printf("/  "); }
    }
    if(c/10==4){
        if(((P.Mat[i][j].chem)%10000)/1000==1 || ((P.Mat[i+1][j+1].chem)%100000000)/10000000==1)
            {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11); if(c%10==1) printf(" \\ "); else printf("  \\"); }
        else {if(c%10==1) printf(" \\ "); else printf("  \\");}
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void afficher(plateau P){      // affichage complet du jeu
    system("cls"); // efface l'ecran
    int i,j;
    printf("\n\n\n\n\n                         #BONJOUR#\n\n\n\n\n");
    printf("\n   °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    for(i=0;i<5;i++)
    {
        printf("   °");
        for(j=0;j<8;j++)
        {
            print_pion(P,i,j);
            print_chemin(P,i,j,3);
        }
        print_pion(P,i,j);
        printf("°\n");
        if(i%2==0 && i!=4)
        {
            printf("   °");print_chemin(P,i,0,1);print_chemin(P,i,0,41); print_chemin(P,i,1,1);print_chemin(P,i,2,21);
            print_chemin(P,i,2,1);print_chemin(P,i,2,41);print_chemin(P,i,3,1);print_chemin(P,i,4,21);print_chemin(P,i,4,1);
            print_chemin(P,i,4,41);print_chemin(P,i,5,1);print_chemin(P,i,6,21);print_chemin(P,i,6,1);print_chemin(P,i,6,41);
            print_chemin(P,i,7,1);print_chemin(P,i,8,21);print_chemin(P,i,8,1);printf("°\n");
            printf("   °");print_chemin(P,i,0,1);print_chemin(P,i,0,42); print_chemin(P,i,1,1);print_chemin(P,i,2,22);
            print_chemin(P,i,2,1);print_chemin(P,i,2,42);print_chemin(P,i,3,1);print_chemin(P,i,4,22);print_chemin(P,i,4,1);
            print_chemin(P,i,4,42);print_chemin(P,i,5,1);print_chemin(P,i,6,22);print_chemin(P,i,6,1);print_chemin(P,i,6,42);
            print_chemin(P,i,7,1);print_chemin(P,i,8,22);print_chemin(P,i,8,1);printf("°\n");
        }
        else if(i%2==1)
        {
            printf("   °");print_chemin(P,i,0,1);print_chemin(P,i,1,21);print_chemin(P,i,1,1);print_chemin(P,i,1,41);
            print_chemin(P,i,2,1);print_chemin(P,i,3,21);print_chemin(P,i,3,1);print_chemin(P,i,3,41); print_chemin(P,i,4,1);
            print_chemin(P,i,5,21);print_chemin(P,i,5,1);print_chemin(P,i,5,41); print_chemin(P,i,6,1);print_chemin(P,i,7,21);
            print_chemin(P,i,7,1);print_chemin(P,i,7,41); print_chemin(P,i,8,1);printf("°\n");
            printf("   °");print_chemin(P,i,0,1);print_chemin(P,i,1,22);print_chemin(P,i,1,1);print_chemin(P,i,1,42);
            print_chemin(P,i,2,1);print_chemin(P,i,3,22);print_chemin(P,i,3,1);print_chemin(P,i,3,42); print_chemin(P,i,4,1);
            print_chemin(P,i,5,22);print_chemin(P,i,5,1);print_chemin(P,i,5,42); print_chemin(P,i,6,1);print_chemin(P,i,7,22);
            print_chemin(P,i,7,1);print_chemin(P,i,7,42); print_chemin(P,i,8,1);printf("°\n");
        }
    }
    printf("   °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
}

// déplacement du curseur dans differents sens
void curseur_haut(plateau *P,int *ci,int *cj,char player){
    int k=1;
    while(*ci>0 && (P->Mat[*ci-k][*cj].genre==player || *ci-k!=0)){
        if(P->Mat[*ci-k][*cj].genre==player) {P->Mat[*ci][*cj].curseur=0; *ci-=k; P->Mat[*ci][*cj].curseur=1; afficher(*P); return;}
        k++;
    }
}

void curseur_haut_droite(plateau *P,int *ci,int *cj,char player){
    int i,j;
    for(i=*ci-1;i>=0;i--){
        for(j=*cj+1;j<=8;j++){
            if(P->Mat[i][j].genre==player) {P->Mat[*ci][*cj].curseur=0; *ci=i; *cj=j; P->Mat[*ci][*cj].curseur=1; afficher(*P); return;}
        }
    }
}

void curseur_droite(plateau *P,int *ci,int *cj,char player){
    int k=1;
    while(*cj<8 && (P->Mat[*ci][*cj+k].genre==player || *cj+k!=8)){
        if(P->Mat[*ci][*cj+k].genre==player) {P->Mat[*ci][*cj].curseur=0; *cj+=k; P->Mat[*ci][*cj].curseur=1; afficher(*P); break;}
        k++;
    }
}

void curseur_droite_bas(plateau *P,int *ci,int *cj,char player){
    int i,j;
    for(i=*ci+1;i<=4;i++){
        for(j=*cj+1;j<=8;j++){
            if(P->Mat[i][j].genre==player) {P->Mat[*ci][*cj].curseur=0; *ci=i; *cj=j; P->Mat[*ci][*cj].curseur=1; afficher(*P); return;}
        }
    }
}

void curseur_bas(plateau *P,int *ci,int *cj,char player){
    int k=1;
    while(*ci<4 && (P->Mat[*ci+k][*cj].genre==player || *ci+k!=4)){
        if(P->Mat[*ci+k][*cj].genre==player ) {P->Mat[*ci][*cj].curseur=0; *ci+=k; P->Mat[*ci][*cj].curseur=1; afficher(*P); break;}
        k++;
    }
}

void curseur_bas_gauche(plateau *P,int *ci,int *cj,char player){
    int i,j;
    for(i=*ci+1;i<=4;i++){
        for(j=*cj-1;j>=0;j--){
            if(P->Mat[i][j].genre==player) {P->Mat[*ci][*cj].curseur=0; *ci=i; *cj=j; P->Mat[*ci][*cj].curseur=1; afficher(*P); return;}
        }
    }
}

void curseur_gauche(plateau *P,int *ci,int *cj,char player){
    int k=1;
    while(*cj>0 && (P->Mat[*ci][*cj-k].genre==player || *cj-k!=0)){
        if(P->Mat[*ci][*cj-k].genre==player) {P->Mat[*ci][*cj].curseur=0; *cj-=k; P->Mat[*ci][*cj].curseur=1; afficher(*P); return;}
        k++;
    }
}

void curseur_gauche_haut(plateau *P,int *ci,int *cj,char player){
    int i,j;
    for(i=*ci-1;i>=0;i--){
        for(j=*cj-1;j>=0;j--){
            if(P->Mat[i][j].genre==player) {P->Mat[*ci][*cj].curseur=0; *ci=i; *cj=j; P->Mat[*ci][*cj].curseur=1; afficher(*P); return;}
        }
    }
}

void curseur_select(plateau *P,int ci,int cj, chemsuiv a){
    if(P->Mat[ci][cj].curseur==2) { P->Mat[ci][cj].chem=0; P->Mat[ci][cj].curseur=1; }
    else { P->Mat[ci][cj].curseur=2; P->Mat[ci][cj].chem=chemin(P,ci,cj,a); }
    afficher(*P);
}

char adv(char c){ // return l'adversaire
    if(c=='B') return 'N';
    else if(c=='N') return 'B';
    else return ' ';
}

int chemin(plateau *P,int ci,int cj,chemsuiv a){ // determine les chemins possibles
// capture des pions au differents sens
    int c=0;
    if(ci-1>0 && ci!=4){
        if(existe((ci-1)*10+cj,a)==0 && P->Mat[ci-1][cj].genre==' ' && (P->Mat[ci+1][cj].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci-2][cj].genre==adv(P->Mat[ci][cj].genre))) c=c+1;
    }
    else if(ci==1){
        if(existe((ci-1)*10+cj,a)==0 && P->Mat[ci-1][cj].genre==' ' && P->Mat[ci+1][cj].genre==adv(P->Mat[ci][cj].genre)) c=c+1;
    }
    else if(ci==4){
        if(existe((ci-1)*10+cj,a)==0 && P->Mat[ci-1][cj].genre==' ' && P->Mat[ci-2][cj].genre==adv(P->Mat[ci][cj].genre)) c=c+1;
    }
    if(ci+1<4 && ci!=0){
        if(existe((ci+1)*10+cj,a)==0 && P->Mat[ci+1][cj].genre==' ' && (P->Mat[ci-1][cj].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci+2][cj].genre==adv(P->Mat[ci][cj].genre))) c=c+10000;
    }
    else if(ci==3){
        if(existe((ci+1)*10+cj,a)==0 && P->Mat[ci+1][cj].genre==' ' && P->Mat[ci-1][cj].genre==adv(P->Mat[ci][cj].genre)) c=c+10000;
    }
    else if(ci==0){
        if(existe((ci+1)*10+cj,a)==0 && P->Mat[ci+1][cj].genre==' ' && P->Mat[ci+2][cj].genre==adv(P->Mat[ci][cj].genre)) c=c+10000;
    }
    if(cj+1<8 && cj!=0){
        if(existe(ci*10+cj+1,a)==0 && P->Mat[ci][cj+1].genre==' ' && (P->Mat[ci][cj-1].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci][cj+2].genre==adv(P->Mat[ci][cj].genre))) c=c+100;
    }
    else if(cj==7){
        if(existe(ci*10+cj+1,a)==0 && P->Mat[ci][cj+1].genre==' ' && P->Mat[ci][cj-1].genre==adv(P->Mat[ci][cj].genre)) c=c+100;
    }
    else if(cj==0){
        if(existe(ci*10+cj+1,a)==0 && P->Mat[ci][cj+1].genre==' ' && P->Mat[ci][cj+2].genre==adv(P->Mat[ci][cj].genre)) c=c+100;
    }
    if(cj-1>0 && cj!=8){
        if(existe(ci*10+cj-1,a)==0 && P->Mat[ci][cj-1].genre==' ' && (P->Mat[ci][cj+1].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci][cj-2].genre==adv(P->Mat[ci][cj].genre))) c=c+1000000;
    }
    else if(cj==1){
        if(existe(ci*10+cj-1,a)==0 && P->Mat[ci][cj-1].genre==' ' && P->Mat[ci][cj+1].genre==adv(P->Mat[ci][cj].genre)) c=c+1000000;
    }
    else if(cj==8){
        if(existe(ci*10+cj-1,a)==0 && P->Mat[ci][cj-1].genre==' ' && P->Mat[ci][cj-2].genre==adv(P->Mat[ci][cj].genre)) c=c+1000000;
    }
    if((ci+cj)%2==0){
        if(ci-1>0 && cj+1<8 && ci!=4 && cj!=0){
            if(existe((ci-1)*10+cj+1,a)==0 && P->Mat[ci-1][cj+1].genre==' ' && (P->Mat[ci+1][cj-1].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci-2][cj+2].genre==adv(P->Mat[ci][cj].genre))) c=c+10;
        }
        else if(ci==1 && cj<=7 || ci>=1 && cj==7){
            if(existe((ci-1)*10+cj+1,a)==0 && P->Mat[ci-1][cj+1].genre==' ' && P->Mat[ci+1][cj-1].genre==adv(P->Mat[ci][cj].genre)) c=c+10;
        }
        else if(ci==4 && cj<=6 || ci>=2 && cj==0){
            if(existe((ci-1)*10+cj+1,a)==0 && P->Mat[ci-1][cj+1].genre==' ' && P->Mat[ci-2][cj+2].genre==adv(P->Mat[ci][cj].genre)) c=c+10;
        }
        if(ci+1<4 && cj+1<8 && ci!=0 && cj!=0){
            if(existe((ci+1)*10+cj+1,a)==0 && P->Mat[ci+1][cj+1].genre==' ' && (P->Mat[ci-1][cj-1].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci+2][cj+2].genre==adv(P->Mat[ci][cj].genre))) c=c+1000;
        }
        else if(ci==3 && cj<=7 || ci<=3 && cj==7){
            if(existe((ci+1)*10+cj+1,a)==0 && P->Mat[ci+1][cj+1].genre==' ' && P->Mat[ci-1][cj-1].genre==adv(P->Mat[ci][cj].genre)) c=c+1000;
        }
        else if(ci==0 && cj<=6 || ci<=2 && cj==0){
            if(existe((ci+1)*10+cj+1,a)==0 && P->Mat[ci+1][cj+1].genre==' ' &&  P->Mat[ci+2][cj+2].genre==adv(P->Mat[ci][cj].genre)) c=c+1000;
        }
        if(ci+1<4 && cj-1>0 && ci!=0 && cj!=8){
            if(existe((ci+1)*10+cj-1,a)==0 && P->Mat[ci+1][cj-1].genre==' ' && (P->Mat[ci-1][cj+1].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci+2][cj-2].genre==adv(P->Mat[ci][cj].genre))) c=c+100000;
        }
        else if(ci==3 && cj>=1 || ci<=3 && cj==1){
            if(existe((ci+1)*10+cj-1,a)==0 && P->Mat[ci+1][cj-1].genre==' ' && P->Mat[ci-1][cj+1].genre==adv(P->Mat[ci][cj].genre)) c=c+100000;
        }
        else if(ci==0 && cj>=2 || ci<=2 && cj==8){
            if(existe((ci+1)*10+cj-1,a)==0 && P->Mat[ci+1][cj-1].genre==' ' && P->Mat[ci+2][cj-2].genre==adv(P->Mat[ci][cj].genre)) c=c+100000;
        }
        if(ci-1>0 && cj-1>0 && ci!=4 && cj!=8){
            if(existe((ci-1)*10+cj-1,a)==0 && P->Mat[ci-1][cj-1].genre==' ' && (P->Mat[ci+1][cj+1].genre==adv(P->Mat[ci][cj].genre) || P->Mat[ci-2][cj-2].genre==adv(P->Mat[ci][cj].genre))) c=c+10000000;
        }
        else if(ci==1 && cj>=1 || ci>=1 && cj==1){
            if(existe((ci-1)*10+cj-1,a)==0 && P->Mat[ci-1][cj-1].genre==' ' && P->Mat[ci+1][cj+1].genre==adv(P->Mat[ci][cj].genre)) c=c+10000000;
        }
        else if(ci==4 && cj>=2 || ci>=2 && cj==8){
            if(existe((ci-1)*10+cj-1,a)==0 && P->Mat[ci-1][cj-1].genre==' ' && P->Mat[ci-2][cj-2].genre==adv(P->Mat[ci][cj].genre)) c=c+10000000;
        }
    }
    return c;
}

void attack_haut(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*ci<4 && *ci>1 && P->Mat[*ci+1][*cj].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci-2][*cj].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || (*ci==4 || ((P->Mat[*ci+1][*cj].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci+1][*cj].genre==' ') && *ci!=4))){
        k+=1;
        while(P->Mat[*ci-k][*cj].genre==adv(P->Mat[*ci][*cj].genre) && k<=*ci){
            if(P->Mat[*ci-k][*cj].genre=='N')        P->pn-=1;
            else if(P->Mat[*ci-k][*cj].genre=='B')       P->pb-=1;
            P->Mat[*ci-k][*cj].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci+1][*cj].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci+k][*cj].genre==adv(P->Mat[*ci][*cj].genre) && *ci+k<=4){
            if(P->Mat[*ci+k][*cj].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci+k][*cj].genre=='N')       P->pn-=1;
            P->Mat[*ci+k][*cj].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci-1][*cj].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci-1][*cj].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *ci-=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_haut_droite(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*ci<4 && *cj>0 && *cj<7 && *ci>1 && P->Mat[*ci+1][*cj-1].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci-2][*cj+2].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || (*ci==4 || *cj==0 || ((P->Mat[*ci+1][*cj-1].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci+1][*cj-1].genre==' ') && *ci!=4 && *cj!=0))){
        k+=1;
        while(P->Mat[*ci-k][*cj+k].genre==adv(P->Mat[*ci][*cj].genre) && k<=*ci && *cj+k<=8){
            if(P->Mat[*ci-k][*cj+k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci-k][*cj+k].genre=='N')       P->pn-=1;
            P->Mat[*ci-k][*cj+k].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci+1][*cj-1].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci+k][*cj-k].genre==adv(P->Mat[*ci][*cj].genre) && *ci+k<=4 && *cj-k>=0){
            if(P->Mat[*ci+k][*cj-k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci+k][*cj-k].genre=='N')       P->pn-=1;
            P->Mat[*ci+k][*cj-k].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci-1][*cj+1].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci-1][*cj+1].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *ci-=1;
    *cj+=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_droite(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*cj>0 && *cj<7 && P->Mat[*ci][*cj-1].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci][*cj+2].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || ((*cj==0 || (P->Mat[*ci][*cj-1].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci][*cj-1].genre==' ') && *cj!=0))) {
        k+=1;
        while(P->Mat[*ci][*cj+k].genre==adv(P->Mat[*ci][*cj].genre) && *cj+k<=8){
            if(P->Mat[*ci][*cj+k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci][*cj+k].genre=='N')       P->pn-=1;
            P->Mat[*ci][*cj+k].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci][*cj-1].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci][*cj-k].genre==adv(P->Mat[*ci][*cj].genre) && *cj-k>=0){
            if(P->Mat[*ci][*cj-k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci][*cj-k].genre=='N')       P->pn-=1;
            P->Mat[*ci][*cj-k].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci][*cj+1].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci][*cj+1].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *cj+=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_droite_bas(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*ci>0 && *cj>0 && *cj<7 && *ci<3 && P->Mat[*ci-1][*cj-1].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci+2][*cj+2].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || (*ci==0 || *cj==0 || ((P->Mat[*ci-1][*cj-1].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci-1][*cj-1].genre==' ') && *ci!=0 && *cj!=0))){
        k+=1;
        while(P->Mat[*ci+k][*cj+k].genre==adv(P->Mat[*ci][*cj].genre) && k+*ci<=4 && *cj+k<=8){
            if(P->Mat[*ci+k][*cj+k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci+k][*cj+k].genre=='N')       P->pn-=1;
            P->Mat[*ci+k][*cj+k].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci-1][*cj-1].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci-k][*cj-k].genre==adv(P->Mat[*ci][*cj].genre) && *ci-k>=0 && *cj-k>=0){
            if(P->Mat[*ci-k][*cj-k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci-k][*cj-k].genre=='N')       P->pn-=1;
            P->Mat[*ci-k][*cj-k].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci+1][*cj+1].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci+1][*cj+1].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *ci+=1;
    *cj+=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_bas(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*ci>0 && *ci<3 && P->Mat[*ci-1][*cj].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci+2][*cj].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || ((*ci==0 || (P->Mat[*ci-1][*cj].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci-1][*cj].genre==' ') && *ci!=0))) {
        k+=1;
        while(P->Mat[*ci+k][*cj].genre==adv(P->Mat[*ci][*cj].genre) && *ci+k<=4){
            if(P->Mat[*ci+k][*cj].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci+k][*cj].genre=='N')       P->pn-=1;
            P->Mat[*ci+k][*cj].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci-1][*cj].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci-k][*cj].genre==adv(P->Mat[*ci][*cj].genre) && *ci-k>=0){
            if(P->Mat[*ci-k][*cj].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci-k][*cj].genre=='N')       P->pn-=1;
            P->Mat[*ci-k][*cj].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci+1][*cj].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci+1][*cj].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *ci+=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_bas_gauche(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*ci>0 && *cj<8 && *cj>1 && *ci<3 && P->Mat[*ci-1][*cj+1].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci+2][*cj-2].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || (*ci==0 || *cj==8 || ((P->Mat[*ci-1][*cj+1].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci-1][*cj+1].genre==' ') && *ci!=0 && *cj!=8))){
        k+=1;
        while(P->Mat[*ci+k][*cj-k].genre==adv(P->Mat[*ci][*cj].genre) && k+*ci<=4 && *cj-k>=0){
            if(P->Mat[*ci+k][*cj-k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci+k][*cj-k].genre=='N')       P->pn-=1;
            P->Mat[*ci+k][*cj-k].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci-1][*cj+1].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci-k][*cj+k].genre==adv(P->Mat[*ci][*cj].genre) && *ci-k>=0 && *cj+k<=8){
            if(P->Mat[*ci-k][*cj+k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci-k][*cj+k].genre=='N')       P->pn-=1;
            P->Mat[*ci-k][*cj+k].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci+1][*cj-1].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci+1][*cj-1].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *ci+=1;
    *cj-=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_gauche(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*cj<8 && *cj>1 && P->Mat[*ci][*cj+1].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci][*cj-2].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || (*cj==8 || ((P->Mat[*ci][*cj+1].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci][*cj+1].genre==' ') && *cj!=8))){
        k+=1;
        while(P->Mat[*ci][*cj-k].genre==adv(P->Mat[*ci][*cj].genre) && k<=*cj){
            if(P->Mat[*ci][*cj-k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci][*cj-k].genre=='N')       P->pn-=1;
            P->Mat[*ci][*cj-k].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci][*cj+1].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci][*cj+k].genre==adv(P->Mat[*ci][*cj].genre) && *cj+k<=8){
            if(P->Mat[*ci][*cj+k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci][*cj+k].genre=='N')       P->pn-=1;
            P->Mat[*ci][*cj+k].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci][*cj-1].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci][*cj-1].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *cj-=1;
    curseur_select(P,*ci,*cj,*a);
}

void attack_gauche_haut(plateau *P,int *ci,int *cj,chemsuiv *a){
    char c='r';
    int k=1;
    if(*ci<4 && *cj<8 && *cj>1 && *ci>1 && P->Mat[*ci+1][*cj+1].genre==adv(P->Mat[*ci][*cj].genre) && P->Mat[*ci-2][*cj-2].genre==adv(P->Mat[*ci][*cj].genre)){
        printf("   percussion(p)/aspiration(a)?: ");
        scanf("%c",&c);
        fflush(stdin);
    }
    if(c=='p' || (*ci==4 || *cj==8 || ((P->Mat[*ci+1][*cj+1].genre==P->Mat[*ci][*cj].genre || P->Mat[*ci+1][*cj+1].genre==' ') && *ci!=4 && *cj!=8))){
        k+=1;
        while(P->Mat[*ci-k][*cj-k].genre==adv(P->Mat[*ci][*cj].genre) && *ci-k>=0 && *cj-k>=0){
            if(P->Mat[*ci-k][*cj-k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci-k][*cj-k].genre=='N')       P->pn-=1;
            P->Mat[*ci-k][*cj-k].genre=' ';
            k++;
        }
    }
    else if(c=='a' || P->Mat[*ci+1][*cj+1].genre==adv(P->Mat[*ci][*cj].genre)){
        while(P->Mat[*ci+k][*cj+k].genre==adv(P->Mat[*ci][*cj].genre) && *ci+k<=4 && *cj+k<=8){
            if(P->Mat[*ci+k][*cj+k].genre=='B')        P->pb-=1;
            else if(P->Mat[*ci+k][*cj+k].genre=='N')       P->pn-=1;
            P->Mat[*ci+k][*cj+k].genre=' ';
            k++;
        }
    }
    a->mat[a->z]=(*ci)*10+*cj;
    a->z+=1;
    P->Mat[*ci-1][*cj-1].genre=P->Mat[*ci][*cj].genre;
    P->Mat[*ci-1][*cj-1].curseur=1;
    P->Mat[*ci][*cj].genre=' ';
    P->Mat[*ci][*cj].chem=0;
    P->Mat[*ci][*cj].curseur=0;
    *ci-=1;
    *cj-=1;
    curseur_select(P,*ci,*cj,*a);
}

int transformer(int a){ // la somme des chiffres d'un nombre pour calculer le nombre des déplacements possibles
    int b=0;
    b+=(a%100000000)/10000000;
    b+=(a%10000000)/1000000;
    b+=(a%1000000)/100000;
    b+=(a%100000)/10000;
    b+=(a%10000)/1000;
    b+=(a%1000)/100;
    b+=(a%100)/10;
    b+=(a%10)/1;
    return b;
}

void curseur_par_def(plateau *P,int *ci,int *cj,char player,chemsuiv a){ // pour mettre curseur dans la bonne position
    P->Mat[*ci][*cj].curseur=0;
    int i;
    int j;
    int k=0;
    int tab[22][3];
    for(i=0;i<22;i++){
        for(j=0;j<3;j++){
            tab[i][j]=0;
        }
    }
    for(i=0;i<5;i++){
        for(j=0;j<9;j++){
            if(P->Mat[i][j].genre==player){
               tab[k][0]=transformer(chemin(P,i,j,a));
               tab[k][1]=i;
               tab[k][2]=j;
               k++;
            }
        }
    }
    int max;
    for(i=0;i<5;i++){
        for(j=0;j<9;j++){
            if(P->Mat[i][j].genre==player){
                max=transformer(chemin(P,i,j,a));
                *ci=i;
                *cj=j;
            }
        }
    }
    for(i=0;i<22;i++){
            if(tab[i][0]>max){
                max=tab[i][0];
                *ci=tab[i][1];
                *cj=tab[i][2];
            }
    }
    P->Mat[*ci][*cj].curseur=1;
    afficher(*P);
}

void TogglePlayer(char *player,chemsuiv *a){ // changer les roles
    if(*player=='N') *player='B';
    else *player='N';
    initialiser_chemsuiv(a); // mettre à niveayu de a pour une autre utilisation
}

int existe(int n,chemsuiv a){ //verifier si un chemin est possible
    int i;
    for(i=0;i<20;i++){
        if(n==a.mat[i]) return 1;
    }
    return 0;
}

int main()
{
    plateau P; //affichage
    chemsuiv a;
    initialiser(&P);
    initialiser_chemsuiv(&a);
    char player='N';
    int key=0,ci=0,cj=0;
    curseur_par_def(&P,&ci,&cj,player,a);
    while(1){ // boucle infini
        key=0;
        key = getch(); // lire les données du clavier
        if(P.Mat[ci][cj].curseur==1){ // donner les chemins possibles selon les sens de déplacement
            if(key==56)  curseur_haut(&P,&ci,&cj,player);
            if(key==57)  curseur_haut_droite(&P,&ci,&cj,player);
            if(key==54)  curseur_droite(&P,&ci,&cj,player);
            if(key==51)  curseur_droite_bas(&P,&ci,&cj,player);
            if(key==50)  curseur_bas(&P,&ci,&cj,player);
            if(key==49)  curseur_bas_gauche(&P,&ci,&cj,player);
            if(key==52)  curseur_gauche(&P,&ci,&cj,player);
            if(key==55)  curseur_gauche_haut(&P,&ci,&cj,player);
        }
        if(key==53) curseur_select(&P,ci,cj,a); // selectionner
        if(P.Mat[ci][cj].curseur==2){ //le pion est selectionné c'est le moment de jouer
            // les cas possibles
            if(key==56){
                if(((P.Mat[ci][cj].chem)%10)/1==1){
                    attack_haut(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) /* s'il ne reste pas de chemin*/ { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci-1][cj].genre==' ' && ci!=0){ // le déplacement
                    P.Mat[ci-1][cj].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    ci-=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==57){
                if(((P.Mat[ci][cj].chem)%100)/10==1){
                    attack_haut_droite(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci-1][cj+1].genre==' ' && ci!=0 && cj!=8){
                    P.Mat[ci-1][cj+1].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    ci-=1;
                    cj+=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==54){
                if(((P.Mat[ci][cj].chem)%1000)/100==1){
                    attack_droite(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci][cj+1].genre==' ' && cj!=8){
                    P.Mat[ci][cj+1].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    cj+=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==51){
                if(((P.Mat[ci][cj].chem)%10000)/1000==1){
                    attack_droite_bas(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci+1][cj+1].genre==' ' && ci!=4 && cj!=8){
                    P.Mat[ci+1][cj+1].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    ci+=1;
                    cj+=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==50){
                if(((P.Mat[ci][cj].chem)%100000)/10000==1){
                    attack_bas(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci+1][cj].genre==' ' && ci!=4){
                    P.Mat[ci+1][cj].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    ci+=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==49){
                if(((P.Mat[ci][cj].chem)%1000000)/100000==1){
                    attack_bas_gauche(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci+1][cj-1].genre==' ' && ci!=4 && cj!=0){
                    P.Mat[ci+1][cj-1].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    ci+=1;
                    cj=-1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==52){
                if(((P.Mat[ci][cj].chem)%10000000)/1000000==1){
                    attack_gauche(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci][cj-1].genre==' ' && cj!=0){
                    P.Mat[ci][cj-1].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    cj-=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
            if(key==55){
                if(((P.Mat[ci][cj].chem)%100000000)/10000000==1){
                    attack_gauche_haut(&P,&ci,&cj,&a);
                    if(P.Mat[ci][cj].chem==0) { TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);}
                }
                else if(P.Mat[ci][cj].chem==0 && P.Mat[ci-1][cj-1].genre==' ' && ci!=0 && cj!=0){
                    P.Mat[ci-1][cj+1].genre=P.Mat[ci][cj].genre;
                    P.Mat[ci][cj].genre=' ';
                    P.Mat[ci][cj].curseur=0;
                    ci-=1;
                    cj+=1;
                    TogglePlayer(&player,&a); curseur_par_def(&P,&ci,&cj,player,a);
                }
            }
        }
        if(P.pb==0) { printf("\n\ngreat!! the black player won ");      break;} // pions epuisés
        else if(P.pn==0)  { printf("\n\ngreat!! the white player won ");    break;}
    }
    return 0;
}


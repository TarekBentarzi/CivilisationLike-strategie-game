#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termios.h>
#include <poll.h>
#include "time.h"
#include <signal.h>
#include "bonus.h"
#include "bombe.h"
#include "menu.h"
//carte du jeu
struct carte{
char carteP[1024];
char carteB[1024];
};typedef struct carte carte;;
//données du joueur
struct joueur1{
int pv;
int vitesse;
int puissance;
int bombes;
//position des bombes que le joueurs peut posé simultanement
int pos1;
int pos1_bombe2;
int pos1_bombe3;
};typedef struct joueur1 joueur1;

struct joueur2{
int pv;
int vitesse;
int puissance;
int bombes;
//position des bombes que le joueurs peut posé simultanement
int pos2;
int pos2_bombe2;
int pos2_bombe3;
};

typedef struct joueur2 joueur2;

int affichage(char carteP[],char carteB[],char infoj1[],char infoj2[],char infoNV[]){
//ce write n'affiche que la derniere image de la carte
write(1,"\033[2J\033[1;1H",10);
write(1,carteP,450);
//write(1,carteB,450);
write(1,"\n",1);
write(1,infoj1,48);
write(1,"\n",1);
write(1,infoj2,48);
write(1,"\n",1);
write(1,infoNV,8);
return 0;
};




int jeu(char*map,int nv,int cmpt){
  //initialisation données J1
struct joueur1 J1;
J1.pv=3;
J1.puissance=1;
J1.bombes=1;
J1.vitesse=1;
char infoj1[50];//info du J1
  //initialisation données J2
struct joueur2 J2;
J2.pv=3;
J2.puissance=1;
J2.bombes=1;
J2.vitesse=1;
char infoj2[50];
char infoNV[50]; //numero du niveau
alarm(0); // before scheduling it to be called.

        
  


	char buf[2]="\0";
  //touches J1
	char*s="s",*q="q",*z="z",*d="d";
  char*e="e";//touche bombe du J1
  //touches J2
  char*bas="B",*gauche="D",*haut="A",*droite="C";
  char*o="!";//touche bombe du J2
  char*n="n";//touche quitter
  int fd;
  //ouverture de la carte
  if((fd=open(map,O_RDWR))==-1){
    perror("erreur pas de fichier");
  }


int positionJ1=61;
int positionJ2=390;
//copies des cartes pricipale et bonus afin de reinitialisé le jeu
char copieCarteP[1024];
char copieCarteB[1024];
	struct carte c;


  //recuperation de la longueur et largeur avec lseek
char bufTaille[2]="\0";
int longueur;
int largeur;

read(fd,bufTaille,2);
largeur=atoi(bufTaille);
lseek(fd,3,SEEK_SET);
read(fd,bufTaille,2);
longueur=atoi(bufTaille);
int taille=longueur*largeur;

lseek(fd,5,SEEK_SET);//on se positionne arés les données de la carte
read(fd,c.carteP,450);
 strcpy (copieCarteP,c.carteP);//copie de la carte principale
lseek(fd,455,SEEK_SET);
read(fd,c.carteB,450);//copie de la carte secondaire
 strcpy (copieCarteB,c.carteB);


//mode canonique
  struct termios original;
  struct termios nouveau;
  //recuperation de la configuration initial du terminal et copie dans la nouvelle struct
  if (tcgetattr(STDIN_FILENO,&original)<0){
  perror("Erreur tcgetattr 1 : ");
}
  nouveau =  original;
  //mode non canonique
  nouveau.c_lflag = !ICANON; 

  nouveau.c_cc[VMIN]=1;
  //tant qu'aucun caractere n'est tapé il y'a attente
  nouveau.c_cc[VTIME]=0;
  //struct pollfd fds[2];
  //application de nouveau dans l'entrée standard

  if (tcsetattr(STDIN_FILENO,TCSANOW,&nouveau)<0)
  perror("Erreur tcgetattr 2 : ");





struct pollfd fds[1];

fds[0].fd=STDIN_FILENO;
fds[0].events=POLLIN;
time_t t=time(NULL);
time_t sec=time(NULL)-9999999;
time_t f=time(NULL);
time_t secf=time(NULL)-9999999;
time_t r=time(NULL);
time_t secr=time(NULL)-9999999;

int tab_time_j2[3]={t,f,r};
int tab_wait_j2[3]={sec,secf,secr};
int position2[3]={J2.pos2,J2.pos2_bombe2,J2.pos2_bombe3};

time_t t1=time(NULL);
time_t sec1=time(NULL)-9999999;
time_t f1=time(NULL);
time_t secf1=time(NULL)-9999999;
time_t r1=time(NULL);
time_t secr1=time(NULL)-9999999;
//time_t tobstacle=time(NULL);
//time_t tobstaclew=time(NULL)-100000;

int tab_time_j1[3]={t1,f1,r1};
int tab_wait_j1[3]={sec1,secf1,secr1};
int position1[3]={J1.pos1,J1.pos1_bombe2,J1.pos1_bombe3};
//controle des obstacles aux positions bas,haut,gauche,droite joueur 2
char obstaclebas2[3];
char obstaclehaut2[3];
char obstaclegauche2[3];
char obstacledroite2[3];

//controle des bonus aux positions bas,haut,gauche,droite joueur 2
char bonusbas2[3];
char bonushaut2[3];
char bonusgauche2[3];
char bonusdroite2[3];
//controle des obstacles aux positions bas,haut,gauche,droite joueur1
char obstaclebas1[3];
char obstaclehaut1[3];
char obstaclegauche1[3];
char obstacledroite1[3];
//controle des bonus aux positions bas,haut,gauche,droite joueur1
char bonusbas1[3];
char bonushaut1[3];
char bonusgauche1[3];
char bonusdroite1[3];
while(1){
   //Fin du jeu si un des player n'a plus de vie
    if(J1.pv==0)
    {
    write(1,"\n",1);
    write(1,"J2 a gagne\n",11);
    sleep(2);
    close(fd);
    //si le numero du niveau est inferieur au compteur on incremente pour ouvrir le prochain
    if(nv<=cmpt){
    nv=nv+1;
    //entre chaque niveau on remet la config d'origine pour ne pas la perdre
    if (tcsetattr(STDIN_FILENO,TCSANOW,&original)<0)
    perror("Erreur tcgetattr 3: ");
    //relance jeu avec nv+1
    niveau_suivant(nv,cmpt);
    //sinon on quitte on remettant la config d'origine
    }else{
    //reaffichage du curseur
    write(1,"\x1b[?25h",6);
    close(fd);
    sleep(1);
    //On remet la configuration d'orgine
    if (tcsetattr(STDIN_FILENO,TCSANOW,&original)<0)
    perror("Erreur tcgetattr 3: ");
    exit(EXIT_SUCCESS);
    }
    }
    
    if(J2.pv==0)
    {
    write(1,"\n",1);
    write(1,"J1 a gagne\n",12);
    sleep(2);
    close(fd);
    if(nv<=cmpt){
    nv=nv+1;
    //entre chaque niveau on remet la config d'origine pour ne pas la perdre
    if (tcsetattr(STDIN_FILENO,TCSANOW,&original)<0)
    perror("Erreur tcgetattr 3: ");
    niveau_suivant(nv,cmpt);
    }else{
    write(1,"\x1b[?25h",6);
    close(fd);
    sleep(1);
    //On remet la configuration d'orgine
    if (tcsetattr(STDIN_FILENO,TCSANOW,&original)<0)
    perror("Erreur tcgetattr 3: ");
    exit(EXIT_SUCCESS);
    }
    }
  //affichage des info du J1 et J2
sprintf(infoj1,"Joueur:1 pv:%d bombes:%d puissance:%d vitesse:%d ",J1.pv,J1.bombes,J1.puissance,J1.vitesse);
sprintf(infoj2,"Joueur:2 pv:%d bombes:%d puissance:%d vitesse:%d ",J2.pv,J2.bombes,J2.puissance,J2.vitesse);
  if(nv<=cmpt){
  sprintf(infoNV,"niveau:%d",nv);
  }
//copie des bonus et des explosion lorsqu'ils sont present dans la carte pricipale

copie_bonus(taille,copieCarteB,copieCarteP);




copieCarteP[positionJ1]='H';
copieCarteP[positionJ2]='A';
affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
//poll attend une seconde avant de rafraichir la carte
poll(fds,1,1);

//lecture avec read du buffer et de la touche tapée par le joueur
if(fds[0].revents && POLLIN){
  int nb;
  nb=read(0,buf,1);
  //Je verifie qu'il ya quelque chose a lire
  if(nb>0){
  //deplacement des joueurs 1 et 2 avec prise en charge des bonus
  //deplacement bas j1;
   if(strcmp(buf,s)==0){

  	for(int i=longueur+1;i<taille+1;i++){
	   	if(copieCarteP[i]=='H'){
       if(copieCarteP[i+longueur+1]==' ' ||copieCarteP[i+longueur+1]=='+' || copieCarteP[i+longueur+1]=='@' ||copieCarteP[i+longueur+1]=='*'){
			   if(J1.vitesse>=1){
         for(int j=1;j<=J1.vitesse;j++){
          if(copieCarteP[i+longueur*j+j]==' ' ||copieCarteP[i+longueur*j+j]=='+' || copieCarteP[i+longueur*j+j]=='@' ||copieCarteP[i+longueur*j+j]=='*'){
            if(copieCarteP[i+longueur*j+j]=='*'){
             if(J1.vitesse<2){
             J1.vitesse=J1.vitesse+1;
             }
            }
            if(copieCarteP[i+longueur*j+j]=='@'){
             if(J1.bombes<3){
             J1.bombes=J1.bombes+1;
             }
            }
            if(copieCarteP[i+longueur*j+j]=='+'){
             if(J1.puissance<3){
             J1.puissance=J1.puissance+1;
             }
            }
          copieCarteP[positionJ1]=' ';
          positionJ1=i+longueur*j+j;
          copieCarteB[positionJ1]=' ';
          copieCarteP[positionJ1]='H';
        }
      }
    }
			
			break;
			}
		}
	}
}
if(strcmp(buf,q)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='H'){
     if(copieCarteP[i-1]==' ' ||copieCarteP[i-1]=='+' || copieCarteP[i-1]=='@' ||copieCarteP[i-1]=='*'){
      if(J1.vitesse>=1){
       for(int j=1;j<=J1.vitesse;j++){
        if(copieCarteP[i-j]==' ' ||copieCarteP[i-j]=='+' || copieCarteP[i-j]=='@' ||copieCarteP[i-j]=='*'){
          if(copieCarteP[i-j]=='*'){
           if(J1.vitesse<2){
           J1.vitesse=J1.vitesse+1;
           }
          }
          if(copieCarteP[i-j]=='@'){
           if(J1.bombes<3){
           J1.bombes=J1.bombes+1;
           }
          }
          if(copieCarteP[i-j]=='+'){
           if(J1.puissance<3){
           J1.puissance=J1.puissance+1;
           }
          }
          copieCarteP[positionJ1]=' ';
          positionJ1=i-j;
          copieCarteB[positionJ1]=' ';
          copieCarteP[positionJ1]='H';
        }
      }
  }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}
if(strcmp(buf,d)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='H'){
      if(copieCarteP[i+1]==' ' ||copieCarteP[i+1]=='+' || copieCarteP[i+1]=='@' ||copieCarteP[i+1]=='*'){
         if(J1.vitesse>=1){
          for(int j=1;j<=J1.vitesse;j++){
           if(copieCarteP[i+j]==' ' ||copieCarteP[i+j]=='+' || copieCarteP[i+j]=='@' ||copieCarteP[i+j]=='*'){
            if(copieCarteP[i+j]=='*'){
             if(J1.vitesse<2){
             J1.vitesse=J1.vitesse+1;
             }
            }
            if(copieCarteP[i+j]=='@'){
             if(J1.bombes<3){
             J1.bombes=J1.bombes+1;
             }
            }
            if(copieCarteP[i+j]=='+'){
             if(J1.puissance<3){
             J1.puissance=J1.puissance+1;
            }
          }
          copieCarteP[positionJ1]=' ';
          positionJ1=i+j;
          copieCarteB[positionJ1]=' ';
          copieCarteP[positionJ1]='H';
        }
      }
    }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}
if(strcmp(buf,z)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='H'){
      if(copieCarteP[i-longueur-1]==' ' ||copieCarteP[i-longueur-1]=='+' || copieCarteP[i-longueur-1]=='@' ||copieCarteP[i-longueur-1]=='*'){   
       if(J1.vitesse>=1){
        for(int j=1;j<=J1.vitesse;j++){
         if(copieCarteP[i-longueur*j-j]==' ' ||copieCarteP[i-longueur*j-j]=='+' || copieCarteP[i-longueur*j-j]=='@' ||copieCarteP[i-longueur*j-j]=='*'){
          if(copieCarteP[i-longueur*j-j]=='*'){
           if(J1.vitesse<2){
           J1.vitesse=J1.vitesse+1;
           }
          }
          if(copieCarteP[i-longueur*j-j]=='@'){
           if(J1.bombes<3){
           J1.bombes=J1.bombes+1;
           }
          }
          if(copieCarteP[i-longueur*j-j]=='+'){
           if(J1.puissance<3){
           J1.puissance=J1.puissance+1;
           }
          }
          copieCarteP[positionJ1]=' ';
          positionJ1=i-longueur*j-j;
          copieCarteB[positionJ1]=' ';
          copieCarteP[positionJ1]='H';
        }
      }
    }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}

//commandes J2

if(strcmp(buf,bas)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='A'){
      if(copieCarteP[i+longueur+1]==' ' ||copieCarteP[i+longueur+1]=='+' || copieCarteP[i+longueur+1]=='@' ||copieCarteP[i+longueur+1]=='*'){
       if(J2.vitesse>=1){
        for(int j=1;j<=J2.vitesse;j++){
         if(copieCarteP[i+longueur*j+j]==' ' ||copieCarteP[i+longueur*j+j]=='+' || copieCarteP[i+longueur*j+j]=='@' ||copieCarteP[i+longueur*j+j]=='*'){
          if(copieCarteP[i+longueur*j+j]=='*'){
           if(J2.vitesse<2){
           J2.vitesse=J2.vitesse+1;
           }
          }
          if(copieCarteP[i+longueur*j+j]=='@'){
           if(J2.bombes<3){
           J2.bombes=J2.bombes+1;
           }
          }
          if(copieCarteP[i+longueur*j+j]=='+'){
           if(J2.puissance<3){
           J2.puissance=J2.puissance+1;
           }
          }
          copieCarteP[positionJ2]=' ';
          positionJ2=i+longueur*j+j;
          copieCarteB[positionJ2]=' ';
          copieCarteP[positionJ2]='A';
        }
      }
    }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}
if(strcmp(buf,gauche)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='A'){
      if(copieCarteP[i-1]==' ' ||copieCarteP[i-1]=='+' || copieCarteP[i-1]=='@' ||copieCarteP[i-1]=='*'){
       if(J2.vitesse>=1){
        for(int j=1;j<=J2.vitesse;j++){
         if(copieCarteP[i-j]==' ' ||copieCarteP[i-j]=='+' || copieCarteP[i-j]=='@' ||copieCarteP[i-j]=='*'){
          if(copieCarteP[i-j]=='*'){
           if(J2.vitesse<2){
           J2.vitesse=J2.vitesse+1;
           }
          }
          if(copieCarteP[i-j]=='@'){
           if(J2.bombes<3){
           J2.bombes=J2.bombes+1;
           }
          }
          if(copieCarteP[i-j]=='+'){
           if(J2.puissance<3){
           J2.puissance=J2.puissance+1;
           }
          }
          copieCarteP[positionJ2]=' ';
          positionJ2=i-j;
          copieCarteB[positionJ2]=' ';
          copieCarteP[positionJ2]='A';
        }
      }
    }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}
if(strcmp(buf,droite)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='A'){
      if(copieCarteP[i+1]==' ' ||copieCarteP[i+1]=='+' || copieCarteP[i+1]=='@' ||copieCarteP[i+1]=='*'){
         if(J2.vitesse>=1){
          for(int j=1;j<=J2.vitesse;j++){
           if(copieCarteP[i+j]==' ' ||copieCarteP[i+j]=='+' || copieCarteP[i+j]=='@' ||copieCarteP[i+j]=='*'){
            if(copieCarteP[i+j]=='*'){
             if(J2.vitesse<2){
             J2.vitesse=J2.vitesse+1;
             }
            }
            if(copieCarteP[i+j]=='@'){
             if(J2.bombes<3){
             J2.bombes=J2.bombes+1;
             }
            }
            if(copieCarteP[i+j]=='+'){
             if(J2.puissance<3){
             J2.puissance=J2.puissance+1;
             }
            }
          copieCarteP[positionJ2]=' ';
          positionJ2=i+j;
          copieCarteB[positionJ2]=' ';
          copieCarteP[positionJ2]='A';
        }
      }
    }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}
if(strcmp(buf,haut)==0){

  for(int i=longueur+1;i<taille+1;i++){
    if(copieCarteP[i]=='A'){
      if(copieCarteP[i-longueur-1]==' ' ||copieCarteP[i-longueur-1]=='+' || copieCarteP[i-longueur-1]=='@' ||copieCarteP[i-longueur-1]=='*'){   
       if(J2.vitesse>=1){
        for(int j=1;j<=J2.vitesse;j++){
          if(copieCarteP[i-longueur*j-j]==' ' ||copieCarteP[i-longueur*j-j]=='+' || copieCarteP[i-longueur*j-j]=='@' ||copieCarteP[i-longueur*j-j]=='*'){
           if(copieCarteP[i-longueur*j-j]=='*'){
            if(J2.vitesse<2){
            J2.vitesse=J2.vitesse+1;
            }
          }
           if(copieCarteP[i-longueur*j-j]=='@'){
            if(J2.bombes<3){
            J2.bombes=J2.bombes+1;
            }
           }
           if(copieCarteP[i-longueur*j-j]=='+'){
            if(J2.puissance<3){
            J2.puissance=J2.puissance+1;
            }
           }
          copieCarteP[positionJ2]=' ';
          positionJ2=i-longueur*j-j;
          copieCarteB[positionJ2]=' ';
          copieCarteP[positionJ2]='A';
        }
      }
    }
      affichage(copieCarteP,copieCarteB,infoj1,infoj2,infoNV);
      break;
      }
    }
  }
}

//Gestion de l'explosion,la fonction explose prend deux tableaux de temps,les positions et le nombre de bombes des joueurs 1 ou 2


if(strcmp(buf,e)==0){
 explose(copieCarteB,copieCarteP,position1,tab_time_j1,tab_wait_j1,J1.bombes,positionJ1);
}

if(strcmp(buf,o)==0){
  explose(copieCarteB,copieCarteP,position2,tab_time_j2,tab_wait_j2,J2.bombes,positionJ2);
}

//la touhe n permet de quitter le jeu et fermer le fichier carte
//elle permet aussi de remettre termios dans son etat initiale
if(strcmp(buf,n)==0){
  write(1,"\x1b[?25h",6);
close(fd);
  if(tcsetattr(STDIN_FILENO,TCSANOW,& original)<0){
    perror("Erreur tcgetattr 3: ");
  }
//on remet la carte original (sans les modification aprés jeu) dans copieCarteP
strcpy(copieCarteP,c.carteP);
strcpy(copieCarteB,c.carteB);
exit(0);
}


}
}
//les bombes explosent la ou il n'ya pas de 0 afin de ne pas detruire le
//contour de la carte
for(int i=0;i<3;i++){
 for(int j=1;j<=J2.puissance;j++){
  if(tab_time_j2[i]==tab_wait_j2[i]+2){
  copieCarteB[position2[i]]='#';
   if((copieCarteP[position2[i]+longueur*j+j]!='0')&&(copieCarteP[position2[i]+longueur*j+j]!='#') && (copieCarteP[position2[i]+longueur*j+j]!='\n')){
    obstaclebas2[j]=copieCarteP[position2[i]+longueur*j+j];
    //si il ya un bonus a cette position dans la carte bonus on le sauvegarde dans bonusBas2[j]
    bonusbas2[j]=copieCarteB[position2[i]+longueur*j+j];
   copieCarteB[position2[i]+longueur*j+j]='#';
   }
   if((copieCarteP[position2[i]-longueur*j-j]!='0')&&(copieCarteP[position2[i]-longueur*j-j]!='#') && (copieCarteP[position2[i]-longueur*j-j]!='\n')){
    obstaclehaut2[j]=copieCarteP[position2[i]-longueur*j-j];
    bonushaut2[j]=copieCarteB[position2[i]-longueur*j-j];
   copieCarteB[position2[i]-longueur*j-j]='#';
   }
   if((copieCarteP[position2[i]+j]!='0')&&(copieCarteP[position2[i]+j]!='#') && (copieCarteP[position2[i]+j]!='\n')){
    obstacledroite2[j]=copieCarteP[position2[i]+j];
    bonusdroite2[j]=copieCarteB[position2[i]+j];
   copieCarteB[position2[i]+j]='#';
   }
   if((copieCarteP[position2[i]-j]!='0')&&(copieCarteP[position2[i]-j]!='#') && (copieCarteP[position2[i]-j]!='\n')){
    obstaclegauche2[j]=copieCarteP[position2[i]-j];
    bonusgauche2[j]=copieCarteB[position2[i]-j];
   copieCarteB[position2[i]-j]='#';
   }
 }
 //48 sert ici a convertir les char 'chiffre' en chiffre en ascci donc '1'-48=1 par exemple
  if(tab_time_j2[i]==tab_wait_j2[i]+4){
  copieCarteB[position2[i]]=' ';
   if((copieCarteP[position2[i]+longueur*j+j]!='0') && (copieCarteP[position2[i]+longueur*j+j]!='\n')){
    if(obstaclebas2[j]-48>1){
      //on diminue la valeure du mur
      obstaclebas2[j]=obstaclebas2[j]-48-1;
      copieCarteB[position2[i]+longueur*j+j]=obstaclebas2[j]+'0';
      //si il ya un bonus dans bonusbas2[j] on le remet dans les cartes
    }else if(bonusbas2[j]=='*' || bonusbas2[j]=='@' || bonusbas2[j]=='+'){
copieCarteB[position2[i]+longueur*j+j]=bonusbas2[j];
copieCarteP[position2[i]+longueur*j+j]=bonusbas2[j];
    }else{
   copieCarteB[position2[i]+longueur*j+j]=' ';
 }
 }
   if((copieCarteP[position2[i]-longueur*j-j]!='0') && (copieCarteP[position2[i]-longueur*j-j]!='\n')){
    if(obstaclehaut2[j]-48>1){
      obstaclehaut2[j]=obstaclehaut2[j]-48-1;
      copieCarteB[position2[i]-longueur*j-j]=obstaclehaut2[j]+'0';
    }else if(bonushaut2[j]=='*' || bonushaut2[j]=='@' || bonushaut2[j]=='+'){
      copieCarteB[position2[i]-longueur*j-j]=bonushaut2[j];
      copieCarteP[position2[i]-longueur*j-j]=bonushaut2[j];
    }else{
   copieCarteB[position2[i]-longueur*j-j]=' ';
    }
   }
   if((copieCarteP[position2[i]+j]!='0') && (copieCarteP[position2[i]+j]!='\n')){
    if(obstacledroite2[j]-48>1){
      obstacledroite2[j]=obstacledroite2[j]-48-1;
      copieCarteB[position2[i]+j]=obstacledroite2[j]+'0';
    }else if(bonusdroite2[j]=='*' || bonusdroite2[j]=='@' || bonusdroite2[j]=='+'){
      copieCarteB[position2[i]+j]=bonusdroite2[j];
      copieCarteP[position2[i]+j]=bonusdroite2[j];
    }else{
   copieCarteB[position2[i]+j]=' ';
   }
 }
   if((copieCarteP[position2[i]-j]!='0') && (copieCarteP[position2[i]-j]!='\n')){
    if(obstaclegauche2[j]-48>1){
      obstaclegauche2[j]=obstaclegauche2[j]-48-1;
      copieCarteB[position2[i]-j]=obstaclegauche2[j]+'0';
    }else if(bonusgauche2[j]=='*' || bonusgauche2[j]=='@' || bonusgauche2[j]=='+'){
    copieCarteB[position2[i]-j]=bonusgauche2[j];
    copieCarteP[position2[i]-j]=bonusgauche2[j];
    }else{
   copieCarteB[position2[i]-j]=' ';
   }
  }
 }
}
}

for(int i=0;i<3;i++){
 for(int j=1;j<=J1.puissance;j++){
  if(tab_time_j1[i]==tab_wait_j1[i]+2){
  copieCarteB[position1[i]]='#';
  //si la position est differente de 0 ou de \n sinon ça traverse le mur et decale la carte
   if((copieCarteP[position1[i]+longueur*j+j]!='0')&&(copieCarteP[position1[i]+longueur*j+j]!='#') && (copieCarteP[position1[i]+longueur*j+j]!='\n')){
    obstaclebas1[j]=copieCarteP[position1[i]+longueur*j+j];
    bonusbas1[j]=copieCarteB[position1[i]+longueur*j+j];
   copieCarteB[position1[i]+longueur*j+j]='#';
   }
   if((copieCarteP[position1[i]-longueur*j-j]!='0')&&(copieCarteP[position1[i]-longueur*j-j]!='#') &&(copieCarteP[position1[i]-longueur*j-j]!='\n')){
    obstaclehaut1[j]=copieCarteP[position1[i]-longueur*j-j];
    bonushaut1[j]=copieCarteB[position1[i]-longueur*j-j];
   copieCarteB[position1[i]-longueur*j-j]='#';
   }
   if((copieCarteP[position1[i]+j]!='0')&&(copieCarteP[position1[i]+j]!='#') && (copieCarteP[position1[i]+j]!='\n')){
    obstacledroite1[j]=copieCarteP[position1[i]+j];
    bonusdroite1[j]=copieCarteB[position1[i]+j];
   copieCarteB[position1[i]+j]='#';
   }
   if((copieCarteP[position1[i]-j]!='0')&&(copieCarteP[position1[i]-j]!='#') && (copieCarteP[position1[i]-j]!='\n')){
    obstaclegauche1[j]=copieCarteP[position1[i]-j];
    bonusgauche1[j]=copieCarteB[position1[i]-j];
   copieCarteB[position1[i]-j]='#';
   }
 }
  if(tab_time_j1[i]==tab_wait_j1[i]+4){
  copieCarteB[position1[i]]=' ';
   if((copieCarteP[position1[i]+longueur*j+j]!='0') && (copieCarteP[position1[i]+longueur*j+j]!='\n')){
    if(obstaclebas1[j]-48>1){
      obstaclebas1[j]=obstaclebas1[j]-48-1;
      copieCarteB[position1[i]+longueur*j+j]=obstaclebas1[j]+'0';
    }else if(bonusbas1[j]=='*' || bonusbas1[j]=='@' || bonusbas1[j]=='+'){
copieCarteB[position1[i]+longueur*j+j]=bonusbas1[j];
copieCarteP[position1[i]+longueur*j+j]=bonusbas1[j];
    }else{
   copieCarteB[position1[i]+longueur*j+j]=' ';
 }
 }
   if((copieCarteP[position1[i]-longueur*j-j]!='0') && (copieCarteP[position1[i]-longueur*j-j]!='\n')){
    if(obstaclehaut1[j]-48>1){
      obstaclehaut1[j]=obstaclehaut1[j]-48-1;
      copieCarteB[position1[i]-longueur*j-j]=obstaclehaut1[j]+'0';
    }else if(bonushaut1[j]=='*' || bonushaut1[j]=='@' || bonushaut1[j]=='+'){
      copieCarteB[position1[i]-longueur*j-j]=bonushaut1[j];
      copieCarteP[position1[i]-longueur*j-j]=bonushaut1[j];
    }else{
   copieCarteB[position1[i]-longueur*j-j]=' ';
    }
   }
   if((copieCarteP[position1[i]+j]!='0') && (copieCarteP[position1[i]+j]!='\n')){
    if(obstacledroite1[j]-48>1){
      obstacledroite1[j]=obstacledroite1[j]-48-1;
      copieCarteB[position1[i]+j]=obstacledroite1[j]+'0';
    }else if(bonusdroite1[j]=='*' || bonusdroite1[j]=='@' || bonusdroite1[j]=='+'){
      copieCarteB[position1[i]+j]=bonusdroite1[j];
      copieCarteP[position1[i]+j]=bonusdroite1[j];
    }else{
   copieCarteB[position1[i]+j]=' ';
   }
 }
   if((copieCarteP[position1[i]-j]!='0') && (copieCarteP[position1[i]-j]!='\n')){
    if(obstaclegauche1[j]-48>1){
      obstaclegauche1[j]=obstaclegauche1[j]-48-1;
      copieCarteB[position1[i]-j]=obstaclegauche1[j]+'0';
    }else if(bonusgauche1[j]=='*' || bonusgauche1[j]=='@' || bonusgauche1[j]=='+'){
    copieCarteB[position1[i]-j]=bonusgauche1[j];
    copieCarteP[position1[i]-j]=bonusgauche1[j];
    }else{
   copieCarteB[position1[i]-j]=' ';
   }
  }
 }
}
}
/*J'utilise une alarme lorsque je trouve # et A a la meme position que le joueur1 ou 2
ou les deux,l'attente est d'une seconde ce qui permet d'eviter d'avoir plusieurs
 vies enlevées et un micro temps d'invincibilité (comme dans le vrai jeu :))*/

//le cas ou Joueur2 est touché
void handle_alarm() {
J2.pv=J2.pv-1;
}
//le cas ou Joueur1 est touché
void handle_alarm2() {
J1.pv=J1.pv-1;
}
//le cas ou les deux sont touchés
void handle_alarm3() {
J1.pv=J1.pv-1;
J2.pv=J2.pv-1;
}
//je verifie si il ya un  et un joueur sur la meme position
if((copieCarteB[positionJ2]=='#' && copieCarteP[positionJ2]=='A') && (copieCarteB[positionJ1]!='#')){
  copieCarteB[positionJ2]=' ';
  struct sigaction act;
  act.sa_handler=handle_alarm;
  sigaction(SIGALRM,&act,NULL);
  alarm(1);
 }else if((copieCarteB[positionJ1]=='#' && copieCarteP[positionJ1]=='H') && (copieCarteB[positionJ2]!='#')){
  copieCarteB[positionJ1]=' ';
  struct sigaction act;
  act.sa_handler=handle_alarm2;
  sigaction(SIGALRM,&act,NULL);
  alarm(1);
 }else if((copieCarteB[positionJ1]=='#' && copieCarteP[positionJ1]=='H') && (copieCarteB[positionJ2]=='#' && copieCarteP[positionJ2]=='A')){
  copieCarteB[positionJ1]=' ';
  copieCarteB[positionJ2]=' ';
  struct sigaction act;
  act.sa_handler=handle_alarm3;
  sigaction(SIGALRM,&act,NULL);
  alarm(1);
  }


/*temps pour les differentes positions des bombes (chaque bombe 1,2 ou 3)
  aura son propre temps d'attente qui est dans le tableau tab_time_j1 ou tab_time_j2*/
tab_time_j1[0]=time(NULL);
tab_time_j1[1]=time(NULL);
tab_time_j1[2]=time(NULL);
tab_time_j2[0]=time(NULL);
tab_time_j2[1]=time(NULL);
tab_time_j2[2]=time(NULL);

}
return 0;
}







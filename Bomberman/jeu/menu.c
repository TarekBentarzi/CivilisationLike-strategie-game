#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/wait.h>


//si le niveau suivant est inferieur ou egale a cmpt alors on lance jeu avec le suivant
void niveau_suivant(int nv,int cmpt){
   if(nv<=cmpt)
    {
      char map[1];
      sprintf(map,"%d",nv);
      jeu(map,nv,cmpt);
      
    }
}

int menu(){

write(1,"\033[2J\033[1;1H",10);

char * menu="\t\tMenu\n";

    write(1,menu,strlen(menu));
    
    //liste des mods dans un tableau
    int i=0;
    char buf[10];
    char *test[10];
    
    
    DIR *rep;
    struct dirent *dirp;
    rep =opendir("MOD");
    if (rep==NULL)
	{ 
	    perror("Impossible d'ouvrir MOD ");
	    sleep(2);
	    exit(EXIT_FAILURE);
	}
    while((dirp=readdir(rep))!=NULL)
    {
     if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0)
     {
	  if((dirp->d_type)&=DT_DIR)
	  {
	    
	    test[i]=dirp->d_name;
	    //affichage du numero+1
	    sprintf(buf,"%d",i+1);
	    write(1,buf,strlen(buf));
	    
	    write(1," - ",3);
	    //affichage du nom du mod
	    write(1,test[i],strlen(test[i]));
	    write(1,"\n",2);
	  }
	  i++;
     }
    }
    closedir(rep);
    write(1,"choisissez un mode de jeu (x pour quitter)\n",43);
    read(STDIN_FILENO,buf,1);
    if(strcmp(buf,"x")==0)
    {
        menu="AU REVOIR !\n";
	write(1,menu,strlen(menu));
	sleep(2);
	exit(EXIT_SUCCESS);
    }
    
    int mod;
    mod=atoi(buf)-1;
    if (chdir("MOD")==-1) 
    {
      perror("Erreur ouverture dossier MOD ");
      sleep(2);
      exit(EXIT_FAILURE);
    }
    if(chdir(test[mod])==-1) 
    { 
      perror("Impossible d'ouvrire ce mode "); 	    
      sleep(2); 
      exit(EXIT_FAILURE);
    }
    //lecture du nombre de niveaux
     int fd=open("deroulement",O_RDONLY);
char buffer[50];
int n=0;
int cmpt=0;
read(fd,buffer,50);
while(buffer[n]!='\0'){
  if(buffer[n]=='\n'){
cmpt=cmpt+1;
}
n++;
}
cmpt=cmpt-1;
if(chdir("niveaux")==-1) 
    { 
      perror("Impossible d'ouvrire niveau ");      
      sleep(2); 
      exit(EXIT_FAILURE);
    }
int level=1;
 niveau_suivant(level,cmpt);
return 0;
}
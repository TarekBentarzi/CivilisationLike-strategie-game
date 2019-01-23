
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

//copie de tout les bonus dans la carte bonus dans la carte principale

void copie_bonus(int taille,char*copieCarteB,char*copieCarteP){
for(int i=0;i<taille;i++){
  if(copieCarteB[i]=='+' && copieCarteP[i]==' '){
  copieCarteP[i]='+';
  }
  if(copieCarteB[i]=='*' && copieCarteP[i]==' '){
  copieCarteP[i]='*';
  }
  if(copieCarteB[i]=='@' && copieCarteP[i]==' '){
  copieCarteP[i]='@';
  }
  if(copieCarteB[i]=='X' && copieCarteP[i]==' '){
  copieCarteP[i]='X';
  }
  if(copieCarteB[i]==' ' && copieCarteP[i]=='#'){
  copieCarteP[i]=' ';
  }
  if(copieCarteB[i]=='#'){
  copieCarteP[i]='#';
  }
  if((copieCarteB[i]-48)>=1 && (copieCarteB[i]-48)<=9){
  copieCarteP[i]=copieCarteB[i];
}

} 
}
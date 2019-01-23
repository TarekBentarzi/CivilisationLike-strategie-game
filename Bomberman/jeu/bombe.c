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


void explose(char*copieCarteB,char*copieCarteP,int position[],int tab_time[],int tab_wait[],int nb_bombes,int positionJ){

//si a la position du joueur on a pas X dans la carte bonus et qu'il n'ya pas de souffle d'explosion aussi on affiche X dans la carte bonus on initialise nos time selon que le nombre de bombes est egale a 1,2 ou 3
 if(copieCarteB[position[0]]!='X' && copieCarteB[position[0]]!='#'){
 position[0]=positionJ;
 copieCarteB[position[0]]='X';
 tab_wait[0]=time(NULL);
 tab_time[0]=time(NULL);
 }else if(nb_bombes==2){
   if((copieCarteB[position[0]]=='X' || copieCarteB[position[0]]=='#') && (copieCarteB[position[1]]=='X' || copieCarteB[position[1]]=='#')){
    }else{
    position[1]=positionJ;
    copieCarteB[position[1]]='X';
    tab_wait[1]=time(NULL);
    tab_time[1]=time(NULL);
    }
  
 }else if(nb_bombes==3){
  if(copieCarteB[position[2]]=='X' || copieCarteB[position[2]]=='#'){
  
  
 }else if((copieCarteB[position[1]]!='X' && copieCarteB[position[1]]!='#' ) &&(copieCarteB[position[2]]=='X' || copieCarteB[position[2]]=='#') ){
   
 }else if((copieCarteB[position[1]]!='X'&& copieCarteB[position[1]]!='#' ) &&(copieCarteB[position[2]]!='X' && copieCarteB[position[2]]!='#')){
  position[1]=positionJ;
  copieCarteB[position[1]]='X';
  tab_wait[1]=time(NULL);
  tab_time[1]=time(NULL);
 }else if((copieCarteB[position[1]]=='X' || copieCarteB[position[1]]=='#') && (copieCarteB[position[2]]!='X' && copieCarteB[position[2]]!='#')){
  position[2]=positionJ;
  copieCarteB[position[2]]='X';
  tab_wait[2]=time(NULL);
  tab_time[2]=time(NULL);
 }
}
}
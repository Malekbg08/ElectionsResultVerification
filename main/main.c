/// \file main.c
/// \brief Recupere les options (balises) afin de décider de l'enchaine de fonctions à executer
/// \author Malek Ben Ghachem
/// \date janvier 2022
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utilsd.c"
#include "csv.c"
#include "condorcetballot.c"
#include "condorcetduel.c"
#include "uninominale.c"

int
main (int argm, char **argv)
{
  /// \brief Récupère les balises saisies par l'utilisateur et réalise l'action souhaitée, sinon affiche un message d'erreur sur stderr

  int iflag = 0;
  int dflag = 0;
  char *mvalue = NULL;
  int index;
  int m;
  int optionprincipale=0;


  opterr = 0;

  while ((m = getopt (argm, argv, "idm:")) != -1)
    switch (m)
      {

      case 'i':
      if(dflag==1) {
        fprintf (stderr, "Les options sont incompatibles \n");
        return -2;

    }
        optionprincipale=1;
        iflag = 1;

        break;
      case 'd':
      if(iflag==1){
        fprintf (stderr, "Les options sont incompatibles \n");

        return -2;
    }
        optionprincipale=1;
        dflag = 1;

        break;



      case 'm':
        mvalue = optarg;


        break;
      case '?':
        if (optopt == 'm' )
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);

        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
      int cm = 0;
      int cs = 0;
      int uni1 = 0;
      int uni2 = 0;
      int all = 0;
      int finoption =0;

      if(strcmp(optarg,"cs")==0 && finoption==0 && optionprincipale==1){

        cs=1;
        finoption =1;
      }
      else{

        if(strcmp(optarg,"cm")==0 && finoption==0 && optionprincipale==1){

          cm=1;
          finoption =1;
        }

        else{

          if(strcmp(optarg,"uni1")==0 && finoption==0 && optionprincipale==1){
            uni1=1;
            finoption =1;
          }
          else{
            if(strcmp(optarg,"uni2")==0 && finoption==0 && optionprincipale==1){
              uni2=1;
              finoption =1;
            }
            else{
              if(strcmp(optarg,"all")==0 && finoption==0 && optionprincipale==1){
                all=1;
                finoption =1;
              }
              else{
                fprintf (stderr, "Les options entrées ne sont pas prises en charge \n");

                return -3;
              }
            }
          }
        }
      }





  for (index = optind; index < argm; index++)
    printf ("Non-option argument %s\n", argv[index]);

if(iflag==1){ //si ballots
  t_mat_char_star_dyn mat;
  creer_t_mat_char_dyn(&mat);
  char nomfichier;
  scanf("%s",&nomfichier);
  FILE *fstream = fopen(&nomfichier,"r");
 csv(fstream,&mat);
  if(uni1==1) uninominale1(&mat);

  else{

    int nbre_candidat=mat.nbCol ;
    int nbre_votants=mat.nbRows;
    t_mat_int_dyn matduel;
    creer_t_mat_int_dyn(&matduel,nbre_candidat-4,nbre_candidat-4);
    construct_mat_duels_d(&mat,&matduel,nbre_candidat,nbre_votants);
  if(cm==1){

    condorcetminimaxballot(&mat,&matduel,nbre_votants-1);
  }
  if(cs==1)
    condorcetschulzeballot(&mat,&matduel,nbre_votants-1);
      if(uni2==1) uninominale2(&mat,&matduel);
  if(all==1){
    uninominale1(&mat);
    uninominale2(&mat,&matduel);
    condorcetminimaxballot(&mat,&matduel,nbre_votants-1);
    condorcetschulzeballot(&mat,&matduel,nbre_votants-1);
  }
  }
}

if(dflag==1){//si matduel
  t_mat_char_star_dyn mat;
  creer_t_mat_char_dyn(&mat);
  char nomfichier;
  scanf("%s",&nomfichier);
  FILE *fstream = fopen(&nomfichier,"r");
 csv(fstream,&mat);
liste arcs;
createList(&arcs);
 construct_data_struct(&mat,&arcs);
if(cm==1)
 condorcetminimax(&mat,&arcs);
if (cs==1)
 condorcetschulze(&mat);
if (all==1){
    condorcetminimax(&mat,&arcs);
    condorcetschulze(&mat);
 }
  return 0;
}

}

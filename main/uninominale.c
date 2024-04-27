/// \file uninominale.c
/// \brief Contient les fonctions relatives aux méthodes uninominales pour un fichier csv de nature ensemble de ballots
/// \author Malek Ben Ghachem
/// \date janvier 2022
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// BALLOTS
int uninominale1(t_mat_char_star_dyn *mat){
/// \param[in] *mat est la matrice de char dynamique telle qu'initialisée par "csv.c" et permettra d'élire un vainqueur

  float max=0;
  float score;
  int jvainqueur;
    int nbre_candidat=mat->nbCol -4;
  int nbre_votants=mat->nbRows-1;
  for(int j=4;j<mat->nbCol;j++){

    int sommevotes=0;

    for(int i=1;i<mat->nbRows;i++){
      if(atoi(mat->tab[i][j])==1)
      sommevotes+=atoi(mat->tab[i][j]);
    }

    if(sommevotes>=max){
      max=sommevotes;
      jvainqueur=j;
    }
  }

  score=(max/nbre_votants)*100;

  printf("\nMode de scrutin : uninominal à un tour, ");
  printf("%d candidats, ",nbre_candidat);
  printf("%d votants, ",nbre_votants);
  printf(" vainqueur = %s, ",mat->tab[0][jvainqueur]);
  printf("score %f%%\n",score);
  return 0;
}

int uninominale2(t_mat_char_star_dyn *mat,t_mat_int_dyn *matduel){
  /// \param[in] *mat est la matrice de char dynamique telle qu'initialisée par "csv.c" et permettra d'élire un vainqueur en deux tours pour simuler un vote uninominale à deux tours

  int nbre_votants=mat->nbRows-1;
  int nbre_candidat=mat->nbCol -4;
  float max=0;
  float max2=0;
  float score;
  float score2;
  int jvainqueur=0;
  int jvainqueur2=1;

  for(int j=4;j<mat->nbCol;j++){

    int sommevotes=0;

    for(int i=1;i<mat->nbRows;i++){
      if(atoi(mat->tab[i][j])==1)
      sommevotes+=atoi(mat->tab[i][j]);
    }
    if(sommevotes>max)
    {
      max2=max;
      max=sommevotes;
      jvainqueur2=jvainqueur;
      jvainqueur=j;

    }
    if(sommevotes<max && sommevotes>=max2){
      max2=sommevotes;
      jvainqueur2=j;
    }
  }

  score=(max/nbre_votants)*100;
  score2=(max2/nbre_votants)*100;
  if(score>=50){
    printf("\nMode de scrutin : uninominal à deux tours, tour 1, ");
    printf("%d candidats, ",nbre_candidat);
    printf("%d votants, ",nbre_votants);
    printf("\nVainqueur :%s\n",mat->tab[0][jvainqueur]);
    printf("\nScore: %f%% \n",score);
    return 0;
  }

  printf("\nMode de scrutin : uninominal à deux tours, tour 1, ");
  printf("%d candidats, ",nbre_candidat);
  printf("%d votants, ",nbre_votants);
  printf(" vainqueur = %s, ",mat->tab[0][jvainqueur]);
  printf("score %f%%\n",score);
  printf("\nMode de scrutin : uninominal à deux tours, tour 1, ");
  printf("%d candidats, ",nbre_candidat);
  printf("%d votants, ",nbre_votants);
  printf(" vainqueur = %s, ",mat->tab[0][jvainqueur2]);
  printf("score %f%%\n",score2);
  //
  //
  score=(matduel->tab[jvainqueur-4][jvainqueur2-4]);

  score2 =(matduel->tab[jvainqueur2-4][jvainqueur-4]);
  float participants_secondtour=score+score2;

if(score>score2){

  printf("\nMode de scrutin : uninominal à deux tours, tour 2, ");
  printf("%d candidats, ",nbre_candidat);
  printf("%d votants, ",nbre_votants);
  printf(" vainqueur = %s, ",mat->tab[0][jvainqueur]);

  printf("score %f%%\n",(score/participants_secondtour)*100);

}
else if(score<score2){
  printf("\nMode de scrutin : uninominal à deux tours, tour 2, ");
  printf("%d candidats, ",nbre_candidat);
  printf("%d votants, ",nbre_votants);
  printf(" vainqueur = %s, ",mat->tab[0][jvainqueur2]);

  printf("score %f%%\n",(score2/participants_secondtour)*100);

}
  return 0;
}

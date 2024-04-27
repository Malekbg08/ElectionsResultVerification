/// \file condorcetduel.c
/// \brief Contient 3 fonctions applicables à un fichier csv de nature matrice de duel
/// \author Malek Ben Ghachem
/// \date janvier 2022
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "liste.c"
#include "elementliste.c"

// MATDUEL
int construct_data_struct(t_mat_char_star_dyn *mat,liste *arcs){
  /// \param[out] *arcs reçoit chacuns des  arcs orientés décrivant l'indice du candidat à l'otigine dans la matrice de char dynamique, l'indice de son adversaire et le nombre de préférences totales pour le candidats à l'origine
  /// \param[in] *mat est la matrice de char dynamique remplie sur laquelle on va se baser pour remplir la liste d'arcs

  int nbre_candidat=atoi(mat->tab[2][0])+atoi(mat->tab[1][1]);


    int i_min;
    int i_dest;


      for(int i=1;i<6;i++){
        int min=nbre_candidat;

      for(int j=0;j<5;j++){

      if(atoi(mat->tab[i][j])<min && atoi(mat->tab[i][j])!=0) {
        min =atoi(mat->tab[i][j]);
        i_min=i;
        i_dest=j;
      }


      }
    t_arc_p arc;
      arc.orig=i_min-1;
      arc.dest=i_dest;
      arc.poids=min;



      arcs->Tabliste[i-1]=arc;
      ++arcs->nbElt;

}


  return 0;
}

int condorcetminimax(t_mat_char_star_dyn *mat, liste *arcs){
  /// \param[out] *arcs contient toutes les infos d'une matrice de duel classique et permettra d'appliquer n'importe quelle méthode de résolution
  /// \param[in] *mat est la matrice de char dynamique remplie sur laquelle on va se baser pour retrouver le nom du vainqueur

int nbre_candidat=atoi(mat->tab[2][0])+atoi(mat->tab[1][1]);
  int nbre_votants=mat->nbRows-1;
int nbre_elements=nbEltList(*arcs);

int i_min=0;
int min=arcs->Tabliste[0].poids;
int vainqueur_direct=false;


    for(int i=1;i<nbre_elements;i++){

    if(arcs->Tabliste[i].poids>=min) {
      min = arcs->Tabliste[i].poids ;
      i_min=i;

    }

    if(min>nbre_candidat/2){

      vainqueur_direct=true;
      break;
    }

}

printf("\nMode de scrutin : Condorcet minimax, ");
printf("%d candidats, ",nbre_votants);
printf("%d votants, ",nbre_candidat);
printf(" vainqueur = %s \n",mat->tab[0][arcs->Tabliste[i_min].orig]);
return 0;
}

void condorcetschulze(t_mat_char_star_dyn *matrice){
  /// \param[in] *matrice est la matrice de char dynamique remplie sur laquelle on va se baser pour appliquer la méthode de condorcet classique et schulze afin d'élire le gagnant
  int nbre_candidat=atoi(matrice->tab[2][0])+atoi(matrice->tab[1][1]);
int jmax,max=0;


int min_all=0;
  int imax=1;
  int vainqueur_direct=false;
  int i_minimax;
  int i_min;


  for(int i=1;i<matrice->nbRows;i++){
    int sommepref=0;
      int min=nbre_candidat;
      int total=0;
    for(int j=0;j<matrice->nbCol;j++){
      sommepref+=atoi(matrice->tab[i][j]);
      if(atoi(matrice->tab[i][j])<min && atoi(matrice->tab[i][j])!=0) {
        min =atoi(matrice->tab[i][j]);
        i_min=i;
    }
    if(sommepref>max){
       max=sommepref;
       jmax=i-1;
  }

}
    if(min>nbre_candidat/2){
  imax=i-1;
  vainqueur_direct=true;
  break;
}
if(min>=min_all){
    min_all = min;
    i_minimax=i_min;
  }
}
if(vainqueur_direct==true){

  printf("\nMode de scrutins : Condorcet schulze, ");
    printf("%d candidats, ",matrice->nbRows-1);
  printf("%d  votants, ",nbre_candidat);

  printf("\n Vainqueur  : %s\n",matrice->tab[0][imax]);
}
else{
  printf("\nMode de scrutin : Condorcet schulze, ");
    printf("%d candidats, ",matrice->nbRows-1);
  printf("%d  votants, ",nbre_candidat);

     printf("\n Vainqueur : %s\n",matrice->tab[0][jmax]);

}
}

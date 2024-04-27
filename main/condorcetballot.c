/// \file condorcetballot.c
/// \brief Contient les fonctions relatives à l'application des méthodes de condorcet pour un fichier csv de nature ensemble de ballots
/// \author Malek Ben Ghachem
/// \date janvier 2022
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//BALLOTS
/* Construit et affiche la matrice de duel grâce à la matrice de char dynamique contenant les éléments du fichier csv */
void construct_mat_duels_d(t_mat_char_star_dyn *mat,t_mat_int_dyn *matduel,int nbcandidats,int nbvotants){
  /// \param[out] *matduel reçoit le nombre de préférences des duels entre chacun des candidats (matrice de duels)
  /// \param[in] *mat est la matrice de char dynamique telle qu'initialisée par "csv.c"
  /// \param[in] nbvotants est le nombre de votants (d'après la matrice mat)
  /// \param[in] nbcandidats désigne le nombre de candidats (d'après la matrice mat)

  for(int i=1;i<nbvotants;i++){
      int imatduel=0;

    for(int j=4;j<nbcandidats;j++){
      int val=atoi(mat->tab[i][j]);

      for(int d=j;d<nbcandidats;d++){

        if(d!=j){
          int val2=atoi(mat->tab[i][d]);
          if(val<val2)
             ++(matduel->tab[imatduel][d-4]);
          if(val2<val)
                ++(matduel->tab[d-4][imatduel]);

        }

      }
      ++imatduel;

    }

  }

}

/* Applique la méthode de condorcet minimax sur la matrice de duel initialisée avec la fonction construct_mat_duels_d */
int condorcetminimaxballot(t_mat_char_star_dyn *matrice,t_mat_int_dyn *mat,int nbre_votants ){
  /// \param[in] *matrice est la matrice de char dynamique telle qu'initialisée par "csv.c" qui servira à afficher le nom du vainqueur
  /// \param[in] *mat est la matrice de duels qui constitue une base cruciale pour cette fonction
  /// \param[in] nbre_votants désigne le nombre de votants (d'après la matrice mat) afin d'appliquer la méthode de condorcet/minimax

int vainqueur_direct=false;
int min_all=0;
int i_minimax;
int i_min;

    for(int i=0;i<mat->nbRows;i++){
      int min=nbre_votants;

    for(int j=0;j<mat->nbCol;j++){

    if((mat->tab[i][j])<min && (mat->tab[i][j])!=0) {
      min =(mat->tab[i][j]);
      i_min=i;
    }

    }
  if(min>nbre_votants/2){

  vainqueur_direct=true;
  break;
  }
  if(min>=min_all){
    min_all = min;
    i_minimax=i_min;
  }

}
if(vainqueur_direct==true){

  printf("\nMode de scrutin : Condorcet minimax, ");
    printf("%d candidats, ",mat->nbRows);
  printf("%d  votants, ",nbre_votants);

  printf("\n Vainqueur  : %s\n",matrice->tab[0][i_minimax+4]);
}
else{
printf("\nMode de scrutin : Condorcet minimax, ");
printf("%d votants, ",nbre_votants);
printf("%d candidats, ",mat->nbRows);
   printf("\n Vainqueur minimax: %s\n",matrice->tab[0][i_minimax+4 ]);
}
return 0;
}

/* Applique la méthode de condorcet minimax sur la matrice de duel initialisée avec la fonction construct_mat_duels_d */
void condorcetschulzeballot(t_mat_char_star_dyn *matrice,t_mat_int_dyn *mat,int nbre_votants ){
  /// \param[in] *matrice est la matrice de char dynamique telle qu'initialisée par "csv.c" qui servira à afficher le nom du vainqueur
  /// \param[in] *mat est la matrice de duels qui constitue une base cruciale pour cette fonction
  /// \param[in] nbre_votants désigne le nombre de votants (d'après la matrice mat) afin d'appliquer la méthode de condorcet/schulze

int nbreelem=matrice->nbCol-4;
int vainqueur_direct=false;
int min_all=0;
int i_minimax;
int i_min;

    for(int i=0;i<mat->nbRows;i++){
      int min=nbre_votants;

    for(int j=0;j<mat->nbCol;j++){

    if((mat->tab[i][j])<min && (mat->tab[i][j])!=0) {
      min =(mat->tab[i][j]);
      i_min=i;
    }

    }
  if(min>nbre_votants/2){

  vainqueur_direct=true;
  break;
  }
}
if(vainqueur_direct==false){
  t_tab_int_dyn pref;
creer_t_tab_int_dyn(&pref,nbreelem);
for(int x=0;x<pref.dim;x++){
  for(int y=0;y<mat->nbCol;y++){
    pref.tab[x]+=mat->tab[x][y];
  }
}

int ivainqueur = chercherindicemaxtab(&pref);
printf("\nMode de scrutin : Condorcet schulze, ");
printf("%d votants, ",nbre_votants);
printf("%d candidats, ",mat->nbRows);
   printf("\n Vainqueur schulze: %s\n",matrice->tab[0][ivainqueur+4 ]);
}
else if(vainqueur_direct==true){

  printf("\nMode de scrutin : Condorcet schulze, ");
    printf("%d candidats, ",mat->nbRows);
  printf("%d  votants, ",nbre_votants);

  printf("\n Vainqueur  : %s\n",matrice->tab[0][i_minimax+4]);
}

}

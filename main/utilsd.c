/// \file utilsd.c
/// \brief contient des structures et fonctions utilitaires pour les autres modules
/// \author Malek Ben Ghachem
/// \date janvier 2022
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#define NB_BALISES 4
#define NB_METHODES 5
#define OPT_I 0
#define OPT_D 1
#define OPT_O 2
#define OPT_M 3
#define OPT_H -1
#define SUCCESS 1
#define ERR -2


#define MAX 300 /// \def< longueur maximale de la ligne dans le fichier
#define MAXINT 1000 /// \def< entier max utile dans le programme
#define LONGMOTS 30 /// \def< longueur max d'une chaîne de caractères
#define NBCOLADM 3 /// \def< nb de colonnes administratives avant la colonne du premier choix
#define KO -1  /// \def< pas bon ou vide
#define OK 0 /// \def< bon
#define NBMAXOPTIONS 4 /// \def < ça parle en soi.
typedef struct s_tab_dyn{
  int * tab;
  int dim;
} t_tab_int_dyn;

typedef struct s_mat_dyn{
  int ** tab;
  int nbRows;
  int nbCol;
} t_mat_int_dyn;

/// \struct idem avec des chaînes de cractères
typedef struct s_mat_char_dyn{
  char *** tab;
  int nbRows;
  int nbCol;
  int offset;

} t_mat_char_star_dyn;


void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol){
  /// \param[out] *stTab reçoit le nombre de lignes et de colonnes passés en paramètre et une zone mémoire du tas
  /// \param[in] *stTab est la matrice d'entiers dynamique à initialiser
  /// \param[in] nbRows est le nombre de lignes de la matrice
  /// \param[in] nbCol est le nombre de colonnes de la matrice
  stTab->nbRows = nbRows;
  stTab->nbCol = nbCol;

  stTab->tab = NULL;
  for(int i=0;i<nbRows;i++){
    stTab->tab=realloc(stTab->tab,MAXINT*sizeof(int**));

    for(int j=0;j<nbCol;j++){
      stTab->tab[i]=realloc(stTab->tab[i],MAXINT*sizeof(int*));
      stTab->tab[i][j]=0;
    }
  }
}
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim){
  /// \param[out] *stTab reçoit la dimension passée en paramètre et une zone mémoire du tas
  /// \param[in] *stTab est le tableau d'entiers dynamique à initialiser
  /// \param[in] dim est le nombre d'éléments du tableau
  stTab->dim = dim;
  stTab->tab = malloc(stTab->dim* sizeof(int));
  for(int i=0;i<dim;i++){

    stTab->tab[i]=0;
  }

}
void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots){
  /// \param[out] *s_tabmots reçoit une zone mémoire du tas (NULL) elle sera ensuite revue à l'aide de realloc dans le csv.c
  /// \param[in] *s_tabmots est la matrice de char dynamique à initialiser

  s_tabmots->nbRows=0;
  s_tabmots->nbCol=0;
  int N = s_tabmots->nbRows * s_tabmots->nbCol;
  s_tabmots->tab = malloc(N*sizeof(char**));

}
/* Affichage de la matrice de char dynamique */
void afficher_t_mat_char_dyn(t_mat_char_star_dyn  s_tabmots){

  for(int i=0;i<s_tabmots.nbRows;i++){
    for(int j=0;j<s_tabmots.nbCol;j++){
      printf(" %s ",s_tabmots.tab[i][j]);
    }
    printf("\n");
  }

}
void afficher_t_mat_int_dyn(t_mat_int_dyn  s_tabmots){

  for(int i=0;i<s_tabmots.nbRows;i++){
    for(int j=0;j<s_tabmots.nbCol;j++){
      printf(" %d ",s_tabmots.tab[i][j]);
    }
    printf("\n");
  }

}
/* Affichage du tableau d'int dynamique */
void afficher_t_tab_int_dyn(t_tab_int_dyn *s_tabmots){
  for(int i=0;i<s_tabmots->dim;i++){

      printf(" %d ",s_tabmots->tab[i]);


  }

}

int chercherindicemintab(t_tab_int_dyn *stTab){
  /// \brief cherche l'indice de l'élément minimal dans un tableau d'int dynamique
  /// \return l'indice de l'élément minimal
  int min=stTab->tab[0];
  int imin=0;
  int dim=stTab->dim;
  for(int i=1;i<dim;i++){
    if(stTab->tab[i]<min){
      min=stTab->tab[i];
      imin=i;
  }
}
  return imin;
}
int chercherindicemaxtab(t_tab_int_dyn *stTab){
  /// \brief cherche l'indice de l'élément maximal dans un tableau d'int dynamique
  /// \return l'indice de l'élément maximal
  int imax=0;
  int max=stTab->tab[0];
  int dim=stTab->dim;
  for(int i=1;i<dim;i++){
    if(stTab->tab[i]>max){
      max=stTab->tab[i];
      imax=i;
    }
  }
  return imax;
}
int chercherminmat(t_mat_int_dyn *stTab){
  /// \brief cherche l'élément minimal dans une matrice d'int dynamique
  /// \return l'élément minmal
  int min=stTab->tab[0][0];
  int lignes=stTab->nbRows;
  int colonnes=stTab->nbCol;
  for(int i=0;i<lignes;i++){
    for(int j=0;j<colonnes;j++){
      if(stTab->tab[i][j]<min) min=stTab->tab[i][j];
    }

  }
  return min;
}

int cherchermaxmat(t_mat_int_dyn *stTab){
  /// \brief cherche l'élément maximal dans une matrice d'int dynamique
  /// \return l'élément maximal
  int max=stTab->tab[0][0];
  int lignes=stTab->nbRows;
  int colonnes=stTab->nbCol;
  for(int i=0;i<lignes;i++){
    for(int j=0;j<colonnes;j++){
      if(stTab->tab[i][j]>max) max=stTab->tab[i][j];
    }

  }
  return max;
}

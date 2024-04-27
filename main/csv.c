/// \file csv.c
/// \brief Transforme un fichier csv directement en matrice de char dynamique
/// \author Malek Ben Ghachem
/// \date janvier 2022
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
   char ***csv(FILE *fstream,t_mat_char_star_dyn *mat)
   /// \param[out] *mat reçoit chacun des éléments du fichier csv afin de pouvoir les utiliser dans le cadre des différents calculs
   /// \param[in] *fstream est le fichier csv utilisable grâce a fopen
   /// \param[in] *mat est la matrice de char dynamique vide

   {
      char *rem,*rem2;
      char buffer[1024] ;
      char *elem,*ligne;
      char ***matrice;
      int i=0,j=0,nbcol=0,nblignes=0;

      matrice=NULL;


      if(fstream == NULL) //Vérfier que le fichier n'est pas vide
      {
         printf("\n Erreur ouverture du fichier");
         exit (-1) ;
      }

      while((ligne=fgets(buffer,sizeof(buffer),fstream))!=NULL)//Comme strtok modifie la ligne sur laquelle on l'utilise je mets en condition de boucle "tant que la ligne d'ou on va récuperer les éléments n'est pas vide"
      {

        elem = strtok(ligne,",");
        j=0;
        nblignes++;
        matrice=realloc(matrice,nblignes*sizeof(char**));//realloc de la zone mémoire des lignes au fur et à mesure
        while(elem != NULL)
        {

        if(i==0 ) nbcol++;
        matrice[i]=realloc(matrice[i],nbcol*sizeof(char*));

        matrice[i][j]= strdup(elem);
        if(i==0 && j==2) rem=strdup(elem);//DEBUG 1 NECESSAIRE
        if(i==0 && j==3) rem2=strdup(elem);//DEBUG 1 NECESSAIRE

        elem = strtok(NULL,",");


        j++;
        }



        ++i ;


   }

mat->tab=matrice;
mat->nbRows=(nblignes);
mat->nbCol=(nbcol);
mat->tab[0][2]=rem;// DEBUG 1 NECESSAIRE
mat->tab[0][3]=rem2;// DEBUG 1 NECESSAIRE





return 0;

    }

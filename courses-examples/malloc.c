#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int nombreDAmis = 0, i = 0;
    int* ageAmis = NULL;

    printf("Combien d'amis avez-vous ? ");
    scanf("%d", &nombreDAmis);

    if (nombreDAmis > 0)
    {
        ageAmis = malloc(nombreDAmis * sizeof(int));
        if (ageAmis == NULL)
        {
            exit(0); 
        }

        for (i = 0 ; i < nombreDAmis ; i++)
        {
            printf("Quel age a l'ami numero %d ? ", i + 1);
            scanf("%d", &ageAmis[i]);
        }

        printf("\n\nVos amis ont les ages suivants :\n");
        for (i = 0 ; i < nombreDAmis ; i++)
        {
            printf("%d ans\n", ageAmis[i]);
        }

        free(ageAmis);
    }

    return 0;
}
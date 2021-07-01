#include "tas_binaire.h"

int main()
{
    //int t1[] = {1, 84, 700, 26, 44, 2, 72, 98, 10, 245, 631, 214, 578, 11, 99, 945};
    //int t2[] = {1, 84, 700, 26, 44, 2, 72, 98, 10, 245, 631, 214, 578, 11, 99, 945};
    //int tab_bis[]= {912, 4, 3, 5, 44, 54, 21, 34, 67, 14};
    //init_tab(tab_v);

    int tab_v[11];

    tab_v[0] = 48;
    tab_v[1] = 912;
    tab_v[10] = 12;
    tab_v[2] = 74;
    tab_v[3] = 98;
    tab_v[4] = 44;
    tab_v[5] = 58;
    tab_v[6] = 24;
    tab_v[7] = 6;
    tab_v[8] = 100;
    tab_v[9] = 41;

    //remplir_tab(tab_v);
    printf("taille du tableau %ld\n", sizeof(tab_v) / sizeof(int));
    affficher_tab(tab_v, sizeof(tab_v) / sizeof(int));

    int *tas = NULL;

    tas = creer_tas_b(tab_v, sizeof(tab_v) / sizeof(int));
    //affficher_tab(tas, NB_ELT_MAX);
    printf("\ntas cree\n");
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
    fichier_graphiz(tas);
    system("dot -Tsvg graph_tas.dot -o img.svg");
    system("display ./img.svg 2> /dev/null");
    /*
    ajouter_elt(tas, 4);
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
    printf("\n\n fin ajout 4\n");
    
    ajouter_elt(tas, 999);
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
    printf("\n\n fin ajout 999\n");

    ajouter_elt(tas, 60);
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
    printf("\n\n fin ajout 60\n");

    ajouter_elt(tas, 10);
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
    printf("\n\n fin ajout 10\n");
*/

    printf("\n\n\n\n\n debut retirage");
    printf("valeur retiree %d\n", retirer_elt(tas));
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    /*
    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
*/
    /*
    printf("valeur modifie tas[%d]=%d -> %d\n", 4, tas[4], 10);
    diminuer_cle(tas, 4, 10);

    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");

    printf("valeur modifie tas[%d]=%d, et nouvelle valeur %d\n", 3, tas[3], 2);
    diminuer_cle(tas, 3, 2);

    fichier_graphiz(tas);
    system("dot -Tjpg graph_tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
*/

    //void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
    time_t debut;
    time_t fin;
    time_t tps_tri_tas_min;
    time_t tps_qsort;

    int *t1 = malloc(sizeof(int) * NB_ELT_MAX);
    int *t2 = malloc(sizeof(int) * NB_ELT_MAX);

    init_tab(t1);
    init_tab(t2);

    printf("\n\n");

    clock_t start_t, end_t, total_t;
    double temps_tri_tas;
    double temps_qsort;

    start_t = clock();
    printf("Debut du Tri par tas, start_t = %ld\n", start_t);
    tri_tas_min(t1, NB_ELT_MAX);
    end_t = clock();
    printf("Fin du Tri par tas,   end_t = %ld\n", end_t);
    temps_tri_tas = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Tri par tas:         Total time taken by CPU: %f\n", temps_tri_tas);

    printf("\n");

    start_t = clock();
    printf("Debut du Tri par tas, start_t = %ld\n", start_t);
    qsort(t2, NB_ELT_MAX, sizeof *t2, compare);
    end_t = clock();
    printf("Fin du Tri par tas,   end_t = %ld\n", end_t);
    temps_qsort = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Tri par tas:         Total time taken by CPU: %f\n", temps_qsort);

    printf("\nComparaison :\n\ttri_tas_min = %f s \n\tqsort       = %f s\n", temps_tri_tas, temps_qsort);

    printf("\n\n");
    //printf("A_etoide avec la distance euclidienne : Total time taken by CPU: %f\n", m_e);

    return 0;
}

void affficher_tab(int *tab, int nb_elt)
{
    for (int i = 0; i < nb_elt; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void init_tab(int tab[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        tab[i] = i;
    }
}

//Creer le tas a partir d'un tableau de valeur, 1 si reussi, 0 sinon
int *creer_tas_b(int *tab_v, int nb_elt)
{
    int *tas = NULL;
    tas = malloc(sizeof(int) * NB_ELT_MAX);

    init_tab(tas);

    if (tas != NULL)
    {

        tas[0] = 0;
        for (int i = 0; i < nb_elt; i++)
        {
            tas[i + 1] = tab_v[i];
            tas[0] += (tab_v[i] != 0);
        }

        for (int i = (tas[0] / 2); i > 0; i--)
        {
            //printf("tas[%d]=%d\n", i, tas[i]);
            entasser(tas, i);
        }
    }
    return tas;
}

int f_g(int i)
{
    return (2 * i);
}
int f_d(int i)
{
    return (2 * i + 1);
}
int pere(int i)
{
    return i / 2;
}

void permute_a_b(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ajouter_elt(int *tas, int val)
{
    if (tas[0] < NB_ELT_MAX)
    {
        tas[0]++;
        tas[tas[0]] = val;
        detasser(tas, tas[0]);
    }
    else
        printf("plus de place dans le tas");
}

int retirer_elt(int *tas)
{
    int rac = 0;
    if (tas[0] > 0)
    {
        rac = tas[1];
        tas[1] = tas[tas[0]];
        tas[0]--;
        entasser(tas, 1);
    }
    else
    {
        printf("plus rien a retirer\n");
    }
    return rac;
}

void entasser(int *tas, int i)
{

    int l = f_g(i);
    int r = f_d(i);
    int min = i;
    //printf("tas[i]=%d, tas[l]=%d, tas[r]=%d\n", tas[i], tas[l], tas[r]);

    if (l <= tas[0] && tas[l] < tas[i])
    {
        min = l;
    }

    if (r <= tas[0] && tas[r] < tas[min])
    {
        min = r;
    }

    if (min != i)
    {
        permute_a_b(&(tas[i]), &(tas[min]));
        entasser(tas, min);
    }
}

void detasser(int *tas, int i)
{

    int p = pere(i);

    int max = i;

    if (p > 0 && tas[p] > tas[i])
    {
        max = p;
    }

    if (max != i)
    {
        permute_a_b(&(tas[i]), &(tas[max]));
        detasser(tas, max);
    }
}

void fichier_graphiz(int *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 1;

    fprintf(fichier, "graph { ");
    while (k <= tas[0])
    {
        if (tas[k] > 0 && tas[f_g(k)] > 0 && f_g(k) <= tas[0])
            fprintf(fichier, "\n\t%d--%d", tas[k], tas[f_g(k)]);

        if (tas[k] > 0 && tas[f_d(k)] > 0 && f_d(k) <= tas[0])
            fprintf(fichier, "\n\t%d--%d", tas[k], tas[f_d(k)]);
        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void modifier_cle(int *tas, int indice, int val_ajoutee)
{
    if (indice < tas[0])
    {
        printf("cle modifie : %d + %d = %d\n", tas[indice], val_ajoutee, tas[indice] + val_ajoutee);
        tas[indice] += val_ajoutee;
        if (val_ajoutee < 0)
            detasser(tas, indice);
        else
        {
            entasser(tas, indice);
            entasser(tas, indice);
        }
    }
    else
        printf("modification impossible : indice trop petit\n");
}

void diminuer_cle(int *tas, int indice, int nouv_key)
{
    if (indice <= tas[0])
    {
        tas[indice] = nouv_key;
        int i = indice;
        int p_i = pere(i);
        while (i > 1 && tas[p_i] > tas[i])
        {
            permute_a_b(&tas[i], &tas[p_i]);
            i = p_i;
            p_i = pere(i);
        }
    }
    else
        printf("modification impossible : indice trop petit\n");
}

int *tri_tas_min(int *tab_valeur, int nb_elt)
{
    int *tas = NULL;
    tas = creer_tas_b(tab_valeur, nb_elt);
    //affficher_tab(tas, NB_ELT_MAX);

    if (tas != NULL)
    {
        int nb_elt = tas[0];
        for (int i = 0; i < nb_elt; i++)
        {
            tab_valeur[i] = retirer_elt(tas);
        }
    }
    else
    {
        printf("echec allocation malloc dans tri_tas_min\n");
    }
    return tab_valeur;
}

/* fonction utilisateur de comparaison fournie a qsort() */
static int compare(void const *a, void const *b)
{
    /* definir des pointeurs type's et initialise's
      avec les parametres */
    int const *pa = a;
    int const *pb = b;

    /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
    return *pa - *pb;
}
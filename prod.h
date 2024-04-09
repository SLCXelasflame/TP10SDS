#define TAILLE 50

#define  NB_MAX_PRODUITS 1000


typedef struct {
    int id;
	char nom[64];
    float prix;
    int stock;
} TProduit;


typedef TProduit TTableauDeProduits[ NB_MAX_PRODUITS];





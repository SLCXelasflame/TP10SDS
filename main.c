////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"


int lireCommande(char* nomCommande, TProduit *prod_list, int max){
	
	FILE *file = fopen(nomCommande, "r");
	if(file == NULL){
		return 0;
	}
	char nom[128];
	TTableauDeProduits pde_tab;
	int id, qte,i =0;
	fscanf(file, "%s", nom);
	do
	{
		if(!feof(file)){
		fscanf(file,"%i %i", &id, &qte);
		pde_tab[i].id = id;
		pde_tab[i].stock = qte;
		i++;
		}
		}while(!feof(file));
	 fclose(file);
	
	char nomFacture[28];
	char num[5] = "";
	int index = -1;
	float total = 0;
	TProduit temp;
	strcpy(nomFacture,"./factures/facture");
	strncpy(num, nomCommande + strlen("./commandes/commande"), 4);
	strcat(nomFacture, num);
	strcat(nomFacture, ".txt");
	FILE *facture = fopen(nomFacture, "w+");
	if(facture == NULL){
		return 0;
	}
	FILE *alerte;
	fprintf(facture, "Client : %s\n", nom);
	int present = 0;
	for(int y = 0; y < i; y++){
		id = pde_tab[y].id;
		qte = pde_tab[y].stock;
	while(temp.id != id && index < max){
					index++;
					temp = prod_list[index];
					}
					if(!(index==max)){
						
					
					if(qte >= temp.stock){
						qte = temp.stock;
					}
					if((temp.stock-qte)== 0 && temp.stock>0){
						temp.stock = 0;
						alerte = fopen("alerte.txt", "a");
						if(alerte == NULL){
							return 0;
						}
						do
						{
							if(!feof(alerte)){
							fscanf(alerte,"%i", &id);
							
							if(id == temp.id){
								printf("alerte id :%d\n", id);
								present = 1;
								break;
							}
							}
							}while(!feof(alerte));
							if(present){
								fprintf(alerte ,"\nRéférence : %d\t | Nom : %s", temp.id, temp.nom);
							}
						fclose(alerte);
						present = 0;
					}
					else{
						temp.stock -= qte;

					}
					prod_list[index] = temp;
					index = -1;


		fprintf(facture, "%i %s (PU=%f€) :: %f€\n", qte, temp.nom, temp.prix, temp.prix*qte);
		total += temp.prix*qte;
		}


	}
	fprintf(facture, "\t TOTAL = %f", total);
	fclose(facture);
	return 1;
		}


int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
	FILE *f;
	int N;
	f=fopen("nextFact","r");
	fread(&N,sizeof(int),1,f);
	fclose(f);
		N = 1;

	//printf("\n--->lu N=%d",N);
	return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
	int m,c,d,u;
	char cm,cc,cd,cu;
	m=N/1000;cm=48+m;
	N%=1000;
	c=N/100;cc=48+c;
	N%=100;
	d=N/10;cd=48+d;
	u=N%10;
	cu=48+u;
	N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}


void lireLesCommandes(TProduit *prod_list, int max) //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
	FILE *alerte = fopen("alerte.txt", "a");
	char var[128];
	fseek(alerte , 0 , SEEK_END);
	if(ftell(alerte) == 0){
		fprintf(alerte, "Référence des stocks vides");
	}
	fclose(alerte);
	FILE *ficCommande=NULL;
	int FINI=0;
	int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
	char NNNN[5];
	char nomCommande[29];

	do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	//printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present \n",nomCommande);
			fclose(ficCommande);
			int result  = lireCommande(nomCommande, prod_list, max); // à vous de coder cette fonction lors de ce TP9
			if(!result){
				printf("Erreur lors du chargement de la commande %s");
			}

		}
	else
		{
			printf("\n toutes les commandes presentes ont ete traitees.\n");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		

}



int main()
{
	FILE *prod = fopen("produits.txt", "r");
	if(prod == NULL){
		return 0;
	}
	TTableauDeProduits prod_list;
	TProduit temp;
	int max = 0;
	do
	{
		if(!feof(prod)){
		fscanf(prod,"%i %s %f",&(temp.id), temp.nom, &(temp.prix));
			prod_list[max] = temp;
			max++;
			}
		}while(!feof(prod));
		fclose(prod);
		
		FILE *stock = fopen("stock.txt", "r");
		int id,nbstock, index = -1;
		do
	{
		if(!feof(stock)){
		fscanf(stock,"%i %i", &id, &nbstock);
			temp = prod_list[index];
				while(temp.id != id && index < max-1){
					index++;
					temp = prod_list[index];
				}
				prod_list[index].stock = nbstock;

				index = 0;

		 
			}

		}while(!feof(stock));
		fclose(stock);

	// 	for(int y = 0; y < max; y++){
	// 	printf("id:%d, nom:%s, prix:%f, stock:%d \n", prod_list[y].id,  prod_list[y].nom,  prod_list[y].prix,  prod_list[y].stock);
	// }
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	/*
	FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);
	*/ 	

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(prod_list, max); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	
	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	
	stock = fopen("stock.txt", "w+");
	if(stock == NULL){
		return 0;
	}
		int y = 0;
		for(int y = 0; y < max; y++){
			temp = prod_list[y];
			fprintf(stock, "%i %i", temp.id, temp.stock);
			if(y <max-1){
				fprintf(stock, "\n");
			}
		 }
		fclose(stock);
	return 0;
}

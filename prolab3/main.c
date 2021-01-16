#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct Dugum
{
    char veri[100];
    int adet;
    struct Dugum *sonraki;
};

struct Dugum *ilk=NULL, *son=NULL;

void SonaEkle(char kelime[100],int adet)
{
    struct Dugum *yeni = (struct Dugum*) malloc(sizeof(struct Dugum));
    strncpy(yeni->veri,kelime,sizeof(char)*100);
    yeni->adet= adet;
    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->sonraki=NULL;
    }
    else
    {
        son->sonraki=yeni;
        son=yeni;
        son->sonraki=NULL;
    }
}

void BasaEkle(char kelime[100],int adet)
{
    struct Dugum *yeni = (struct Dugum*) malloc(sizeof(struct Dugum));
    strncpy(yeni->veri,kelime,sizeof(char)*100);
    yeni->adet= adet;
    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->sonraki=NULL;
    }
    else
    {
        yeni->sonraki=ilk;
        ilk=yeni;
    }
}

void ArayaEkle(struct Dugum* onceki,char kelime[100],int adet)
{
    struct Dugum *yeni = (struct Dugum*) malloc(sizeof(struct Dugum));
    strncpy(yeni->veri,kelime,sizeof(char)*100);
    yeni->adet= adet;
    yeni->sonraki=onceki->sonraki;
    onceki->sonraki = yeni;
}

struct Dugum *Ara(char kelime[100])
{
    struct Dugum *ara=ilk;

    while(ara!=NULL)
    {
        if(strcmp(ara->veri,kelime)==0)
            return ara;
        ara=ara->sonraki;
    }
    return NULL;
}

void Listele()
{
    struct Dugum *liste=ilk;
    int sayac = 1;
    while(liste!=NULL)
    {
        printf("%d. %s: %d\n",sayac++,liste->veri,liste->adet);
        liste=liste->sonraki;
    }
}

int KelimeyiSay(char c[100])
{
    FILE *fp;
    fp = fopen("oku.txt","r");
    char kelime[100];
    int sayac=0;
    while(fscanf(fp,"%s",&kelime)==1)
    {
        if(strcmp(c,kelime) == 0) sayac++;  //https://stackoverflow.com/questions/8004237/how-do-i-properly-compare-strings-in-c
    }

    fclose(fp);

    return sayac;
}


int KelimeListedeVarMi(char c[100])
{
    if(Ara(c)!=NULL) return 1;
    else return 0;
}

void ListeyeEkle(char kelime[100],int adet)
{
    if(ilk==NULL)
    {
        SonaEkle(kelime,adet);
    }
    else
    {
        if(adet>=ilk->adet)
        {
            BasaEkle(kelime,adet);
            return;
        }
        struct Dugum *liste=ilk;
        struct Dugum *eklenecekYer=ilk;
        while(liste!=NULL && adet<liste->adet)
        {
            eklenecekYer = liste;
            liste=liste->sonraki;
        }
        ArayaEkle(eklenecekYer,kelime,adet);

    }

}

int main()
{
    FILE *fp;
    char kelime[100];
    fp = fopen("oku.txt","r");
    while(fscanf(fp,"%s",&kelime)==1)
    {
        if(!KelimeListedeVarMi(kelime))
        {
            int adet = KelimeyiSay(kelime);
            ListeyeEkle(kelime,adet);
        }

    }
    fclose(fp);
    Listele();
    return 0;
}

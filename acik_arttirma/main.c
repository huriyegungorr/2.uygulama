#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxKatilimci 50
// struct sayesinde tek bir i�aret�iyle main i�inde bir �ok de�i�ken �a��r�labilir typedef okunulabilirli�i artt�r�r
typedef struct AcikArtirma {
    char urun[50];
    float baslangicFiyati;
    float enYuksekTeklif;
    int kazananTeklifVeren;
} AcikArtirma;

typedef struct Katilimci {
    int numara;
    float teklif;
} Katilimci;
//voide tan�mlanan komut sayesinde birden fazla kez ayn� terimler �a��r�labilir
//burada her �a��r�ld���nda teklif ister
void teklifVer(AcikArtirma *artirma, Katilimci *katilimci) {
    if (katilimci->teklif > artirma->enYuksekTeklif) {
        artirma->enYuksekTeklif = katilimci->teklif;
        artirma->kazananTeklifVeren = katilimci->numara;
        printf("Katilimci %d yeni teklif: %.2f\n", katilimci->numara, katilimci->teklif);
    } else {
        printf("Gecersiz teklif. Teklifiniz en y�ksek tekliften kucuk.\n");
    }
}
//bu son durumu g�sterir
void durumuGoster(AcikArtirma *artirma) {
    printf("%s icin acik artirma durumu:\n", artirma->urun);
    printf("Baslangic Fiyati: %.2f\n", artirma->baslangicFiyati);
    printf("En Yuksek Teklif: %.2f (Katilimci %d)\n", artirma->enYuksekTeklif, artirma->kazananTeklifVeren);
}
// bu i�lem ile kaznan ki�iye kadar verilen teklifler �demeye eklenir 
double odemeGoster(Katilimci *katilimcilar, int kullaniciSayisi, int kazananTeklifVeren) {
    double odeme = 0.0;
    int i;

    for (i = 0; i < kullaniciSayisi; i++) {
        if (i != kazananTeklifVeren - 1) {
            odeme += katilimcilar[i].teklif;
            printf("Katilimci %d icin odeme: %.2f\n", i + 1, katilimcilar[i].teklif);
        }
    }

    return odeme;
}

int main() {
    int kullaniciSayisi;
    AcikArtirma acikArtirma;
    Katilimci katilimcilar[maxKatilimci];

    printf("Katilimci sayisini girin (en fazla %d): ", maxKatilimci);
    scanf("%d", &kullaniciSayisi);

    if (kullaniciSayisi > maxKatilimci) {
        printf("Hata: Maks katilimci sayisindan fazlasiniz\n");
        return 1;
    }

    strcpy(acikArtirma.urun, "Baslangic");
    acikArtirma.baslangicFiyati = 50;
    acikArtirma.enYuksekTeklif = acikArtirma.baslangicFiyati;
    acikArtirma.kazananTeklifVeren = 0;

    durumuGoster(&acikArtirma);
//bu for d�ng�s� kat�l�mc�lara numara vererek birden fazla teklif ister
    int i;
    for (i = 0; i < kullaniciSayisi; i++) {
        katilimcilar[i].numara = i + 1;
        printf("Katilimci %d, teklifinizi girin: ", katilimcilar[i].numara);
        scanf("%f", &katilimcilar[i].teklif);

        teklifVer(&acikArtirma, &katilimcilar[i]);
    }

    durumuGoster(&acikArtirma);

    double toplamOdeme = odemeGoster(katilimcilar, kullaniciSayisi, acikArtirma.kazananTeklifVeren);
    printf("Toplam odeme: %.2f\n", toplamOdeme);

    return 0;
}


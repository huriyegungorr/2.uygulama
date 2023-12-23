#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxKatilimci 50
//t�m mainde kullan�labilmesi i�in de�ikenlerimizi main d���nda tan�ml�yoruz
struct AcikArtirma {
    char urun[50];
    float baslangicFiyati;
    float enYuksekTeklif;
    int kazananTeklifVeren;
};

struct Katilimci {
    int numara;
    float teklif;
};
// void ile geri d���s�z komutlar�m�z� tan�ml�yoruz bunun nedeni main i�inin kar��mamas� ve birden fazla kez kolayca g�sterilebilmesi
// bu k�s�mda birden fazla kullan�c�dan teklif istiyoruz
void teklifVer(struct AcikArtirma *artirma, struct Katilimci *katilimci) {
    if (katilimci->teklif > artirma->enYuksekTeklif) {
        artirma->enYuksekTeklif = katilimci->teklif;
        artirma->kazananTeklifVeren = katilimci->numara;
        printf("Katilimci %d yeni teklif: %.2f\n", katilimci->numara, katilimci->teklif);
    } else {
        printf("Gecersiz teklif. Teklifiniz en y�ksek tekliften kucuk.\n");
    }
}
//bu ks�m sayesinde artt�rmada som durumu g�r�yoruz
void durumuGoster(struct AcikArtirma *artirma) {
    printf("%s icin acik artirma durumu:\n", artirma->urun);
    printf("Baslangic Fiyati: %.2f\n", artirma->baslangicFiyati);
    printf("En Yuksek Teklif: %.2f (Katilimci %d)\n", artirma->enYuksekTeklif, artirma->kazananTeklifVeren);
}
// odeme bir �nceki kullan�c�lar�n teklifleri kadar olmas� i�in for ile kazanana kadarki teklifleri al�p �demeye ekliyrouz
double odemeGoster(struct Katilimci *katilimcilar, int kullaniciSayisi, int kazananTeklifVeren) {
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
    struct AcikArtirma acikArtirma;
    struct Katilimci katilimcilar[maxKatilimci];

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
// buradaki for d�ng�m�z her kullan�c�ya artt�rarak numara verir
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


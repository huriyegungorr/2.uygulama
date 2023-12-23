#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxKatilimci 50
// struct sayesinde tek bir iþaretçiyle main içinde bir çok deðiþken çaðýrýlabilir typedef okunulabilirliði arttýrýr
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
//voide tanýmlanan komut sayesinde birden fazla kez ayný terimler çaðýrýlabilir
//burada her çaðýrýldýðýnda teklif ister
void teklifVer(AcikArtirma *artirma, Katilimci *katilimci) {
    if (katilimci->teklif > artirma->enYuksekTeklif) {
        artirma->enYuksekTeklif = katilimci->teklif;
        artirma->kazananTeklifVeren = katilimci->numara;
        printf("Katilimci %d yeni teklif: %.2f\n", katilimci->numara, katilimci->teklif);
    } else {
        printf("Gecersiz teklif. Teklifiniz en yüksek tekliften kucuk.\n");
    }
}
//bu son durumu gösterir
void durumuGoster(AcikArtirma *artirma) {
    printf("%s icin acik artirma durumu:\n", artirma->urun);
    printf("Baslangic Fiyati: %.2f\n", artirma->baslangicFiyati);
    printf("En Yuksek Teklif: %.2f (Katilimci %d)\n", artirma->enYuksekTeklif, artirma->kazananTeklifVeren);
}
// bu iþlem ile kaznan kiþiye kadar verilen teklifler ödemeye eklenir 
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
//bu for döngüsü katýlýmcýlara numara vererek birden fazla teklif ister
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


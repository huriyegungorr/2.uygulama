#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxKatilimci 50
//tüm mainde kullanýlabilmesi için deðikenlerimizi main dýþýnda tanýmlýyoruz
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
// void ile geri döüþsüz komutlarýmýzý tanýmlýyoruz bunun nedeni main içinin karýþmamasý ve birden fazla kez kolayca gösterilebilmesi
// bu kýsýmda birden fazla kullanýcýdan teklif istiyoruz
void teklifVer(struct AcikArtirma *artirma, struct Katilimci *katilimci) {
    if (katilimci->teklif > artirma->enYuksekTeklif) {
        artirma->enYuksekTeklif = katilimci->teklif;
        artirma->kazananTeklifVeren = katilimci->numara;
        printf("Katilimci %d yeni teklif: %.2f\n", katilimci->numara, katilimci->teklif);
    } else {
        printf("Gecersiz teklif. Teklifiniz en yüksek tekliften kucuk.\n");
    }
}
//bu ksým sayesinde arttýrmada som durumu görüyoruz
void durumuGoster(struct AcikArtirma *artirma) {
    printf("%s icin acik artirma durumu:\n", artirma->urun);
    printf("Baslangic Fiyati: %.2f\n", artirma->baslangicFiyati);
    printf("En Yuksek Teklif: %.2f (Katilimci %d)\n", artirma->enYuksekTeklif, artirma->kazananTeklifVeren);
}
// odeme bir önceki kullanýcýlarýn teklifleri kadar olmasý için for ile kazanana kadarki teklifleri alýp ödemeye ekliyrouz
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
// buradaki for döngümüz her kullanýcýya arttýrarak numara verir
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


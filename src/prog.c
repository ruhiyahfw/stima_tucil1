// RUHIYAH FARADISHI WIDIAPUTRI - 13519034

#include<stdio.h>
#include<stdlib.h>
#include"time.h"
#include "boolean.h"
#include"katachar.h"

char line[20];
combin node;
int angkapakai[10];
int totaltes,totalkombinasi;
char taknol[10]; // char mana saja yang nilainya tidak boleh sama dengan nol
boolean siap;

address Alokasi (char line[]){
    address P;
    P = (address) malloc (1*sizeof(listring));
    if (P != NULL){
        P->word = CharToKata(line);
        P->next = NULL;
    }
}

void InsLast (List *L, char line[]){
    address P, last;
    if (First(*L)==NULL){
        P = Alokasi(line);
        if (P != NULL){
            P->next = L->First;
            L->First = P;
        }
    }
    else{
        P = Alokasi(line);
        if (P != NULL){
            last = L->First;
            while (last->next != NULL){
                last = last->next;
            }
            last->next = P;
            (last->next)->next = NULL;
        }
    }
}

boolean hurufawal (int idx){
    boolean found = false;
    int i = 0;
    while (!found && i <= 10 ){
        if (node.hu[idx].hur == taknol[i]){
            found = true;
        }
        else{
            i = i+1;
        }
    }
    return found;
}

int carinilai(char c){
    int j = 0;
    int hasil;
    boolean found;
    found = false;
    while (!found && j < 10){
        if (c == node.hu[j].hur){
            hasil = node.hu[j].nilainya;
            found = true;
        }
        else{
            j++;
        }
    }
    return hasil;
}

boolean ketemu(List L){
    int hitung1, hitung2;
    hitung1 = 0;
    hitung2 = 0;
    address P;
    P = First(L);
    while (P->word.TabKata[0] != '-'){
        int pengali = 1;
        for (int i = P->word.Length-1; i >= 0; i--){
            if (P->word.TabKata[i] != '+' && P->word.TabKata[i] != ' '){
                int n = carinilai(P->word.TabKata[i]);
                hitung1 = hitung1 + (pengali * n);
                pengali = pengali * 10;
            }
        }
        P = Next(P);
    }
    P = Next(P);
    int pengali = 1;
    for (int i = P->word.Length-1; i >= 0; i--){
        if (P->word.TabKata[i] != ' '){
            int n = carinilai(P->word.TabKata[i]);
            hitung2 = hitung2 + (pengali * n);
            pengali = pengali * 10;
        }
    }
    return (hitung1 == hitung2);
}

void salinhasil(List L){
    printf("HASIL YANG DITEMUKAN:\n");
    address P;
    int i, nilai;
    P = L.First;
    while (P != NULL){
        for (i=0; i<P->word.Length; i++){
            if (P->word.TabKata[i] != '-' && P->word.TabKata[i] != '+' && P->word.TabKata[i] != ' '){
                nilai = carinilai(P->word.TabKata[i]);
                printf("%d",nilai);
            }
            else{
                printf("%c",P->word.TabKata[i]);
            }
        }
        printf("\n");
        P = P->next;
    }
    printf("\n");
}

boolean permutasi (List L, int idx){
    if (idx == node.length - 1){
        for (int a = 0; a < 10; a++){
            if (angkapakai[a] == 0 && (a != 0 || (!hurufawal(idx) && a == 0))){
                node.hu[idx].nilainya = a;
                if (ketemu(L)){
                    salinhasil(L);
                    // return true;  -- kalau mau mencari 1 solusi saja hapus // supaya tidak jadi komentar
                }
                totaltes++;
            }
        }
        return false;
    }
    for (int b=0; b<10; b++){
        if (angkapakai[b] == 0 && (b != 0 || (!hurufawal(idx) && b == 0))){
            node.hu[idx].nilainya = b;
            angkapakai[b] = 1;
            if (permutasi(L,idx+1)){
                return true;
            }
            angkapakai[b] = 0;
        }
    }
    return false;
}

int main(){
    int i=0;
    listring s;
    address P;
    List L;

    First(L) = NULL;
    totaltes = 0;

    // Membaca dari txt dan menyimpannya
    FILE *teks = fopen("../test/tes1.txt","r");
    while (fgets(line,sizeof(line),teks) != NULL){
        InsLast(&L,line);
    }

    // mulai hitung waktu
    clock_t start, end;
    start = clock();

    // mencetak soal ke layar
    printf("PERSOALAN CRYPTARITHMETIC: \n");
    P = L.First;
    while (P != NULL){
        for (i=0; i<P->word.Length; i++){
            printf("%c",P->word.TabKata[i]);
        }
        printf("\n");
        P = P->next;
    }
    printf("\n");

    // mengecek ada berapa huruf
    int hurufapa[26];
    for (i=0; i<26; i++){
        hurufapa[i] = 0;
    }
    P = First(L);
    while (P != NULL){
        for (i=0; i<P->word.Length; i++){
            if (P->word.TabKata[i] != '+' && P->word.TabKata[i] != '-' && P->word.TabKata[i] != ' '){
                int indeks = P->word.TabKata[i]-'A';
                if (hurufapa[indeks]==0){
                    hurufapa[indeks] = 1;
                }
            }
        }
        P = Next(P);
    }
    int count=0;
    for (i=0; i<26; i++){
        if (hurufapa[i] != 0){
            count++;
        }
    }
    
    // mencari permutasi yang cocok
    if (count > 10){
        printf("Tidak ada solusi yang mungkin\n");
    }
    else{
        // -- mendata huruf yang ada
        int j = 0;
        for (i=0;i < 26; i++){
            if (hurufapa[i] != 0){
                node.hu[j].hur = (char) (i+'A');
                j++;
            }
        }
        node.length = count;
        // -- membuat angka yang diapakai apa saja hehe
        for (i=0; i<10; i++){
            angkapakai[i] = 0;
        }
        // -- mencatat huruf mana saja yang nilainya tidak boleh 0
        for (int j=0; j<10; j++){
            taknol[j] = '?';
        }
        P = First(L);
        i = 0;
        while (P != NULL){
            if (P->word.TabKata[0] != '-' ){
                int j=0;
                while ((P->word.TabKata[j] == '+' || P->word.TabKata[j] == ' ') && j < P->word.Length){
                    j=j+1;
                }
                taknol[i] = P->word.TabKata[j];
                i++;
            }
            P = Next(P);
        }
        // -- mencari permutasi yang cocok
        siap = permutasi(L,0);
        end = clock();
        double time_taken = (double)(end-start)/(double)(CLOCKS_PER_SEC);
        printf("Waktu yang dibutuhkan: %.10lf sekon\n",time_taken);
        printf("Total tes yang dilakukan: %d\n",totaltes);
    }
    return 0;
}
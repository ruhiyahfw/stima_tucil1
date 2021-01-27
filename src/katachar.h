#ifndef __KATA_CHAR_H_
#define __KATA_CHAR_H_

#define NMax 50

typedef struct {
	char TabKata[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
    int Length;
} Kata;
typedef struct listr *address;
typedef struct listr{
    Kata word;
    address next;
} listring;
typedef struct {
    address First;
}List;
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

typedef struct nilaihuruf{
    char hur;
    int nilainya;
} nilaihuruf;
typedef struct combi{
    nilaihuruf hu[10];
    int length;
} combin;

Kata CharToKata(char Line[]);

#endif
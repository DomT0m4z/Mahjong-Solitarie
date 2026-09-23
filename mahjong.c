# Mahjong-Solitarie

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define pcs 144

typedef struct {
    char tps;
    int  vlr;
    int  cmd;
    int  lnh;
    int  cln;
    int  rmvd;
    int  blckd;
} Tblr;

Tblr mjng[pcs];
int  r_tps;
int  mvs;

void inicializar(void);
void embaralhar(void);
void clr_blocks(void);
void exbr_t(void);
void exbr_s(void);
int  lvr(int i);
int  pv(int a, int b);
void rp(int a, int b);
int  tpl(void);
int  t_l(void);

int main(void) {
    int a;
    int b;

    srand((unsigned int)time(NULL));

    r_tps = pcs;
    mvs = 0;

    inicializar();
    embaralhar();
    clr_blocks();

    printf("========================================\n");
    printf("        MAHJONG SOLITARIO em C          \n");
    printf("========================================\n");
    printf("Selecione 2 tiles identicos e livres.\n");
    printf("Indice visivel ao lado de cada tile.\n\n");

    while (!t_l()) {
        if (!tpl()) {
            printf("\n!! JOGO TRAVADO\n");
            printf("   Nenhum par livre disponivel.\n");
            printf("   Tiles restantes: %d\n", r_tps);
            break;
        }

        exbr_t();
        exbr_s();

        printf("Tile 1 (indice 0-%d): ", pcs - 1);
        scanf("%d", &a);

        printf("Tile 2 (indice 0-%d): ", pcs - 1);
        scanf("%d", &b);

        if (!pv(a, b)) {
            printf("\n!! Par invalido ou tile bloqueado.\n");
            printf("   Verifique os indices e tente novamente.\n\n");
            continue;
        }

        rp(a, b);
        clr_blocks();

        mvs++;
        printf("\n>> Par [%c%d] removido. Movimento %d.\n\n",
               mjng[a].tps, mjng[a].vlr, mvs);
    }

    if (t_l()) {
        printf("========================================\n");
        printf("         VITORIA! PARABENS!             \n");
        printf("========================================\n");
        printf("Movimentos: %d\n", mvs);
        printf("Pares removidos: %d\n", mvs);
    }

    return 0;
}

void inicializar(void) {
    char pcs1[] = {'B','C','D','W','F'};
    int idx = 0;

    for (int s = 0; s < 5; s++) {
        for (int v = 1; v <= 9; v++) {
            for (int c = 0; c < 4; c++) {
                mjng[idx].tps    = pcs1[s];
                mjng[idx].vlr   = v;
                mjng[idx].cmd   = 0;
                mjng[idx].lnh     = idx / 12;
                mjng[idx].cln     = idx % 12;
                mjng[idx].rmvd = 0;
                mjng[idx].blckd = 0;
                idx++;
            }
        }
    }
}

void embaralhar(void) {
    for (int i = pcs - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Tblr tmp  = mjng[i];
        mjng[i]  = mjng[j];
        mjng[j]  = tmp;
    }
}

void clr_blocks(void) {
    for (int i = 0; i < pcs; i++) {
        if (mjng[i].rmvd) {
            mjng[i].blckd = 0;
            continue;
        }
        mjng[i].blckd = (i % 2 != 0) ? 1 : 0;
    }
}

void exbr_t(void) {
    printf("\n");
    for (int i = 0; i < pcs; i++) {
        printf("%3d:", i);
        if (mjng[i].rmvd)
            printf("[  ] ");
        else if (mjng[i].blckd)
            printf("[##] ");
        else
            printf("[%c%d] ", mjng[i].tps, mjng[i].vlr);
        if ((i + 1) % 12 == 0)
            printf("\n");
    }
    printf("\n");
}

void exbr_s(void) {
    printf("----------------------------------------\n");
    printf("Tiles restantes : %d\n", r_tps);
    printf("Movimentos      : %d\n", mvs);
    printf("----------------------------------------\n");
}

int lvr(int i) {
    return i >= 0
        && i < pcs
        && !mjng[i].rmvd
        && !mjng[i].blckd;
}

int pv(int a, int b) {
    return a != b
        && lvr(a)
        && lvr(b)
        && mjng[a].tps  == mjng[b].tps
        && mjng[a].vlr == mjng[b].vlr;
}

void rp(int a, int b) {
    mjng[a].rmvd = 1;
    mjng[b].rmvd = 1;
    r_tps -= 2;
}

int tpl(void) {
    for (int i = 0; i < pcs; i++)
        for (int j = i + 1; j < pcs; j++)
            if (pv(i, j))
                return 1;
    return 0;
}

int t_l(void) {
    return r_tps == 0;
}

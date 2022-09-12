#include <stdio.h>
#include <stdlib.h>

// Aluno: Isabelle

const int amax = 2047, levmax = 3, cxmax = 200;

enum fct {LIT, OPR, LOD, STO, CAL, INT, JMP, JPC};
struct Instruction {
    enum fct f;
    int l;
    int a;
} ;

struct Instruction code[200]; // cxmax
const int stacksize = 500;
int s[500]; // stacksize
int p, b, t;

int base(int l){
    int b1;
    b1 = b;
    while(l > 0){
        b1 = s[b1];
        l = l-1;
    }
    return b1;
}

int main(){
   struct Instruction i;
  // Instructions:
  // Instructions:
  code[0].f = INT; code[0].l = 0; code[0].a = 5;
  code[1].f = LIT; code[1].l = 0; code[1].a = 5;
  code[2].f = STO; code[2].l = 0; code[2].a = 8;
  code[3].f = CAL; code[3].l = 0; code[3].a = 6;
  code[4].f = LOD; code[4].l = 0; code[4].a = 12;
  code[5].f = OPR; code[5].l = 0; code[5].a = 0;
  //função
  code[6].f = INT; code[6].l = 0; code[6].a = 9;
  code[7].f = LOD; code[7].l = 0; code[7].a = 3;
  code[8].f = LIT; code[8].l = 0; code[8].a = 2; // Inicia contador
  code[9].f = STO; code[9].l = 0; code[9].a = 4;
  code[10].f = LIT; code[10].l = 0; code[10].a = 0; // first term
  code[11].f = STO; code[11].l = 0; code[11].a = 5;
  code[12].f = LIT; code[12].l = 0; code[12].a = 1; // second term
  code[13].f = STO; code[13].l = 0; code[13].a = 6;
  code[14].f = LIT; code[14].l = 0; code[14].a = 0; //fibo(next term)
  code[15].f = STO; code[15].l = 0; code[15].a = 7;
  code[16].f = LOD; code[16].l = 0; code[16].a = 5;     // Inicio do loop (load first)
  code[17].f = LOD; code[17].l = 0; code[17].a = 6;     // Load second
  code[18].f = OPR; code[18].l = 0; code[18].a = 2;     // first + second
  code[19].f = STO; code[19].l = 0; code[19].a = 7;     // Salva em fibo
  code[20].f = LOD; code[20].l = 0; code[20].a = 4;     // Load aux/contador
  code[21].f = LOD; code[21].l = 0; code[21].a = 3;  // Load Máximo
  code[22].f = OPR; code[22].l = 0; code[22].a = 10; // Menor que
  code[23].f = JPC; code[23].l = 0; code[23].a = 32; // Saida do loop
  code[24].f = LOD; code[24].l = 0; code[24].a = 4;  // Load aux
  code[25].f = OPR; code[25].l = 0; code[25].a = 2;  // Aux + 1
  code[26].f = STO; code[26].l = 0; code[26].a = 4;
  code[27].f = LOD; code[27].l = 0; code[27].a = 6; // carrega termo 2
  code[28].f = STO; code[28].l = 0; code[28].a = 5; // termo 1 = termo 2
  code[29].f = LOD; code[29].l = 0; code[29].a = 7; // carrega fibo
  code[30].f = STO; code[30].l = 0; code[30].a = 6; // termo 2 = fibo
  code[31].f = JMP; code[31].l = 0; code[31].a = 16;  // Fim do loop
  code[32].f = OPR; code[32].l = 0; code[32].a = 0;
    {
        printf(" start pl/0 ");
        t = 0;
        b = 1;
        p = 0;
        s[1] = 0;
        s[2] = 0;
        s[3] = 0;
        printf("\n t |  b |  p |"); 
        do {
            i =  code[p];
            printf("\n%2d | %2d | %2d |", t, b, p); 
            // printf("\n%d",i.f);
            p = p+1;
            switch (i.f){
                case LIT:
                    t = t+1;
                    s[t] = i.a;
                    break;
                case OPR:
                    switch(i.a){
                        case 0: 
                            t = b - 1;
                            p = s[t + 3];
                            b = s[t + 2];
                            break;
                        case 1:
                            s[t] = -s[t];
                            break;
                        case 2: 
                            t = t - 1;
                            s[t] = s[t] + s[t + 1];
                            break;
                        case 3:
                            t = t - 1;
                            s[t] = s[t] - s[t + 1];
                            break;
                        case 4: 
                            t = t - 1;
                            s[t] = s[t] * s[t + 1];
                            break;
                        case 5:
                            t = t - 1;
                            s[t] = s[t] / s[t + 1]; // div = divisao?
                            break;
                        case 6:
                            s[t] = (s[t]) % 2; // ord??
                            break;
                        case 8:
                            t = t - 1;
                            s[t] = (s[t] = s[t + 1]);
                            break;
                        case 9:
                            t = t - 1;
                            s[t] = (s[t] != s[t + 1]); // simbolo <> ??
                            break;
                        case 10:
                            t = t - 1;
                            s[t] = (s[t] < s[t + 1]);
                            break;
                        case 11:
                            t = t - 1;
                            s[t] = (s[t] >= s[t + 1]);
                            break;
                        case 12: 
                            t = t - 1;
                            s[t] = (s[t] > s[t + 1]);
                            break;
                        case 13: 
                            t = t - 1;
                            s[t] = (s[t] <= s[t + 1]);
                            break;
                    }
                    break;
                case LOD: 
                    t = t + 1;
                    s[t] = s[base(i.l) + i.a];
                    break;
                case STO:
                    s[base(i.l) + i.a] = s[t];
                    //printf("%d", s[t]);
                    t = t - 1;
                    break;
                case CAL:
                    s[t + 1] = base(i.l);
                    s[t + 2] = b;
                    s[t + 3] = p;
                    b = t + 1;
                    p = i.a;
                    break;
                case INT:
                    t = t + i.a;
                    break;
                case JMP:
                    p = i.a;
                    break;
                case JPC: 
                    if (s[t] == 0){
                        p = i.a;
                        t = t - 1;
                    }
                    break;
            }
            for(int j = 1; j <= t; j++){
                printf("[%d]", s[j]); 
            }
        } while(p != 0);
    }
    return 0;
}

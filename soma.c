#include <stdio.h>
#include <stdlib.h>

// Aluno: Isabelle Cruz

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
  code[0].f = INT; code[0].l = 0; code[0].a = 5;
  code[1].f = LIT; code[1].l = 0; code[1].a = 2; 
  code[2].f = LIT; code[2].l = 0; code[2].a = 3;
  code[3].f = OPR; code[3].l = 0; code[3].a = 2;   // soma 
  code[4].f = OPR; code[4].l = 0; code[4].a = 0;
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

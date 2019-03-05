#ifndef __Indexes_h_
#define __Indexes_h_
#define one (0)
#define al_r(n) (1+2*(n))
#define al_i(n) (2+2*(n))
#define DI_r(n,m) (1+2*nfibs + (((n)==(m))?((n)):(nfibs + (2*nfibs - 1 - (n))*(n) + 2*((m) - (n) - 1))))
#define DI_i(n,m) (1+2*nfibs + (((n)==(m))?(0):(nfibs + (2*nfibs - 1 - (n))*(n) + 2*((m) - (n) - 1) + 1)))
#define Da_r(n,m) (1+2*nfibs + nfibs*nfibs + (((n)==(m))?(2*(n)):(2*nfibs + (2*nfibs - 1 - (n))*(n) + 2*((m) - (n) - 1))))
#define Da_i(n,m) (1+2*nfibs + nfibs*nfibs + (((n)==(m))?(2*(n) + 1):(2*nfibs + (2*nfibs - 1 - (n))*(n) + 2*((m) - (n) - 1) + 1)))
#endif /*__Operator_h_*/

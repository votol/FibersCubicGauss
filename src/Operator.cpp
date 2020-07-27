#include "Operator.h"
#include <cuda_runtime.h>
#include <iostream>
#include <list>
#include <vector>
#include "OperatorKernels.h"
#include "ParameterDefines.h"
#include "Indexes.h"
#define SUM_NUM 25

void alpha_re_maker(std::list<OperatorElement>& in, const std::vector<double>& parameters, const unsigned int n)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    if(n != 0)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = al_i(n - 1);
    }

    if(n != nfibs - 1)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = al_i(n + 1);
    }

    in.push_back(OperatorElement());
    in.back().coe = - G / 2.0;
    in.back().ind1 = one;
    in.back().ind2 = one;
    in.back().ind3 = al_r(n);

    in.push_back(OperatorElement());
    in.back().coe = -L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = al_i(n);

    in.push_back(OperatorElement());
    in.back().coe = -L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = al_i(n);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(n,n);
    in.back().ind3 = al_i(n);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(n,n);
    in.back().ind3 = al_r(n);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(n,n);
    in.back().ind3 = al_i(n);
}

void alpha_im_maker(std::list<OperatorElement>& in, const std::vector<double>& parameters, const unsigned int n)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    if(n != 0)
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = al_r(n - 1);
    }

    if(n != nfibs - 1)
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = al_r(n + 1);
    }

    in.push_back(OperatorElement());
    in.back().coe = - G / 2.0;
    in.back().ind1 = one;
    in.back().ind2 = one;
    in.back().ind3 = al_i(n);

    in.push_back(OperatorElement());
    in.back().coe = L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = al_r(n);

    in.push_back(OperatorElement());
    in.back().coe = L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = al_r(n);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(n,n);
    in.back().ind3 = al_r(n);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(n,n);
    in.back().ind3 = al_r(n);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(n,n);
    in.back().ind3 = al_i(n);
}

void DI_re_maker(std::list<OperatorElement>& in, const std::vector<double>& parameters, const unsigned int n, const unsigned int m)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    if(n != 0)
    {
        in.push_back(OperatorElement());
        in.back().coe = (n==m)? 2.0 : 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_i(n - 1, m);
    }
    if(m != nfibs-1)
    {
        in.push_back(OperatorElement());
        in.back().coe = (n==m)? -2.0 : -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_i(n, m + 1);
    }
    if(m !=0 && m != n)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_i(n, m - 1);
    }
    if((n != nfibs - 1) && (m != n))
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_i(n + 1, m);
    }

    in.push_back(OperatorElement());
    in.back().coe = - G;
    in.back().ind1 = one;
    in.back().ind2 = one;
    in.back().ind3 = DI_r(n, m);

    if(n!=m)
    {
        in.push_back(OperatorElement());
        in.back().coe = -2.0*L;
        in.back().ind1 = one;
        in.back().ind2 = DI_r(m,m);
        in.back().ind3 = DI_i(n,m);

        in.push_back(OperatorElement());
        in.back().coe = 2.0*L;
        in.back().ind1 = one;
        in.back().ind2 = DI_r(n,n);
        in.back().ind3 = DI_i(n,m);

        in.push_back(OperatorElement());
        in.back().coe = -2.0*L;
        in.back().ind1 = al_r(m);
        in.back().ind2 = al_r(m);
        in.back().ind3 = DI_i(n,m);

        in.push_back(OperatorElement());
        in.back().coe = -2.0*L;
        in.back().ind1 = al_i(m);
        in.back().ind2 = al_i(m);
        in.back().ind3 = DI_i(n,m);

        in.push_back(OperatorElement());
        in.back().coe = 2.0*L;
        in.back().ind1 = al_r(n);
        in.back().ind2 = al_r(n);
        in.back().ind3 = DI_i(n,m);

        in.push_back(OperatorElement());
        in.back().coe = 2.0*L;
        in.back().ind1 = al_i(n);
        in.back().ind2 = al_i(n);
        in.back().ind3 = DI_i(n,m);
    }

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(m,m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(n,n);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(m,m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(n,n);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_r(m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = al_i(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = Da_i(n,m);
}

void DI_im_maker(std::list<OperatorElement>& in, const std::vector<double>& parameters, const unsigned int n, const unsigned int m)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    if(n != 0)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_r(n - 1, m);
    }
    if(m != nfibs-1)
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_r(n, m + 1);
    }
    if(m !=0 )
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_r(n, m - 1);
    }
    if(n != nfibs - 1)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = DI_r(n + 1, m);
    }

    in.push_back(OperatorElement());
    in.back().coe = - G;
    in.back().ind1 = one;
    in.back().ind2 = one;
    in.back().ind3 = DI_i(n, m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(m,m);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(n,n);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_r(m);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_i(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = DI_r(n,m);


    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(m,m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(n,n);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = Da_i(n,m);


    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(m,m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(n,n);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_r(m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = al_i(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = Da_r(n,m);
}

void Da_re_maker(std::list<OperatorElement>& in, const std::vector<double>& parameters, const unsigned int n, const unsigned int m)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    if(n != 0)
    {
        in.push_back(OperatorElement());
        in.back().coe = (n==m)? -2.0 : -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_i(n - 1, m);
    }
    if(m != nfibs-1)
    {
        in.push_back(OperatorElement());
        in.back().coe = (n==m)? -2.0 : -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_i(n, m + 1);
    }
    if(m !=0 && m != n)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_i(n, m - 1);
    }
    if((n != nfibs - 1) && (m != n))
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_i(n + 1, m);
    }

    in.push_back(OperatorElement());
    in.back().coe = - G;
    in.back().ind1 = one;
    in.back().ind2 = one;
    in.back().ind3 = Da_r(n, m);

    //-------------------------------------------
    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(n,n);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(m,m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_r(m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_i(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = Da_i(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = Da_i(n,m);
    //---------------------------------
    
    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(n,n);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_i(m,m);
    in.back().ind3 = DI_r(n,m);
    
    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = DI_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = -2.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = DI_r(n,m);

    if(n!=m)
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0*L;
        in.back().ind1 = one;
        in.back().ind2 = Da_r(m,m);
        in.back().ind3 = DI_i(n,m);
        
        in.push_back(OperatorElement());
        in.back().coe = -1.0*L;
        in.back().ind1 = one;
        in.back().ind2 = Da_r(n,n);
        in.back().ind3 = DI_i(n,m);
        
        in.push_back(OperatorElement());
        in.back().coe = -1.0*L;
        in.back().ind1 = al_r(n);
        in.back().ind2 = al_r(n);
        in.back().ind3 = DI_i(n,m);
        
        in.push_back(OperatorElement());
        in.back().coe = 1.0*L;
        in.back().ind1 = al_r(m);
        in.back().ind2 = al_r(m);
        in.back().ind3 = DI_i(n,m);
        
        in.push_back(OperatorElement());
        in.back().coe = -1.0*L;
        in.back().ind1 = al_i(m);
        in.back().ind2 = al_i(m);
        in.back().ind3 = DI_i(n,m);
        
        in.push_back(OperatorElement());
        in.back().coe = 1.0*L;
        in.back().ind1 = al_i(n);
        in.back().ind2 = al_i(n);
        in.back().ind3 = DI_i(n,m);
    }
    
    if(n == m)
    {
        in.push_back(OperatorElement());
        in.back().coe = -2.0*L;
        in.back().ind1 = al_r(m);
        in.back().ind2 = al_i(m);
        in.back().ind3 = one;
        
        in.push_back(OperatorElement());
        in.back().coe = -1.0*L;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_i(m,m);
    }
}

void Da_im_maker(std::list<OperatorElement>& in, const std::vector<double>& parameters, const unsigned int n, const unsigned int m)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    if(n != 0)
    {
        in.push_back(OperatorElement());
        in.back().coe = (n==m)? 2.0 : 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_r(n - 1, m);
    }
    if(m != nfibs-1)
    {
        in.push_back(OperatorElement());
        in.back().coe = (n==m)? 2.0 : 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_r(n, m + 1);
    }
    if(m !=0 && m != n)
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_r(n, m - 1);
    }
    if((n != nfibs - 1) && (m != n))
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_r(n + 1, m);
    }

    in.push_back(OperatorElement());
    in.back().coe = - G;
    in.back().ind1 = one;
    in.back().ind2 = one;
    in.back().ind3 = Da_i(n, m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(n,n);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = one;
    in.back().ind2 = DI_r(m,m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_r(m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_i(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = Da_r(n,m);

    in.push_back(OperatorElement());
    in.back().coe = 2.0*L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = Da_r(n,m);
    //----------------------------------------
    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(m,m);
    in.back().ind3 = DI_r(n,m);
    
    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = one;
    in.back().ind2 = Da_r(n,n);
    in.back().ind3 = DI_r(n,m);
    
    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = al_r(n);
    in.back().ind2 = al_r(n);
    in.back().ind3 = DI_r(n,m);
    
    in.push_back(OperatorElement());
    in.back().coe = 1.0*L;
    in.back().ind1 = al_r(m);
    in.back().ind2 = al_r(m);
    in.back().ind3 = DI_r(n,m);
    
    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = al_i(m);
    in.back().ind2 = al_i(m);
    in.back().ind3 = DI_r(n,m);
    
    in.push_back(OperatorElement());
    in.back().coe = -1.0*L;
    in.back().ind1 = al_i(n);
    in.back().ind2 = al_i(n);
    in.back().ind3 = DI_r(n,m);
    
    if(n!=m)
    {
        in.push_back(OperatorElement());
        in.back().coe = -1.0*L;
        in.back().ind1 = one;
        in.back().ind2 = Da_i(n,n);
        in.back().ind3 = DI_i(n,m);
    
        in.push_back(OperatorElement());
        in.back().coe = 1.0*L;
        in.back().ind1 = one;
        in.back().ind2 = Da_i(m,m);
        in.back().ind3 = DI_i(n,m);
        
        in.push_back(OperatorElement());
        in.back().coe = -2.0*L;
        in.back().ind1 = al_r(n);
        in.back().ind2 = al_i(n);
        in.back().ind3 = DI_i(n,m);
    
        in.push_back(OperatorElement());
        in.back().coe = 2.0*L;
        in.back().ind1 = al_r(m);
        in.back().ind2 = al_i(m);
        in.back().ind3 = DI_i(n,m);
    }
    
    if(n==m)
    {
        in.push_back(OperatorElement());
        in.back().coe = 1.0*L;
        in.back().ind1 = one;
        in.back().ind2 = one;
        in.back().ind3 = Da_r(m,m);
        
        in.push_back(OperatorElement());
        in.back().coe = 1.0*L;
        in.back().ind1 = al_r(m);
        in.back().ind2 = al_r(m);
        in.back().ind3 = one;
        
        in.push_back(OperatorElement());
        in.back().coe = -1.0*L;
        in.back().ind1 = al_i(m);
        in.back().ind2 = al_i(m);
        in.back().ind3 = one;
    }
}

std::vector<std::list<OperatorElement> >  build_oper_pre(const std::vector<double>& parameters, unsigned int dim)
{
    unsigned int nfibs = (unsigned int)Nfibs;
    std::vector<std::list<OperatorElement> > result(dim);
    for(unsigned int ind1 = 0; ind1 < nfibs; ind1++)
    {
        alpha_re_maker( result[al_r(ind1)], parameters,ind1);
        alpha_im_maker( result[al_i(ind1)], parameters,ind1);
    }

    for(unsigned int n = 0; n < nfibs; n++)
    {
        for(unsigned int m = n; m < nfibs; m++)
        {
            DI_re_maker( result[DI_r(n,m)], parameters,n,m);
            if(m != n)
                DI_im_maker( result[DI_i(n,m)], parameters,n,m);
            Da_re_maker( result[Da_r(n,m)], parameters,n,m);
            Da_im_maker( result[Da_i(n,m)], parameters,n,m);
        }
    }
    return result;
}

std::vector<OperatorElement> build_oper(const std::vector<double>& params, unsigned int dim)
{

    std::vector<OperatorElement> result(SUM_NUM * dim);
    std::vector<std::list<OperatorElement> > tmp(build_oper_pre(params, dim));
    auto it = result.begin();
    for(unsigned int ind =0; ind < dim; ind++)
    {
        auto it_tmp = tmp[ind].begin();
        for(unsigned int ind1 =0; ind1 < SUM_NUM; ind1++)
        {
            if(it_tmp == tmp[ind].end())
            {
                it->coe = 0.0;
                it->ind1 =0;
                it->ind2 =0;
                it->ind3 =0;
            }
            else
            {
                *it = *it_tmp;
                ++it_tmp;
            }
            ++it;
        }
    }
    return result;
}

OperatorBase::OperatorBase(const std::vector<double>& params, unsigned int dim)
{
    DIM = dim;
    //std::cout<< DIM<<std::endl;
    std::vector<OperatorElement> tmp_oper(build_oper(params, dim));
    /*for(unsigned int ind =  30696-24 ; ind < 30696 + 100; ind ++)
    {
        std::cout<<tmp_oper[ind].coe << " " <<tmp_oper[ind].ind1 <<" "<< tmp_oper[ind].ind2<<" "<< tmp_oper[ind].ind3<<std::endl;
    }*/
    cudaMalloc((void**)&device_operator,SUM_NUM * dim * sizeof(device_operator[0]));
    cudaMemcpy(device_operator, tmp_oper.data(),
            SUM_NUM * dim  * sizeof(device_operator[0]),
            cudaMemcpyHostToDevice);
}

OperatorBase::~OperatorBase()
{
    cudaFree(device_operator);
}

void OperatorBase::apply(double* out, const double* in,
        const std::vector<double>& parameters)
{
    ProceedVector(out, in, device_operator, DIM, (unsigned int)(Nfibs));
}

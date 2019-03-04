#ifndef __complex_h_
#define __complex_h_
#include <math.h>
#include <iostream>
template<typename T> class complex;
template<typename T> complex<T> conj(const complex<T> &);
template<typename T> T abs2(const complex<T>& );

template<typename T>
class complex
  {
  public:
    static complex i;
    
    T __re;
    T __im;
    complex():__re(T(0)),__im(T(0)){};
    complex(T re,T im)
        {
        __re=re;
        __im=im;
        }
    complex(const complex &a)
        {
        __re=a.__re;
        __im=a.__im;
        }
    complex(const T &a)
        {
        __re=a;
        __im=T(0);
        }
    
    complex(T &a)
        {
        __re=a;
        __im=0;
        }
    complex&  operator =(const complex &a)
        {
        __re=a.__re;
        __im=a.__im;
        return *this;
        }
    bool operator ==(const complex &a) const
        {
        return __re==a.__re&&__im==a.__im;
        }
    bool operator !=(const complex &a) const
        {
        return __re!=a.__re||__im!=a.__im;
        }  
    complex operator +() const
        {
        return complex(__re,__im);
        }
    complex operator -()const
        {
        return complex(-__re,-__im);
        }
    complex operator +(const complex &a) const
        {
        return complex(__re+a.__re,__im+a.__im);
        }
    complex operator -(const complex &a) const
        {
        return complex(__re-a.__re,__im-a.__im);
        }
    complex operator *(const complex &a) const
        {
        return complex(a.__re*__re-a.__im*__im,a.__im*__re+a.__re*__im);
        }
    complex operator /(const complex &a) const
        {
        return conj<T>(a)*complex(__re,__im)/abs2<T>(a);
        }
    void operator +=(const complex &a)
        {
        __re+=a.__re;
        __im+=a.__im;
        }
    void operator -=(const complex &a)
        {
        __re-=a.__re;
        __im-=a.__im;
        }
    void operator *=(const complex &a)
        {
        complex per(__re,__im);
        per=per*a;
        __re=per.__re;
        __im=per.__im;
        }
    void operator /=(const complex &a)
        {
        complex per(__re,__im);
        per=per/a;
        __re=per.__re;
        __im=per.__im;
        }
    complex operator +(const T& a) const
        {
        return complex(__re+a,__im);
        }
    complex operator -(const T& a) const
        {
        return complex(__re-a,__im);
        }
    complex operator *(const T& a) const
        {
        return complex(__re*a,__im*a);
        }
    complex operator /(const T& a) const
        {
        return complex(__re/a,__im/a);
        }
    void operator +=(const T& a)
        {
        __re+=a;
        }
    void operator -=(const T& a)
        {
        __re-=a;
        }
    void operator *=(const T& a)
        {
        __re*=a;
        __im*=a;
        }
    void operator /=(const T& a)
        {
        __re/=a;
        __im/=a;
        }
    std::ostream & operator<< (std::ostream & o)
        {
        return o;
        }
  };

template<typename T>
complex<T> complex<T>::i=complex<T>(T(0),T(1));

template<typename T>
complex<T> conj(const complex<T> &a)
    {
    return complex<T>(a.__re,-a.__im);
    }
template<typename T>
T abs2(const complex<T> &a)
  {
  return a.__re*a.__re+a.__im*a.__im;
  }

template<typename T>
complex<T> operator +(const T& a,const complex<T> &b)
  {
  return complex<T>(b.__re+a,b.__im);
  }
template<typename T>
complex<T>  operator -(const T& a,const complex<T> &b)
  {
  return complex<T>(a-b.__re,-b.__im);
  }
template<typename T>
complex<T> operator *(const T& a,const complex<T> &b)
  {
  return complex<T>(a*b.__re,a*b.__im);
  }
template<typename T>
complex<T> operator /(const T& a,const complex<T> &b)
  {
  return a*conj(b)/abs2(b);
  }
template<typename T>
complex<T> exp(const complex<T> &a)
  {
  return complex<T>(cos(a.__im),sin(a.__im))*exp(a.__re);
  }
template<typename T>
std::ostream& operator<<( std::ostream & in, const complex<T> &a)
  {
    if(a.__re!=T(0.0))
        {
        in<<a.__re;
        if(a.__im>T(0.0))
            in<<"+";
        if(a.__im!=T(0.0))
            in<<a.__im<<"i";
        }
    else
        {
        if(a.__im!=T(0.0))
            in<<a.__im<<"i";
        else
            in<<"0";
        }
    return in;
  }

#endif

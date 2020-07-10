#ifndef Standard_H_
#define Standard_H_

#include <climits>
#define maxsize INT_MAX

typedef int KeyType;
struct records{
    KeyType key;
};
typedef records List[maxsize];

template<class T>
inline void swap(T &a,T &b){
    T temp = a;
    a = b;
    b = temp;
}

#endif
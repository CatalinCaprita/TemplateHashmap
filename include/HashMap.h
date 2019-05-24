#ifndef HASHMAP_H
#define HASHMAP_H
#include <iostream>
#include <exception>
#include <vector>
#include <list>
#include <utility>
#include <string>
using namespace std;
template <class W>
struct KeyHash
{
    unsigned long operator ()(const W &key) const
    {
        return reinterpret_cast<unsigned long>(&key) % 111;
    }

};
template<class K, class V,class F = KeyHash<K> >
class HashMap
{
    public:
        HashMap(int sz = TABLE_SIZE);
        HashMap(const HashMap<K,V,F>&);
        ~HashMap();
        void Inserts(const pair <K,V> &);
        bool Searches(const pair <K,V>&) const;
        void Deletes(const pair <K,V>&);
        int getKeyNumber() const;
        vector<V> KeyPrint(const K&);
        V& operator[](int index) const;
        HashMap & operator = ( const HashMap<K,V,F> &);
        friend ostream & operator <<( ostream & out, const HashMap<K,V,F> & ob)
        {
            out<<"\nFunction hashtable is as follows:\n";
            for(int i = 0; i < ob.KeyArray.size(); i++)
            {
                if(!ob.KeyArray[i].empty())
                {
                    out<<"\n Index "<<i<< ": ";
                        for( V j : ob.KeyArray[i])
                        out<<j<<" ";
                    out<<endl;
                }
            }
            return out;
        }


    private:
         vector< list <V> > KeyArray;
         int Dim;
         F HashFunction;
         int KeyNumber;
         static const int TABLE_SIZE = 100;

};


template <class K,class V,class F >
HashMap<K,V,F>::HashMap(int Size):Dim(Size),KeyNumber(0)
{
    KeyArray.resize(Dim);

}
template <class K,class V,class F >
HashMap<K,V,F>::HashMap(const  HashMap<K,V,F> &ob1): Dim(ob1.Dim), HashFunction(ob1.HashFunction), KeyNumber(0)
{
    KeyArray.resize(Dim);
    std::cout<<"HashTable created using copy constructor!";
    for(int i = 0 ;i< ob1.KeyArray.size(); i++)
    {
        for( V j : ob1.KeyArray[i])
            KeyArray[i].push_back(j);
    }

}
template <class K, class V, class F >
void HashMap<K,V,F>::Inserts(const pair<K,V> & Val)
{
    int index = HashFunction(Val.first);
    if( KeyArray[index].empty())
        KeyNumber++;
    KeyArray[index].push_back(Val.second);


}
template <class K,class V,class F>
HashMap <K,V,F>& HashMap<K,V,F>::operator = (const HashMap<K,V,F> &ob1)
{
    Dim = ob1.dim;
    KeyNumber = ob1.KeyNumber;
    KeyArray.resize(Dim);
    HashFunction = ob1.HashFuntion;
    for(int i = 0 ;i< ob1.KeyArray.size(); i++)
    {
        for( V j : ob1.KeyArray[i])
            KeyArray[i].push_back(j);
    }
    return *this;
}

template <class K,class V,class F  >
bool HashMap<K,V,F>::Searches (const pair<K,V> &Val) const
{
    int index = HashFunction(Val.first);
        for( V j : KeyArray[index])
            if( j == Val.second)
            {
                cout<<"\n Value Found !";
                return true;
            }
    return false;
}

template <class K,class V,class F  >
void HashMap<K,V,F>::Deletes(const pair <K,V> &Val)
{
    int index = HashFunction( Val.first);
    //pentru ca lista este name dependant, adica depinde de V, trebuie typename in fata
    typename list<V>::iterator it;
          for( it = KeyArray[index].begin(); it != KeyArray[index].end(); it++)
        {
            if( *it == Val.second)
            {
                KeyArray[index].erase(it);
                return ;
            }

        }
}

template <class K,class V,class F  >
vector<V> HashMap<K,V,F>::KeyPrint(const K &key)
{
    vector <V> output;
    typename list<V>::iterator it;
    for( it = KeyArray[key].begin(); it != KeyArray[key].end(); it++)
        output.push_back(*it);
    return output;
}

template <class K,class V,class F  >
int HashMap<K,V,F>::getKeyNumber() const
{
    return KeyNumber;
}

template< class K,class V,class F>
V& HashMap<K,V,F>::operator[](int index) const
{
    if(index <0 || index >Dim || KeyArray[index].empty())
        throw out_of_range("\nElement out of range!\n");
    static V value = *KeyArray[index].begin();
    return value;
}

template <class K,class V,class F  >
HashMap<K,V,F>::~HashMap()
{
    for( int i = KeyArray.size()-1 ; i >= 0 ;i--)
        KeyArray[i].clear();
        KeyNumber = 0;
        Dim = 0;
}
#endif // HASHMAP_H

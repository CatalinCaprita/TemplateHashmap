#include <iostream>
#include "HashMap.h"
#include <string>
#include <assert.h>
using namespace std;
template <class K>
class HashFunction2
{
public:
    int operator () ( const  K &key) const
    {
        return key%10;
    }
};
void ContentModifier()
{

}
int main()
{
    HashMap<int,int,HashFunction2<int> > Map1;
    //Testarea functiilor de Stergere si Inserare
    Map1.Inserts( std::make_pair(12,13));
    Map1.Inserts( std::make_pair(5,25));
    Map1.Inserts( std::make_pair(5,111));
    Map1.Inserts( std::make_pair(5,17));
    cout<<Map1;
    assert(Map1.Searches(std::make_pair(5,111)) == true);
   Map1.Deletes(std::make_pair(5,25));
    assert(Map1.Searches(std::make_pair(5,25)) == false);
    cout<<Map1;


    vector <int> Tester (Map1.KeyPrint(5));
    assert(Tester[0] == 111);
    for(int i=0 ;i< Tester.size(); i++)
        cout<<Tester[i]<<" ";


    HashMap<int,int,HashFunction2<int> > Map2 (Map1);
    assert(Map2.Searches(std::make_pair(5,25)) == false);
    Map2.Inserts( std::make_pair(12,13));
    cout<<Map2;
    cout<<endl;
    Map2.Deletes(make_pair(5,111));
    Map2.Deletes(make_pair(5,13));
    vector <int> Tester2(Map2.KeyPrint(5));
    //Testam operatorul []
    Tester2[0] = Map2[5];
    assert(Tester2[0] == 17);
    HashMap<int,string> Map3;
    Map3.Inserts( std::make_pair(1,"Johnny"));
    Map3.Inserts( std::make_pair(1400,"Samantha"));
    Map3.Inserts( std::make_pair(5,"Django"));
    Map3.Inserts( std::make_pair(5,"Michelle"));
    cout<<Map3;
    //Testam Keynumber
    assert(Map3.getKeyNumber() == 4);
    //Constructor de Copiere
        HashMap<int,int,HashFunction2<int> > Map4(Map2);
    assert(Map4.Searches(std::make_pair(12,13)) == true);
    return 0;
}

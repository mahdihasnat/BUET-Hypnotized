#include <bits/stdc++.h>
using namespace std;

int fact[12];
int getvalue(string s)///"abc"->0 , "cba"->5
{
    int ret=0;
    int id[10]= {0,1,2,3,4,5,6,7,8,9};
    for(int i=0,j=s.size()-1; i<s.size(); i++,j--)
    {
        ret+=id[(s[i]-'a')]*fact[j];
        for(int k=s[i]-'a'+1; k<s.size(); k++)
            id[k]--;
    }
    return ret;
}
string getpermutaion(int value,int size)/// (0,3) ->"abc", (5,3)->"cba"
{
    string ret="";
    int id[10]= {0,1,2,3,4,5,6,7,8,9};
    for(int i=0,j=size-1; i<size; i++,j--)
    {
        ret.push_back(id[value/fact[j]]+'a');
        for(int k=value/fact[j]; k<size-1; k++)
            swap(id[k],id[k+1]);
        value%=fact[j];
    }
    return ret;
}
void pre()
{
    fact[0]=1;
    for(int i=1; i<12; i++)
        fact[i]=i*fact[i-1];
}
int main()
{
    pre();
    string s="abcdefgh";
    do
    {
        assert(s==getpermutaion(getvalue(s),8));
    }
    while(next_permutation(s.begin(),s.end()));
}

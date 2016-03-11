#include <iostream>
using namespace std;
int main()
{
    int n,m,p,q[10],q0,v[10],f[10],d[10][10],s[20],r;
    cout<<"Dati nr de stari ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Dati starile ";
        cin>>q[i];
    }
    cout<<"Dati nr de litere ";
    cin>>m;
    for(int i=0;i<m;i++)
    {
        cout<<"Dati literele ";
        cin>>v[i];
    }
    q0=0;
    cout<<"Dati nr de stari finale ";
    cin>>p;
    for(int i=0;i<p;i++)
    {
        cout<<"Dati starile finale ";
        cin>>f[i];
    }
    cout<<"Daca nu exista tranzitie se va scrie -1"<<endl;
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
    {
        cout<<"Tranzitia de la starea "<<i<<" cu simbolul "<<j<<"= ";
        cin>>d[i][j];
    }
    cout<<"Dati dimensiunea cuvantului ";
    cin>>r;
    for(int i=0;i<r;i++)
    cin>>s[i];
    int g=q0;
    for(int i=0;i<r;i++)
    {
        g=d[g][s[i]];
        if(g==-1)
        {
            cout<<"Nu exista drum spre starea respectiva";
            return 0;
        }
    }
    for(int i=0;i<p;i++)
    {
        if(g==f[i])
        {
            cout<<"Cuvantul e acceptat";
            return 0;
        }
        else
        {
            cout<<"Cuvantul nu e acceptat";
            return 0;
        }
    }
}

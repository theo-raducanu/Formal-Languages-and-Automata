#include<iostream>
using namespace std;
int main()
{
    int n,m,p,q[10],q0,v[10],f[10],d[10][10][10],i,j,s[20],r,trz[10][10],t,ok;
    cout<<"Dati nr de stari ";
    cin>>n;
    for(i=0;i<n;i++)
    {
        cout<<"Dati starile ";
        cin>>q[i];
    }
    cout<<"Dati nr de litere ";
    cin>>m;
    for(i=0;i<m;i++)
    {
        cout<<"Dati literele ";
        cin>>v[i];
    }
    q0=0;
    cout<<"Dati nr de stari finale ";
    cin>>p;
    for(i=0;i<p;i++)
    {
        cout<<"Dati starile finale ";
        cin>>f[i];
        }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
        {
            cout<<"Cate tranzitii de la starea "<<i<<" cu simbolul "<<j<<" exista ? ";
            cin>>trz[i][j];
            for(int k=0;k<trz[i][j];k++)
            {
                cout<<"Tranzitia cu numarul "<<k+1<<" de la starea "<<i<<" cu simbolul "<<j<<"= ";
                cin>>d[i][j][k];
            }
        }
    cout<<"Dati dimensiunea cuvantului ";
    cin>>r;
    for(i=0;i<r;i++)
    {
        int sem=0;
        cin>>s[i];
        for(j=0;j<m;j++)
        if(s[i]==v[j])
        sem=1;
        if (sem==0)
        {
            cout<<"Introduceti un caracter din alfabet!";
            i--;
        }
    }
    int g=q0;
    for(int i=0;i<r;i++)
    {
        ok=0;
        for(int j=0;j<trz[g][s[i]] || trz[g][s[i]]==-1;j++)
        {   t=trz[g][s[i]];
            if(ok==0)
            {
                g=d[g][s[i]][j];
                ok=1;
            }
            if(t==-1)
            {
                cout<<"Nu exista drum catre acest cuvant";
                return 0;
            }
        }
    }
    for(int i=0;i<p;i++)
    if(g==f[i])
    {
        cout<<"Cuvantul e acceptat!";
        return 0;
    }
    else
    {
        cout<<"Nu e stare finala";
        return 0;
    }
}

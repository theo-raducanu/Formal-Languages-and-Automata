#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int Q, q0, F[10], nr;
char *cuv, c, *V,*p;
char a[20][20]; //contine doar tranzitiile reprezentate prin litere

int caut(int p);

void verif(int poz, int st, bool &ok);

int main ()
{
	ifstream f("afnl.in");
	f>>Q;
	f>>q0;
	f>>nr;
	int i;
	for (i = 0; i < nr; ++i)
		f >> F[i];
	V = new char [10];
	f >> V;

	int j;
	while (!f.eof())
	{
		f >> i >> j >> c;
		a[i][j] = c;
	}
    cout<<"Introduceti un cuvant format din litere ale alfabetul: "<<V<<endl;
	cuv = new char[256];
	cin>>cuv;
	int l=strlen(cuv);
    bool ok =false;
    if(strcmp(cuv,"#")==0)
    {
            ok=true;
            if(caut(q0))
            {
                  cout<<"Cuvantul vid acceptat. ";
                    return 0;
            }
    }
	for(i=0;i<l && ok==false;i++)
    {
        p=strchr(V,cuv[i]);
        if(!p)
         {
             cout<<"Cuvantul introdus nu contine toate literele din alfabet";
             return 0;
         }
    }
    ok=false;
    verif(0, q0, ok);
        if(ok==1)
        cout << "Cuvantul este acceptat. ";
            else
        cout<<  "Cuvantul este respins. ";
        cout<<endl;
	return 0;

}

int caut(int p)
{
	int i;
	for (i=0; i<nr;++i)
		if (F[i]==p)
			return 1;
	return 0;
}

void verif(int poz, int st, bool &ok)
{
	int i,j,k;
	if (poz>=strlen(cuv))
		if (caut(st)==true)
			    ok=true;
    for (i = 0; i < Q; ++i)
        if(a[st][i]!=NULL)
			{
			    if (a[st][i] == cuv[poz] && ok == false)
					{
					    verif (poz + 1, i, ok);
					}
			     if (a[st][i] == '#' && ok == false)
				     {
				         verif (poz, i, ok);
				     }
			}
}

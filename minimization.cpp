#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

//AFNL
int Q, q0, F[10], nr;
char a[20][20][20];
//AFN
int Q2,q02, F2[10] ,nr2;
char b[20][20][20];
//DFA
int Q3,q03, F3[10] ,nr3;
int d[20][20],df[20][20];
int stari[20][20];
int cntstari=0;
//Altele
int y;
char *cuv, c, *V;
int lambda[20][20];

void del(int v[20])
{
    for(int i=0;i<20;i++)
        v[i]=0;
}
int caut (int p,int F[10],int nr)
{
	int i;
	for (i = 0; i < nr; ++i)
		if (F[i] == p)
			return true;
	return false;
}

void verif (int poz, int st, bool &ok,char a[20][20][20],int Q,int F[10],int nr)
{
	int i,j,k;
	if (poz >= strlen (cuv))
		if (ok == false)
			ok = caut (st,F,nr) ? true : false;
	for (i = 0; i < Q; ++i)
		for (j = 1; j <= a[st][i][0]; ++j)
			if (a[st][i][j] == cuv[poz] && ok == false) //Daca este acelasi simbol, se continua parcurgerea recursiv
					verif (poz + 1, i, ok,a,Q,F,nr);
			    else if (a[st][i][j] == '#' && ok == false)
				     verif (poz, i, ok,a,Q,F,nr);
}
void lambda_inchidere(int x)
{
            for (int j = 0; j < Q; ++j)
                for (int l = 1; l <= a[x][j][0]; ++l)
                if(a[x][j][l]=='#')
                {
                    lambda[y][j]=1;
                    lambda_inchidere(j);
                }
}

void lambda_matrice()
{
    int i,j;
    /* Initilizare matrice inchidere lambda* */
    for (j = 0; j < Q; ++j)
        lambda[j][j]=1;

    for (i = 0; i < Q; ++i)
		{
		    y=i;
		    lambda_inchidere(i);
		}
    //Stari finale
    q02=q0;
    nr2=0;
    Q2=Q;
    for (i = 0; i < Q; ++i)
    {
        if(lambda[q02][i])
            F2[nr2++]=i;
    }
    /*for (i = 0; i < Q; ++i)
    {
        for (j = 0; j < Q; ++j)
            cout<<lambda[i][j]<<" ";
        cout<<endl;
    }
    */

}
void afnl2afn()
{
    lambda_matrice();
    int temp[20],cnt,temp2[20],cnt2,viz[20];
    int i,j,k,l=strlen(V),u,m;
    for (i = 0; i < Q; ++i)
        for (j = 0; j < l; ++j)
        {
            cnt=0;
            del(temp);
            //inchidere lambda cu i
            for(k=0;k< Q;++k)
            {
                if(lambda[i][k])
                    //nl2n[i][j][++nl2n[i][j][0]]=k;
                temp[cnt++]=k;
            }
            /*cout<<endl;
            for(k=0;k<cnt;k++)
                cout<<temp[k];
            */

            del(temp2);
            cnt2=0;
            //i cu stare
            for(k=0;k<cnt;k++)
            {
                for (int u = 0; u < Q; ++u)
                    for (int m = 1; m <= a[temp[k]][u][0]; ++m)
                    if(a[temp[k]][u][m]==V[j])
                        temp2[cnt2++]=u;
            }

            /*cout<<endl;
            for(k=0;k<cnt2;k++)
                cout<<temp2[k];
            */

            //inchidere lambda cu i
            del(temp);
            cnt=0;
            for(k=0;k<cnt2;++k)
            {
                for (int u = 0; u < Q; ++u)
                if(lambda[temp2[k]][u])
                    temp[cnt++]=u;
            }

            /*cout<<endl;
            for(k=0;k<cnt;k++)
                cout<<temp[k];
            */
            del(temp2);
            del(viz);
            cnt2=0;
            for(k=0;k<cnt;++k)
                viz[temp[k]]=1;
            for(k=0;k<20;++k)
                if(viz[k])
                {
                    temp2[cnt2++]=k;
                }
            /*cout<<endl;
            for(k=0;k<cnt2;k++)
                cout<<temp2[k];
            cout<<endl;
            */
            if(cnt2!=0)
            for(k=0;k<cnt2;k++)
            {
                b[i][temp2[k]][++b[i][temp2[k]][0]]=V[j];
            }
        }
}
int existmat(int cnt,int temp[20])
{
    int ok=0,i,j;
    for(i=1;i<=cntstari;i++)
        if(cnt==stari[i][0])
            for(j=1;j<=stari[i][0];j++)
                if(stari[i][j]==temp[j-1])
                    ok=i;
                else
                {
                    ok=0;
                    break;
                }
    return ok;
}
void afn2dfa()
{
    cout<<"DFA :";
    int l=strlen(V),i,k,j,h,cnt=0,noi[20],noicnt=0,u,x,ntmp,viz[20],noitemp[20];
    int temp[20];
    q03=q02;
    for(i=0;i<l;++i)
    {
        cout<<endl<<V[i]<<" ";
        cnt=0;
        for (k = 0; k < Q; ++k)
            for (j = 1; j <=b[q03][k][0]; ++j)
            {
                if(b[q03][k][j]==V[i])
                    temp[cnt++]=k;

            }
        if(existmat(cnt,temp)==0)
        {
              cntstari++;
                stari[cntstari][0]=cnt;
                for(h=0;h<cnt;h++)
                    stari[cntstari][h+1]=temp[h];
                df[q03][i]=cntstari;
                noi[noicnt++]=cntstari;

        }
        for(h=1;h<=stari[cntstari][0];++h)
            cout<<stari[cntstari][h]<<" ";
        cout<<endl;
    }
    while(noicnt)
    {
        ntmp=0;
        del(viz);
        ntmp=noicnt;
        for(i=0;i<noicnt;i++)
            noitemp[i]=noi[i];
        noicnt=0;
        del(noi);
        for(u=0;u<ntmp;u++)
        {
            for(i=0;i<2;++i)
            {
                cnt=0;
                del(temp);
                for(x=0;x<stari[noitemp[u]][0];++x)
                 {
                     for (k = 0; k < Q; ++k)
                        for (j = 1; j <=b[stari[noitemp[u]][x+1]][k][0]; ++j)
                           {
                               if(b[stari[noitemp[u]][x+1]][k][j]==V[i])
                                temp[cnt++]=k;
                           }
                 }
                    del(viz);
                    for(k=0;k<cnt;++k)
                        viz[temp[k]]=1;
                    cnt=0;
                    del(temp);
                    for(k=0;k<10;++k)
                        if(viz[k])
                        {
                            temp[cnt++]=k;
                        }
                    if(existmat(cnt,temp)==0)
                    {
                    cntstari++;
                    stari[cntstari][0]=cnt;
                    for(h=0;h<cnt;h++)
                        stari[cntstari][h+1]=temp[h];
                    df[noitemp[u]][i]=cntstari;
                    noi[noicnt++]=cntstari;
                    }
                    else
                    {
                        df[noitemp[u]][i]=existmat(cnt,temp);
                    }
            }
        }
    }

}
void afisautomat(char a[20][20][20],int Q,int F[10],int nr)
{
    int i,j,l;
    for (i = 0; i < Q; ++i)
		for (j = 0; j < Q; ++j)
			for (l = 1; l <= a[i][j][0]; ++l)
				cout << "De la " << i << " la " << j << " prin " << a[i][j][l] << "\n";
    cout<<"Starile finale :\n";
    for (i = 0; i < nr; ++i)
        cout<<F[i]<<" ";
    cout<<endl;
}

void verifautomat(int q0,char a[20][20][20],int Q,int F[10],int nr)
{
    cuv = new char[256];
	cin >> cuv;
	bool ok = false;
	if (strlen (cuv) == 1 && cuv == "#" && caut(q0,F,nr)) //Verificam separat daca se citeste cuvantul vid.
         cout << "Cuvant acceptat. ";
	else
    verif(0, q0, ok,a,Q,F,nr);
        if(ok==1)
        cout << "Cuvantul este acceptat. ";
            else
        cout<<  "Cuvantul este respins. ";
}
int main ()
{
	ifstream f("afnl.in");
	f >> Q;
	f >> q0;
	f >> nr;
	int i;
	for (i = 0; i < nr; ++i)
		f >> F[i];
	V = new char [10];
	f >> V;

	int j;
	while (!f.eof())
	{
		f >> i >> j >> c;
		if (f.eof())
			break;
		a[i][j][++a[i][j][0]] = c;
	}
	int l;
	cout<<"AFNL :\n";

    afisautomat(a,Q,F,nr);
    afnl2afn();
    cout<<"AFN :\n";
    afisautomat(b,Q,F2,nr2);

    /*cout<<"\nVerificare cuv AFNL : ";
    verifautomat(q0,a,Q,F,nr);

     cout<<"\nVerificare cuv AFN : ";
    verifautomat(q02,b,Q,F2,nr2);
    */

    afn2dfa();
	return 0;
}

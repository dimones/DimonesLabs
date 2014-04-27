/*----------------À‡·Ó‡ÚÓÌ‡ˇ ‡·ÓÚ‡ π1-------------
 1. √ÛÔÔ‡ ¿¬“-309, ‚‡Ë‡ÌÚ π8,·Ë„‡‰‡ π7, ¡ÎËÌÓ‚ Õ.
 2. ”ÒÎÓ‚ËÂ Á‡‰‡˜Ë:
 œÓÎˇ ‘»Œ, ÍÓÎ-‚Ó ÓˆÂÌÓÍ, ÓˆÂÌÍË, ÒÂ‰ÌËÈ ·‡ÎÎ.
 3. ŒÔËÒ‡ÌËÂ ÔÓ„‡ÏÏ˚
 
 */
// 4. “ÂÍÒÚ ÔÓ„‡ÏÏ˚ Ò ÍÓÏÏÂÌÚ‡ËˇÏË
#include <stdio.h> //¡Ë·ÎËÓÚÂÍË
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;
//---------------------------------------------------------
struct stud //ÒÚÛÍÚÛ‡
{
    char name[30];	//ÙËÓ
    int count;		//ÍÓÎ-‚Ó ÓˆÂÌÓÍ
    int *p;			//ÓˆÂÌÍË
    float srz;		//ÒÂ‰ÌËÈ ·‡Î
    //char show();
};
//---------------------------------------------------------
stud *D;			//Ï‡ÒÒË‚
int n=0, sz=10;		//‡ÁÏÂ Ë ËÌ‰ÂÍÒ ÍÓÌˆ‡
char c[100];		//·ÛÙÂ
//---------------------------------------------------------
void extend()									//‡Ò¯ËÂÌËÂ
{
    if(n!=sz)return;						//ÂÒÎË ÌÂ Ì‡‰Ó ÚÓ ÌÂ ·Û‰ÂÏ
    sz*=2;									//‡ÁÏÂ ‚ ‰‚ÓÂ
    D=(stud*)realloc(D, sz*sizeof(stud));
}
//---------------------------------------------------------
void rus(char c[])				//Ô‡¯ÂÏ ÔÓ-ÛÒÒÍË
{
    char str[200];			//·ÛÙÂ
    CharToOem(c, str);
    printf("%s", str);		//‚˚‚Â‰ÂÏ
}
//---------------------------------------------------------
void add()															//‰Ó·‡‚ÎÂÌËÂ ‚ ·‡ÁÛ
{
    extend();													//‡Ò¯ËÂÌËÂ
    rus("¬‚Â‰‡ÚÂ ‘»Œ: ");
    scanf("%s", &D[n].name);									//ÙËÓ
    gets(c);
    rus("¬‚Â‰‡ÚÂ ÍÓÎ-‚Ó ÓˆÂÌÓÍ: ");
    scanf("%d", &D[n].count);									//ÍÓÎ-‚Ó ÓˆÂÌÓÍ
    D[n].srz=0.0;
    int buf=D[n].count;
    D[n].p= new int[buf];										//Ï‡ÒÒË‚ ÓˆÂÌÓÍ
    for(int i=0; i<buf; i++)									//Á‡ÔÓÌˇÂÏ Â„Ó
    {
        while(1)
        {
            sprintf(c, "¬‚Â‰ËÚÂ %d ÓˆÂÌÍÛ: ", i+1);
            rus(c);
            scanf("%d", &D[n].p[i]);
            if(D[n].p[i]>0&&D[n].p[i]<=5)
            {
                D[n].srz+=D[n].p[i];
                break;
            }
        }
    }
    D[n].srz/=D[n].count;										//Ò˜ËÚ‡ÂÏ ÒÂ‰ÌËÈ ·‡Î
    n++;														//ÍÛÚËÏ ËÌ‰ÂÍÒ
}
//---------------------------------------------------------
void show()															//‚˚‚Ó‰ ·‰
{																//¯‡ÔÍ‡)
    rus("\nπ  ‘»Œ\t\t\tŒˆÂÌÍË\t\t\t\t—Â‰ÌËÈ ·‡Î\n-----------------------------------------------------------------\n");
    for(int i=0; i<n;i++)										//‚˚‚Ó‰ËÏ ‚ÒÂ
    {
        printf("%-3d %-30s" , i+1, D[i].name);
        for(int j=0; j<D[i].count; j++)
            printf("%d ", D[i].p[j]);
        printf("\t%0.2f\n", D[i].srz);
        if((i+1)%20==0)getch();								//ÔÓ 20 ¯ÚÛÍ
    }
    
}
//---------------------------------------------------------
void deleteall()						//Ó˜ËÒÚËÏ ·‰
{
    delete D;						//Û‰‡ÎËÏ ·‰
    sz=10;
    n=0;
    D=new stud[sz];					//Ë ÒÌÓ‚‡ ÒÓÁ‰‡‰ËÏ
}
//---------------------------------------------------------
int get_num()									//‚‚Ó‰ ÌÓÏÂ‡
{
    int m;
    do{
        rus("¬‚Â‰ËÚÂ ÌÓÏÂ ˝Î-Ú‡: ");	//Á‡ÔÓÒ
        scanf("%d",&m);					//‚‚Ó‰
    }while(m<1||m>n);						//ÔÓ‚ÂÍ‡
    return m-1;								//ÂÁÛÎ¸Ú‡Ú
}
//---------------------------------------------------------
void save(char f[])											//ÒÓı‡ÌÂÌËÂ
{
    FILE *base=fopen(f,"w");							//ÓÚÍÓÂÏ Ù‡ÈÎ
    fprintf(base, "%d\n", n);							//ÍÓÎ-‚Ó ˝ÎÂÏÂÌÚÓ‚
    for(int i=0; i<n; i++)								//‚˚‚Ó‰
    {
        fprintf(base, "%s\n",D[i].name);
        fprintf(base, "%d\n",D[i].count);
        for(int j=0; j<D[i].count;j++)
            fprintf(base,"%d\n",D[i].p[j]);
    }
    fclose(base);										//Á‡ÍÓÂÏ Ù‡ÈÎ
}
//---------------------------------------------------------
void load(char f[])												//Á‡„ÛÁÍ‡
{
    FILE *base=fopen(f, "r");								//ÓÚÍÓÂÏ Ù‡ÈÎ
    if(base==NULL) return;									//ÂÒÎË ÌÂ ÓÚÍ˚ÎË
    int m;
    fscanf(base, "%d", &m);									//˜ËÚ‡ÂÏ ÍÓÎ-‚Ó
    for(;m!=0;m--,n++)										//˜ËÚ‡ÂÏ ÔÓ ¯ÚÛ˜ÌÓ
    {
        extend();										//‡Ò¯ËÂÌËÂ
        fscanf(base, "%s", &D[n].name);
        fscanf(base, "%d", &D[n].count);
        int buf=D[n].count;
        D[n].p= new int[buf];
        D[n].srz=0.0;
        for(int j=0; j<buf;j++)
        {
            fscanf(base, "%d", &D[n].p[j]);
            D[n].srz+=D[n].p[j];
        }
        D[n].srz/=D[n].count;							//Ò˜ËÚ‡ÂÏ ÒÂ‰ÌËÈ ·‡ÎÎ
    }
    fclose(base);											//Á‡ÍÓÂÏ Ù‡ÈÎ
}
//---------------------------------------------------------
void sortbysrz()												//ÒÓÚËÓ‚Í‡ ÔÓ ÒÂ‰ÌÂÏÛ ·‡ÎÛ
{	stud buf;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(D[i].srz<D[j].srz)
            {
                buf=D[i];
                D[i]=D[j];
                D[j]=buf;
            }
        }
    }
}
//---------------------------------------------------------
void sortbycount()													//ÔÓ ÍÓÎ-‚Û ÓˆÂÌÓÍ
{	stud buf;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(D[i].count>D[j].count)
            {
                buf=D[i];
                D[i]=D[j];
                D[j]=buf;
            }
        }
    }
}
//---------------------------------------------------------
void findbest()
{    //œÓËÒÍ ‚ ÒÚÛÍÚÛÂ
	
    char name[20]; cin >> name; int I = strlen(name);
    for (int i = 0; i<n; i++)
    {
        if (strstr(D[i].name, name) != NULL)
        {
            printf("%s %d %f", D[i].name, D[i].count, D[i].srz)
        }
    }
}


void edit()
{
	cout << "¬‚Â‰ËÚÂ ËÏˇ ‰Îˇ ÒÏÂÌ˚" << endl;
	char temp[60]; cin >> temp;
	for (int i = 0; i < sz; i++)
	{
		if (strcmp(D[i].name, temp) == 0)
		{
			cout << "Vvedite novoe imya" << endl;
			char t[50]; cin >> t;
			strcpy(D[i].name, t);
			break;
		}
        
	}
}

//---------------------------------------------------------
void main()
{
    int k,i;
    D= new stud[sz];								//ÒÓÁ‰‡‰ËÏ ·‰
    while(1)
    {											//ÏÂÌ˛
        rus("1-ƒÓ·‡‚ËÚ¸\n2-œÓÍ‡Á‡Ú¸\n3-”‰‡ÎËÚ¸\n4-—Óı‡ÌËÚ¸\n5-«‡„ÛÁËÚ¸\n6-—ÓÚËÓ‚‡Ú¸ ÔÓ ÒÂ‰ÌÂÏÛ ·‡ÎÛ\n7-—ÓÚËÓ‚‡Ú¸ ÔÓ ÍÓÎ-‚Û ÓˆÂÌÓÍ\n8-Õ‡ÈÚË\n9-Œ˜ËÒÚËÚ¸\n");
        switch(getch())							//ÙÛÌÍˆËÓÌ‡Î
        {
            case '1': add(); break;
            case '2': show(); break;
            case '3': if(n==0) break;
                k=get_num();
                for(i=k; i<n-1;i++)
                    D[i]=D[i+1];
                n--;
                break;
            case '4': save("base.txt"); break;
            case '5': load("base.txt"); break;
            case '6': sortbysrz(); break;
            case '7': sortbycount(); break;
            case '8': findbest(); break;
            case '0': deleteall(); break;
            case 27: return;
        }
    }
}

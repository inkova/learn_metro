#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int generation( int b)  //a=0
{

    int c=rand()%(b + 1); // generation c in [a;b]
    return c;
}

int find_b(int *user_line, int *number_station) //viszitivaet b
{
    int b=0, i;
    for(i=0; i<13; i++)
    if (user_line[i]) b+=number_station[i];
    return b;
}

int recovery_station(int *number_station, int *user_line, int c, char *right_name)  // poisc stanzii otvezauschii c
{
     FILE *file;
    file=fopen("spisok_linii_translit.txt","r");
    if (file==NULL){printf("\n\t\t! ERROR !\nDatabases not found. You should contact technical support.\n");  return -1;}
    int i, j;
     for(i=0; i<13; i++)
        if(user_line[i])
            if(c-number_station[i]>0)
                {
                    for(j=0; j<number_station[i]; j++) fgets(right_name, 100, file);
                    c=c-number_station[i];
                }
             else
                {
                     for(j=0; j<c; j++) fgets(right_name, 100, file);
                     fclose(file);
                     return i;
                }
        else
            for(j=0; j<number_station[i]; j++) fgets(right_name, 100, file);
    return -2;
}

int main()
{
   srand(time(NULL));
   int number_station[13]= {22, 23, 22, 13, 12, 24, 23, 16, 25, 23, 3, 7, 31};
   int user_line[13], user_question[4];
   int i,j; for(i=0; i<13; i++) user_line[i]=1; for(i=0; i<4; i++) user_question[i]=1;
   char *name_linies[13]={"Sokol'nicheskaya(KRASNAYA)", "Zamoskvoreckaya(ZELYONAYA)", "Arbatsko-Pokrovskaya(SINAYA)", "Filevskaya(GOLUBAYA)", "Kol'cevaya(KORICHNEVAYA)", "Kaluzhsko-Rizhskaya(ORANZHEVAYA)", "Tagansko-Krasnopresnenskaya(FIOLETOVAYA)", "Kalininskaya(ZHYOLTAYA)", "Serpuhovsko-Timiryazevskaya(SERAYA)", "Lyublinsko-Dmitrovskaya(SALATOVAYA)", "Kahovskaya(BIRYUZOVAYA)", "Butovskaya(SERO-GOLUBAYA)", "Moskovskoe central'noe kol'co(BELO-KRASNAYA)"}; // DOBAVKA ZVETOV

   int b=find_b(user_line, number_station);
  int c=generation(b);
   char right_name[100];
   i=recovery_station(number_station, user_line, c, right_name);
   if(i==-1) return -1;

   printf("%s \n", right_name);
   printf("%s\n", name_linies[i]);
 return 0;
}

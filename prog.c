#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generation( int b)  //a=0
{
    srand(time(NULL));
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

int main()
{
   int number_station[13]= {22, 23, 22, 13, 12, 24, 23, 16, 25, 23, 3, 7, 31};
   int user_line[13], user_question[4];
   int i,j; for(i=0; i<13; i++) user_line[i]=1; for(i=0; i<4; i++) user_question[i]=1;
   char *name_linies[13]={"Sokol'nicheskaya(KRASNAYA)", "Zamoskvoreckaya(ZELYONAYA)", "Arbatsko-Pokrovskaya(SINAYA)", "Filevskaya(GOLUBAYA)", "Kol'cevaya(KORICHNEVAYA)", "Kaluzhsko-Rizhskaya(ORANZHEVAYA)", "Tagansko-Krasnopresnenskaya(FIOLETOVAYA)", "Kalininskaya(ZHYOLTAYA)", "Serpuhovsko-Timiryazevskaya(SERAYA)", "Lyublinsko-Dmitrovskaya(SALATOVAYA)", "Kahovskaya(BIRYUZOVAYA)", "Butovskaya(SERO-GOLUBAYA)", "Moskovskoe central'noe kol'co(BELO-KRASNAYA)"}; // DOBAVKA ZVETOV

   int b=find_b(user_line, number_station);
   printf("\n  %d\n", b);
   int c=generation(b);
   printf("c=%d\n", c);
   return 0;
}
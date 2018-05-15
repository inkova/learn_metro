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

int generation_question_1(int i, char **name_linies, char * right_name, int *user_line, int *number_station, int b, int *mass_c)
{
    printf("What station is on the %s branch?\n", name_linies[i]);
    int j,k,siz, number=generation(3);
    int c;
    char wrong_name[100];
    user_line[i]=0;
    b-=number_station[i];
    for(j=0; j<4; j++)
        if(j==number) {
            if (j%2) printf("%d)  %s", (j+1), right_name);
            else {
                    printf("%d)  ", (j+1));
                    siz=strlen(right_name);
                    for(k=0; k< (siz-1); k++) printf("%c", right_name[k]);
                        printf("\t\t");
                 }
        }
        else {
           while(1){
              c=generation(b);
              siz=0;
              for(k=0;k<j; k++) if(c!=mass_c[k]) siz++;
              if(siz==j) break;
            }
            mass_c[j]=c;
            if((recovery_station(number_station, user_line, c, wrong_name))==-1) return -1;
            if (j%2) printf("%d)  %s", (j+1), wrong_name);
            else {
                    siz=strlen(wrong_name);
                    printf("%d)  ",(j+1));
                    for(k=0; k<(siz-1); k++) printf("%c", wrong_name[k]);
                        printf("\t\t");
                 }
     }
    user_line[i]=1;
    return number;
}

int check_answer_1(int answer, int number, char* right_name, int c, int *number_station, int *user_line)
{
      if( answer!=number ) {
                        char wrong_name[100];

                       if((recovery_station(number_station, user_line, c, wrong_name))==-1) return -1;
                        printf("right answer-%s\nyuor answer - %s", right_name, wrong_name);
                    }
      else printf("YOUR ANSWER IS RIGHT!!!");
}

int main()
{
   srand(time(NULL));
   int number_station[13]= {22, 23, 22, 13, 12, 24, 23, 16, 25, 23, 3, 7, 31};
   int user_line[13], user_question[4], mass_c[4];
   int i,j,k,c, answer; for(i=0; i<13; i++) user_line[i]=1; for(i=0; i<4; i++) user_question[i]=1;
   char right_name[100];
   char *name_linies[13]={"Sokol'nicheskaya(KRASNAYA)", "Zamoskvoreckaya(ZELYONAYA)", "Arbatsko-Pokrovskaya(SINAYA)", "Filevskaya(GOLUBAYA)", "Kol'cevaya(KORICHNEVAYA)", "Kaluzhsko-Rizhskaya(ORANZHEVAYA)", "Tagansko-Krasnopresnenskaya(FIOLETOVAYA)", "Kalininskaya(ZHYOLTAYA)", "Serpuhovsko-Timiryazevskaya(SERAYA)", "Lyublinsko-Dmitrovskaya(SALATOVAYA)", "Kahovskaya(BIRYUZOVAYA)", "Butovskaya(SERO-GOLUBAYA)", "Moskovskoe central'noe kol'co(BELO-KRASNAYA)"}; // DOBAVKA ZVETOV

   int b=find_b(user_line, number_station);
   int user_count=10;
   for(k=0; k < user_count; k++){
     c=generation(b);

     i=recovery_station(number_station, user_line, c, right_name);
     if(i==-1) return -1;

     printf("%s \n", right_name);

     for(j=0;j<4; j++) mass_c[j]=(-1);
     j=generation_question_1(i, name_linies, right_name, user_line,number_station, b, mass_c);
     if(j==-1) return -2;

     scanf("%d", &answer);
    answer--;
     user_line[i]=0;
     if((check_answer_1(answer, j, right_name, mass_c[answer], number_station, user_line))==-1) return -3;
     user_line[i]=1;
     printf("\n\n\n\n\n\n");
   }

 return 0;
}

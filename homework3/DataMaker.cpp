#include<iostream>
#include <fstream>
#include<random>
#define SEED 114514
#define N 100000
#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;
void RandName(FILE*fp) {
    int x = rand() % 26, y = rand() % 26, z = rand() % 26;
    fprintf(fp,"%c%c%c ", x + 'a', y + 'a', z + 'a');
    fprintf(fp, "U202%d%d%d%d%d%d\n",x%10,y % 10,z % 10,(x^y) % 10,(x^z) % 10,(y^z) % 10);
}
void RandScores(FILE*fp) {
    int t = 8;
    while (t--) {
        fprintf(fp,"%d ", rand() % 100);
    }
    fputc('\n',fp);
}
void MakeData(FILE*fp)
{
    srand(SEED);
    fprintf(fp, "%s","陈嘉 U202390060 \n" );
    RandScores(fp);
    for (int i = 1; i < N; i++) {
        RandName(fp);
        RandScores(fp);
    }
}
int main()
{
    FILE* fp = NULL;
    fp = fopen("homeworkdata.dat", "w");
    MakeData(fp);
    fclose(fp);
    printf("AC");
    return 0;
}
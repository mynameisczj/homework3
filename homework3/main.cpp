#include<iostream>
#include<Windows.h>
#include<random>
#define N 100000
#define TestNum 10
using namespace std;
struct student {
    char  name[8];
    char  sid[11];
    short  scores[8];
    short  average;
};
student s[N];
void LoadData()
{
    FILE *fp;
    fp = fopen("homeworkdata.dat","r");
    for (int i = 0; i < N; i++) {
        int tmp=fscanf(fp, "%s%s", s[i].name, s[i].sid);
        for (int j = 0; j < 8; j++) {
            tmp=fscanf(fp, "%hd", &s[i].scores[j]);
        }
    }
    fclose(fp);
}
void Print(int k) {
    for (int i = 0; i < k; i++) {
        printf("%s %s ", s[i].name, s[i].sid);
        for (int j = 0; j < 8; j++) {
            printf("%d ", s[i].scores[j]);
        }
        printf("Average: %d", s[i].average);
        putchar('\n');
    }
}
void CountAverage() {
    for (int i = 0; i < N; i++) {
        s[i].average = 0;
        for (int j = 0; j < 8; j++) {
            s[i].average += s[i].scores[j];
        }
        s[i].average >>=3;
    }
}

void  SortScores(student *s ,int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i].average < s[j].average) {
                student tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
}
extern "C" void AsmSortScores(student *s ,int n);
int main()
{
    unsigned long long  start, finish;
    LoadData();
    start = GetTickCount64();
    CountAverage();
    finish= GetTickCount64();
    printf("CountAverage: %lld\n", finish - start);
    start = GetTickCount64();
    SortScores(s, N);
    finish = GetTickCount64();
    printf("Sort: %lld\n", finish - start);
    Print(min(N,TestNum));
    printf("-----------------------------------------------\n");
    LoadData();
    start = GetTickCount64();
    CountAverage();
    finish = GetTickCount64();
    printf("CountAverage: %lld\n", finish - start);
    start = GetTickCount64();
    AsmSortScores(s, N);
    finish = GetTickCount64();
    printf("AsmSort: %lld\n", finish - start);
    Print(min(N, TestNum));
    return 0;
}
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<random>
#define N 100000
#define TestNum 10
bool Testbool[2] = {1,1};
using namespace std;
struct student {
    char  name[8];
    char  sid[11];
    short  scores[8];
    short  average;
};
student s[N];
static void LoadData()
{
    FILE *fp;
    if(Testbool[1])
    fp = fopen("homeworkdata.dat","r");
    else fp = fopen("homeworkdata0.dat", "r");
    for (int i = 0; i < N; i++) {
        int tmp=fscanf(fp, "%s%s", s[i].name, s[i].sid);
        for (int j = 0; j < 8; j++) {
            tmp=fscanf(fp, "%hd", &s[i].scores[j]);
        }
    }
    fclose(fp);
}
static void Print(int k) {
    for (int i = 0; i < k; i++) {
        printf("%s %s ", s[i].name, s[i].sid);
        for (int j = 0; j < 8; j++) {
            printf("%d ", s[i].scores[j]);
        }
        printf("Average: %d", s[i].average);
        putchar('\n');
    }
}
static void CountAverage(student* s, int n) {
    for (int i = 0; i < n; i++) {
        s[i].average = 0;
        for (int j = 0; j < 8; j++) {
            s[i].average += s[i].scores[j];
        }
        s[i].average >>=3;
    }
}
static void QuickCountAverage(student* s, int n) {
    for (int i = 0; i < n; i++) {
        s[i].average = s[i].scores[0];
        s[i].average += s[i].scores[1];
        s[i].average += s[i].scores[2];
        s[i].average += s[i].scores[3];
        s[i].average += s[i].scores[4];
        s[i].average += s[i].scores[5];
        s[i].average += s[i].scores[6];
        s[i].average += s[i].scores[7];
        s[i].average >>= 3;
    }
}
static void  SortScores(student *s ,int n) {
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
extern "C" void AsmCountAverage(student* s, int n);

pair<short, int> temp[N]; 
static void Print1(int k) {
    for (int i = 0; i < k; i++) {
        printf("%s %s ", s[temp[i].second].name, s[temp[i].second].sid);
        for (int j = 0; j < 8; j++) {
            printf("%d ", s[temp[i].second].scores[j]);
        }
        printf("Average: %d", s[temp[i].second].average);
        putchar('\n');
    }
}
int main()
{
    LARGE_INTEGER start, end, freq;
    double elapsedTime;
    LoadData();
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[0]) CountAverage(s,N);
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("CountAverage: %f\n", elapsedTime);
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[1]) SortScores(s, N);
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("Sort: %f\n", elapsedTime);
    Print(min(N, TestNum));
    printf("-----------------------------------------------\n");
    LoadData();
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[0]) AsmCountAverage(s,N);
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("AsmCountAverage: %f\n", elapsedTime);
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[1]) AsmSortScores(s, N);
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("AsmSort: %f\n", elapsedTime);
    Print(min(N, TestNum));
    printf("-----------------------------------------------\n");
    LoadData();
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[0]) QuickCountAverage(s,N);
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("CountAverage: %f\n", elapsedTime);
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[1]) sort(s, s + N, [](student& x, student& y) {return x.average > y.average; });
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("QuickSort: %f\n", elapsedTime);
    Print(min(N, TestNum));
    printf("-----------------------------------------------\n");
    LoadData();
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[0]) QuickCountAverage(s, N);
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("CountAverage: %f\n", elapsedTime);
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    if (Testbool[1]) {
        for (int i = 0; i < N; i++)temp[i].first = s[i].average, temp[i].second = i;
        sort(temp, temp + N, [](pair<short,int>& x, pair<short,int>& y) {return x.first > y.first; });
    }
    QueryPerformanceCounter(&end);
    elapsedTime = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000.0;
    printf("MyQuickSort: %f\n", elapsedTime);
    Print1(min(N, TestNum));
    return 0;
}
#include <stdio.h>

#include <stdlib.h>

#define NUMBER_OF_PROCESS 200

typedef struct P
{
    int id;
    int bt;
    int at;

    int flag;

    int ct;
    int tt;
    int wt;
} P;

void scan_from_file(FILE *in, P p[]);
void print_to_file(FILE *out, P p[]);
int isDone(P p[]);
int range(int cct, P p[]);

int main()
{
    P p[NUMBER_OF_PROCESS];

    // Open input - output file
    FILE *in;
    if ((in = fopen("processes", "r")) == NULL)
    {
        printf("Error - Opening p file.");
        exit(1);
    }
    FILE *out;
    if ((out = fopen("SJF.out", "w")) == NULL)
    {
        printf("Error - Opening out file.");
        exit(1);
    }
    scan_from_file(in, p);

    int cct = 0;
    int i = 0;
    int done = 0;
    while (!done)
    {
        cct += p[i].bt;
        p[i].ct += cct;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        p[i].flag = 1;

        done = isDone(p);
        if (done)
        {
            break;
        }

        int end = range(cct, p);
        int min = 9999;
        int j = 0;

        while (j < end)
        {
            if (p[j].bt < min && p[j].flag == 0)
            {
                min = p[j].bt;
                i = j;
            }
            j++;
        }
    }

    print_to_file(out, p);
    // Close input - output file
    fclose(in);
    fclose(out);
    return 0;
}

void scan_from_file(FILE *in, P p[])
{
    int a, b, c;

    int i = 0;
    while (fscanf(in, "%d %d %d", &a, &b, &c) != -1)
    {
        p[i].id = a;
        p[i].bt = b;
        p[i].at = c;

        p[i].flag = 0;

        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;

        i++;
    }
}

void print_to_file(FILE *out, P p[])
{
    fprintf(out, "%s %s %s %s %s %s %s\n", "I", "B", "A", "C", "T", "W", "D");

    int i;
    for (i = 0; i < NUMBER_OF_PROCESS; i++)
    {
        fprintf(out, "%d %d %d %d %d %d %d\n", p[i].id, p[i].bt, p[i].at, p[i].ct, p[i].tt, p[i].wt, p[i].flag);
    }
}

int isDone(P p[])
{
    int i = 0;
    while (i < NUMBER_OF_PROCESS)
    {
        if (p[i].flag == 0)
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int range(int cct, P p[])
{
    int j = 0;
    while (cct > p[j].at)
    {
        j++;
    }
    return j - 1;
}
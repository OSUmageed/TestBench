
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <ctime>
#include <omp.h>

using namespace std;

bitset<1028> bits;

double mult_act(double a, double b)
{
    return a*b;
}

void bitsetit(double *a, double *b, double *c, const int tpb)
{
    const int tpbp = tpb+1;
    
    // #pragma omp parallel for
    for (int k=1; k<(tpbp); k++) bits.flip(k);

    size_t y, z;
    for (int k=0; k<tpb; k++)
    {
        y = k;
        z = tpbp-k;
        bits.flip(y), bits.flip(z);
        if (bits.none()) continue;

        // #pragma omp parallel for
        for (int i=0; i<(tpbp+1); i++)
        {
            if (bits.test(i)) c[i] = mult_act(a[i], b[i]);
        }
    }
}

void traditional(double *a, double *b, double *c, const int tpb)
{
    int ht = tpb/2;
    int bs = tpb+2;
    for (int k=1; k<(ht+1); k++)
    {
        #pragma omp parallel for
        for (int i=k; i<(bs-k); i++)
        {
            c[i] = mult_act(a[i], b[i]);
        }
    }

    for (int k=ht; k>0; k--)
    {
        #pragma omp parallel for
        for (int i=k; i<(bs-k); i++)
        {
            c[i] = mult_act(a[i], b[i]);
        }
    }
}

void populate(time_t tnow, double *a, double *b, int tpb)
{
    srand(tnow);

    #pragma omp parallel for
    for (int k = 0; k<tpb+2;  k++)
    {
        a[k] = (double)rand() * .0001;
        b[k] = (double)rand() * .00052;
    }
}

int main(int argc, char *argv[])
{
    time_t now;
    double ti, tf, tBit, tTrad;
    double seconds;
    double *aa, *bb, *cc;
    int bs, tpbs = 32;
    int pows = 5;
    double bRatio, timS;

    cout << "Number -- 2^ -- tBitset -- tTrad -- tDiff ";
    cout << "-- timeDiff" << endl;
    int dbl = sizeof(double);

    for (int k = 0; k<6; k++)
    {
        time(&now);
        bs = tpbs+2;
        aa = (double* ) malloc(bs*dbl);
        bb = (double* ) malloc(bs*dbl);
        cc = (double* ) malloc(bs*dbl);

        ti = omp_get_wtime();
        bitsetit(aa, bb, cc, tpbs);
        tf = omp_get_wtime();
        tBit = tf - ti;

        time(&now);
        populate(now, aa, bb, tpbs);

        ti = omp_get_wtime();
        traditional(aa, bb, cc, tpbs);
        tf = omp_get_wtime();
        tTrad = tf - ti;

        bRatio =  (tTrad)/(tBit);

        cout << tpbs << " " << pows << " " << tBit << " " << tTrad << " ";
        cout << bRatio << " " << endl;
        tpbs *= 2;
        pows++;

        free(aa);
        free(bb);
        free(cc);
        
    }

    return 0;
}
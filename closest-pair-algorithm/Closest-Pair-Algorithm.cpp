#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <float.h>
using namespace std;

struct Points
{
    double x, y;
};
Points p1, p2;
int compareX(const void *a, const void *b)
{
    Points *p1 = (Points *)a, *p2 = (Points *)b;
    return (p1->x - p2->x);
}
int compareY(const void *a, const void *b)
{
    Points *p1 = (Points *)a, *p2 = (Points *)b;
    return (p1->y - p2->y);
}

float dist(Points p1, Points p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

float bruteForce(Points P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);

    return min;
}

float min(float x, float y)
{
    return (x < y) ? x : y;
}

float stripClosest(Points strip[], int size, float d)
{
    float min = d;

    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

float closestUtil(Points Px[], Points Py[], int n)
{
    if (n <= 3)
        return bruteForce(Px, n);

    int mid = n / 2;
    Points midPoint = Px[mid];

    Points Pyl[mid];
    Points Pyr[n - mid];
    int li = 0, ri = 0;
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x && li < mid)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }

    float dl = closestUtil(Px, Pyl, mid);
    float dr = closestUtil(Px + mid, Pyr, n - mid);

    float d = min(dl, dr);

    Points strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    return stripClosest(strip, j, d);
}

float closest(Points P[], int n)
{
    Points Px[n];
    Points Py[n];
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(Points), compareX);
    qsort(Py, n, sizeof(Points), compareY);

    return closestUtil(Px, Py, n);
}

main()
{
    Points P[100];
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        double randomx = ((double)rand() / (double(RAND_MAX)));
        double randomy = ((double)rand() / (double(RAND_MAX)));
        P[i].x = randomx;
        P[i].y = randomy;
    }
    int size = sizeof(P) / sizeof(P[0]);
    cout << "Closest Pair " << closest(P, size);
    // cout << p1.x << " " << p1.y << endl;
    // cout << p2.x << " " << p2.y;
}
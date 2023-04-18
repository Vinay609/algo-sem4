#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// to represent interval
class Interval
{
public:
    int start, end, weight;
};

// A utility function that is used for sorting events
// according to finish time
bool compare(Interval a, Interval b)
{
    return (a.end < b.end);
}

// Find the latest job (in sorted array) that doesn't
// conflict with the job[i]
int get_P(Interval arr[], int i)
{
    for (int j = i - 1; j >= 0; j--)
    {
        if (arr[j].end <= arr[i].start)
            return j;
    }
    return -1;
}

void findSolution(Interval arr[], int table[], int n, int i)
{
    if (i < 0)
        return;

    int taken = arr[i].weight;
    int Pi = get_P(arr, i);
    if (Pi != -1)
        taken += table[Pi];

    int not_taken = table[i - 1];
    if (taken >= not_taken)
    {
        cout << arr[i].start << ", " << arr[i].end << endl;
        return findSolution(arr, table, n, Pi);
    }
    return findSolution(arr, table, n, i - 1);
}

void solution(Interval arr[], int n)
{
    sort(arr, arr+n, compare);

    int table[n];

    for (int i = 0; i < n; i++)
    {
        int take = arr[i].weight; 
        int Pi = get_P(arr, i);
        if (Pi != -1)
            take += table[Pi];
        
        int not_take = table[i - 1];

        table[i] = max(take, not_take);
    }

    for (int i = 0; i < n; i++)
        cout << table[i] << " ";
    cout << endl;

    cout << "\nIntervals that should be taken: "<< endl;
    findSolution(arr, table, n, n);
}



int main()
{
    int n = 6;
    Interval arr[n] = {
        {1, 7, 2},
        {2, 13, 4},
        {8, 15, 4},
        {5, 17, 7},
        {16, 18, 2},
        {16, 20, 1},
    };
    
    solution(arr, n);
    
}

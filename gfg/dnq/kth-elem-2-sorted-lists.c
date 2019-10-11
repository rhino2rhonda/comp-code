#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_M 1000000

int solve_on(int A[], int B[], int n, int m, int k){
    int a=0, b=0;
    int curr = -1;
    while(a + b < k) {
        if (a < n && (b >= m || A[a] < B[b])) curr = A[a++];
        else curr = B[b++];
    }
    return curr;
}

int solve_ologn(int A[], int B[], int n, int m, int k){
    int as = 0, ae = n-1;
    int bs = 0, be = m-1;
    while(1) {
        // printf("dbg k:%d as:%d ae:%d bs:%d be:%d\n", k, as, ae, bs, be);
        if (as > ae) return B[bs + k - 1];
        if (bs > be) return A[as + k - 1];

        int a_mid = (as + ae) / 2;
        while(a_mid < ae && A[a_mid] == A[a_mid+1]) a_mid++;
        int b_mid = (bs + be) / 2;
        while(b_mid < be && B[b_mid] == B[b_mid+1]) b_mid++;

        int num_smaller = a_mid + b_mid + 1 - as -bs;
        if (A[a_mid] > B[b_mid]) {
            if (k <= num_smaller) {
                // printf("case 1\n");
                ae = a_mid-1;
                be = b_mid;
            } else {
                // printf("case 2\n");
                as = a_mid;
                bs = b_mid+1;
                k -= num_smaller;
            }
        } else {
            if (k <= num_smaller) {
                // printf("case 3\n");
                ae = a_mid;
                be = b_mid-1;
            } else {
                // printf("case 4\n");
                as = a_mid+1;
                bs = b_mid;
                k -= num_smaller;
            }
        }
    }
    
}

void run_tc() {
    //code
    int A[MAX_N];
    int B[MAX_M];
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        for(int i=0; i<n; i++) scanf("%d", &A[i]);
        for(int i=0; i<m; i++) scanf("%d", &B[i]);
       printf("%d\n", solve_ologn(A, B, n, m, k));
    }
}

void bubble_sort(int A[], int n) {
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if (A[j] <= A[j+1]) continue;
            int temp = A[j];
            A[j] = A[j+1];
            A[j+1] = temp;
        }
    }
}

void test() {
    int A[] = {0,0,0,1,3,3,4,4,5,5,6,6,8,10,10,11,12,12,13,14,14,15,15,17,17,17,18,19,19,19};
    int B[] = {1,1,1,1,2,2,3,4,5,8,14,14,15,15,16,17,18,18,19,19};
    int n=30, m=20, k = 10;
    printf("Solution(On): %d\n", solve_on(A, B, n, m, k));
    printf("Solution(Ologn): %d\n", solve_ologn(A, B, n, m, k));

    // Generated test case
    srand(time(NULL));
    n=30000, m=20000;
    k = 10000 + (((float)rand()) * 35000 / RAND_MAX);
    printf("%d %d %d\n", n, m, k);

    int C[100000];
    for (int i=0; i<n; i++) C[i] = (((float)rand()) * 100000 / RAND_MAX);
    bubble_sort(C, n);
    int D[100000];
    for (int i=0; i<m; i++) D[i] = (((float)rand()) * 100000 / RAND_MAX);
    bubble_sort(D, m);

    // for (int i=0; i<n; i++) printf("%d ", C[i]);
    // printf("\n");
    // for (int i=0; i<m; i++) printf("%d ", D[i]);
    // printf("\n");
    int reps = 100000;

    int time_a = time(NULL);
    int sol;
    for (int i=0; i<reps; i++) sol = solve_on(C, D, n, m, k);
    int time_b = time(NULL);
    printf("Solution(On): %d\n", sol);
    printf("time(On): %d\n", time_b - time_a);

    for (int i=0; i<reps; i++) sol = solve_ologn(C, D, n, m, k);
    printf("Solution(Ologn): %d\n",sol);
    int time_c = time(NULL);
    printf("time(Ologn): %d\n", time_c - time_b);
}

int main() {
	// run_tc();
    test();
    return 0;
}

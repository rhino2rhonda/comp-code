#include <stdio.h>
#include <math.h>

#define MAX_STRLEN 100
#define MAX_GROUPS 100
#define MAX_HT 10000

void getPrimes(int primes[], int n){
	int count=0, p=2;
	while(count < n){
		int prime = 1;
		for(int i=2; i<=sqrt(n); i++){
			if (p%i == 0) {
				prime = 0;
				break;
			}
		}
		if (prime) {
			primes[count++] = p;
		}
		p++;
	}
}

void printArray(int arr[], int n){
	printf("Array: ");
	for(int i=0; i<n; i++) printf("%d ", arr[i]);
	printf("\n");
}

void testGetPrimes(){
	int primes[MAX_STRLEN];
	int n = 75;
	getPrimes(primes, n);
	printArray(primes, n);
}

int hashString(char str[]){
	int primes[MAX_STRLEN];
	int len=0;
	for(int i=0; str[i]!='\0'; i++) len++;
	getPrimes(primes, len);
	int hash = (len>0) ? len*primes[0] : 0;
	for(int i=1; i<len; i++) hash += (str[i]-str[0]) * primes[i];
	return hash;
}

void testHashString(){
	char str1[] = "acknowledgmentacknowledgmentacknowledgmentacknowledgmentacknowledgment";
	printf("hash for %s is %d\n", str1, hashString(str1));
}

void printGroups(char* groups[], int n){
	int HT[MAX_HT][MAX_GROUPS];
	int HT_counts[MAX_HT];
	for (int i=0; i<MAX_HT; i++) HT_counts[i] = 0;
	for (int i=0; i<n; i++){
		int hash = hashString(groups[i]);
		HT[hash][HT_counts[hash]++] = i;
	}
	for (int i=0; i<MAX_HT; i++) {
		if(HT_counts[i] == 0) continue;
		for(int j=0; j<HT_counts[i]; j++){
			printf("%s ", groups[HT[i][j]]);
		}
		printf("\n");
	}
}

void testGrouping(){
	char *groups[] = {
		"acd", "dfg", "wyz", "yab", "mop",
        "bdfh", "a", "x", "moqs"
	};
	printGroups(groups, 9);
}

int main(){
	testGrouping();
	return 1;
}
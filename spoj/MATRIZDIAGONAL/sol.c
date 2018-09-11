// AC solution in C

#include <stdio.h>

int inp() {
	int ch;
	do {
		ch = getchar_unlocked();
	}
	while(ch < '0' || ch > '9');

	int n=0;
	do{
		n *= 10;
		n += ch - '0';
		ch = getchar_unlocked();
	} while(ch >= '0' && ch <= '9');
	return n;
}

int main(){
  int m = inp();
  int falso = 0;
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      int n = inp();
      if(i != j && n != 0){
		falso = 1;
        printf("Falso\n");
        break;
      }
    }
    if (falso) break;
  }
  if (!falso) printf("Verdadero\n");
  return 0;
}

// 21500344 서찬솔

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _City{
  int num;
  int neighbor;
  int *listN;
}City;

int myDP(City *c, int num, int i);

int main(){

  City *c;
  FILE *fp = fopen("2.in", "r");
  int num, link, buf = 0, first, second, max = 0;

  fscanf(fp, "%d %d", &num, &link);

  c = (City*)malloc(sizeof(City)*num);

  for(int i=0; i < num; i++){
    c[i].num = i;
    c[i].neighbor = 0;
    c[i].listN = (int*)malloc(sizeof(int)*(c[i].neighbor));
  }
  for(int i=0; i <= link; i++){
    fscanf(fp, "%d %d", &first, &second);
    c[first].neighbor++;
    c[first].listN = (int*)realloc(c[first].listN, sizeof(int)*c[first].neighbor);
    c[first].listN[ (c[first].neighbor) - 1 ] = second;
    c[second].neighbor++;
    c[second].listN = (int*)realloc(c[second].listN, sizeof(int)*c[second].neighbor);
    c[second].listN[ (c[second].neighbor) - 1 ] = first;
  }

  for(int i=0; i < num; i++){
    buf = myDP(c, num, i);
    if(buf>max) max = buf;
  }

  printf("%d", max);

  free(c);
  fclose(fp);
  return 0;
}

int myDP(City *c, int num, int i){

  int tmp = 0, min = i, cnt = 1, miso = i;

  while(1){
    for(int j = 0; j < c[miso].neighbor; j++){
      if(c[miso].neighbor < c[ c[miso].listN[j] ].neighbor){
        tmp = c[miso].listN[j];
        if(min == miso) min = tmp;
        else if(c[tmp].neighbor < c[min].neighbor) min = tmp;
      }
    }

    if(min == miso){
      return cnt;
    } else{
      cnt++;
      miso = min;
    }
  }
}

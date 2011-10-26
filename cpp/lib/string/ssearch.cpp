#include<cstring>

/* aの中の部分文字列pを探す */
int kmpsearch(const char *p, const char *a){
  int M = strlen(p);
  int N = strlen(a);
  int i,j;
  /* nextを初期化 */
  int next[M];
  next[0] = -1;
  for(i=0, j=-1; i<M; i++, j++, next[i]=j)
    while((j>=0) && (p[i]!=p[j])) j=next[j];
  
  /* 検索 */
  for(i=j=0; j<M && i<N; i++, j++)
    while((j>=0) && (a[i]!=p[j])) j = next[j];
  if(j==M) return i-M;//発見
  else return -1;     //なかった
}

int rksearch(const char *p, const char *a){
  const int q = 33554393;
  const int d = 128;
  unsigned int M = strlen(p), N = strlen(a);
  unsigned int i, dM=1, h1=0, h2=0;
  for(i=1; i<M; i++) dM = (d*dM)%q;
  for(i=0; i<M; i++){
    h1 = (h1*d+p[i]) % q;
    h2 = (h2*d+a[i]) % q;
  }
  /* hashなので確認が必要では？ */
  for(i=0; h1!=h2 || strncmp(p, &a[i], M)!=0; i++){
    h2 = (h2+d*q-a[i]*dM) %q;
    h2 = (h2*d+a[i+M])    %q;
    if(i>N-M) return -1;
  }
  return i;
}

/*
 * 幅w，高さhの格子点上に正方形が何個あるか計算
 * 斜めの正方形は，軸に平行な(面積4以上の)正方形と，その辺上の1点を決めると決定できる
 */
long long howMany(int width, int height){
  int m = min(width,height);
  long long ret = 0ll;
  long long w = width, h = height;
  
  for(int s = 0; s<m; s++){
    ret += (w-s)*(h-s);
    if(s!=0){
      ret += (w-s)*(h-s)*s;
    }
  }
  return ret;
}

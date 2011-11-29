//
// if (y1 <= y2) and (x1 <= x2)
//   ret[y1][x1][y2][x2] = sigma(g[i][j])
//   (y1 <= i <= y2, x1 <= j <= x2)
// otherwise
//   ret[y1][x1][y2][x2] = 0
//
// O(h^2 * w^2)
template<class T1, class T2, int H, int W>
void sum(const T1 (&g)[H][W], T2 (&ret)[H][W][H][W], int h = H, int w = W){
  // initialize
  for(int i = 0; i < h; i++)
    for(int j = 0; j < w; j++)
      for(int k = 0; k < h; k++)
	for(int l = 0; l < w; l++)
	  ret[i][j][k][l] = 0;

  // DP
  for(int sy = 0; sy < h; sy++)
    for(int sx = 0; sx < w; sx++)
      for(int y = 0; y + sy < h; y++)
	for(int x = 0; x + sx < w; x++){
	  ret[y][x][y + sy][x + sx] =
	    (sy == 0 ? 0 : ret[y][x][y + sy - 1][x + sx]) +
	    (sx == 0 ? 0 : ret[y + sy][x][y + sy][x + sx - 1]) +
	    g[y + sy][x + sx];
	}
}

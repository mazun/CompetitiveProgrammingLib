class Dice{
public:
  enum direction{
    UP    = 0, // 上に90度転がす
    RIGHT = 1, // 右
    DOWN  = 2, // 下
    LEFT  = 3, // 左
    RRIGHT= 4, // 右に90度回転(上面は変わらない)
    RLEFT = 5  // 左
  };
  
  /*
   *   6
   *   2
   * 3 1 4
   *   5
   */
  
private:
  static int next_top[7][7][6];
  static int next_right[7][7][6];
  static int front[7][7];
  
  int _top;
  int _right;

  static void initDie(){
    front[1][3] = 2; front[1][2] = 4; front[1][4] = 5; front[1][5] = 3;
    front[2][1] = 3; front[2][3] = 6; front[2][4] = 1; front[2][6] = 4;
    front[3][1] = 5; front[3][2] = 1; front[3][5] = 6; front[3][6] = 2;
    for(int i = 4; i < 7; i++){
      for(int j = 1; j < 7; j++){
        if(i == j || i + j == 7) continue;
        int t = 7 - i;
        int l = 7 - j;
        front[i][j] = front[t][l];
      }
    }
    
    for(int t = 1; t < 7; t++){
      for(int r = 1; r < 7; r++){
        if(t == r || t + r == 7) continue;
        
        next_top[t][r][UP]     = front[t][r];
        next_top[t][r][LEFT]   = r;
        next_top[t][r][RIGHT]  = 7 - r;
        next_top[t][r][DOWN]   = 7 - front[t][r];
        next_top[t][r][RRIGHT] = t;
        next_top[t][r][RLEFT]  = t;
        
        next_right[t][r][UP]     = r;
        next_right[t][r][LEFT]   = 7 - t;
        next_right[t][r][RIGHT]  = t;
        next_right[t][r][DOWN]   = r;
        next_right[t][r][RRIGHT] = 7 - front[t][r];
        next_right[t][r][RLEFT]  = front[t][r];
      }
    }
  }

  static void init(){ 
    static bool _init = false;

    if(!_init){
      initDie();
      _init = true;
    }
  }

public:
  /*
   * インスタンスを通して使うインターフェース*
   */
  Dice(int t = 1, int r = 3) : _top(t), _right(r) {
    init();
  }

  int getTop() const{ return _top; }
  int getRight() const{ return _right; }
  int getButtom() const{ return 7 - _top; }
  int getLeft() const{ return 7 - _right; }
  int getFront() const{ return front[_top][_right]; }
  int getBack() const{ return 7 - front[_top][_right]; }

  void next(int dir){
    int tmp = _top;
    _top     = next_top[_top][_right][dir];
    _right   = next_right[tmp][_right][dir];
  }

  void right() { next(RIGHT);  }
  void left()  { next(LEFT);   }
  void up()    { next(UP);     }
  void down()  { next(DOWN);   }
  void rright(){ next(RRIGHT); }
  void rleft() { next(RLEFT);  }

  /*
   * 直接使うインターフェース
   */
  static int forceInit(){ init(); }

  static int nextTop(int t, int r, int d){
    return next_top[t][r][d];
  }

  static int nextRight(int t, int r, int d){
    return next_right[t][r][d];
  }

};

int Dice::next_right[7][7][6] = {0};
int Dice::next_top[7][7][6]   = {0};
int Dice::front[7][7]         = {0};

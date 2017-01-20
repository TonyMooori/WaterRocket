#ifndef TOP_DETECTOR_HEADER_FILE
#define TOP_DETECTOR_HEADER_FILE

#define GRAVITY_ACCEL (9.8)

class TopDetector {
  public:
    // コンストラクタ
    TopDetector() {
      reset();
    }

    // 変数の初期化を行うメソッド
    void reset() {
      for (int i = 0 ; i < 3 ; i++ ) {
        _x[i] = 0.0;
        _b[i] = 0.0;
        for (int j = 0 ; j < 3 ; j++ ) {
          _A[i][j] = 0.0;
        }
      }
      _n_data = 0;
    }

    // データを追加するメソッド
    void push(float t, float y) {
      const float t0 = 1;
      const float t1 = t0 * t;
      const float t2 = t1 * t;
      const float t3 = t2 * t;

      _A[0][0] += t2;
      _A[0][1] += t1;

      _A[1][0] += t1;
      _A[1][1] += t0;

      _b[0] += t1 * y + 0.5 * GRAVITY_ACCEL * t3;
      _b[1] += t0 * y + 0.5 * GRAVITY_ACCEL * t2;

      _n_data++;
    }

    // データが有れば放物線の係数を計算するメソッド
    void calc() {
      if ( _n_data == 0 )
        return;
      solve<2>(_A, _x, _b);

    }

    // 追加されたデータ数を返すメソッド
    int get_n_data() {
      return _n_data;
    }

    // 計算済みならばt^2のパラメータを返すメソッド
    float get_a() {
      return -GRAVITY_ACCEL*0.5;
    }

    // 計算済みならばt^1のパラメータを返すメソッド
    float get_b() {
      return _x[0];
    }

    // 計算済みならばt^0のパラメータを返すメソッド
    float get_c() {
      return _x[1];
    }

    // 頂点時間
    float get_top_time() {
      if ( _x[1] == 0.0 )
        return 1e+10;
      else
        return _x[0]/GRAVITY_ACCEL;
    }

  private:

    template<int N>
    void solve(const float M[N][N], float x[N], const float b[N]) {
        float A[N][N];
        float B[N];
        float temp;
        
        // コピー
        for(int i = 0 ; i < N ; i++ ){
            B[i] = b[i];
            for(int j = 0 ; j < N ; j++ ){
                A[i][j] = M[i][j];
            }
        }
        
        for (int i = 0 ; i < N ; i++ ) {
            // ピボット選択
            for (int j = i + 1 ; j < N ; j++ ) {
                if ( abs(A[i][j]) >= 1e-8 )
                    break;

                for (int k = 0 ; k < N ; k++ )
                    A[i][k] += A[j][k];
                B[i] += B[j];
            }

            // 対角成分を1に
            temp = A[i][i];
            for (int j = i ; j < N ; j++ )
                A[i][j] /= temp;
            B[i] /= temp;

            // 前進消去
            for (int j = i + 1 ; j < N ; j++ ) {
                temp = A[j][i];

                for (int k = i ; k < N ; k++ )
                    A[j][k] -= temp * A[i][k];
                B[j] -= temp * B[i];
            }
        }
        
        // 後進消去
        for (int i = N - 1 ; i >= 0 ; i-- ){
            for (int j = i - 1 ; j >= 0 ; j-- ){
                B[j] -= A[j][i] * B[i];
            }
        }
        
        for(int i = 0 ; i < N ; i++ )
            x[i] = B[i];
    }

    float _A[2][2];     // 係数行列
    float _b[2];        // 出力ベクトル
    float _x[2];        // 解ベクトル

    int _n_data;
};

#endif
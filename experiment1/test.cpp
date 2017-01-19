#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "TopDetector.h"

#define INF 99999999
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)


#define MAX_ERROR 0.5   // 誤差の最大値[m]

using namespace std;

// [min_x,max_x)の一様乱数を返す
float random(float min_x,float max_x);
// f(x) = a ( t - top_time ) ^ 2 + max_height
float parabola(float t,float a,float top_time,float max_height);
// シミュレーションを行う
void test(float a,float top_time,float max_height,float from_time,float wait_time,int N);

int main(void){
    float a = -4.9;
    int n_datas[5] = {10,30,50,100,500};
    
    srand(1);
    
    printf("%8s","a");
    printf("%8s","top_t");
    printf("%8s","from_t");
    printf("%8s","wait_t");
    printf("%8s","N");
    printf("%8s","a ans");
    printf("%10s\n","top_t ans");
    
    REP(i,60)
        cout << "-";
    cout << endl;
    
    // t^2の係数, 最高到達時間，最高高度，開始時間，サンプリング周波数，サンプリング数
    REP(i,5)
        test(a, 25.0,  30,  20.0,  0.03, n_datas[i]);
    
    REP(i,5)
        test(a, 25.0,  30,  15.0,  0.03, n_datas[i]);
    
    REP(i,5)
        test(a, 55.0,  100,  40.0,  0.03, n_datas[i]);
    
    return 0;
}


// [min_x,max_x)の一様乱数を返す
float random(float min_x,float max_x){
    return (max_x-min_x)*float(rand())/(RAND_MAX + 1)+min_x;
}

// f(x) = a ( t - top_time ) ^ 2 + max_height
float parabola(float t,float a,float top_time,float max_height){
    float delta_t = t - top_time;
    
    return a * (delta_t * delta_t) + max_height;
}

// シミュレーションを行う
void test(float a,float top_time,float max_height,float from_time,float wait_time,int N){
    TopDetector td;
    
    float t,y;
    
    REP(i,N){
        t = from_time + wait_time * i;
        y = parabola(t,a,top_time,max_height) + random(-MAX_ERROR,MAX_ERROR);
        
        td.push( t , y );
    }
    
    td.calc();
    
    printf("%8.2lf",a);
    printf("%8.2lf",top_time);
    printf("%8.2lf",from_time);
    printf("%8.2lf",wait_time);
    printf("%8d",N);
    printf("%8.2lf",td.get_a());
    printf("%8.2lf\n",td.get_top_time());
}

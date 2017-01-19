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


#define N 30
#define T_FROM      48.0
#define WAIT_TIME   (0.03f)

#define MAX_ERROR 2.0   // 誤差の最大値[m]

using namespace std;


// [min_x,max_x)の一様乱数を返す
float random(float min_x,float max_x);
// f(x) = a ( t - top_time ) ^ 2 + max_height
float parabola(float t,float a,float top_time,float max_height);
// ログデータから動作をテスト
void test();

int main(void){
    srand(1);
    
    test();
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

// ログデータから動作をテスト
void test(){
    TopDetector td;
    float t,y;
    FILE *fp;
    char buff[256];
    
    //ファイルの読み込み
    fp = fopen("data.csv","r");
    if( fp == NULL ){
        cout << "File not found." << endl;
        return;
    }
    
    // ヘッダー読み取り
    if( fgets(buff,256,fp) == NULL ){
        cout << "Header not found." << endl;
        return;
    }
    
    cout << "---------------------------------------" << endl;
    cout << "t\ty"<< endl;
    
    // ログデータ読み取り
    while (fscanf(fp,"%f,%f",&t,&y) != EOF) {
        cout << t << "\t" << y << endl;
        td.push(t,y);
    }
    // ファイルクローズ
    fclose(fp);
    
    td.calc();
    
    cout << "---------------------------------------" << endl;
    
    cout <<  "a\t" << td.get_a() << endl;
    cout <<  "b\t" << td.get_b() << endl;
    cout <<  "c\t" << td.get_c() << endl;
    cout <<  "top\t" << td.get_top_time() << endl;
}
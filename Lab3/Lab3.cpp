// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <locale.h>
#include "LongDouble.h"
#include <string>
#include <vector>
#include <ctime>
#include "ConsoleFrontEnd.h"
using namespace std;

// ---- 1 ----
double Get_R(double R1_, double R2_, string dt_) {
    return ((dt_ == "double") ? (double)((double)1 / (((double)1 / R1_) + ((double)1 / R2_)))
                              : (float)((float)1 / ((float)((float)1 / (float)R1_) + (float)((float)1 / (float)R2_))));
}

double Get_R_eq(double R1_, double R2_, string dt_) {
    return ((dt_ == "double") ? (double)((R1_ * R2_) / (R1_ + R2_)) 
                              : (float)((float)((float)R1_ * (float)R2_) / (float)((float)R1_ + (float)R2_)));
}
// -----------

int main() {
    setlocale(LC_ALL, "Russian");
    // ---- 1 ----
    StartBlock('*', "1, вар. 1");
    double R1_d, R2_d, R_d, R_eq_d, R_R_eq_d;
    float R1_f, R2_f, R_f, R_eq_f, R_R_eq_f;
    int w1, w2, w3, prec;
    cout << "R1 = ";
    cin >> R1_d;
    R1_f = (float)R1_d;
    cout << "R2 = ";
    cin >> R2_d;
    R2_f = (float)R2_d;

    // вычисление R по формуле (1) для float и double
    R_d = Get_R(R1_d, R2_d, "double");
    R_f = (float)Get_R(R1_f, R2_f, "float");

    // вычисление R экв по формуле (2) для float и double
    R_eq_d = Get_R_eq(R1_d, R2_d, "double");
    R_eq_f = (float)Get_R_eq(R1_f, R2_f, "float");

    // вычисление разности между R и R экв
    R_R_eq_d = (double)abs((double)(R_d - R_eq_d));
    R_R_eq_f = (float)abs((float)(R_f - R_eq_f));

    // количество знаков после запятой
    prec = 20;

    // отображение чисел в привычном формате (фиксированной форме)
    cout.setf(ios::fixed);
    cout << setprecision(prec);

    // установка длины отступов между числами на экране в зависимости от количества разрядов в них
    w1 = max(to_string(R_d).length(), to_string(R_f).length()) + prec;
    w2 = max(to_string(R_eq_d).length(), to_string(R_eq_f).length()) + prec;
    w3 = max(to_string(R_R_eq_d).length(), to_string(R_R_eq_f).length()) + prec;

    // вывод результатов на экран
    cout << setw(w1 + 19) << "R" << setw(w2) << "R экв" << setw(w3) << "Разность R и R экв" << endl;
    cout << "Одинарная точность:" << setw(w1) << R_f << setw(w2) << R_eq_f << setw(w3) << R_R_eq_f << endl;
    cout << "Двойная точность:" << setw(w1 + 2) << R_d << setw(w2) << R_eq_d << setw(w3) << R_R_eq_d << endl;

    EndBlock('*');
    // -----------

    // ---- 1 ----
    StartBlock('*', "1, вар. 2");
    StartBlock('*', "a");
    double d_inf = numeric_limits<double>::infinity();
    double div_inf_0 = d_inf / 0, div_0_inf = 0 / d_inf, div_inf_inf = d_inf / d_inf;
    cout << setprecision(0) << "inf / 0 = " << div_inf_0 << "\n0 / inf = " << div_0_inf << "\ninf / inf = " << div_inf_inf << endl;
    StartBlock('*', "б");
    cout << "0 = -0: " << ((0 == -0) ? "верно" : "ложно") << "\ninf = -inf: " << ((d_inf == -d_inf) ? "верно" : "ложно") << endl;
    EndBlock('*');
    // -----------

    // ---- 2 ----
    StartBlock('*', "2");
    LongDouble add1 = LongDouble("8309485856059584393958546960484720297837") + LongDouble("1937465869473945906747398506847496902943759");
    LongDouble sub1 = LongDouble("6384958736495606843659604736495698374395") - LongDouble("126459057498607373595067365097873599483");
    LongDouble mul1 = LongDouble("9367519472402846495694375470482729402386") * LongDouble("274595781467495956473834905385493755954");
    LongDouble div1 = LongDouble("5892749589362960729275294746295057265950") / LongDouble("9564638272658267294806435829538574");
    LongDouble var1 = LongDouble("37894627638472");
    float f1 = 22.4;
    float f2 = 22.5;
    float f3 = 22.6;
    LongDouble n1 = (LongDouble)f1;
    LongDouble n2 = (LongDouble)f2;
    LongDouble n3 = (LongDouble)f3;
    LongDouble n4 = (LongDouble)-f1;
    LongDouble n5 = (LongDouble)-f2;
    LongDouble n6 = (LongDouble)-f3;
    cout << setprecision(1) << setw(5) << "n" << setw(14) << "n.round(2)" << setw(14) << "n.floor(2)" << setw(14) << "n.ceil(2)" << setw(14) << "n.trunc(2)" << setw(19) << "n.bank_round(2)" << endl;
    cout << setw(5) << f1 << setw(13) << n1.round(2) << setw(13) << n1.floor(2) << setw(13) << n1.ceil(2) << setw(13) << n1.trunc(2) << setw(18) << n1.bank_round(2) << endl;
    cout << setw(5) << f2 << setw(13) << n2.round(2) << setw(13) << n2.floor(2) << setw(13) << n2.ceil(2) << setw(13) << n2.trunc(2) << setw(18) << n2.bank_round(2) << endl;
    cout << setw(5) << f3 << setw(13) << n3.round(2) << setw(13) << n3.floor(2) << setw(13) << n3.ceil(2) << setw(13) << n3.trunc(2) << setw(18) << n3.bank_round(2) << endl;
    cout << setw(5) << -f1 << setw(12) << n4.round(2) << setw(12) << n4.floor(2) << setw(12) << n4.ceil(2) << setw(12) << n4.trunc(2) << setw(17) << n4.bank_round(2) << endl;
    cout << setw(5) << -f2 << setw(12) << n5.round(2) << setw(12) << n5.floor(2) << setw(12) << n5.ceil(2) << setw(12) << n5.trunc(2) << setw(17) << n5.bank_round(2) << endl;
    cout << setw(5) << -f3 << setw(12) << n6.round(2) << setw(12) << n6.floor(2) << setw(12) << n6.ceil(2) << setw(12) << n6.trunc(2) << setw(17) << n6.bank_round(2) << endl;
    cout << setprecision(0);
    //cout << var1.round(6) << endl;
    //cout << var1.floor(6) << endl;
    //cout << var1.ceil(6) << endl;
    EndBlock('*');
    // -----------

    // ---- 3 ----
    StartBlock('*', "3");
    double alpha = 1, 
           beta = 1;
    LongDouble x[6] = { ((LongDouble)10).pow((LongDouble)alpha), 
                        (LongDouble)1223, 
                        ((LongDouble)10).pow((LongDouble)(alpha - 1)), 
                        ((LongDouble)10).pow((LongDouble)(alpha - 2)), 
                        (LongDouble)3, 
                        ((LongDouble)-10).pow((LongDouble)(alpha - 5)) },
               y[6] = { ((LongDouble)10).pow((LongDouble)beta), 
                        (LongDouble)2, 
                        ((LongDouble)-10).pow((LongDouble)(beta + 1)), 
                        ((LongDouble)10).pow((LongDouble)beta), 
                        (LongDouble)2111, 
                        ((LongDouble)10).pow((LongDouble)(beta + 3)) },
               xy = (LongDouble)0;
    for (int i = 0; i < 6; i++) xy += x[i] * y[i];
    cout << "x * y = " << xy << endl;
    EndBlock('*');
    // -----------
}
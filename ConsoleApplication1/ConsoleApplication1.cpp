#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <clocale>
#include "LongDouble.h"
using namespace std;

int main() {
	LongDouble tdt1 = LongDouble("-27588738432934287328743487387423287187132") + LongDouble("274454373474321283944289918819898423");
	LongDouble tdt2 = LongDouble("2723287187132") - LongDouble("274454373474321283944289918819898423");
	LongDouble tdt3 = LongDouble("232") * LongDouble("54373474321283944289918819898423");
	LongDouble tdt4 = LongDouble("27588738432934287328743487387423287187132") / LongDouble("54373474321283944289918819898423");
	setlocale(LC_ALL, "Russian");
	cout << "результат сложения: " << tdt1 << endl;
	cout << endl;
	cout << "результат вычитания: " << tdt2 << endl;
	cout << endl;
	cout << "результат умножения: " << tdt3 << endl;
	cout << endl;
	cout << "результат деления: " << tdt4 << endl;
	cout << endl;
	system("pause");
}
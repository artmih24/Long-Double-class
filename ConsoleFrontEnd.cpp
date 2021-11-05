#include <iostream>
#include "ConsoleFrontEnd.h"
using namespace std;

void StartBlock(char st_, string str_, int ww_) {
	int str_len_ = str_.length();
	int line_len_ = (ww_ - str_len_ - 2) / 2;
	for (int i = 0; i < line_len_; i++) cout << st_;
	cout << " " << str_ << " ";
	for (int i = 0; i < line_len_; i++) cout << st_;
	cout << endl;
}


void EndBlock(char st_, int ww_) {
	for (int i = 0; i < ww_; i++) cout << st_;
	cout << endl << endl << endl;
}
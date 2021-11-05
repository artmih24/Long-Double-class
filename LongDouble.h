#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

class LongDouble {
	const size_t divDigits = 1000;
	const size_t sqrtDigits = 100;
	const size_t Preciss = 128; // длина разрядной сетки

	//int sign;
	//std::vector<int> digits;
	//long exponent;

	void initFromString(const std::string& s);
	void removeZeroes();
	//void normalize();

public:
	int sign;
	std::vector<int> digits;
	long exponent;

	LongDouble();
	LongDouble(const LongDouble& x);
	LongDouble(long double value);
	LongDouble(const std::string& s);
	void normalize();

	LongDouble& operator=(const LongDouble& x);

	bool operator>(const LongDouble& x) const;
	bool operator<(const LongDouble& x) const;
	bool operator>=(const LongDouble& x) const;
	bool operator<=(const LongDouble& x) const;
	bool operator==(const LongDouble& x) const;
	bool operator!=(const LongDouble& x) const;

	LongDouble operator-() const;

	LongDouble operator+(const LongDouble& x) const;
	LongDouble operator-(const LongDouble& x) const;
	LongDouble operator*(const LongDouble& x) const;
	LongDouble operator/(const LongDouble& x) const;

	LongDouble& operator+=(const LongDouble& x);
	LongDouble& operator-=(const LongDouble& x);
	LongDouble& operator*=(const LongDouble& x);
	LongDouble& operator/=(const LongDouble& x);

	LongDouble operator++(int);
	LongDouble operator--(int);

	LongDouble& operator++();
	LongDouble& operator--();

	LongDouble inverse() const;
	LongDouble sqrt() const;
	LongDouble pow(const LongDouble& n) const;
	LongDouble abs() const;

	LongDouble floor(int n_);
	LongDouble round(int n_);
	LongDouble ceil(int n_);
	LongDouble trunc(int n_);
	LongDouble bank_round(int n_);

	bool isInteger() const;
	bool isEven() const;
	bool isOdd() const;
	bool isZero() const;

	friend std::ostream& operator<<(std::ostream& os, const LongDouble& value);
};
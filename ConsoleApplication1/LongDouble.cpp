#include "LongDouble.h"
#include <algorithm>


using namespace std;

void LongDouble::initFromString(const string& s) {
	size_t index;

	if (s[0] == '-') {
		sign = -1;
		index = 1;
	} else {
		sign = 1;
		index = 0;
	}

	exponent = s.length() - index;

	while (index < s.length()) {
		if (s[index] == '.')
			exponent = sign == 1 ? index : index - 1;
		else
			digits.push_back(s[index] - '0');

		index++;
	}
}

void LongDouble::removeZeroes() {
	size_t n = max((long) 1, exponent);

	while (digits.size() > n && digits[digits.size() - 1] == 0)
		digits.erase(digits.end() - 1);

	while (digits.size() > 1 && digits[0] == 0) {
		digits.erase(digits.begin());
		exponent--;
	}

	while (digits.size() > 1 && digits[digits.size() - 1] == 0)
		digits.erase(digits.end() - 1);

	if (isZero()) {
		exponent = 1;
		sign = 1;
	}

	normalize();
}

void LongDouble::normalize() {
	size_t start = max(exponent, (long) 0);
	size_t realDigits = digits.size() - start;

	if (realDigits >= divDigits) {
		size_t count = 0;
		size_t maxCount = 0;

		size_t i = start;

		while(i < digits.size()) {
			count = 0;

			while (i < digits.size() && digits[i] == 9) {
				count++;
				i++;
			}
			
			if (count > maxCount)
				maxCount = count;

			i++;
		}
		
		if (maxCount > divDigits * 4 / 5) {
			i = digits.size() - 1;

			do {
				count = 0;

				while (i > 0 && digits[i] != 9)
					i--;

				while (i > 0 && digits[i] == 9) {
					count++;
					i--;
				}
			} while (count != maxCount);

			digits.erase(digits.begin() + i + 1, digits.end());
			digits[i]++;
		}
	}
}

LongDouble::LongDouble() {
	sign = 1;
	digits = vector<int>(1, 0);
	exponent = 1;
}

LongDouble::LongDouble(const LongDouble& x) {
	sign = x.sign;
	exponent = x.exponent;
	digits = vector<int>(x.digits.size());

	for (size_t i = 0; i < x.digits.size(); i++)
		digits[i] = x.digits[i];
}

LongDouble::LongDouble(long double value) {
	stringstream ss;
	ss << setprecision(15) << value;

	initFromString(ss.str());
	removeZeroes();
}

LongDouble::LongDouble(const string& s) {
	initFromString(s);
	removeZeroes();
}

LongDouble& LongDouble::operator=(const LongDouble& x) {
	if (this == &x)
		return *this;

	sign = x.sign;
	exponent = x.exponent;
	digits = vector<int>(x.digits.size());

	for (size_t i = 0; i < x.digits.size(); i++)
		digits[i] = x.digits[i];

	return *this;
}

// проверка, что число больше другого
bool LongDouble::operator>(const LongDouble& x) const {
	if (sign != x.sign)
		return sign > x.sign; // если знаки разные, то положительное число больше

	if (exponent != x.exponent)
		return (exponent > x.exponent) ^ (sign == -1); // если экспоненты разные, то больше число с большей экспонентой с учётом знака

													   // копируем вектора
	vector<int> d1(digits);
	vector<int> d2(x.digits);
	size_t size = max(d1.size(), d2.size()); // определяем максимальный размер векторов

											 // выравниваем размеры векторов, добавляя в концы нули
	while (d1.size() != size)
		d1.push_back(0);

	while (d2.size() != size)
		d2.push_back(0);

	// проходим по всем цифрам числа
	for (size_t i = 0; i < size; i++)
		if (d1[i] != d2[i])
			return (d1[i] > d2[i]) ^ (sign == -1); // если в каком-то разряде цифры разные, то больше число с большей цифрой с учётом знака

	return false; // иначе числа равны, а значит не больше
}

bool LongDouble::operator<(const LongDouble& x) const {
	return !(*this > x || *this == x);
}

bool LongDouble::operator>=(const LongDouble& x) const {
	return *this > x || *this == x;
}


bool LongDouble::operator==(const LongDouble& x) const {
	if (sign != x.sign)
		return false;

	if (exponent != x.exponent)
		return false;

	if (digits.size() != x.digits.size())
		return false;

	for (size_t i = 0; i < digits.size(); i++)
		if (digits[i] != x.digits[i])
			return false;

	return true;
}


// унарный минус
LongDouble LongDouble::operator-() const {
	LongDouble res; // создаём число
	res.sign = -sign; // меняем знак на противоположный
	res.exponent = exponent; // копируем экспоненту
	res.digits = vector<int>(digits); // копируем цифры

	return res; // возвращаем результат
}

LongDouble LongDouble::operator+(const LongDouble& x) const {
	if (sign == x.sign) { // если знаки одинаковые
		long exp1 = exponent; // запоминаем экспоненту первого
		long exp2 = x.exponent; // и второго чисел
		long exp = max(exp1, exp2); // находим максимальную экспоненту. К ней будем приводить оба числа

									// создаём вектора из векторов цифр наших чисел
		vector<int> d1(digits);
		vector<int> d2(x.digits);

		// выравниваем экспоненты
		while (exp1 != exp) {
			d1.insert(d1.begin(), 0); // добавляя нули в начало первого
			exp1++;
		}

		while (exp2 != exp) {
			d2.insert(d2.begin(), 0); // и в начало второго векторов
			exp2++;
		}

		size_t size = max(d1.size(), d2.size()); // определяем максимальный размер векторов

												 // выравниваем размеры векторов, добавляя нули в конец каждого из них
		while (d1.size() != size)
			d1.push_back(0);

		while (d2.size() != size)
			d2.push_back(0);

		size_t len = 1 + size;

		LongDouble res; // создаём новое число

		res.sign = sign; // знак результата совпадает со знаком чисел
		res.digits = vector<int>(len, 0); // создаём вектор из len нулей

										  // заполняем каждую ячейку вектора суммой двух соответствующих цифр
		for (size_t i = 0; i < size; i++)
			res.digits[i + 1] = d1[i] + d2[i];

		// проверяем переполнения
		for (size_t i = len - 1; i > 0; i--) {
			res.digits[i - 1] += res.digits[i] / 10; // прибавляем к более старшему разряду десятки текущего
			res.digits[i] %= 10; // оставляем у текущего разряда только единицы
		}

		res.exponent = exp + 1; // восстанавливаем экспоненту
		res.removeZeroes(); // убираем нули

		return res; // возвращаем число
	}

	if (sign == -1)
		return x - (-(*this)); // если первое число отрицательное, то из второго вычитаем первое с обратным знаком

	return *this - (-x); // иначе из первого вычитаем второе с обратным знаком
}

LongDouble LongDouble::operator-(const LongDouble& x) const {
	if (sign == 1 && x.sign == 1) { // если боа числа положительны
		bool cmp = *this > x; // получаем флаг того, больше ли первое число

		long exp1 = cmp ? exponent : x.exponent; // сохраняем экспоненту большего числа
		long exp2 = cmp ? x.exponent : exponent; // сохраняем экспоненту меньшего числа
		long exp = max(exp1, exp2); // определяем максимальную экспоненту, чтобы к ней привести числа

		vector<int> d1(cmp ? digits : x.digits); // запоминаем вектор цифр большего числа
		vector<int> d2(cmp ? x.digits : digits); // запоминаем вектор цифр меньшего числа

												 // выравниваем экспоненты как при сложении (добавляя нули вначале числа)
		while (exp1 != exp) {
			d1.insert(d1.begin(), 0);
			exp1++;
		}

		while (exp2 != exp) {
			d2.insert(d2.begin(), 0);
			exp2++;
		}

		size_t size = max(d1.size(), d2.size()); // определяем максимальный размер

												 // добавляем нули в конец векторов цифр
		while (d1.size() != size)
			d1.push_back(0);

		while (d2.size() != size)
			d2.push_back(0);

		size_t len = 1 + size;

		LongDouble res; // создаём число для результата

		res.sign = cmp ? 1 : -1; // знак будет 1, если первое больше второго, и -1, если первое меньше второго
		res.digits = vector<int>(len, 0); // создаём вектор из len нулей

		for (size_t i = 0; i < size; i++)
			res.digits[i + 1] = d1[i] - d2[i]; // вычитаем соответствующие разряды

											   // обрабатываем переполнения
		for (size_t i = len - 1; i > 0; i--) {
			if (res.digits[i] < 0) { // если текущий разряд стал меньше нуля
				res.digits[i] += 10; // занимаем у предыдущего, прибавляя 10 к текущему
				res.digits[i - 1]--; // уменьшаем на 1 предыдущий разряд
			}
		}

		res.exponent = exp + 1; // восстанавливаем экспоненту
		res.removeZeroes(); // удаляем лишнии нули

		return res; // возвращаем результат
	}

	if (sign == -1 && x.sign == -1)
		return (-x) - (-(*this)); // если оба числа отрицательны, то из второго с обратным знаком вычитаем первое с обратным знаком

	return *this + (-x); // если знаки разные, прибавляем к первому отрицательное второе
}

LongDouble LongDouble::operator*(const LongDouble& x) const {
	size_t len = digits.size() + x.digits.size(); // максимальная длина нового числа не больше суммы длин перемножаемых чисел

	LongDouble res; // создадим объект для результата

	res.sign = sign * x.sign; // перемножаем знаки
	res.digits = vector<int>(len, 0); // создаём вектор из нулей
	res.exponent = exponent + x.exponent; // складываем экспоненты

										  // умножаем числа в столбик
	for (size_t i = 0; i < digits.size(); i++)
		for (size_t j = 0; j < x.digits.size(); j++)
			res.digits[i + j + 1] += digits[i] * x.digits[j]; // прибавляем результат произведения цифр из i-го и j-го разрядов

															  // в результате такого перемножения в ячейках могли получиться двузначные числа, поэтому нужно выполнить переносы
	for (size_t i = len - 1; i > 0; i--) {
		res.digits[i - 1] += res.digits[i] / 10; // добавляем к более старшему разряду десятки текущего разряда
		res.digits[i] %= 10; // оставляем только единицы у текущего разряда
	}

	res.removeZeroes(); // удаляем нули, как в конструкторе из строки, если таковые имеются
	//res.digits.erase(res.digits.begin() + res.exponent, res.digits.end());

	return res; // возвращаем результат умножения двух чисел
}

LongDouble LongDouble::operator/(const LongDouble& x) const {
	LongDouble res = *this * x.inverse(); // выполняем умножение на обратный элемент

										  // избавляемся от записи вида d...dd(9), которая эквивалентна d...dd+1
	size_t i = res.digits.size() - 1 - max((long)0, exponent);
	size_t n = max((long)0, res.exponent);

	// если в указанном месте девятка, то ищем место, в котором девятки закончатся
	if (i > n && res.digits[i] == 9) {
		while (i > n && res.digits[i] == 9)
			i--;

		// если дошли до целой части
		if (res.digits[i] == 9) {
			res.digits.erase(res.digits.begin() + n, res.digits.end()); // то удаляем всю вещественную часть
			res = res + res.sign; // и прибавляем 1 (или -1 к отрицательному) 
		}
		else {
			res.digits.erase(res.digits.begin() + i + 1, res.digits.end()); // иначе обрезаем с найденного места
			res.digits[i]++; // и увеличиваем на 1 текущий разряд
		}
	}
	//res.digits.erase(res.digits.begin() + res.exponent, res.digits.end());

	return res; // возвращаем результат деления
}

	
LongDouble& LongDouble::operator-=(const LongDouble& x) {
	return (*this = *this - x);
}


LongDouble LongDouble::inverse() const {
	if (isZero())
		throw string("Ошибка в LongDouble LongDouble::inverse() - деление на ноль!");

	LongDouble x(*this);
	x.sign = 1;

	LongDouble d("1");

	LongDouble res;
	res.sign = sign;
	res.exponent = 1;
	res.digits = vector<int>();

	while (x < 1) {
		x.exponent++;
		res.exponent++;
	}

	while (d < x)
		d.exponent++;	
	
	res.exponent -= d.exponent - 1;

	size_t numbers = 0;
	size_t intPart = max((long) 0, res.exponent);
	size_t maxNumbers = divDigits + intPart;

	do {
		int div = 0;

		//цикл целочисленного деления
		while (d >= x) {
			div++;
			d -= x;
		}
		//div - целая часть результата деления
		//d - дробная часть результата деления

		d.exponent++;
		d.removeZeroes();

		res.digits.push_back(div);
		numbers++;
	} while (!d.isZero() && numbers < maxNumbers);

	return res;
}


bool LongDouble::isInteger() const {
	if (exponent < 0)
		return false;

	return digits.size() <= (size_t) exponent;
}


bool LongDouble::isZero() const {
	return digits.size() == 1 && digits[0] == 0;
}


ostream& operator<<(ostream& os, const LongDouble& value) {
	if (value.sign == -1)
		os << '-';

	if (value.exponent > 0) {
		size_t i = 0;
		size_t e = value.exponent;

		while(i < value.digits.size() && i < e)
			os << value.digits[i++];

		while (i < e) {
			os << "0";
			i++;
		}

		if (i < value.digits.size()) {
			os << ".";

			while(i < value.digits.size())
				os << value.digits[i++];
		}
	}
	else if (value.exponent == 0) {
		os << "0.";

		for (size_t i = 0; i < value.digits.size(); i++)
			os << value.digits[i];
	}
	else {
		os << "0.";

		for (long i = 0; i < -value.exponent; i++)
			os << "0";

		for (size_t i = 0; i < value.digits.size(); i++)
			os << value.digits[i];
	}

	return os;
}
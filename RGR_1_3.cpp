#include<vector>
#include<iostream>
#include<climits>

using namespace std;

vector<int> v;

void input() {
	int a;
	while (cin >> a) {  // вводим массив
		v.push_back(a);
	}
	v.push_back(INT_MIN);
}

void package(const vector<int>& v) { // упаковка массива
	for (int i = 0; i < v.size() - 1; ++i) {
		if (v[i] == v[i + 1]) { // если соседние числа равны
			int counter = 0; // счётчик одинаковых чисел
			for (int j = i; j < v.size() - 1; ++j) {
				if (v[j] == v[i]) { // поиск кол-ва всех одинаковых значений
					++counter; // закрывается счётчик
				}
			}
			cout << '(' << -counter << ')' << ' ' << v[i] << ' '; // запись кол-ва цифры перед самой цифрой с "-" в начале
			i += counter - 1;
		}
		else {
			int counter = 1;
			for (int j = i + 1; j < v.size() - 1; ++j) {
				if (v[j] != v[j - 1]) { // если не равен предыдущему то счетчик увелич. 1 раз (просто позиция единичной цифры 1,2,3,...)
					++counter;
				}
				else {
					--counter;
					break;
				}
			}
			cout << '(' << counter << ')' << ' ';  
			for (int j = i; j < i + counter && j < v.size() - 1; ++j) {
				cout << v[j] << ' ';  // вывод этой единичной цифры с номером перед
			}
			i += counter - 1; // обнуление счетчика
		}
	}
	return;
}

int main() {
	input();
	package(v);
}

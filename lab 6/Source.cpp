#include <set>
#include <algorithm>
#include <iterator>
#include <conio.h>
#include <vector>
#include <ctime>
#include <iostream>


using namespace std;


const size_t SIZE = 2; // Мощность размещаемого в структурах множества
const size_t COUNT = 4; // Максимальное количество элементов в множествах


// Класс для работы с последовательностями
class mySeq {

public:

	vector<set<int>::iterator> seq;
	set<int> tree;


	// Конструктор с генерацией последовательности
	mySeq() {

		for (size_t i = 0; i < COUNT; ++i) {

			int temp = rand() % SIZE + 1;

			tree.insert(temp);

			seq.push_back(tree.find(temp));
		}
	}


	// Вывод последовательности
	void print() {

		for (size_t i = 0; i < seq.size(); ++i) {

			cout << *seq[i] << " ";
		}

		cout << endl;
	}


	// Исключение из последовательности подпоследовательности с индекса left до right
	void erase(size_t left, size_t right) {

		set<int> tempSet;
		vector<set<int>::iterator> tempSeq;

		for (size_t i = 0; i < seq.size(); ++i) {

			if (!(i >= left && i <= right)) {

				tempSet.insert(*seq[i]);
				tempSeq.push_back(tempSet.find(*seq[i]));
			}
		}

		swap(tempSet, tree);
		swap(tempSeq, seq);
	}


	// Добавление к последовательности в конец этой же последовательности count раз
	void mul(size_t count) {

		size_t tempSize = seq.size();

		for (size_t i = 0; i < count; ++i) {

			for (size_t j = 0; j < tempSize; ++j) {

				seq.push_back(seq[j]);
			}
		}
	}


	// Исключение из последовательности всех вхождений подпоследовательности exclSeq
	void excl(mySeq exclSeq) {

		if (seq.size() >= exclSeq.seq.size()) {

			int j = 0;

			for (int i = 0; i < seq.size(); ++i) {

				if (*seq.at(i) == *exclSeq.seq.at(j)) {
					++j;
				}
				else {
					i -= j;
					j = 0;
				}

				if (j == exclSeq.seq.size()) {

					for (int g = i; g > i - j; --g)
						seq.erase(seq.begin() + g);

					i -= j - 1;
					j = 0;

					if (seq.size() != 0 && i < seq.size())
						if (*seq.at(i) == *exclSeq.seq.at(j)) {
							++j;
						}
						else {
							i -= j;
							j = 0;
						}
				}
			}
		}
	}


};


// Генерация случайного дерева
void generate(set<int> & seq) {
	
	for (size_t i = 0; i < COUNT; ++i) {

		seq.insert(rand() % SIZE + 1);
	}
}


// Вывод дерева
void print(set<int> & seq) {

	for (set<int>::iterator it = seq.begin(); it != seq.end(); ++it) {

		cout << (*it) << " ";
	}

	cout << endl;
}


int main()
{
	srand(time(0));


	//............................................................РЕШЕНИЕ ЦЕПОЧКИ ОПЕРАЦИЙ НАД МНОЖЕСТВАМИ
	set<int> A, B, C, D, E, temp1, temp2, temp3, result;


	// Генерация множеств
	generate(A);
	generate(B);
	generate(C);
	generate(D);
	generate(E);


	// Вывод множеств
	cout << "A: ";
	print(A);

	cout << "B: ";
	print(B);

	cout << "C: ";
	print(C);

	cout << "D: ";
	print(D);

	cout << "E: ";
	print(E);


	// Вывод промежуточных значений и результата цепочки операций
	cout << endl << "A or B XOR (C and D dif E)" << endl;
	set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(temp1, temp1.begin()));
	cout << endl << "A or B: " << endl;
	print(temp1);

	set_intersection(C.begin(), C.end(), D.begin(), D.end(), inserter(temp2, temp2.begin()));
	cout << endl << "C and D: " << endl;
	print(temp2);

	set_difference(temp2.begin(), temp2.end(), E.begin(), E.end(), inserter(temp3, temp3.begin()));
	cout << endl << "C and D dif E: " << endl;
	print(temp3);

	set_symmetric_difference(temp1.begin(), temp1.end(), temp3.begin(), temp3.end(), inserter(result, result.begin()));
	cout << endl << "result: " << endl;
	print(result);


	//............................................................ДЕМОНСТРАЦИЯ РАБОТЫ С ПОСЛЕДОВАТЕЛЬНОСТЯМИ
	mySeq S1, S2;
	size_t left, right; // Границы для операции erase
	size_t count;

	left = 2;
	right = 25;
	count = 1;


	// Вывод последовательностей
	cout << endl << endl << endl << "S1: ";
	S1.print();
	cout << "S2: ";
	S2.print();


	// Операции над последовательностями
	// ERASE
	cout << endl << endl << "erase S2 from " << left << " to " << right << ": " << endl;
	cout << "S2: ";
	S2.print();
	S2.erase(left, right);
	cout << "new S2: ";
	S2.print();


	// MUL
	cout << endl << endl << "mul x" << count << " S1: " << endl;
	cout << "S1: ";
	S1.print();
	S1.mul(count);
	cout << "new S1: ";
	S1.print();


	// EXCL
	cout << endl << endl << "excl S2 from S1: " << endl;
	cout << "S1: ";
	S1.print();
	cout << "S2: ";
	S2.print();
	S1.excl(S2);
	cout << "new S1: ";
	S1.print();

	_getch();
}
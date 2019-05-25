#include <set>
#include <algorithm>
#include <iterator>
#include <conio.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>


using namespace std;


const size_t SIZE = 1; // Мощность размещаемого в структурах множества
const size_t COUNT = 6; // Размер последовательностей


// Класс для работы с последовательностями
class MySeq {

	void seqRestart() {

		seq.clear();

		for (set<int>::iterator it = tree.begin(); it != tree.end(); ++it)
			seq.push_back(it);

	}

	// Перезапись дерева по элементам вектора
	void treeRestart() {

		set<int> tempTree;
		vector<set<int>::iterator> tempSeq;
		for (size_t i = 0; i < seq.size(); ++i) {

			tempTree.insert(*seq.at(i));
			tempSeq.push_back(tempTree.find(*seq.at(i)));
		}


		swap(tempTree, tree);
		swap(tempSeq, seq);
	}

public:

	vector<set<int>::iterator> seq;
	set<int> tree;


	// Конструктор с генерацией последовательности
	MySeq() {

		for (size_t i = 0; i < COUNT; ++i) {

			int temp = rand() % SIZE + 1;

			tree.insert(temp);

			seq.push_back(tree.find(temp));
		}
	}


	// Вывод последовательности
	void print() {

		cout << "Tree [" << tree.size() << "] :\t";

		for (set<int>::iterator it = tree.begin(); it != tree.end(); ++it)
			cout << setw(5) << *it;

		cout << "\nSeq [" << seq.size() << "] :\t";

		for (size_t i = 0; i < seq.size(); ++i)
			cout << setw(5) << *seq[i];

		cout << endl;
	}


	// Исключение из последовательности подпоследовательности с индекса left до right
	void erase(size_t left, size_t right) {

		if (left <= right && right < seq.size()) {

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

			treeRestart();
		}
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
	void excl(MySeq exclSeq) {

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

		treeRestart();
	}


	// Пересечение множеств
	MySeq & operator & (const MySeq & Seq) {

		MySeq * result = new MySeq;
		result->seq.clear();
		result->tree.clear();

		set_intersection(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result->tree, result->tree.begin()));

		result->seqRestart();

		return *result;
	}


	// Объединение множеств
	MySeq & operator | (const MySeq & Seq) {

		MySeq * result = new MySeq;
		result->seq.clear();
		result->tree.clear();

		set_union(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result->tree, result->tree.begin()));

		result->seqRestart();

		return *result;
	}


	// Разность множеств
	MySeq & operator / (const MySeq & Seq) {

		MySeq * result = new MySeq;
		result->seq.clear();
		result->tree.clear();

		set_difference(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result->tree, result->tree.begin()));

		result->seqRestart();

		return *result;
	}


	// Симметрическая разность множеств
	MySeq & operator ^ (const MySeq & Seq) {

		MySeq * result = new MySeq;
		result->seq.clear();
		result->tree.clear();

		set_symmetric_difference(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result->tree, result->tree.begin()));

		result->seqRestart();

		return *result;
	}


	// Оператор присваивания
	MySeq & operator = (const MySeq & Seq) {

		tree.clear();
		seq.clear();

		for (size_t i = 0; i < Seq.seq.size(); ++i) {

			tree.insert(*Seq.seq.at(i));
			seq.push_back(tree.find(*Seq.seq.at(i)));
		}

		return *this;
	}
};


int main()
{
	srand(time(0));

	//............................................................РЕШЕНИЕ ЦЕПОЧКИ ОПЕРАЦИЙ НАД МНОЖЕСТВАМИ
	MySeq A, B, C, D, E, Temp1, Temp2, Temp3, Result;

	// Вывод множеств
	cout << "A: \n";
	A.print();

	cout << "\nB: \n";
	B.print();

	cout << "\nC: \n";
	C.print();

	cout << "\nD: \n";
	D.print();

	cout << "\nE: \n";
	E.print();


	// Вывод промежуточных значений и результата цепочки операций
	cout << "\nA or B: \n";
	Temp1 = A | B;
	Temp1.print();

	cout << "\nC and D: \n";
	Temp2 = C & D;
	Temp2.print();

	cout << "\nC and D dif E: \n";
	Temp3 = Temp2 / E;
	Temp3.print();

	cout << "\nA or B XOR (C and D dif E): \n";
	Result = Temp1 ^ Temp3;
	Result.print();


	//............................................................ДЕМОНСТРАЦИЯ РАБОТЫ С ПОСЛЕДОВАТЕЛЬНОСТЯМИ
	MySeq S1, S2;
	size_t left, right; // Границы для операции erase
	size_t count; // Количество вставок mul

	left = 0;
	right = 4;
	count = 1;


	// Вывод последовательностей
	cout << "\n---------------------------------------------------------\n\n\n";
	cout << "S1: \n";
	S1.print();
	cout << "\nS2: \n";
	S2.print();


	// Операции над последовательностями
	// ERASE
	cout << "\n\nErase S2 [" << left << "; " << right << "] : \n";
	cout << "Current S2: \n";
	S2.print();
	S2.erase(left, right);
	cout << "New S2: \n";
	S2.print();


	// MUL
	cout << "\n\nMul(" << count << ") S1: \n";
	cout << "Current S1: \n";
	S1.print();
	S1.mul(count);
	cout << "New S1: \n";
	S1.print();


	// EXCL
	cout << "\n\nExcl S2 from S1: \n";
	cout << "Current S1: \n";
	S1.print();
	cout << "Current S2: \n";
	S2.print();
	S1.excl(S2);
	cout << "New S1: \n";
	S1.print();

	_getch();
}
#include <set>
#include <algorithm>
#include <iterator>
#include <conio.h>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>


using namespace std;


size_t SIZE = 40; // Мощность размещаемого в структурах множества
size_t N = 10; // Мощность генерируемых множеств


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

		std::pair<set<int>::iterator, bool> tempPair;

		for (size_t i = 0; i < N;) {

			tempPair = tree.insert(rand() % SIZE + 1);

			if (tempPair.second)
				++i;
			seq.push_back(tempPair.first);
		}
	}


	// Конструктор копирования
	MySeq(const MySeq & Seq) {

		for (size_t i = 0; i < Seq.seq.size(); ++i)
			tree.insert(*Seq.seq.at(i));

		seqRestart();
	}


	// Перегенерация множества
	void regenerate() {

		seq.clear();
		tree.clear();

		std::pair<set<int>::iterator, bool> tempPair;

		for (size_t i = 0; i < N;) {

			tempPair = tree.insert(rand() % SIZE + 1);

			if (tempPair.second)
				++i;
			seq.push_back(tempPair.first);
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

		if (right >= seq.size())
			right = seq.size() - 1;

		if (left <= right) {

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

		if (seq.size() >= exclSeq.seq.size() && exclSeq.seq.size() != 0) {

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

					i -= j;
					j = 0;
				}
			}
		}

		treeRestart();
	}


	// Пересечение множеств
	MySeq operator & (const MySeq & Seq) {

		MySeq result = MySeq();
		result.seq.clear();
		result.tree.clear();

		set_intersection(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result.tree, result.tree.begin()));

		result.seqRestart();

		return MySeq(result);
	}


	// Объединение множеств
	MySeq operator | (const MySeq & Seq) {

		MySeq result = MySeq();
		result.seq.clear();
		result.tree.clear();

		set_union(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result.tree, result.tree.begin()));

		result.seqRestart();

		return MySeq(result);
	}


	// Разность множеств
	MySeq operator / (const MySeq & Seq) {

		MySeq result = MySeq();
		result.seq.clear();
		result.tree.clear();

		set_difference(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result.tree, result.tree.begin()));

		result.seqRestart();

		return MySeq(result);
	}


	// Симметрическая разность множеств
	MySeq operator ^ (const MySeq & Seq) {

		MySeq result = MySeq();
		result.seq.clear();
		result.tree.clear();

		set_symmetric_difference(tree.begin(), tree.end(), Seq.tree.begin(), Seq.tree.end(), inserter(result.tree, result.tree.begin()));

		result.seqRestart();

		return MySeq(result);
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
	MySeq A, B, C, D, E, Result;
	MySeq S1, S2;
	size_t left, right; // Границы для операции erase
	size_t count; // Количество вставок mul
	size_t G = 201; // Количество генераций

	left = 0;
	right = 5;
	count = 1;

	ofstream output("output.txt");

	output << G - 10 << endl;

	for (N = 10; N < G; ++N, ++SIZE) {

		left = 0;
		right = N / 2;

		cout << N << " ";
		
		A.regenerate();
		B.regenerate();
		C.regenerate();
		D.regenerate();
		E.regenerate();
		S1.regenerate();
		S2.regenerate();

		std::chrono::high_resolution_clock::time_point t1 =
			std::chrono::high_resolution_clock::now();

		// Цепочка операций над множествами
		Result = (A | B) ^ ((C & D) / E);

		// Цепочка операций над последовательностями
		S2.erase(left, right);
		S1.mul(count);
		S1.excl(S2);

		chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
		auto dt = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

		output << N << ' ' << (dt.count())<< endl ;
	}

	output.close();

	_getch();
}
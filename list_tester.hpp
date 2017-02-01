#pragma once

#include<cppunit/TestResult.h>
#include<cppunit/TestCase.h>
#include<cppunit/TextTestRunner.h>
#include<cppunit/TestAssert.h>
#include<cppunit/TextOutputter.h>
#include<cppunit/XmlOutputter.h>
#include<algorithm>
#include<vector>
#include "uj_list.hpp"

using namespace std;


class TestConstructors : public CppUnit::TestCase {
public:
	class Integer {
	public:
		int a = 5;
	};
	void runTest() {
		uj::list<int> lista;
		uj::list<string> lista2;
		uj::list<Integer> lista3;
		lista3.push_back(*(new Integer()));
		auto it = lista3.begin();
		CPPUNIT_ASSERT_EQUAL(true, (it)->a == 5);
		uj::list<int> lista4(lista);
		uj::list<int> lista5((size_t)5, 10);
		vector<double> vec2 = { 10,10,10,10,10 };
		int i = 0;
		for (auto it : lista5) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec2[i]);
			++i;
		}
		vector<double> vec = { 1,2,3,4,5 };
		uj::list<double> lista6(vec.begin(), vec.end());
		i = 0;
		for (auto it : lista6) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec[i]);
			++i;
		}
	}
};

class TestAssignSwapResize : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<double> lista;
		lista.assign((size_t)5, 10);
		vector<double> vec2 = { 10,10,10,10,10 };
		int i = 0;
		for (auto it : lista) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec2[i]);
			++i;
		}
		vector<double> vec = { 1,2,3,4,5,6 };
		uj::list<double> lista2;
		lista2.push_back(5);
		lista2.assign(vec.begin(), vec.end());
		i = 0;
		for (auto it : lista2) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec[i]);
			++i;
		}
		lista.swap(lista2);
		i = 0;
		for (auto it : lista2) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec2[i]);
			++i;
		}
		i = 0;
		for (auto it : lista) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec[i]);
			++i;
		}
		uj::list<int> lista3;
		lista.push_back(10);
		lista3.resize((size_t)5, 10);
		i = 0;
		for (auto it : lista3) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec2[i]);
			++i;
		}
		vector<double> vec3 = { 10 };
		lista3.resize(1);
		i = 0;
		for (auto it : lista3) {
			CPPUNIT_ASSERT_EQUAL(true, it == vec3[i]);
			++i;
		}
	}
};

class TestRemoveUniqueReverseSort : public CppUnit::TestCase {
public:
	   class Pred {
	   public:
		   bool operator()(double a) {
			   return a > 2.5;
		   }
	   };
	void runTest() {
		vector<double> vec = { 1,2,3,5,6 };
		vector<double> vec2 = { 4,1,2,4,3,4,4,5,6 };
		vector<double> vec3 = { 1,1,2,2,2,3,3,5,6,6 };
		vector<double> vec4 = { 3,6,2,1,5 };
		uj::list<double> lista(vec2.begin(), vec2.end());
		uj::list<double> lista2(vec3.begin(), vec3.end());
		uj::list<double> lista3(vec.begin(), vec.end());
		uj::list<double> lista4(vec.begin(), vec.end());
		uj::list<double> lista5(vec4.begin(), vec4.end());
		lista.remove(4);
		lista2.unique();
		int i = 0;
		for (auto it = lista.begin(); it != lista.end(); ++it) {
				CPPUNIT_ASSERT_EQUAL(true, (*it)==vec[i]);
			++i;
		}
		i = 0;
		for (auto it = lista2.begin(); it != lista2.end(); ++it) {
			CPPUNIT_ASSERT_EQUAL(true, (*it) == vec[i]);
			++i;
		}
		i = 1;
		lista3.remove_if(*(new Pred()));
		for (auto it = lista3.begin(); it != lista3.end(); ++it) {
			CPPUNIT_ASSERT_EQUAL(true, (*it) == i);
			++i;
		}
		lista4.reverse();
		i = 0;
		for (auto it = lista4.begin(); it != lista4.end(); ++it) {
			CPPUNIT_ASSERT_EQUAL(true, (*it) == vec[4-i]);
			++i;
		}
		i = 0;
		lista5.sort();
		for (auto it = lista5.begin(); it != lista5.end(); ++it) {
			CPPUNIT_ASSERT_EQUAL(true, (*it) == vec[i]);
			++i;
		}
	}
};

class TestSpliceMerge : public CppUnit::TestCase {
public:
	void runTest() {
		vector<double> vec = { 1,2,3,4,5,6,7 };
		vector<double> vec2 = { 2,4,6 };
		vector<double> vec3 = { 1,3,5,7 };
		vector<double> vec4 = { 1,3,2,4,6,5,7 };
		uj::list<double> lista(vec2.begin(), vec2.end());
		uj::list<double> lista2(vec3.begin(), vec3.end());
		uj::list<double> lista3(vec3.begin(), vec3.end());
		lista.merge(lista2);
		int i = 0;
		for (auto it = lista.begin(); it != lista.end(); ++it) {
			CPPUNIT_ASSERT_EQUAL(true, (*it) == vec[i]);
			++i;
		}
		CPPUNIT_ASSERT_EQUAL(0, (int)lista2.size());
		uj::list<double> lista4(vec2.begin(), vec2.end());
		auto it = lista3.begin();
		++it; ++it;
		lista3.splice(it, lista4);
		i = 0;
		for (auto it = lista3.begin(); it != lista3.end(); ++it) {
			CPPUNIT_ASSERT_EQUAL(true, (*it) == vec4[i]);
			++i;
		}
		CPPUNIT_ASSERT_EQUAL(0, (int)lista4.size());
	}
};

class TestList_Iterators : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		CPPUNIT_ASSERT_EQUAL(0, (int)lista.size());
		CPPUNIT_ASSERT_EQUAL(true, lista.empty());
		CPPUNIT_ASSERT_EQUAL(true, lista.begin() == lista.end());
	}
};

class TestPushes : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		uj::list<int> lista2;
		lista.push_back(5);
		lista2.push_front(5);
		CPPUNIT_ASSERT_EQUAL(false, lista.empty());
		CPPUNIT_ASSERT_EQUAL(5, *lista2.begin());
		CPPUNIT_ASSERT_EQUAL(5, *lista.begin());
		lista.push_front(2);
		CPPUNIT_ASSERT_EQUAL(2, *lista.begin());
		CPPUNIT_ASSERT_EQUAL(5, *(++lista.begin()));
		lista.push_back(7);
		CPPUNIT_ASSERT_EQUAL(3, (int)lista.size());
		CPPUNIT_ASSERT_EQUAL(7, *(++(++lista.begin())));
	}
};

class TestPops : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		lista.push_back(5);
		lista.push_back(6);
		lista.push_back(7);
		CPPUNIT_ASSERT_EQUAL(5, *lista.begin());
		lista.pop_front();
		CPPUNIT_ASSERT_EQUAL(6, *lista.begin());
		while (lista.size() > 0) {
			lista.pop_front();
		}
		CPPUNIT_ASSERT_EQUAL(true, lista.begin() == lista.end());
		lista.push_back(5);
		lista.push_back(6);
		lista.push_back(7);
		CPPUNIT_ASSERT_EQUAL(true, lista.back() == 7);
		lista.pop_back();
		CPPUNIT_ASSERT_EQUAL(true, lista.back() == 6);
		while (lista.size() > 0) {
			lista.pop_back();
		}
		CPPUNIT_ASSERT_EQUAL(true, lista.begin() == lista.end());
	}
};

class TestFrontBack : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		lista.push_front(7); lista.push_front(5); lista.push_front(3);
		CPPUNIT_ASSERT_EQUAL(true, lista.front() == 3);
		CPPUNIT_ASSERT_EQUAL(true, lista.back() == 7);
	}
};

class TestInsert : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		lista.insert(lista.begin(), 7);
		lista.insert(lista.begin(), 5);
		CPPUNIT_ASSERT_EQUAL(5, *lista.begin());
		CPPUNIT_ASSERT_EQUAL(7, *(++lista.begin()));
		CPPUNIT_ASSERT_EQUAL(5, lista.front());
		CPPUNIT_ASSERT_EQUAL(7, lista.back());
		auto it = lista.begin();
		++it;
		lista.insert(it, 6);
		int *tab = new int[3];
		int tab2[] = { 5,6,7 };
		int i = 0;
		for (auto it = lista.begin(); it != lista.end(); ++it) {
			tab[i] = *it;
			++i;
		}
		CPPUNIT_ASSERT_EQUAL(true, std::equal(tab, tab+3, tab2));
	}
};

class TestClearErase : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		lista.push_front(5);
		lista.push_front(4);
		lista.push_front(3);
		CPPUNIT_ASSERT_EQUAL(3, (int)lista.size());
		auto it = lista.begin();
		++it;
		lista.erase(it);
		CPPUNIT_ASSERT_EQUAL(2, (int)lista.size());
		lista.erase(lista.begin());
		CPPUNIT_ASSERT_EQUAL(1, (int)lista.size());
		lista.clear();
		CPPUNIT_ASSERT_EQUAL(0, (int)lista.size());
		lista.push_front(5);
		lista.push_front(4);
		lista.push_front(3);
		CPPUNIT_ASSERT_EQUAL(3, (int)lista.size());
		lista.clear();
		CPPUNIT_ASSERT_EQUAL(0, (int)lista.size());
	}
};

class TestCopyConstructorAndAssign : public CppUnit::TestCase {
public:
	void runTest() {
		uj::list<int> lista;
		lista.push_front(5);
		lista.push_front(4);
		lista.push_front(3);
		uj::list<int> lista2(lista);
		CPPUNIT_ASSERT_EQUAL(true, std::equal(lista.begin(), lista.end(), lista2.begin()));
		auto it = lista.begin();
		++it;
		lista.insert(it, 6);
		CPPUNIT_ASSERT_EQUAL(false, std::equal(lista.begin(), lista.end(), lista2.begin()));
		lista2 = lista;
		CPPUNIT_ASSERT_EQUAL(true, std::equal(lista.begin(), lista.end(), lista2.begin()));
	}
};

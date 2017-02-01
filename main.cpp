#include<iostream>
#include"uj_list.hpp"
#include<string>
#include<algorithm>
#include"list_tester.hpp"

using namespace std;
 
int main() {
	CppUnit::TextTestRunner runner;
	runner.addTest(new TestList_Iterators);
	runner.addTest(new TestFrontBack);
	runner.addTest(new TestInsert);
	runner.addTest(new TestPushes);
	runner.addTest(new TestPops);
	runner.addTest(new TestConstructors);
	runner.addTest(new TestClearErase);
	runner.addTest(new TestAssignSwapResize);
	runner.addTest(new TestCopyConstructorAndAssign);
	runner.addTest(new TestRemoveUniqueReverseSort);
	runner.addTest(new TestSpliceMerge);
	runner.setOutputter(new CppUnit::TextOutputter(&runner.result(), std::cout));
	runner.run();

}


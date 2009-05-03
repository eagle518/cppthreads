#include<main.hpp>
#include<iostream>
using namespace std;
void TestClass::print () {
	cout << "Test Class"<<endl;
}
int main(void)
{
	TestClass ts;
	ts.print();
}

// bitset_app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<vector>
#include<string>
#include<new>
#include<memory>
#include<bitset>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<math.h>
#include<utility>

using namespace std;

// function that takes a question number and a value to 
// indicate a true/false answer and updates the quiz results accordingly
template<unsigned T>
void Questions_func(bitset<T> &Questions, int Question_no, bool Question_ans)
{
	Questions.set((Question_no - 1), Question_ans);
}

// function that generates grades on the quiz
template<unsigned T>
double Grades(bitset<T>&Questions, bitset<T>&Question_Answers)
{
	double i{};
	for (size_t iii = 0; iii < Questions.size(); iii++)
		if (Questions[iii] == Question_Answers[iii])
			++i;

	return ((i/grades.size()) * 100);
}

int main()
{
	/*bitset<22>bits("1000000010000100101110");
	vector<int>ivec{ 1,2,3,5,8,13,21 };
	bitset<22>bits1;
	bits1.set();
	for each (auto var in ivec)
	{
		bits1.set(var);
	}
	cout << bits1 << "\n" << bits;*/

	bitset<10>Questions;
	Questions_func(Questions, 5, "true");
	cout << Questions;
    return 0;
}


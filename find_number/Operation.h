#pragma once
#include <vector>
#include <iostream>
using namespace std;

#define ID_OP_DEV_DIG 0
#define ID_OP_DEV_SUM 1 
#define ID_OP_DEV_CNT 2
#define ID_OP_GREAT	  3
#define ID_OP_LESS    4
class Operation
{
	int type;
	int indx_prime;
	bool div[20];
	char question[100];
public:
	void init(int type);
	bool (*testinput)();
	bool (*poperation)(int i, int j);
	void setype(int t);
	int gettype();
	void setquestion(char *q);
	void setop(bool v, int indx = -1);
	bool getop(int indx = -1);
	int getindx();
	void setindx(int indx);
	bool testop(int val, vector<int>&prime_numb);
	bool getanswer(vector<int>&prime_numb, bool debug = false, int findk = 0);
	bool getanswer(bool debug,int findk, int v);
};
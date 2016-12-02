#include "Operation.h"
void Operation::init(int type)
{
	this->type = type;
	indx_prime = 0;
}
void Operation::setype(int t)
{
	type = t;
}
int Operation::gettype()
{
	return type;
}
void Operation::setquestion(char *q)
{
	strcpy(question, q);
}

void Operation::setop(bool v, int indx)
{
	if (indx < 0)
		div[indx_prime-1] = v;
	else
		div[indx] = v;
}
bool Operation::getop(int indx)
{
	if (indx<0)
		return div[indx_prime-1];
	else
		return div[indx];
}
int Operation::getindx()
{
	return indx_prime;
}
void Operation::setindx(int indx)
{
	indx_prime = indx;
}
bool Operation::getanswer(vector<int>&prime_numb, bool debug, int find_k)
{
	bool ret;
	cout << question << prime_numb[indx_prime] << "? (yes/no) ";

	if ((debug && (find_k% prime_numb[indx_prime] == 0)) || ((!debug) && testinput()))
	{
		div[indx_prime] = true;
		ret = true;
	}
	else
	{
		div[indx_prime] = false;
		ret = false;
	}
	if (debug)
	{
		if (ret) cout << "yes\n";
		else cout << "no\n";
	}
		else cout << "\n";
	indx_prime++;
	return ret;
}
bool Operation::getanswer(bool debug, int find_k,int v)
{
	cout << question << v << "? (yes/no) ";
	if ((debug && (poperation(find_k,v))) || ((!debug) && testinput()))
	{
		if (debug) cout << "yes\n"; else cout << "\n";
		return true;
	}
	else
	{
		if (debug)cout << "no\n"; else cout << "\n";
		return false;
	}
}
bool Operation::testop(int val, vector<int>&prime_numb)
{
	bool need = true;
	int j = 0;
	while (j < indx_prime)
	{

		if (div[j])
		{
			if (val%prime_numb[j] != 0)
			{
				need = false;
				break;
			}
		}
		else
			if (val%prime_numb[j] == 0)
			{
				need = false;
				break;
			}
		j++;
	}
	return need;
}
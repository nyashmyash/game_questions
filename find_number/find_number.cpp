// find_number.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include "Operation.h"
#pragma comment (lib, "User32.lib")

using namespace std;
//простые числа на которые будет проверятся делимость
vector<int> getprime_numb(int n)
{
	vector<char> prime(n + 1, true);
	prime[0] = prime[1] = false;
	for (int i = 2; i <= n; ++i)
		if (prime[i])
			if (i * 1ll * i <= n)
				for (int j = i*i; j <= n; j += i)
					prime[j] = false;
	vector <int> ret;
	for (int i = 0; i < prime.size(); i++)
		if (prime[i])
			ret.push_back(i);
	return ret;
}

int pow1(int a, int pow)
{
	int i = 0;
	int res = 1;
	while (i < pow)
	{
		res *= a;
		i++;
	}
	return res;
}
int getdigitsInPos(int k, int pos)
{
	k = k / pow1(10, pos-1);
	return k;
}
//количество цифр и сумма
void cnt_sum_digits(int k, int &sum, int& cnt)
{
	cnt = 0;
	sum = 0;
	while (k>0)
	{
		cnt++;
		sum += k % 10;
		k = k / 10;
	}
}
bool testinput()
{
	bool ok = false;
	bool ret = true;
	while (!ok)
	{
		char answ[100];
		char tmp[100];
		cin >> answ;
		OemToChar(answ, tmp);
		if (strcmp(tmp, "да") == 0)
		{
			ret = true;
			ok = true;
		}
		if (strcmp(tmp, "нет") == 0)
		{
			ret = false;
			ok = true;
		}
		if (!ok)
		{
			cout << "неверно набран ответ, должно быть да или нет, введите еще раз\n";
		}
		else
			ok = true;
	}
	return ret;
}
bool opGreat(int i, int j)
{
 	return i > j;
}
bool opLess(int i, int j)
{
	return i < j;
}
//поведение

struct behavior
{
	int cntop;
	vector<Operation> oper;
	vector<int>prime_numb;//простые числа
	int prev_op_indx;
	int mt;
	int nt;
	void change_mn(int &m, int &n)
	{
		if (prev_op_indx != ID_OP_DEV_CNT)
		{
			while (!iselemneed(m) && m<=n) m++;
			while (!iselemneed(n) && n>=m) n--;
			if (m > n || n < m)
			{
				m = -1;
				n = -1;
			}
		}
		else
		{
			int sum, cnt;
			cnt_sum_digits(m, sum, cnt);
			if (!oper[ID_OP_DEV_CNT].testop(cnt, prime_numb))
				m = pow1(10, cnt);
			cnt_sum_digits(n, sum, cnt);
			if (!oper[ID_OP_DEV_CNT].testop(cnt, prime_numb))
				n = pow1(10, cnt-1)-1;
		}

	}
	void setop()
	{
		cntop = 5;
		prev_op_indx = 0;
		mt = 0;
		nt = 0;
		for (int i = 0; i < cntop; i++)
		{
			Operation op;
			op.testinput = &testinput;
			op.init(i);
			if (i == ID_OP_DEV_DIG)
				op.setquestion("делится ли ваше число на ");
			if (i == ID_OP_DEV_SUM)
				op.setquestion("делится ли сумма цифр вашего числа на ");
			if (i == ID_OP_DEV_CNT)
				op.setquestion("делится ли количество цифр числа на ");
			if (i == ID_OP_GREAT)
			{
				op.poperation = opGreat;
				op.setquestion("ваше число больше ");
			}
			if (i == ID_OP_LESS)
			{
				op.poperation = opLess;
				op.setquestion("ваше число меньше ");
			}
			
			oper.push_back(op);
		}
	}
	bool iselemneed(int i)
	{
		bool need = true;
		int j = 0;
		need = oper[ID_OP_DEV_DIG].testop(i, prime_numb);
		if (!need) return need;
		int sum, cnt;

		cnt_sum_digits(i, sum, cnt);
		need = oper[ID_OP_DEV_SUM].testop(sum, prime_numb);
		return need;
	}
};
int max_(int i, int j)
{
	return i > j ? i : j;
}
int main()
{
	int m = 100;
	int n = 1110109900;
	bool debug = 0;
	int find_k = 175190;
	int alg = 2;
	setlocale(LC_ALL, "Russian");
	
	if (!debug)
	{
		cout << "введите границы значений m и n:\n";
		bool ok = false;
		while (!ok)
		{
			char mch[100], nch[100];
			cin >> mch >> nch;
			m = atoi(mch);
			n = atoi(nch);
			if (n == 0 || m == 0 || n < m || (n + m) <0)
			{
				cout << "неверные значения, введите еще раз\n";
			}
			else

				ok = true;
		}
	}
	behavior beh;
	beh.prime_numb = getprime_numb(sqrt(n));
	beh.setop();
	int res = 0;
	int numb_q = 0;
	int cnt_q = 1;
	int indx_prime_numb = 0;
	
	while (1)
	{
		if (alg == 1)
		{
			int ind = (n + m) / 2;
			cout << "ваше число больше " << ind << "? (да/нет)" << endl;
			if ((debug&&(find_k > ind)) || ((!debug)&&testinput()))
			{
				m = ind + 1;
			}
			else
			{
				n = ind;
			}
			if ((n - m) < 1)
				break;
		}
		else
		if (cnt_q % 3 !=0)
		{
			if (m < 0 || n < 0)
			{
				cout << "ответ неверен, значение не найдено\n";
				break;
			}
			int v = (n + m) / 2;
			
			if (cnt_q > 9)
			{
				int tempv1 = v;
				int tempv2 = v;
				int tempm = m;
				int tempn = n;
				beh.change_mn(tempm, tempv1);
				beh.change_mn(tempv2, tempn);

				if (tempm == -1 && tempv1 == -1)
				{
					m = tempv2; n = tempn;
				}
				
				if (tempn == -1 && tempv2 == -1)
				{
					n = tempv1; m = tempm;
				}
				v = (n + m) / 2;
				
			}
			if (cnt_q % 3 == 1)
			{
				if(beh.oper[ID_OP_GREAT].getanswer(debug, find_k, v))
				{
					m = v + 1;
				}
				else
				{
					n = v;
				}
			}
			else
			{
				if (beh.oper[ID_OP_LESS].getanswer(debug, find_k, v))
				{
					n = v - 1;
				}
				else
				{
					m = v;
				}
			}
			if ((n - m) < 1)
				break;
		}
		else
		{
			if (alg == 2)
			{
				int min[4] = { 0,0,0,0 };
				int indx = ID_OP_DEV_DIG;
				int sum, cnt;
				cnt_sum_digits(n - m, sum, cnt);

				int ttempmt = m, ttempnt = n, ttempmf = m, ttempnf = n;
				
				int min_ = 0;
				int indxtmp = 0;
				int tempmt, tempnt, tempmf, tempnf;
				for (int i = 0; i < 3; i++)
				{
					tempmt = m;
					tempnt = n;
					tempmf = m;
					tempnf = n;
					beh.oper[i].setindx(beh.oper[i].getindx() + 1);
					beh.oper[i].setop(true);
					beh.prev_op_indx = i;
					beh.change_mn(tempmt, tempnt);
					beh.oper[i].setop(false);
					beh.change_mn(tempmf, tempnf);

					beh.oper[i].setindx(beh.oper[i].getindx() - 1);
					if (tempmt < 0 || tempnt < 0 || tempmf < 0 || tempnf < 0) continue;
					int mx = max_((tempnt - tempmt),(tempnf - tempmf));
					if (i == ID_OP_DEV_DIG)
					{
						min_ = mx;
						ttempmt = tempmt; ttempnt = tempnt; ttempmf = tempmf; ttempnf = tempnf;
					}
					if (min_ > mx)
					{
						min_ = mx;
						indx = i;
						ttempmt = tempmt; ttempnt = tempnt; ttempmf = tempmf; ttempnf = tempnf;
					}
				}
				
				int find = find_k;
				cnt_sum_digits(find_k, sum, cnt);
				if (indx == ID_OP_DEV_SUM)
					find = sum;
				if (indx == ID_OP_DEV_CNT)
					find = cnt;
					
				bool ret = beh.oper[indx].getanswer(beh.prime_numb, debug, find);
				beh.prev_op_indx = indx;
			
				if (ret)
				{
					m = ttempmt;
					n = ttempnt;
				}
				else
				{
					m = ttempmf;
					n = ttempnf;
				}
					
			}
		}
		cnt_q++;
	}
	cout << "ваше число: " << n << endl;
	cout <<"количество шагов " <<cnt_q << endl;
	if (debug) getchar();
	else
	{
		int i = 0;
		while (getchar() && i < 1)i++;
	}

	return 0;
}



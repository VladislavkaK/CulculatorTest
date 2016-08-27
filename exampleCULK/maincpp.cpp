#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <locale>

const int  N = 1024;

double eval(char *str);
double number(char *, unsigned *);
double expr(char *, unsigned *);
double term(char *, unsigned *);
double factor(char *, unsigned *);

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	char str[N];

	cout<<"Введите выражение: ";
	fgets(str, N, stdin);

	printf("Результат: %lf\n", eval(str));
	system("pause");
	return 0;
}

double eval(char *str)
{
	unsigned i = 0;

	return expr(str, &i);
}

double number(char *str, unsigned *idx)
{
	double result = 0.0;
	double div = 10.0;
	int sign = 1;

	if (str[*idx] == '-')
	{
		sign = -1;
		++*idx;
	}
	

	while (str[*idx] >= '0' && str[*idx] <= '9')
	{
		result = result * 10.0 + (str[*idx] - '0');

		++*idx;
	}
	

	if (str[*idx] == '.' || str[*idx] == ',')
	{
		++*idx;

		while (str[*idx] >= '0' && str[*idx] <= '9')
		{
			result = result + (str[*idx] - '0') / div;
			div *= 10.0;

			++*idx;
		}
	
	}

	

	return sign * result;
}

double expr(char *str, unsigned *idx)
{
	double result = term(str, idx);

	while (str[*idx] == '+' || str[*idx] == '-')
	{
		switch (str[*idx])
		{
		case '+':
			++*idx;

			result += term(str, idx);

			break;
		case '-':
			++*idx;

			result -= term(str, idx);

			break;
		}
	}

	return result;
}

double term(char *str, unsigned *idx)
{
	double result = factor(str, idx);
	double div;

	while (str[*idx] == '*' || str[*idx] == '/')
	{
		switch (str[*idx])
		{
		case '*':
			++*idx;

			result *= factor(str, idx);

			break;
		case '/':
			++*idx;

			div = factor(str, idx);

			if (div != 0.0)
			{
				result /= div;
			}
			else
			{
				printf("Деление на ноль!\n");
				exit(-1);
			}

			break;
		
		}
	}

	return result;
}

double factor(char *str, unsigned *idx)
{
	double result;
	int sign = 1;

	if (str[*idx] == '-')
	{
		sign = -1;

		++*idx;
	}

	if (str[*idx] == '(')
	{
		++*idx;

		result = expr(str, idx);

		if (str[*idx] != ')')
		{
			printf("Несбалансированные скобки!\n");
			exit(-2);
		}

		++*idx;
	}
	else
		result = number(str, idx);


	return sign * result;
}

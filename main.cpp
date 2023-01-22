#include <stdio.h>
#include <string.h>
#include <locale.h>
#define N 100

int RomantoArabic(char* Rnumber);
int cheking(char* Rnumber);

int main()
{

	setlocale(LC_ALL, "Rus");
	printf("Перевод числа из римской записи в арабскую.\n");
	printf("Введите число. В круглых скобках запишите тысячные разряды числа. Например: (ХХ)С = 20100. \n");

	char p[N];
	char* Rnumber;

	Rnumber = gets_s(p);   // Ввод числа в римской записи

	int number = RomantoArabic(Rnumber);

	if (cheking(Rnumber) == 1) printf("%i\n", number);
}

int romanvalue(char s) // Функция возвращает значение римской цифры в арабской системе
{

	if (s == 'I') return 1;
	if (s == 'V') return 5;
	if (s == 'X') return 10;
	if (s == 'L') return 50;
	if (s == 'C') return 100;
	if (s == 'D') return 500;
	if (s == 'M') return 1000;
}



int RomantoArabic(char* Rnumber) //Основная функция
{

	int arabvalue = 0, number = 0, beg = 0, numberin = 0;

	if (strchr(Rnumber, '(') != NULL && strchr(Rnumber, ')') != NULL)
	{

		for (int k = strcspn(Rnumber, "(") + 1; k < strcspn(Rnumber, ")"); k++)
		{

			int prevvalue2 = numberin;

			numberin = romanvalue(Rnumber[k]) * 1000;
			if (numberin > prevvalue2)
			{
				int stab2 = -2 * prevvalue2;
				number += stab2;
			}
			number += numberin;
			beg = k + 2;
		}
	}
	for (int i = beg; i < strlen(Rnumber); i++)
	{
		int prevvalue = arabvalue;

		arabvalue = romanvalue(Rnumber[i]);
		if (arabvalue > prevvalue)
		{
			int stab = -2 * prevvalue;
			number += stab;
		}
		number += arabvalue;
	}
	return number;
}

// Блок проверки
int countchar(char c, char* s)
{
	int count = 1;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == c == s[i + 1]
			&& s[i] == s[i + 2] == s[i + 3])
			count = 0;
	}
	return count;
}

int cheking(char* Rnumber)
{

	int flag = 1;

	for (int i = 0; i < strlen(Rnumber); i++) // Проверка числа на правильность записи
	{
		if (Rnumber[i] == 'V' || Rnumber[i] == 'L' || Rnumber[i] == 'D')
		{
			if (Rnumber[i] == Rnumber[i + 1])
			{
				printf("Число записано неверно\nКод ошибки: 1");
				flag = 0;
				break;
			}
		}

		if ((Rnumber[i] != 'I' && Rnumber[i] != 'V' && Rnumber[i] != 'X'
			&& Rnumber[i] != 'L' && Rnumber[i] != 'C' && Rnumber[i] != 'D'
			&& Rnumber[i] != 'M' && Rnumber[i] != '(' && Rnumber[i] != ')'))
		{
			printf("Число записано неверно\nКод ошибки: 2");
			flag = 0;
			break;
		}
		if (countchar(Rnumber[i], Rnumber) == 0 || (strchr(Rnumber, '(') == NULL && strchr(Rnumber, ')') != NULL)
			|| (strchr(Rnumber, ')') == NULL && strchr(Rnumber, '(') != NULL))
		{
			printf("Число записано неверно\nКод ошибки: 3");
			flag = 0;
			break;
		}
	}
	return flag;
}

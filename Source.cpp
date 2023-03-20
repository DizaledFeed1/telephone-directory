#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
int quantity_Calls = -1;
using namespace std;
struct duration_Calls
{
	int hour;
	int minute;
	int second;
};
struct calls_Date 
{
	int day;
	int month;
	int year;
};
struct calls_information
{
	int number_Phone;
	struct calls_Date date;
	struct duration_Calls duration;
	int code_city;
};
struct Table
{
	struct calls_information Inf[10];
	int calls_number;
};

void make_new_call(struct Table* a, int i) // добавление звонка
{
		cout << "Введите номер телефона:";
		scanf_s("%d", &(a->Inf[i].number_Phone));

		if (a->Inf[i].number_Phone < 1000000 || a->Inf[i].number_Phone > 10000000)
		{
			cout << "Неправильная форма записи номера телефона. Пожалуста, проверьте корректность введеной даты и попробуйте заново.\n"; 
			make_new_call(a, i);
		}

			cout << "Когда начался звонок?\n";
			cout << "День:";
			scanf_s("%d", &(a->Inf[i].date.day));
			cout << "Месяц:";
			scanf_s("%d", &(a->Inf[i].date.month));
			cout << "Год:";
			scanf_s("%d", &(a->Inf[i].date.year)); 
			if (a->Inf[i].date.year < 2000 || a->Inf[i].date.month > 12 || a->Inf[i].date.month < 1 || a->Inf[i].date.day >(30 + ((a->Inf[i].date.month + (a->Inf[i].date.month / 8)) % 2)) || a->Inf[i].date.day < 1)
			{
				cout << "Неправильная запись даты. Пожалуста, проверьте корректность введеной даты и попробуйте заново.\n";
				make_new_call(a, i);
			}
			if (a->Inf[i].date.month == 2 && a->Inf[i].date.day > 28)
			{
				cout << "Неправильная запись даты. Пожалуста, проверьте корректность введеной даты и попробуйте заново.\n";
				make_new_call(a, i);
			}
			
			cout << "Сколько длился звонок?\n";
			cout << "Часы:";
			scanf_s("%d", &(a->Inf[i].duration.hour));
			cout << "Минуты:";
			scanf_s("%d", &(a->Inf[i].duration.minute));
			cout << "Секунды:";
			scanf_s("%d", &(a->Inf[i].duration.second));
			
			if (a->Inf[i].duration.hour < 0 || a->Inf[i].duration.minute > 60 || a->Inf[i].duration.minute < 0 || a->Inf[i].duration.second > 60 || a->Inf[i].duration.second < 0)
			{
				cout << "Неправильная запись времени. Пожалуста, проверьте корректность введеного времени и попробуйте заново.\n";
				make_new_call(a, i);
			} 
			cout << "Введите код города:";
			scanf_s("%d", &(a->Inf[i].code_city));
			if (a->Inf[i].code_city < 100 || a->Inf[i].code_city > 1000)
			{
				cout << "Неправильная запись кода города. Пожалуста, проверьте корректность введеного времени и попробуйте заново.\n";
				make_new_call(a, i);
			}
	
		

}
void make_new_calls(struct Table* TT, int calls_number) // Добавление новых звонков
{
	for (int i = TT->calls_number; i < TT->calls_number + calls_number; i++)
	{
		make_new_call(TT, i);
	}
	TT->calls_number += calls_number;
}

void transfer(struct Table* TT, FILE* Doc) // фунция перемещающая из файла в программу
{
	int i = 0;
	TT->calls_number = 0;

	if ((Doc = fopen("D:\\Games\\text.txt", "r")) == NULL)
	{
		printf("File wasn't open\n");
		system("pause");
	}
	else
	{
		while (!feof(Doc)) // читаем из файла
		{
			fscanf(Doc, "%d %d %d %d %d %d %d %d\n",
				&TT->Inf[i].number_Phone,

				&TT->Inf[i].date.day,
				&TT->Inf[i].date.month,
				&TT->Inf[i].date.year,

				&TT->Inf[i].duration.hour,
				&TT->Inf[i].duration.minute,
				&TT->Inf[i].duration.second,

				&TT->Inf[i].code_city);
			TT->calls_number++;
			i++;
		}
		fclose(Doc);
	}
}
void paint(struct Table TT) { // фунция выводы в консоль

	{
		for (int i = 0; i < TT.calls_number; i++)
		{
				cout<< TT.Inf[i].number_Phone << "\t",

					printf(" %02d.%02d.%04d \t", TT.Inf[i].date.day, TT.Inf[i].date.month, TT.Inf[i].date.year);
	
				printf(" %02d:%02d:%02d\t", TT.Inf[i].duration.hour,  TT.Inf[i].duration.minute, TT.Inf[i].duration.second) ,

				cout << TT.Inf[i].code_city << "\n";
		}
		
	}
}
void save(struct Table TT, FILE* Doc) // функция сохранения в файл
{
	Doc = fopen("D:\\Games\\text.txt", "w");  // Открытие документа для записи
	for (int i = 0; i < TT.calls_number; i++)
	{
		fprintf(Doc, "%d ", TT.Inf[i].number_Phone);// Запись в текстовый файл
		
		fprintf(Doc, "%d ", TT.Inf[i].date.day);
		fprintf(Doc, "%d ", TT.Inf[i].date.month);
		fprintf(Doc, "%d ", TT.Inf[i].date.year);

		fprintf(Doc, "%d ", TT.Inf[i].duration.hour);
		fprintf(Doc, "%d ", TT.Inf[i].duration.minute);
		fprintf(Doc, "%d ", TT.Inf[i].duration.second);

		fprintf(Doc, "%d \n", TT.Inf[i].code_city);
	}
	fclose(Doc);
}
void delet(struct Table* TT, int a) // функция удаления
{
	for (int i = a-1; i != TT->calls_number - 1; i++) 
	{
		TT->Inf[i] = TT->Inf[i+1];
	}
	TT->calls_number--;
}

void meny() { // меню вывода
	cout << "Нажмите 1 чтобы добавить информацию о новом звонке\n Нажмите 2 для загрузки таблицы с файла\n Нажмите 3 для сохранения таблицы в файл\n Нажмите 4 чтобы посмотреть таблицу\n Нажмите 5 для сортировки таблицы\n Нажмите 6 для поиска конкретной информации по таблице\n Нажмите 7 чтобы удалить конкретную запись\n Нажмите 8 чтобы изенить конкретную запись\n Нажмите 9 чтобы узнать суммарную продолжительность всех звонков\n Нажмите 0 для выхода\n";
}

void special(struct Table* TT) {
	int hours=0, minute=0, second=0, full_second;
	for (int i = 0; i < TT->calls_number; i++)
	{
		hours += TT->Inf[i].duration.hour;
		minute += TT->Inf[i].duration.minute;
		second += TT->Inf[i].duration.second;
	}
	full_second = (hours * 3600 + minute * 60 + second);
	hours = full_second / 3600;
	minute = (full_second - hours *3600) / 60;
	second = (full_second - hours * 3600 - minute * 60);
	cout << hours << ":" << minute << ":" << second<<"\n";
}

int Time_comparison_for_researching_in_table(struct Table* TT, int i, int j) // Функция сравнения дат для последующей сортировки
{
	if (TT->Inf[j].duration.second != TT->Inf[i].duration.second)
	{
		return TT->Inf[j].duration.second - TT->Inf[i].duration.second;
	}
	if (TT->Inf[j].duration.minute != TT->Inf[i].duration.minute)
	{
		return TT->Inf[j].duration.minute - TT->Inf[i].duration.minute;
	}
	if (TT->Inf[j].duration.hour != TT->Inf[i].duration.hour)
	{
		return TT->Inf[j].duration.hour - TT->Inf[i].duration.hour;
	}
	return 0;
}
int Date_comparison_for_researching_in_table(struct Table* TT, int i, int j) // Функция сравнения дат для последующей сортировки
{
	if (TT->Inf[j].date.year != TT->Inf[i].date.year)
	{
		return TT->Inf[j].date.year - TT->Inf[i].date.year;
	}
	if (TT->Inf[j].date.month != TT->Inf[i].date.month)
	{
		return TT->Inf[j].date.month - TT->Inf[i].date.month;
	}
	if (TT->Inf[j].date.day != TT->Inf[i].date.day)
	{
		return TT->Inf[j].date.day - TT->Inf[i].date.day;
	}
	return 0;
}
void sort(struct Table* TT) 
{
	int number;
	cout << "Нажмите 1 для сортировки по номеру телефона\n";
	cout << "Нажмите 2 для сортировки по дате звонка\n";
	cout << "Нажмите 3 для сортировки по продолжительности звонка\n";
	cout << "Нажмите 4 для сортировки по коду города\n";
	cin >> number;
	
	switch (number)
	{
	case 1: {
		for (int i = 0; i < (TT->calls_number) - 1; i++)
		{
			for (int j = i + 1; j < TT->calls_number; j++)
				if (TT->Inf[j].number_Phone - TT->Inf[i].number_Phone < 0)
				{
					struct calls_information inf = TT->Inf[i];
					TT->Inf[i] = TT->Inf[j];
					TT->Inf[j] = inf;
				}
		}
		cout << "Успешно.\n";
		break;
		}
	case 2: //Сортировка по дате
		for (int i = 0; i < (TT->calls_number) - 1; i++)

		{
			for (int j = i + 1; j < TT->calls_number; j++)
				if (Date_comparison_for_researching_in_table(TT, i, j) < 0)
				{
					struct calls_information inf = TT->Inf[i];
					TT->Inf[i] = TT->Inf[j];
					TT->Inf[j] = inf;
				}
		}
		cout << "Успешно.\n";
		break;
	case 3://Сортировка по времени
		for (int i = 0; i < (TT->calls_number) - 1; i++)

		{
			for (int j = i + 1; j < TT->calls_number; j++)
				if (Time_comparison_for_researching_in_table(TT, i, j) < 0)
				{
					struct calls_information inf = TT->Inf[i];
					TT->Inf[i] = TT->Inf[j];
					TT->Inf[j] = inf;
				}
		}
		cout << "Успешно.\n";
		break;
	case 4: { // сортировка по коду города
		for (int i = 0; i < (TT->calls_number) - 1; i++)
		{
			for (int j = i + 1; j < TT->calls_number; j++)
				if (TT->Inf[j].code_city - TT->Inf[i].code_city < 0)
				{
					struct calls_information inf = TT->Inf[i];
					TT->Inf[i] = TT->Inf[j];
					TT->Inf[j] = inf;
				}
		}
		cout << "Успешно.\n";
		break;
	}
	default:
		break;
	}
}

void searching_time(Table TT, int i, int a, int c) 
{
	int min = -1, max = -1;
	int min_time = 0, max_time = 2147483647;
	int sum_time1 = 0, sum_time2 = 0;
	int flag = 0;
	for (int j = 0; j < TT.calls_number; j++)
	{
		if (TT.Inf[j].duration.hour == i && TT.Inf[j].duration.minute == a && TT.Inf[j].duration.second == c)
		{
			cout << TT.Inf[j].number_Phone << "\t",

				printf(" %02d.%02d.%04d \t", TT.Inf[j].date.day, TT.Inf[j].date.month, TT.Inf[j].date.year);

			printf(" %02d:%02d:%02d\t", TT.Inf[j].duration.hour, TT.Inf[j].duration.minute, TT.Inf[j].duration.second),

				cout << TT.Inf[j].code_city << "\n";
			flag = 1;
		}
	}
	if (flag == 0)
	{
		{
			sum_time1 = i * 10000 + a * 100 + c;
			for (int j = 0; j < TT.calls_number; j++)
			{
				sum_time2 = TT.Inf[j].duration.hour * 10000 + TT.Inf[j].duration.minute * 100 + TT.Inf[j].duration.second;
				if (sum_time1 > sum_time2 && sum_time2 > min_time)
				{
					min_time = sum_time2;
					min = j;
				}
				if (sum_time1 < sum_time2 && sum_time2 < max_time)
				{
					max_time = sum_time2;
					max = j;
				}
			}
			cout << "Возможно вы имели в виду это\n";
			if (min != -1)
			{
				cout << TT.Inf[min].number_Phone << "\t",

					printf(" %02d.%02d.%04d \t", TT.Inf[min].date.day, TT.Inf[min].date.month, TT.Inf[min].date.year);

				printf(" %02d:%02d:%02d\t", TT.Inf[min].duration.hour, TT.Inf[min].duration.minute, TT.Inf[min].duration.second),

					cout << TT.Inf[min].code_city << "\n";
			}
			if (max != -1)
			{
				cout << TT.Inf[max].number_Phone << "\t",

					printf(" %02d.%02d.%04d \t", TT.Inf[max].date.day, TT.Inf[max].date.month, TT.Inf[max].date.year);

				printf(" %02d:%02d:%02d\t", TT.Inf[max].duration.hour, TT.Inf[max].duration.minute, TT.Inf[max].duration.second),

					cout << TT.Inf[max].code_city << "\n";
			}
		}
	}

}
void searching_date(Table TT, int i, int a, int c)  // функция поиска по дате звонка
{
	int min = -1, max = -1;
	int min_date = 0, max_date = 2147483647;
	int sum_date1 = 0, sum_date2 = 0;
	int flag = 0;
	for (int j = 0; j < TT.calls_number; j++)
	{
		if (TT.Inf[j].date.day == i && TT.Inf[j].date.month == a && TT.Inf[j].date.year == c)
		{
			cout << TT.Inf[j].number_Phone << "\t",

				printf(" %02d.%02d.%04d \t", TT.Inf[j].date.day, TT.Inf[j].date.month, TT.Inf[j].date.year);

			printf(" %02d:%02d:%02d\t", TT.Inf[j].duration.hour, TT.Inf[j].duration.minute, TT.Inf[j].duration.second),

				cout << TT.Inf[j].code_city << "\n";
			flag = 1;
		}
	}
	if (flag == 0)
	{
		{
			sum_date1 = c*10000 + a*100 + i;
				for (int j = 0; j < TT.calls_number; j++)
				{
					sum_date2 = TT.Inf[j].date.year*10000 + TT.Inf[j].date.month*100 + TT.Inf[j].date.day;
					if (sum_date1 > sum_date2 && sum_date2 > min_date)
					{
						min_date = sum_date2;
						min = j;
					}
					if (sum_date1 < sum_date2 && sum_date2 < max_date)
					{
						max_date = sum_date2;
						max = j;
					}
				}
				cout << "Возможно вы имели в виду это\n";
				if (min != -1)
				{
					cout << TT.Inf[min].number_Phone << "\t",

						printf(" %02d.%02d.%04d \t", TT.Inf[min].date.day, TT.Inf[min].date.month, TT.Inf[min].date.year);

					printf(" %02d:%02d:%02d\t", TT.Inf[min].duration.hour, TT.Inf[min].duration.minute, TT.Inf[min].duration.second),

						cout << TT.Inf[min].code_city << "\n";
				}
				if (max != -1)
				{
					cout << TT.Inf[max].number_Phone << "\t",

						printf(" %02d.%02d.%04d \t", TT.Inf[max].date.day, TT.Inf[max].date.month, TT.Inf[max].date.year);

					printf(" %02d:%02d:%02d\t", TT.Inf[max].duration.hour, TT.Inf[max].duration.minute, TT.Inf[max].duration.second),

						cout << TT.Inf[max].code_city << "\n";
				}
			}
		}
	}
void searching_Code_city(struct Table* TT, int i) // поиск по номеру телефона
{
	for (int j = 0; j < TT->calls_number; j++)
	{
		if (TT->Inf[j].code_city == i)
		{
			cout << TT->Inf[j].number_Phone << "\t",

				printf(" %02d.%02d.%04d \t", TT->Inf[j].date.day, TT->Inf[j].date.month, TT->Inf[j].date.year);

			printf(" %02d:%02d:%02d\t", TT->Inf[j].duration.hour, TT->Inf[j].duration.minute, TT->Inf[j].duration.second),

				cout << TT->Inf[j].code_city << "\n";
		}
		else {
			int n = 0;
			int c = 10;
			for (int a = 100; a >= 1; a = a / 10) //приблезительный поиск
			{
				if ((i / a) - (i / a) / c * c == ((TT->Inf[j].code_city / a)- (TT->Inf[j].code_city / a) / c * c) + 1 || (i / a) - (i / a) / c * c == ((TT->Inf[j].code_city / a) - (TT->Inf[j].code_city / a) / c * c) - 1 || i / a == (TT->Inf[j].code_city / a) - 1 || i / a == (TT->Inf[j].code_city / a) + 1 || i / a == TT->Inf[j].code_city / a || (i / a) - (i / a) / c * c == (TT->Inf[j].code_city - (TT->Inf[j].code_city / a) / c * c))
				{
					n++;
				}
			}
			if (n >= 2)
			{
				cout << "Возможно вы имели в виду это\n";

				cout << TT->Inf[j].number_Phone << "\t",

					printf(" %02d.%02d.%04d \t", TT->Inf[j].date.day, TT->Inf[j].date.month, TT->Inf[j].date.year);

				printf(" %02d:%02d:%02d\t", TT->Inf[j].duration.hour, TT->Inf[j].duration.minute, TT->Inf[j].duration.second),

					cout << TT->Inf[j].code_city << "\n";
			}
		}
	}
}
void searching_Number_Phone(struct Table* TT, int i) // поиск по номеру телефона
	{

		for (int j = 0; j < TT->calls_number; j++)
		{
			if (TT->Inf[j].number_Phone == i)
			{
				cout << TT->Inf[j].number_Phone << "\t",

					printf(" %02d.%02d.%04d \t", TT->Inf[j].date.day, TT->Inf[j].date.month, TT->Inf[j].date.year);

				printf(" %02d:%02d:%02d\t", TT->Inf[j].duration.hour, TT->Inf[j].duration.minute, TT->Inf[j].duration.second),

					cout << TT->Inf[j].code_city << "\n";
				break;
			}
			else if(i > 1000000 && i < 10000000)
			{
				int n = 0;
				int c = 10;
				for (int a = 1000000; a > 7; a = a / 10) //приблезительный поиск
				{
					if ((i/a) - (i /a)/ c * c == ((TT->Inf[j].number_Phone /a)- (TT->Inf[j].number_Phone /a) / c * c)+1 || (i / a) - (i / a) / c * c == ((TT->Inf[j].number_Phone / a)- (TT->Inf[j].number_Phone / a) / c * c) - 1 || i/a == (TT->Inf[j].number_Phone/a)-1 || i / a == (TT->Inf[j].number_Phone / a) + 1 || i / a == TT->Inf[j].number_Phone / a || (i / a) - (i / a) / c * c == ((TT->Inf[j].number_Phone / a) - (TT->Inf[j].number_Phone / a) / c * c))
					{
						n++;
					}
				}
				if (n >= 3)
				{
					cout << "Возможно вы имели в виду это\n";

					cout << TT->Inf[j].number_Phone << "\t",

						printf(" %02d.%02d.%04d \t", TT->Inf[j].date.day, TT->Inf[j].date.month, TT->Inf[j].date.year);

					printf(" %02d:%02d:%02d\t", TT->Inf[j].duration.hour, TT->Inf[j].duration.minute, TT->Inf[j].duration.second),

						cout << TT->Inf[j].code_city << "\n";
				}
			}
		}
	}
void searching(struct Table TT) // общая функция поиска 
{
	int number, meaning, day, mounth, yaer , hour, minute, second;
	cout << "Нажмите 1 чтобы искать по номеру телефона\n";
	cout << "Нажмите 2 чтобы искать по дате звонка\n";
	cout << "Нажмите 3 чтобы искать по продолжительности звонка\n";
	cout << "Нажмите 4 чтобы искать по коду города\n";
	cin >> number;
	switch (number)
	{
	case 1: {
		cout << "Введите номер телефона:";
		cin >> meaning;
		searching_Number_Phone(&TT, meaning);
		break;

	}
	case 2: {
		cout << "Введите день:";
		cin >> day;
		cout << "Введите месяц:";
		cin >> mounth;
		cout << "Введите год:";
		cin >> yaer;
		searching_date(TT, day, mounth, yaer);
		break;
	}
	case 3: {
		cout << "Введите количество часов:";
		cin >> hour;
		cout << "Введите количество минут:";
		cin >> minute;
		cout << "Введите количество секунд:";
		cin >> second;
		searching_time(TT,hour,minute,second);
	}
	case 4: {cout << "Введите код города:";
	{
		cin >> meaning;
		searching_Code_city(&TT, meaning);
		break;
	}
	default:
		break;
	}

	}

	
}
void main() 
{
	system("chcp 1251"); // Для русского языка
	system("cls");
	setlocale(LC_ALL, "Rus");
	FILE* file{};
	int number;
	int  i;
	int numbers;
	struct  Table TT;
	TT.calls_number = 0;
	meny();
	while (1)
	{
		cout << "Что вы ходите сделать?";
		cin >> number;
		if (number ==0) {
			cout << "Работа завершена";
			break;
		}
		switch (number)
		{
		case 1: {
			cout << "Сколько звонков вы хотите добавить?";
			cin >> i;
			make_new_calls(&TT,i);
			break;
		}
		case 2: {
			save(TT, file);
			cout << ("Успешно.\n");
			break;
		}
		case 3: {
			transfer(&TT, file);
			cout << ("Успешно.\n");
			break;
		}
		case 4: {
			paint(TT);
			break;
		}
		case 5: {
			sort(&TT);
			break;
		}
		case 6: { 
			searching(TT);
			break;
		}
		case 7: {
			cout << "Какую запись вы хотите удалить?";
			cin >> numbers;
			delet(&TT, numbers);
			break;
		}
		case 8: {
			cout << "Какую запись вы хотите изменить?";
			cin >> numbers;
			make_new_call(&TT, numbers-1);
			cout << ("Успешно.\n");
			break;
		}
		case 9: 
		{
			special(&TT);
			break;
		}
		case 0: {
			break;
		}
		default:
		{
			cout << "Ошибка! \n";
		}
			break;
		}
		
	}
}
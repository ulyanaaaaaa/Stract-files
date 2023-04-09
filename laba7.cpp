
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <conio.h>
#include <iomanip>
#include <Windows.h>

using namespace std;

typedef struct
{
	char surname[20];
	int numberOfGroup;
	int physicsGrade;
	int mathsGrade;
	int InformaticsGrade;
	double averageGrade;
}info;

int checkInputInt();
void individualTask(info*, int);
void writeStudentInFile(info*, int, FILE*);
void writeInFile(info*, int);
int main();
int menu();
int newStudent(info*, int);
void showStudent(info*, int);
void showStudents(info*, int);
void changeStudent(info*, int);
int changeMenu();
void sortStudents(info*, int);
int removeStudent(info*, int);

int main()
{
	info* students;
	students = new info[30];

	if (!students)
	{
		cout << "Память не выделилась";
		return 1;
	}

	int counterOfStudents = 0;

	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251); 

	while (1)
	{
		switch (menu())
		{
		case 1:
			system("cls");
			counterOfStudents = newStudent(students, counterOfStudents);
			break;
		case 2:
			system("cls");
			if (!counterOfStudents)
				cout << "Нету студентов";
			else
				showStudents(students, counterOfStudents);
			break;
		case 3:
			system("cls");
			if (!counterOfStudents)
				cout << "Нету студентов";
			else
				individualTask(students, counterOfStudents);
			break;
		case 4:
			system("cls");
			if (!counterOfStudents)
				cout << "Нету студентов";
			else
				writeInFile(students, counterOfStudents);
			break;
		case 5:
			system("cls");
			if (!counterOfStudents)
				cout << "Нету студентов";
			else
				changeStudent(students, counterOfStudents);
			break;
		case 6:
			system("cls");
			if (!counterOfStudents)
				cout << "Нету студентов";
			else
				counterOfStudents = removeStudent(students, counterOfStudents);
			break;
		case 7:
			system("cls");
			if (!counterOfStudents)
				cout << "Нету студентов";
			else
				sortStudents(students, counterOfStudents);
			break;
		case 8:
			system("cls");
			return 0;
		default:
			cout << "Введен неправильный вариант" << endl;
			break;
		}
	}

}
int menu()
{
	cout << endl << "Меню:" << endl;
	cout << "1. Добавить новых студентов" << endl;
	cout << "2. Просмотр информации всех студентов" << endl;
	cout << "3. Вывести студентов-отличников, фамилии которых начинаются с интересующей вас буквы" << endl;
	cout << "4. Записать информацию в файл" << endl;
	cout << "5. Изменить данные о студенте" << endl;
	cout << "6. Удалить студента" << endl;
	cout << "7. Сортировать студентов" << endl;
	cout << "8. Выход" << endl;
	cout << "Выберите один из вариантов: ";
	return checkInputInt();
}
int checkInputInt()
{
	int value;

	while (!scanf_s("%d", &value))
	{
		cout << "Некорректный ввод" << endl;
		rewind(stdin);
	}

	return value;
}
void individualTask(info* students, int counterOfStudents)
{
	bool flag = true;
	char letter[20];

	do
	{
		cout << "Введите букву, с которой должны начинаться фамилии: ";
		rewind(stdin);
		cin >> letter;
	} while (!((letter[0] >= 'A' && letter[0] <= 'Z') || (letter[0] >= 'a' && letter[0] <= 'z')
		|| (letter[0] >= 'а' && letter[0] <= 'я') || (letter[0] >= 'А' && letter[0] <= 'Я')) || strlen(letter) != 1);


	for (int i = 0; i < counterOfStudents; i++)
		if (students[i].mathsGrade > 8 && students[i].InformaticsGrade > 8 && students[i].physicsGrade > 8 && (students[i].surname)[0] == letter[0])
		{
			flag = false;
			break;
		}

	if (flag)
		cout << "Студентов-отличников, фамилии которых начинаются с интересующей вас буквы  нету" << endl;
	else
	{
		cout << "Студентов-отличников, фамилии которых начинаются с интересующей вас буквы: " << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		for (int i = 0; i < counterOfStudents; i++)
			if (students[i].mathsGrade > 8 && students[i].InformaticsGrade > 8 && students[i].physicsGrade > 8 && (students[i].surname)[0] == letter[0])
				showStudent(students, i);
	}
}
void writeStudentInFile(info* students, int index, FILE* f)
{
	fputs("\nФамилия студента: ", f);
	fwrite(&students[index].surname, sizeof(strlen(students[index].surname)), 1, f);
	fputs("\nГруппа студента: ", f);
	fprintf(f, "%d", students[index].numberOfGroup);
	fputs("\nОценка по физике: ", f);
	fprintf(f, "%d", students[index].physicsGrade);
	fputs("\nОценка по математике: ", f);
	fprintf(f, "%d", students[index].mathsGrade);
	fputs("\nОценка по информатике: ", f);
	fprintf(f, "%d", students[index].InformaticsGrade);
	fputs("\nСредняя оценка за 3 предмета: ", f);
	fprintf(f, "%.2f", students[index].averageGrade);
	fputs("\n-------------------------------------------------------------------------", f);
	  
}
void writeInFile(info* students, int counterOfStudents)
{
	FILE* file;

	char name[20];
	cout << "Введите имя файла: ";
	cin >> name;
	if ((file = fopen(name, "wb")) == NULL)
	{
		cout << "Ошибка при открытии" << endl;
		exit(1);
	}
	fputs("-----------------------Инфорамция о всех студентах-----------------------", file);

	for (int i = 0; i < counterOfStudents; i++)
	{
		writeStudentInFile(students, i, file);
	}

	bool flag = true;

	for (int i = 0; i < counterOfStudents; i++)
		if ((students[i].mathsGrade > 8 && students[i].InformaticsGrade > 8) && (students[i].physicsGrade == 4 || students[i].physicsGrade == 5))
		{
			flag = false;
			break;
		}

	if (flag)
		fputs("\nСтудентов, имеющих отметку 4 или 5 по физике и больше 8 по остальным предметам нету", file);
	else
	{
		fputs("\nСтуденты, имеющие отметку 4 или 5 по физике и больше 8 по остальным предметам: ", file);
		for (int i = 0; i < counterOfStudents; i++)
			if ((students[i].mathsGrade > 8 && students[i].InformaticsGrade > 8) && (students[i].physicsGrade == 4 || students[i].physicsGrade == 5))
				writeStudentInFile(students, i, file);
	}
	cout << "Вся информация записана в " << name << endl;
}
int newStudent(info* students, int counterOfStudents)
{
	cout << "-----------------------------------------------------------" << endl;
	cout << "Введите фамилию: ";
	cin >> students[counterOfStudents].surname;

	do
	{
		cout << "Введите номер группы: ";
		rewind(stdin);
	} while (!scanf_s("%d", &students[counterOfStudents].numberOfGroup) || students[counterOfStudents].numberOfGroup < 0);

	do
	{
		cout << "Введите оценку по физике: ";
		rewind(stdin);
	} while (!scanf_s("%d", &students[counterOfStudents].physicsGrade) || (students[counterOfStudents].physicsGrade > 10 || students[counterOfStudents].physicsGrade < 0));

	do
	{
		cout << "Введите оценку по математике: ";
		rewind(stdin);
	} while (!scanf_s("%d", &students[counterOfStudents].mathsGrade) || (students[counterOfStudents].mathsGrade > 10 || students[counterOfStudents].mathsGrade < 0));

	do
	{
		cout << "Введите оценку по информатике: ";
		rewind(stdin);
	} while (!scanf_s("%d", &students[counterOfStudents].InformaticsGrade) || (students[counterOfStudents].InformaticsGrade > 10 || students[counterOfStudents].InformaticsGrade < 0));

	if (students[counterOfStudents].InformaticsGrade + students[counterOfStudents].mathsGrade + students[counterOfStudents].physicsGrade == 0)
		students[counterOfStudents].averageGrade = 0;
	else
		students[counterOfStudents].averageGrade = (students[counterOfStudents].InformaticsGrade + students[counterOfStudents].mathsGrade + students[counterOfStudents].physicsGrade) / 3;

	counterOfStudents++;

	return counterOfStudents;
}
void showStudent(info* students, int index)
{
	cout << "Фамилия студента: " << students[index].surname << endl;
	cout << "Номер группы: " << students[index].numberOfGroup << endl;
	cout << "Оценка по физике: " << students[index].physicsGrade << endl;
	cout << "Оценка по математике: " << students[index].mathsGrade << endl;
	cout << "Оценка по информатике: " << students[index].InformaticsGrade << endl;
	cout << "Средняя оценка по предметам: " << students[index].averageGrade << endl;
	cout << "-------------------------------------------------------------------------" << endl;
}
void showStudents(info* students, int counterOfStudents)
{
	cout << "-----------------------Инфорамция о всех студентах-----------------------" << endl;

	for (int i = 0; i < counterOfStudents; i++)
	{
		showStudent(students, i);
	}
}
void changeStudent(info* students, int counterOfStudents)
{
	char changeSurname[20];
	int index;
	bool flag = false;

	cout << "Введите фамилию студента, данные которого хотите изменить: ";
	cin >> changeSurname;

	for (int i = 0; i < counterOfStudents; i++)
		if (!strcmp(changeSurname, students[i].surname))
		{
			flag = true;
			index = i;
			showStudent(students, index);
			break;
		}

	if (!flag)
	{
		cout << "Такого студента нету" << endl;
		return;
	}

	while (1)
	{
		switch (changeMenu())
		{
		case 1:
			cout << "Введите новую фамилию студента: ";
			rewind(stdin);
			cin >> students[index].surname;
			break;
		case 2:
			cout << "Введите новую группу студента: ";
			cin >> students[index].numberOfGroup;
			break;
		case 3:
			cout << "Введите новую оценку по физике студента: ";
			cin >> students[index].physicsGrade;
			break;
		case 4:
			cout << "Введите новую оценку по математике студента: ";
			cin >> students[index].mathsGrade;
			break;
		case 5:
			cout << "Введите новую оценку по информатике студента: ";
			cin >> students[index].InformaticsGrade;
			break;
		case 6:
			system("cls");
			return;
		default:
			cout << "Неверный выбор" << endl;
			break;
		}
	}
}
int changeMenu()
{
	cout << "\nВведите параметр который хотите изменить\n";
	cout << "1. Фамилия\n";
	cout << "2. Номер группы\n";
	cout << "3. Оценку по физике\n";
	cout << "4. Оценку по математике\n";
	cout << "5. Оценку по информатике\n";
	cout << "6. Закончить изменения \n";
	return checkInputInt();
}
void sortStudents(info* students, int counterOfStudents)
{
	info tmp;

	for (int i = 0; i < counterOfStudents - 1; i++)
		for (int j = i + 1; j < counterOfStudents; j++)
			if (strcmp(students[i].surname, students[j].surname) > 0)
			{
				tmp = students[i];
				students[i] = students[j];
				students[j] = tmp;
			}
	cout << "Список студентов отсортирован" << endl;
}
int removeStudent(info* students, int counterOfStudents)
{
	char removeSurname[20];
	int index;
	bool flag = true;

	cout << "Введите фамилию студента, данные которого хотите удалить: ";
	cin >> removeSurname;

	for (int i = 0; i < counterOfStudents; i++)
		if (!strcmp(removeSurname, students[i].surname))
		{
			flag = false;
			index = i;
			break;
		}

	if (flag == false)
	{
		cout << "Такого студента нету" << endl;
		return counterOfStudents;
	}

	if (counterOfStudents == 1)
		return 0;
	else
	{
		for (int i = index; i < counterOfStudents - 1; i++)
			students[i] = students[i + 1];

		return counterOfStudents - 1;
	}
}

  
	




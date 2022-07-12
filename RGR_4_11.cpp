#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int value; // новая вершина
	int left; // левый указатель
	int right; // правый указатель
};


void save(char* filename, int v) // функция включения нового значения
{    // запись структуры в файл
	FILE* fp;
	int pos, pos2;
	struct node t, p = { v, 0, 0 };
	if (fopen_s(&fp, filename, "r+b") != 0) { fopen_s(&fp, filename, "w+b"); goto z2; }
	rewind(fp); // перемещает указатель на начало потока файла
z:;
	fread(&t, sizeof(struct node), 1, fp); // считывание файла
	if (feof(fp)) goto z2; // контролируется положение указателя в файле
	if (t.left == 0 || t.right == 0) // если левая или правая ветка равна 0
	{
		pos = ftell(fp); // значение соответствующее количеству байт потока от начала файла
		fseek(fp, 0, 2); // устанавление указателя в файле для ввода вывода значения
		pos2 = ftell(fp);
		fseek(fp, pos - sizeof(struct node), 0); // добавление значения с учетом заполнения в других нодах и смещения
		pos2 = pos2 / sizeof(struct node) + 1; 
		if (t.left == 0) t.left = pos2; else t.right = pos2; // заполнение одной из нод
		fwrite(&t, sizeof(struct node), 1, fp); //  запись в файл
		goto z2;
	}
	goto z;
z2:;
	fseek(fp, 0, 2);
	fwrite(&p, sizeof(struct node), 1, fp);

	fclose(fp);
}

void show(char* filename) // функция вывода содержания файла на консоль
{
	FILE* fp;
	struct node t;
	fopen_s(&fp, filename, "rb");
	rewind(fp);
zz:;
	fread(&t, sizeof(struct node), 1, fp);
	if (feof(fp)) goto zz2;
	std::cout << t.value << " " << t.left << " " << t.right << "\n";
	goto zz;
zz2:;
	fclose(fp);
}

int main()
{
	char filename[] = "tree.dat";
	save(filename, 1);
	show(filename);
	system("pause");
	return 0;
}
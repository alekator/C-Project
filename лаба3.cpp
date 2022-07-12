#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void)
{
	int size, i, j, a, ressize = 1;
	int* mass;
	int* nevozr;
	int** result;

	printf("Vvedite razmernost' massiva ");
	scanf_s("%d", &size);
	mass = (int*)malloc(size * sizeof(int)); //??????? ???.??????
	for (i = 0; i < size; i++)
	{
		printf("arr[%d]=", i);
		scanf_s("%d", &mass[i]);
	}

	result = (int**)malloc(sizeof(int*));
	nevozr = (int*)malloc(sizeof(int));
	nevozr[0] = 1;
	a = 0;
	i = 1;
	if (i >= size) goto z2;
z:;
	if (mass[i] < mass[i - 1])
	{
		nevozr = (int*)realloc(nevozr, (++nevozr[0]) * sizeof(int));
		nevozr[nevozr[0] - 1] = mass[i];
	}
	else if (++i < size) goto z;
	if (i - 1 > a)
	{
		ressize++;
		result = (int**)realloc(result, ressize * sizeof(int*));
		result[ressize - 1] = (int*)malloc((i - a + 1) * sizeof(int));
		result[ressize - 1][0] = i - a + 1;
		for (j = i - a; j >= 1; j--) result[ressize - 1][j] = mass[a + j - 1];
	}
	a = i;
	if (i + 1 < size) {
		++i;
		goto z;
	}
z2:;
	result[0] = nevozr;

	for (i = 0; i < ressize; ++i)
	{
		printf("\n%i | ", result[i][0]);
		for (j = 1; j < result[i][0]; ++j)
		{
			printf("%i ", result[i][j]);
		}
	}

	free(mass);
	system("pause");
	return 0;
}


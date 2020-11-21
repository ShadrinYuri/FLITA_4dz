# 14.	Найти частоту степеней вершин и отсортировать вершины по возрастанию степени вершины (сортировка выбором)

## Алгоритм:

- определение степени каждой вершины и запись их в массив

``` C
	int* head_grade = (int*) calloc(n, sizeof(int));
	int sum = 0;
	for (int i = 0; i < n; ++i){
		for (int k = 0; k < n; ++k){
			sum += mtx[i][k];
		}
		head_grade[i] = sum;
		sum = 0;
	}
```

- создание такого же массива-близнеца для привязки к номеру в массиве names 

```C
	int* head_grade_twin = (int*) calloc(n, sizeof(int));

	for (int i = 0; i < n; ++i){
		head_grade_twin[i] = head_grade[i];
	}
```

- сортировка выбором исходного массива:

```C
	int swap = 0;

	for (int i = 0; i < n; ++i){
		int min = i;
		for (int k = i; k < n; ++k){
			if (head_grade[k] < head_grade[min]){
				min = k;
			}
		}
		if (head_grade[i] != head_grade[min]){
			swap = head_grade[i];
			head_grade[i] = head_grade[min];
			head_grade[min] = swap;
			swap = 0;
		}
	}
``` 

- вывод имен вершин и соответствующих им степеней:

``` C
	for (int i = 0; i < n;){
		if (i != n - 1){
		for (int j = i + 1; j < n; ++j){
			if (head_grade[i] == head_grade[j]) {
				++i;
			} else {
				break;
			}
		}
		}
		for (int k = 0; k < n; ++k){
			if (head_grade[i] == head_grade_twin[k]){
				printf("%s - %d\n", names[k], head_grade[i]);
			}
		}
		++i;
	}
```

## Блок-схема алгоритма:

![Alt-текст](https://github.com/igorkorobenko/FLITA_4dz/blob/main/ДЗ4.png "блок-схема ДЗ4")

## Результат работы: 

![Alt-текст](https://github.com/igorkorobenko/FLITA_4dz/blob/main/term.png "териминал ДЗ4")

## Отображение графа:

![Alt-текст](https://github.com/igorkorobenko/FLITA_4dz/blob/main/test.png "граф ДЗ")

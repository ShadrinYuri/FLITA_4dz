#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){

	int bg = -1;
	while ((bg != 1) && (bg != 0)){
		printf("0 - for graph\n");
		printf("1 - for digraph\n");
		scanf("%d", &bg);
	}

	int n;
	printf("Num of elements: ");
	scanf("%d", &n);

	while (n < 0){
        printf("Num > 0 !\n");
        scanf("%d",&n);
        printf("\n");
    }

	int mtx[n][n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			mtx[i][j] = 0;
		}
	}

	char* names[n];

	printf("Fill the names of elements\n");

	for (int i = 0; i < n; i++){
		printf("#%d ", i + 1);
		char *s = (char*) malloc(20 * sizeof(char));
		scanf("%s", s);
		names[i] = s;
	}

	putchar('\n');

	printf("Connections\n");

	printf("Example:\n");
	printf("lol\n");
	printf(";\n\n");

	for (int i = 0; i < n; i++){
		printf("#%d: %s\n", i + 1, names[i]);
		_Bool flag = 1;

		while (flag){
			char* cmp_sting = (char*) malloc(20 * sizeof(char));
			scanf("%s", cmp_sting);

			for (int j = 0; j < n; j++){
				if (strcmp(names[j], cmp_sting) == 0){
					mtx[i][j]++;
					if ((bg == 0) && (i != j)){
						mtx[j][i]++;
					}
				}
			}
			if (strcmp(cmp_sting, ";") == 0){
				flag = 0;
			}
			free(cmp_sting);
		}	
	}


	// проверка на связанность графа (крест)

	_Bool goriz = 1;
	for (int i = 0; i < n; i++){
		_Bool vertic = 0;
		for (int j = 0; j < n; j++){
			if (mtx[i][j] > 0)
				vertic = 1;

			if (mtx[j][i] > 0)
				vertic = 1;
		}
		if (vertic == 0)
			goriz = 0;
	}
	if (!goriz){
		printf("Unrelated graph\n");
	}
	else {
		printf("Related graph\n");
	}

	for (int i = 0; i < n; i++){
		printf("#%d %10s: ", i + 1, names[i]);
			for (int k = 0; k < n; k++){
				printf("%d ", mtx[i][k]);
			}
			printf("\n");
	}

// запись на языке DOT

	char* graph_name = (char*) calloc(40, sizeof(char));

	printf("The name of file .dot (without .dot)\n");
	scanf("%s", graph_name);

	char* graph_name_twin = (char*) calloc(40, sizeof(char));
	strcat(graph_name_twin, graph_name);
	strcat(graph_name, ".dot");

	char* arr = (char*) calloc(500, sizeof(char));

	if(bg == 1){
		strcat(arr, "digraph G {");
		for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (mtx[i][j] > 0){
				for (int a = 0; a < mtx[i][j]; a++){
					strcat(arr, names[i]);
					strcat(arr, "->");
					strcat(arr, names[j]);
					strcat(arr, ";");
				}
			}
		}
	}
	}
	else {
		strcat(arr, "graph G {");
		for (int i = 0; i < n; i++){
			strcat(arr, names[i]);
			strcat(arr, ";");
		}
		for (int i = 0; i < n; i++){
			for (int j = i; j < n; j++){
				if (mtx[i][j] > 0){
					for (int a = 0; a < mtx[i][j]; a++){
						strcat(arr, names[i]);
						strcat(arr, "--");
						strcat(arr, names[j]);
						strcat(arr, ";");
					}
				}
			}
		}
		}

	strcat(arr, "}");

	FILE* f = fopen(graph_name, "w");
	fprintf(f, "%s\n", arr);
	fclose(f);

	char* term = (char*) calloc(500, sizeof(char));

	strcat(term, "echo \"");
	strcat(term, arr);

	strcat(term, "\" | dot -Tpng >./");
	strcat(term, graph_name_twin);
	strcat(term, ".png");
	printf("%s\n", term);
	system(term);

	int* head_grade = (int*) calloc(n, sizeof(int));
	int sum = 0;
	for (int i = 0; i < n; ++i){
		for (int k = 0; k < n; ++k){
			sum += mtx[i][k];
		}
		sum -= mtx[i][i];
		head_grade[i] = sum;
		sum = 0;
	}

	int* head_grade_twin = (int*) calloc(n, sizeof(int));

	for (int i = 0; i < n; ++i){
		head_grade_twin[i] = head_grade[i];
	}

	// choice sort

	int swap = 0;

	printf("\n");
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


	free(term);
	free(arr);
	free(graph_name);
	free(graph_name_twin);
	free(head_grade);
	free(head_grade_twin);

	return 0;
}
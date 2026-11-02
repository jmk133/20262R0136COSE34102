#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 101

// 방식 1

int* add(int arr_1[], int arr_2[], int count, int count_2) {
	int max = (count > count_2) ? count : count_2;
	int* answer = malloc(sizeof(int) * max);
	for (int i = 0; i < max; i++) {
		int a_idx = i + (count - max);
		int b_idx = i + (count_2 - max);
		int a = (a_idx >= 0) ? arr_1[a_idx] : 0;
		int b = (b_idx >= 0) ? arr_2[b_idx] : 0;
		answer[i] = a + b;
	}
	return answer;
}

int* multiply(int arr_1[], int arr_2[], int count, int count_2) {
	int size = (count - 1) + (count_2 - 1) + 1;
	int* result = calloc(size, sizeof(int));  // 0으로 초기화

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count_2; j++) {
			result[i + j] += arr_1[i] * arr_2[j];
		}
	}

	return result;
}

int evaluate(int* poly, int degree, int x) {
	int result = 0;
	for (int i = 0; i <= degree; i++) {
		int power = degree - i;  // 최고차항부터 계산
		int term = poly[i];
		for (int j = 0; j < power; j++) {
			term *= x;
		}
		result += term;
	}
	return result;
}


int main() {
	char input[101];
	char input_2[101];
	int* coeffs = NULL;
	int* coeffs_2 = NULL;
	char* tokens[MAX_TERMS];
	char* tokens_2[MAX_TERMS];
	int count = 0;
	int count_2 = 0;

	printf("수식 1을 입력하세요 : ");
	fgets(input, sizeof(input), stdin);

	char* token = strtok(input, " ");
	while (token != NULL) {
		tokens[count] = token;
		count++;
		token = strtok(NULL, " "); // strtok는 한 번 자르고 나서 NULL로 인자 받음
	}

	coeffs = (int*)malloc(sizeof(int) * count);
	for (int i = 0; i < count; i ++) {
		coeffs[i] = atoi(tokens[i]);
	}

	printf("수식 2를 입력하세요 : ");
	fgets(input_2, sizeof(input_2), stdin);

	char* token_2 = strtok(input_2, " ");
	while (token_2 != NULL) {
		tokens_2[count_2] = token_2;
		count_2++;
		token_2 = strtok(NULL, " "); // strtok는 한 번 자르고 나서 NULL로 인자 받음
	}

	coeffs_2 = (int*)malloc(sizeof(int) * count_2);
	for (int i = 0; i < count_2; i++) {
		coeffs_2[i] = atoi(tokens_2[i]);
	}

	int* sum = add(coeffs, coeffs_2, count, count_2);
	int maximum = count > count_2 ? count : count_2;
	printf("수식 1 + 2 = ");
	int started = 0;
	for (int i = 0; i < maximum; i++) {
		int coef = sum[i];
		int deg = maximum - 1 - i;

		if (coef != 0) {
			if (started && coef > 0) printf("+");
			if (deg > 1) {
				printf("%dx**%d", coef, deg);
			}
			else if (deg == 1) {
				printf("%dx", coef);
			}
			else {
				printf("%d", coef);
			}
			started = 1;
		}
	}
	if (!started) printf("0");
	printf("\n");

	int* multi = multiply(coeffs, coeffs_2, count, count_2);
	int multi_size = count + count_2 - 1;
	printf("수식 1 * 2 = ");
	started = 0;
	for (int i = 0; i < multi_size; i++) {
		int coef = multi[i];
		int deg = multi_size - 1 - i;

		if (coef != 0) {
			if (started && coef > 0) printf("+");
			if (deg > 1) {
				printf("%dx**%d", coef, deg);
			}
			else if (deg == 1) {
				printf("%dx", coef);
			}
			else {
				printf("%d", coef);
			}
			started = 1;
		}
	}
	if (!started) printf("0");
	printf("\n");

	printf("수식에 값을 넣으세요 ");
	int num;
	scanf("%d", &num);

	// 수식 1 계산
	int val1 = evaluate(coeffs, count - 1, num);
	// 수식 2 계산
	int val2 = evaluate(coeffs_2, count_2 - 1, num);
	// 수식 1 + 2 계산
	int val_sum = evaluate(sum, maximum - 1, num);
	// 수식 1 * 2 계산
	int val_multi = evaluate(multi, multi_size - 1, num);

	printf("수식1 = %d, 수식2 = %d, 수식1+2 = %d, 수식1*2 = %d\n", val1, val2, val_sum, val_multi);

	free(coeffs);
	free(coeffs_2);
	return 0;
}
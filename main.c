#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main() {
	FILE *fp, *fpw;
	char fname[256] = "D:\\test_darknet-master\\darknet-master\\build\\darknet\\x64\\results\\results.txt";
	char fnamew[100] = "result.txt";
	char line[512];
	int lines = 0;
	char* word[50];
	int count[6] = { 0,0,0,0,0,0 };
	int idx = 0;
	int sum_count = 0;

	word[0] = "drugstore";
	word[1] = "factory";
	word[2] = "hospital";
	word[3] = "house";
	word[4] = "policeman";
	word[5] = "ship";

	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		return 0;
	}
	
	while (fgets(line, sizeof(line), fp)) {
		lines++;
		if (strstr(line, word[0])) count[0]++;
		else if (strstr(line, word[1])) count[1]++;
		else if (strstr(line, word[2])) count[2]++;
		else if (strstr(line, word[3])) count[3]++;
		else if (strstr(line, word[4])) count[4]++;
		else if (strstr(line, word[5])) count[5]++;
	}
	
	idx = get_idx(count);

	printf("lines : %d\n", lines);
	printf("predict = %s\n", word[idx]);
	fclose(fp);

	if ((fp = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "파일을 쓰기 전용으로 열 수 없습니다.");
		return 0;
	}

	if ((fpw = fopen(fnamew, "w+")) == NULL) {
		fprintf(stderr, "result.txt파일 쓰기 불가");
		return 0;
	}

	sum_count += count[0];
	sum_count += count[1];
	sum_count += count[2];
	sum_count += count[3];
	sum_count += count[4];
	sum_count += count[5];

	printf("sum : %d", sum_count);

	if (sum_count >= 1) {
		fprintf(fpw, word[idx]);
	}
	else {
		fprintf(fpw, "null");
	}
	
	fprintf(fp, "");

	fclose(fpw);
	fclose(fp);

	return 0;
}

int get_idx(int *a) {
	int max_idx = 0;
	int max_value = 0;
	int tmp, k, i, j;
	for (k = 0; k < 6; k++) {
		for (i = 0; i < 6; i++) {
			if (max_value < a[i]) {
				max_value = a[i];
			}
		}
	}

	for (i = 0; i < 6; i++) {
		if (a[i] == max_value) {
			max_idx = i;
			break;
		}
	}

	for (k = 0; k < 6; k++) {
		printf("%d\n", a[k]);
	}


	printf("max_idx = %d\n", max_idx);

	return max_idx;
}
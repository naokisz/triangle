#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {

	int number, layer = 0, start = -1, goal = -1, step = -1;
	int pow_tmp, rand_tmp;

	srand(time(NULL));

	for(;;) {
		printf("何層の三角形を積んだ三角形にしますか？＞");
		scanf("%d", &layer);
		while(getchar() != '\n') { }
		if(layer > 0) break;
	}

	for(;;) {
		printf("スタートする番号を入力してください。ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &start);
		while(getchar() != '\n') { }

		if(start == 0) {
			start = rand() % (pow(layer, 2) + 1);
		}
		number = start;

		if(start > -1) break;
	}

	for(;;) {
		printf("ゴールの番号を入力してください。ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &goal);
		while(getchar() != '\n') { }

		if(goal == 0) {
			goal = rand() % (pow(layer, 2) + 1);
		}

		if(goal > -1) break;
	}

	for(;;) {
		printf("何ステップ動かしますか？ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &step);
		while(getchar() != '\n') { }
		
		if(step == 0) {
			step = rand();
		}

		if(step > -1) break;
	}

	for(i = 0; i < step; i++) {

		/*三角形の頂点にいたら、決まった場所に移動する。*/
		if(number == 1) number = 3;

		else if(number == pow(layer, 2)) {
			number = pow(layer, 2) - 1;
		}

		else if(number == (pow(layer - 1, 2) + 1)) {
			number = pow(layer - 1, 2) + 1;
		}

		/*三角形の端にいたら、動ける場所を制限される。*/
		for(j = 1; j <= layer; j++) {

			pow_tmp = pow(i, 2);

			if(number == pow_tmp) {

				rand_tmp = rand() % 2;

				if(rand_tmp == 0) {
					number = number - 1;
					break;
				}

				if else(rand_tmp == 1) {
					number = number + pow_tmp + 1;
					break;
				}
			}

			else if(number == pow_tmp + 1) {
				
				rand_tmp = rand() % 2;

				if(rand_tmp == 0) {
					number = number + 

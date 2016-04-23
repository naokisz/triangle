#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int main(int argc, char *argv[]) {

	if(argc == 2 && strcmp(argv[1], "--help") == 0) {

		printf("ヘルプ\n\n");
		printf("このプログラムについて\n");
		printf("（確か）東大のある入試問題をパソコンで解こうとしてみただけです。\n\n");
		printf("オプション\n");
		printf("--help：このヘルプを表示します。\n");
		printf("-l, --layer：何層の三角形か指定する。\n");
		printf("-s, --start：スタートする番号を指定する。\n");
		printf("-g, --goal：ゴールする番号を指定する。\n");
		printf("-sp, --step：1回でどのくらい動くのか指定する。\n");
		printf("-t, --times：何回動かすのか指定する。\n");
		printf("--show-number：動いた場所の数字を表示する。\n");

		return 0;
	}

	int layer = -1, number, start = -1, goal = -1, step = -1;
	int try_times = -1, pow_tmp, rand_tmp, reached_times = 0;
	int i, j, k, show_number = 0;
	double probability = 0;

	srand(time(NULL));

	for(i = 1; i < argc; i++) {
		if(strcmp(argv[i], "--show-number") == 0) {
			show_number = 1;
			break;
		}
	}

	for(;;) {

		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-l") == 0
				|| strcmp(argv[i], "--layer") == 0) {

				layer = atoi(argv[i + 1]);
				goto finish_layer;
			}
		}

		printf("何層の三角形を積んだ三角形にしますか？");
		printf("ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &layer);
		while(getchar() != '\n') { }

		if(layer == 0) {
			/*46340:int型で2乗してもオーバーフローしない限界*/
			layer = (int)(((double)rand() / RAND_MAX) * 46340) + 1;
			printf("%d層\n", layer);
		}

		if(layer > -1) break;

		printf("もう一度入力してください。\n");
	}

	finish_layer:

	for(;;) {

		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-s") == 0 ||
				strcmp(argv[i], "--start") == 0) {

				start = atoi(argv[i + 1]);
				if(start <= pow(layer, 2) && start >= 1) {
					number = start;
					goto finish_start;
				} else {
					printf("引数エラー：start ");
					printf("有効な数字を入力してください。\n");
					goto error_start;
				}
			}
		}
				
		error_start:

		printf("スタートする番号を入力してください。");
		printf("ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &start);
		while(getchar() != '\n') { }

		if(start == 0) {
			start = (int)(((double)rand() / RAND_MAX) * pow(layer, 2)) + 1;
			printf("%d\n", start);
		}

		if(start > -1 && start <= pow(layer, 2)) break;

		printf("もう一度入力してください。\n");
	}

	finish_start:

	for(;;) {

		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-g") == 0 || 
				strcmp(argv[i], "--goal") == 0) {

				goal = atoi(argv[i + 1]);
				if(goal <= pow(layer, 2) && goal >= 1)
					goto finish_goal;
				else  {
					printf("引数エラー：goal ");
					printf("有効な数字を入力してください。\n");
					goto error_goal;
				}
			}
		}

		error_goal:

		printf("ゴールの番号を入力してください。");
		printf("ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &goal);
		while(getchar() != '\n') { }

		if(goal == 0) {
			goal = (int)(((double)rand() / RAND_MAX) * pow(layer, 2)) + 1;
			printf("%d\n", goal);
		}

		if(goal > -1 && goal <= pow(layer, 2)) break;

		printf("もう一度入力してください。\n");
	}

	finish_goal:

	for(;;) {

		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-sp") == 0
				|| strcmp(argv[i], "--step") == 0) {

				step = atoi(argv[i + 1]);
				goto finish_step;
			}
		}

		printf("一回で何ステップ動かしますか？");
		printf("ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &step);
		while(getchar() != '\n') { }

		if(step == 0) {
			step = rand();
			printf("%dステップ\n", step);
		}


		if(step > -1) break;

		printf("もう一度入力してください。\n");
	}

	finish_step:

	for(;;) {

		for(i = 1; i < argc; i++) {
			if(strcmp(argv[i], "-t") == 0
				|| strcmp(argv[i], "--times") == 0) {

				try_times = atoi(argv[i + 1]);
				goto finish_times;
			}
		}

		printf("何回実行しますか？");
		printf("ランダムに決めても良い場合は０を入力してください。＞");
		scanf("%d", &try_times);

		if(try_times == 0) {
			try_times = rand();
			printf("%d回\n", try_times);
		}

		if(try_times > -1) break;

		printf("もう一度入力してください。\n");
	}

	finish_times:

	for(i = 0; i < try_times; i++) {

		number = start;

		for(j = 0; j < step; j++) {

			/*三角形の頂点にいたら、決まった場所に移動する。*/
			if(layer == 1 && number == 1) goto continue_step;
			else if(number == 1) {
				number = 3;
				goto continue_step;
			}
			else if(layer == 2 && number == 4) {
				number--;
				goto continue_step;
			}


			/*1の時の処理をforで回さないと
				2の時の処理が出来ないのでここに書く*/
			if(layer == 2 && number == 2) {
				number++;
				goto continue_step;
			}
			else if(number == 2) {

				rand_tmp = rand() % 2;

				if(rand_tmp == 0) {
					number++;
					goto continue_step;
				}

				else if(rand_tmp == 1) {
					number = 6;
					goto continue_step;
				}
			}

			else if(number == pow(layer, 2)) {
				number = pow(layer, 2) - 1;
				goto continue_step;
			}

			else if(number == (pow(layer - 1, 2) + 1)) {
				number = pow(layer - 1, 2) + 2;
				goto continue_step;
			}

			/*三角形の端にいたら、動ける場所を制限される。*/
			for(k = 2; k <= layer; k++) {

				pow_tmp = pow(k, 2);

				if(number == pow_tmp) {

					rand_tmp = rand() % 2;

					if(rand_tmp == 0) {
						number--;
						goto continue_step;
					}

					else if(rand_tmp == 1) {
						number += pow_tmp - pow(k - 1, 2) + 1;
						goto continue_step;
					}
				}

				else if(number == pow_tmp + 1) {

					rand_tmp = rand() % 2;

					if(rand_tmp == 0) {
						number++;
						goto continue_step;
					}

					else if(rand_tmp == 1) {
						number += (pow(k + 1, 2) - pow(k, 2)) + 1;
						goto continue_step;
					}
				}
			}

			/*三角形の下端*/
			for(k = pow(layer - 1, 2) + 1; k < pow(layer, 2); k += 2) {

				if(number == k) {

					rand_tmp = rand() % 2;

					if(rand_tmp == 0) {
						number--;
						goto continue_step;
					}

					else if(rand_tmp == 1) {
						number++;
						goto continue_step;
					}
				}
			}

			/*三方向どこにも動ける三角形*/
			rand_tmp = rand() % 3;

			if(rand_tmp == 0) {
				number--;
				goto continue_step;
			}

			else if(rand_tmp == 1) {
				number++;
				goto continue_step;
			}

			/*XXX:予想以上にゴリ押しなコードになったので要修正?*/
			else if(rand_tmp == 2) {

				/*numberの一個前の右端の数を求める。*/
				for(k = 1; k < number; k++) {
					pow_tmp = pow(k, 2);
					if(pow_tmp > number) {
						pow_tmp = pow(k - 1, 2);
						break;
					}
				}

				/*三角形が上向き、下向きかで動きを決める*/
				if(((number - (pow_tmp + 1)) % 2) == 0) {
					number += (pow(k, 2) - pow(k - 1, 2)) + 1;
					goto continue_step;
				}
				else if(((number - (pow_tmp + 1)) % 2) == 1) {
					number -= (pow(k - 1, 2) - pow(k - 2, 2)) + 1;
					goto continue_step;
				}
			}

			continue_step:
			if(show_number) printf("%d\n", number);
			continue;
		}

		if(number == goal) {
			reached_times++;
			if(!show_number) {
				printf("ゴールに到達しました。\n");
			}
		}

		probability = (double)reached_times / (double)i;
		if(!show_number) {
			printf("試行回数：%d回 ゴールに到達した回数：%d回 確率：%.15lf\n"
				, i + 1, reached_times, probability);
		}
	}

	if(!show_number) {
		printf("試行が終了しました。\n");
	}

	return 0;
}


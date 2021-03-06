#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <softPwm.h>

#define GREEN 23
#define YELLOW 24
#define RED 21
#define switch_green 18
#define switch_yellow 25
#define switch_red 20


int main(void)
{
	wiringPiSetupGpio();
	unsigned int checktimebefore;
	unsigned int checktime;
	int num;
	int score = 0;
	int fail = 0;

	pinMode(GREEN, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(switch_green, INPUT);
	pinMode(switch_yellow, INPUT);
	pinMode(switch_red, INPUT);

	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, LOW);

	printf("2021-2 Mechatronics Problem #4\n");
	fflush(stdout);
	printf("---------------------------\n");
	fflush(stdout);
	printf("GAME START\n-----------------------------");
	fflush(stdout);
	delay(2000);
	printf("\n");


	checktimebefore = millis();

re:

	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, LOW);

	num = rand() % 3;

	if (num == 0)
	{
		printf("GREEN BLINK\t");
		fflush(stdout);
		digitalWrite(GREEN, HIGH);
		delay(300);

		while (1)
		{
			checktime = millis();

			if (digitalRead(switch_green) == HIGH)
			{
				score += 1;
				printf("Score : %d\tFail : %d\n", score, fail);
				checktimebefore = checktime;
				goto re;
			}
			else if (digitalRead(switch_red) == HIGH || digitalRead(switch_yellow) == HIGH)
			{
				fail += 1;
				if (fail == 5)
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					goto finished;
				}
				else
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					checktimebefore = checktime;
					goto re;
				}
			}
			else if (checktime - checktimebefore >= 1000)
			{
				fail += 1;
				if (fail == 5)
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					goto finished;
				}
				else
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					checktimebefore = checktime;
					goto re;
				}

			}

		}

	}

	if (num == 1)
	{
		printf("YELLOW BLINK\t");
		fflush(stdout);
		digitalWrite(YELLOW, HIGH);
		delay(300);

		while (1)
		{
			checktime = millis();

			if (digitalRead(switch_yellow) == HIGH)
			{
				score += 1;
				printf("Score : %d\tFail : %d\n", score, fail);
				checktimebefore = checktime;
				goto re;
			}
			else if (digitalRead(switch_red) == HIGH || digitalRead(switch_green) == HIGH)
			{
				fail += 1;
				if (fail == 5)
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					goto finished;
				}
				else
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					checktimebefore = checktime;
					goto re;
				}
			}
			else if (checktime - checktimebefore >= 1000)
			{
				fail += 1;
				if (fail == 5)
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					goto finished;
				}
				else
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					checktimebefore = checktime;
					goto re;
				}

			}

		}

	}

	if (num == 2)
	{
		printf("RED BLINK\t");
		fflush(stdout);
		digitalWrite(RED, HIGH);
		delay(300);

		while (1)
		{
			checktime = millis();

			if (digitalRead(switch_red) == HIGH)
			{
				score += 1;
				printf("Score : %d\tFail : %d\n", score, fail);
				checktimebefore = checktime;
				goto re;
			}
			else if (digitalRead(switch_green) == HIGH || digitalRead(switch_yellow) == HIGH)
			{
				fail += 1;
				if (fail == 5)
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					goto finished;
				}
				else
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					checktimebefore = checktime;
					goto re;
				}
			}
			else if (checktime - checktimebefore >= 1000)
			{
				fail += 1;
				if (fail == 5)
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					goto finished;
				}
				else
				{
					printf("Score : %d\tFail : %d\n", score, fail);
					checktimebefore = checktime;
					goto re;
				}

			}

		}

	}

finished:
	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, LOW);
	printf("------------------------------\n");
	printf("GAME OVER (Final score : %d)", score);



	return 0;
}



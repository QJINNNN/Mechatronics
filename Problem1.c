#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define LED_3 12
#define LED_6 25
#define LED_9 18


int main(void)
{
	wiringPiSetupGpio();
	unsigned int checktimebefore = millis();
	unsigned int checktime;
	unsigned int cnt = 0;

	pinMode(LED_3, OUTPUT);
	pinMode(LED_6, OUTPUT);
	pinMode(LED_9, OUTPUT);

	printf("2021-2 Mechatronics Problem #3\n");
	printf("---------------------------\n");

	while (1)
	{
		checktime = millis();
		if (checktime - checktimebefore >= 1000)
		{
			cnt += 1;

			if ((cnt % 10 == 3 || cnt % 10 == 6 || cnt % 10 == 9) && cnt / 10 != 3 && cnt / 10 != 6 && cnt / 10 != 9)
			{
				printf("Clap\t");
				fflush(stdout);
				if (cnt % 10 == 3)
				{
					digitalWrite(LED_3, HIGH);
					delay(1000);
					digitalWrite(LED_3, LOW);
				}
				else if (cnt % 10 == 6)
				{
					digitalWrite(LED_6, HIGH);
					delay(1000);
					digitalWrite(LED_6, LOW);
				}
				else if (cnt % 10 == 9)
				{
					digitalWrite(LED_9, HIGH);
					delay(1000);
					digitalWrite(LED_9, LOW);
				}
			}

			else if (cnt / 10 == 3)
			{
				if (cnt % 10 == 3 || cnt % 10 == 6 || cnt % 10 == 9)
				{
					printf("Clap Clap\t");
					fflush(stdout);

					if (cnt % 10 == 3)
					{
						digitalWrite(LED_3, HIGH);
						delay(300);
						digitalWrite(LED_3, LOW);
						delay(300);
						digitalWrite(LED_3, HIGH);
						delay(400);
						digitalWrite(LED_3, LOW);
					}
					if (cnt % 10 == 6)
					{
						digitalWrite(LED_3, HIGH);
						delay(300);
						digitalWrite(LED_3, LOW);
						delay(300);
						digitalWrite(LED_6, HIGH);
						delay(400);
						digitalWrite(LED_6, LOW);
					}
					if (cnt % 10 == 9)
					{
						digitalWrite(LED_3, HIGH);
						delay(300);
						digitalWrite(LED_3, LOW);
						delay(300);
						digitalWrite(LED_9, HIGH);
						delay(400);
						digitalWrite(LED_9, LOW);
					}
				}
				else
				{
					printf("Clap\t");
					fflush(stdout);
					digitalWrite(LED_3, HIGH);
					delay(1000);
					digitalWrite(LED_3, LOW);
				}
			}

			else if (cnt / 10 == 6)
			{
				if (cnt % 10 == 3 || cnt % 10 == 6 || cnt % 10 == 9)
				{
					printf("Clap Clap\t");
					fflush(stdout);

					if (cnt % 10 == 3)
					{
						digitalWrite(LED_6, HIGH);
						delay(300);
						digitalWrite(LED_6, LOW);
						delay(300);
						digitalWrite(LED_3, HIGH);
						delay(400);
						digitalWrite(LED_3, LOW);
					}
					if (cnt % 10 == 6)
					{
						digitalWrite(LED_6, HIGH);
						delay(300);
						digitalWrite(LED_6, LOW);
						delay(300);
						digitalWrite(LED_6, HIGH);
						delay(400);
						digitalWrite(LED_6, LOW);
					}
					if (cnt % 10 == 9)
					{
						digitalWrite(LED_6, HIGH);
						delay(300);
						digitalWrite(LED_6, LOW);
						delay(300);
						digitalWrite(LED_9, HIGH);
						delay(400);
						digitalWrite(LED_9, LOW);
					}
				}
				else
				{
					printf("Clap\t");
					fflush(stdout);
					digitalWrite(LED_6, HIGH);
					delay(1000);
					digitalWrite(LED_6, LOW);
				}
			}

			else if (cnt / 10 == 9)
			{
				if (cnt % 10 == 3 || cnt % 10 == 6 || cnt % 10 == 9)
				{
					printf("Clap Clap\t");
					fflush(stdout);

					if (cnt % 10 == 3)
					{
						digitalWrite(LED_9, HIGH);
						delay(300);
						digitalWrite(LED_9, LOW);
						delay(300);
						digitalWrite(LED_3, HIGH);
						delay(400);
						digitalWrite(LED_3, LOW);
					}
					if (cnt % 10 == 6)
					{
						digitalWrite(LED_9, HIGH);
						delay(300);
						digitalWrite(LED_9, LOW);
						delay(300);
						digitalWrite(LED_6, HIGH);
						delay(400);
						digitalWrite(LED_6, LOW);
					}
					if (cnt % 10 == 9)
					{
						digitalWrite(LED_9, HIGH);
						delay(300);
						digitalWrite(LED_9, LOW);
						delay(300);
						digitalWrite(LED_9, HIGH);
						delay(400);
						digitalWrite(LED_9, LOW);
					}
				}
				else
				{
					printf("Clap\t");
					fflush(stdout);
					digitalWrite(LED_9, HIGH);
					delay(1000);
					digitalWrite(LED_9, LOW);
				}
			}
			else if (cnt > 100)
			{
				break;
			}
			else
			{
				printf("%d\t", cnt);
				fflush(stdout);
				checktimebefore = checktime;
			}
		}
	}

	return 0;
}

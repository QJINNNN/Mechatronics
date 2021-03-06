#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define GREEN 23
#define YELLOW 24
#define RED 12
#define switch_green 18
#define switch_yellow 25
#define switch_red 20

#define MOTOR1 26
#define MOTOR2 19


int main(void)
{
	wiringPiSetupGpio();
	softPwmCreate(MOTOR1, 0, 100);
	softPwmCreate(MOTOR2, 0, 100);

	softPwmCreate(GREEN, 0, 100);
	softPwmCreate(YELLOW, 0, 100);
	softPwmCreate(RED, 0, 100);


	pinMode(switch_green, INPUT);
	pinMode(switch_yellow, INPUT);
	pinMode(switch_red, INPUT);

	softPwmWrite(MOTOR1, 0);
	softPwmWrite(MOTOR2, 0);

	softPwmWrite(GREEN, 0);
	softPwmWrite(YELLOW, 100);
	softPwmWrite(RED, 0);

	int cnt = 0;
	int rotation = 0;

	while (1)
	{
		if (digitalRead(switch_green) == HIGH)
		{
			if (cnt == 100)
			{
				continue;
			}
			else if (rotation == 0 || rotation == 1)
			{
				rotation = 1;
				cnt += 20;
				softPwmWrite(MOTOR1, cnt);
				softPwmWrite(MOTOR2, 0);
				softPwmWrite(GREEN, cnt);
				softPwmWrite(YELLOW, 0);
				softPwmWrite(RED, 0);
				delay(300);
			}
			else if (rotation == -1)
			{
				rotation = -1;
				cnt += 20;
				softPwmWrite(MOTOR1, 0);
				softPwmWrite(MOTOR2, cnt);
				softPwmWrite(GREEN, 0);
				softPwmWrite(YELLOW, 0);
				softPwmWrite(RED, cnt);
				delay(300);
			}
		}
		else if (digitalRead(switch_red) == HIGH)
		{
			if (cnt == 0)
			{
				rotation = 1;
				cnt += 20;
				softPwmWrite(MOTOR1, cnt);
				softPwmWrite(MOTOR2, 0);
				softPwmWrite(GREEN, cnt);
				softPwmWrite(YELLOW, 0);
				softPwmWrite(RED, 0);
				delay(300);
			}
			else if (rotation == 1)
			{
				rotation = -1;
				softPwmWrite(GREEN, 0);
				softPwmWrite(YELLOW, 0);
				softPwmWrite(RED, cnt);
				softPwmWrite(MOTOR1, 0);
				softPwmWrite(MOTOR2, cnt);
				delay(300);
			}
			else if (rotation == -1)
			{
				rotation = 1;
				softPwmWrite(GREEN, cnt);
				softPwmWrite(YELLOW, 0);
				softPwmWrite(RED, 0);
				softPwmWrite(MOTOR1, cnt);
				softPwmWrite(MOTOR2, 0);
				delay(300);
			}
		}
		else if (digitalRead(switch_yellow) == HIGH)
		{
			cnt = 0;
			rotation = 0;
			softPwmWrite(GREEN, 0);
			softPwmWrite(YELLOW, 100);
			softPwmWrite(RED, 0);
			softPwmWrite(MOTOR1, 0);
			softPwmWrite(MOTOR2, 0);

		}

	}

	return 0;
}


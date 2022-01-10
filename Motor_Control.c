#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <math.h>

#define LOOPTIME 10

#define ENCODER_A 24
#define ENCODER_B 23
#define ENCGEAR_1X 54
#define ENCGEAR_2X 108
#define ENCGEAR_4X 216

#define MOTOR1 20
#define MOTOR2 21

#define PGAIN 600
#define IGAIN 5
#define DGAIN 5

int n;
int encA;
int encB;
int encoderPosition = 0;
float redGearPosition = 0;
float referencePosition = 5;
float errorPosition = 0;
float interrorPosition = 0;
float diferrorPosition = 0;
float error_prev = 0;
float int_sum = 0;

unsigned int startTime;
unsigned int checkTime;
unsigned int checkTimeBefore;

void funcEncoder_1X()
{
	encA = digitalRead(ENCODER_A);
	encB = digitalRead(ENCODER_B);
	if (encA == HIGH)
	{
		if (encB == LOW)
		{
			encoderPosition--;
		}
		else
		{
			encoderPosition++;
		}
	}
	redGearPosition = (float)encoderPosition / ENCGEAR_1X;
	printf("A : %d B : %d encPos : %d gearPos : %f\n", encA, encB, encoderPosition, redGearPosition);
}

void funcEncoder_2X()
{
	encA = digitalRead(ENCODER_A);
	encB = digitalRead(ENCODER_B);
	if (encA == HIGH)
	{
		if (encB == LOW)
		{
			encoderPosition--;
		}
		else
		{
			encoderPosition++;
		}
	}
	else
	{
		if (encB == LOW)
		{
			encoderPosition++;
		}
		else
		{
			encoderPosition--;
		}
	}
	redGearPosition = (float)encoderPosition / ENCGEAR_2X;
	printf("A : %d B : %d encPos : %d gearPos : %f\n", encA, encB, encoderPosition, redGearPosition);
}

void funcEncoder_4X_A()
{
	encA = digitalRead(ENCODER_A);
	encB = digitalRead(ENCODER_B);
	if (encA == HIGH)
	{
		if (encB == LOW)
		{
			encoderPosition--;
		}
		else
		{
			encoderPosition++;
		}
	}
	else
	{
		if (encB == LOW)
		{
			encoderPosition++;
		}
		else
		{
			encoderPosition--;
		}
	}
	redGearPosition = (float)encoderPosition / ENCGEAR_4X;
	printf("A : %d B : %d encPos : %d gearPos : %f\n", encA, encB, encoderPosition, redGearPosition);
}

void funcEncoder_4X_B()
{
	encA = digitalRead(ENCODER_A);
	encB = digitalRead(ENCODER_B);
	if (encB == HIGH)
	{
		if (encA == LOW)
		{
			encoderPosition++;
		}
		else
		{
			encoderPosition--;
		}
	}
	else
	{
		if (encA == LOW)
		{
			encoderPosition--;
		}
		else
		{
			encoderPosition++;
		}
	}
	redGearPosition = (float)encoderPosition / ENCGEAR_4X;
	printf("A : %d B : %d encPos : %d gearPos : %f\n", encA, encB, encoderPosition, redGearPosition);
}

int main(void)
{
	wiringPiSetupGpio();
	startTime = millis();

	pinMode(ENCODER_A, INPUT);
	pinMode(ENCODER_B, INPUT);

	FILE* fp = fopen("/home/pi/Desktop/2021-Mechatronics/PID_control/STEPINPUT5/test.txt", "w");
	softPwmCreate(MOTOR1, 0, 100);
	softPwmCreate(MOTOR2, 0, 100);

	while (1)
	{
		printf("Choose integer(1 or 2 or 4) : ");
		scanf("%d", &n);
		if (n == 1 || n == 2 || n == 4)
		{
			break;
		}
		else
		{
			printf("Wrong input. Retry!\n");
		}
	}

	if (n == 1)
	{
		printf("1X ENCODER\n");
		wiringPiISR(ENCODER_A, INT_EDGE_RISING, funcEncoder_1X);
	}

	if (n == 2)
	{
		printf("2X ENCODER\n");
		wiringPiISR(ENCODER_A, INT_EDGE_BOTH, funcEncoder_2X);
	}

	if (n == 4)
	{
		printf("4X ENCODER\n");
		wiringPiISR(ENCODER_A, INT_EDGE_BOTH, funcEncoder_4X_A);
		wiringPiISR(ENCODER_B, INT_EDGE_BOTH, funcEncoder_4X_B);
	}

	checkTimeBefore = millis();

	int Loop_num = 1;

	while (1)
	{
		if (Loop_num > 1500)
		{
			softPwmWrite(MOTOR1, 0);
			softPwmWrite(MOTOR2, 0);
			delay(500);
			break;
		}
		checkTime = millis();
		if (checkTime - checkTimeBefore > LOOPTIME)
		{
			checkTimeBefore = checkTime;
			errorPosition = referencePosition - redGearPosition;
			if (errorPosition > 0)
			{
				softPwmWrite(MOTOR1, 0);
				softPwmWrite(MOTOR2, fabs(errorPosition * PGAIN + interrorPosition * IGAIN + diferrorPosition * DGAIN));
			}
			else
			{
				softPwmWrite(MOTOR1, fabs(errorPosition * PGAIN + interrorPosition * IGAIN + diferrorPosition * DGAIN));
				softPwmWrite(MOTOR2, 0);
			}
			interrorPosition = interrorPosition + errorPosition * (LOOPTIME * 0.001);
			diferrorPosition = (errorPosition - error_prev) / (LOOPTIME * 0.001);
			fprintf(fp, "%d\t%f\n", Loop_num, redGearPosition);
			error_prev = errorPosition;
			Loop_num = Loop_num + 1;
		}
	}
	return 0;
}


#pragma config(Sensor, S3, lightSensor, sensorLightActive)

/*
Authors: Vlad Silin, Mrigank Mehta
Date: April 4, 2014

Description: This program makes a lego NXT robot follow a black line and shoot a ball into a set of bowling pins
from a position marked by a green line
*/

task main()
{
	//Variables for calibration
	int blackAvg, blackValue, greenAvg, greenValue = 0;
	//Variable used for making sure that the robot is really on a green line
	int counter = 0;

	wait1Msec(2000);

	//Calibration for black values
	for (int x= 0; x < 500; x++)
	{
		blackValue = SensorValue[lightSensor];
		if (x > 100)
			blackAvg += blackValue;
	}
	blackAvg = blackAvg/399;
	PlaySound(soundBeepBeep);
	wait1Msec(3000);

	//Calibration for green values
	for (int x= 0; x < 500; x++)
	{
		greenValue = SensorValue[lightSensor];
		if (x > 100)
			greenAvg += greenValue;
	}
	greenAvg = greenAvg/399;
	PlaySound(soundBeepBeep);
	wait1Msec(3000);

	//Main program loop
	while(true)
	{
		//Check if sensor is on black, set the motor speed accordingly
		if (SensorValue[lightSensor] > blackAvg - 3 && SensorValue[lightSensor] < blackAvg + 3)
		{
			motor[motorB] = 9;
			motor[motorC] = 30;
			counter = 0;
		}
		/*
		Checks if the sensor is reading the green values, which may mean that the robot is on a green line or that it
		is reading the value between the black and white surface
		*/
		if(SensorValue[lightSensor] > greenAvg - 3 && SensorValue[lightSensor] < greenAvg + 3)
		{
			counter ++;
			//Checks if robot is really on green
			if (counter < 840)
			{
				motor[motorB] = 30;
				motor[motorC] = 9;
			}
			else
			{
				greenLine ++;
				motor[motorB] = 0;
				motor[motorC] = 0;
				wait1Msec(1000);
				motor[motorA] = -10;
				wait1Msec(1500);
				motor[motorA] = 0;
				wait1Msec(3000);
				motor[motorA] = 70;
				wait1Msec(900);
				motor[motorA] = 0;
			}
		}
	}
}

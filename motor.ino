void setup_motors()
{
	pinMode(M0_IN1, OUTPUT);
  pinMode(M0_IN2, OUTPUT);
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);
 
	pinMode(M0_PWM, OUTPUT);
	pinMode(M1_PWM, OUTPUT);
	pinMode(M2_PWM, OUTPUT);
	pinMode(M3_PWM, OUTPUT);
}

/* moves the bot in a given direction, x and y components of velocity must be given */
void move_in_direction(int x, int y) {
	
  double val1 = (double)x + y; /* activation of wheels 2 and 4 */
  double val2 = (double)y - x; /* activation of wheels 1 and 3 */

  double maxVal = max(val1, val2);
  double convFactor = maxVal/255.0;

  if(convFactor > 1) {
    val1 /= convFactor;
    val2 /= convFactor;
  }

  setMotor(M0_IN1, M0_IN2, M0_PWM, val1); /* top right */
  setMotor(M1_IN1, M1_IN2, M1_PWM, val2); /* top left */
  setMotor(M2_IN1, M2_IN2, M2_PWM, val2); /* bottom right */
  setMotor(M3_IN1, M3_IN2, M3_PWM, val1); /* bottom left */
}

// to set motor direction and speed using PWM
void setMotor(int in1, int in2, int pwmChannel, int speed) {
  speed = constrain(speed, -255, 255);
  int pwmSpeed = abs(speed);

  if (speed > 0) {							/* one direction */
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
	else if (speed < 0) {					/* other direction */
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else        /* off */
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  /* set pwm speed */
  analogWrite(pwmChannel, pwmSpeed);
}

/* stop the bot */
void stopMotors() {
  setMotor(M0_IN1, M0_IN2, M0_PWM, 0);
  setMotor(M1_IN1, M1_IN2, M1_PWM, 0);
  setMotor(M2_IN1, M2_IN2, M2_PWM, 0);
  setMotor(M3_IN1, M3_IN2, M3_PWM, 0);
}

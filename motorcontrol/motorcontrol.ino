class MotorControl{
  private:
    int input1;//digital
    int input2;//digital
    int pwm;//pwm

  public:
    MotorControl(int input1, int input2, int pwm){
      this -> input1 = input1;
      this -> input2 = input2;
      this -> pwm = pwm;

      pinMode(input1, OUTPUT);
      pinMode(input2, OUTPUT);
      pinMode(pwm, OUTPUT);
    }
    void go(int power){
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      analogWrite(pwm, power);
    }
    void back(int power){
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
      analogWrite(pwm, power);
    }
    void stop(){
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      analogWrite(pwm, 0);
    }
    void changePower(int power){
      analogWrite(pwm, power);
    }
};

// 모터 인스턴스 생성 (핀 번호와 PWM 핀 번호 지정 필요)
MotorControl leftMotor(22, 23, 5); // 왼쪽 모터를 위한 핀 설정
MotorControl rightMotor(24, 25, 6); // 오른쪽 모터를 위한 핀 설정

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftMotor.go(20);
  rightMotor.go(20);
  Serial.print("asdf");
  delay(1000);

  leftMotor.stop();
  rightMotor.stop();

  delay(1000);
}

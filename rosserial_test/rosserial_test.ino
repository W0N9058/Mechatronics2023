#include <ros.h>
#include <std_msgs/Int32.h>

// ROS NodeHandle
ros::NodeHandle nh;

// 포텐시오미터 메시지와 퍼블리셔 선언
std_msgs::Int32 pot_msg;
ros::Publisher pot_pub("angle_topic", &pot_msg);

// 키보드 입력 메시지와 구독자 선언
std_msgs::Int32 key_msg;
void keyCallback(const std_msgs::Int32 &msg);

// 포텐시오미터 핀 설정
const int potPin = A0;

MotorControl leftMotor(22, 23, 5); // 왼쪽 모터를 위한 핀 설정
MotorControl rightMotor(24, 25, 6); // 오른쪽 모터를 위한 핀 설정







void setup()
{
  // ROS 노드 초기화
  nh.initNode();
  
  // 퍼블리셔와 구독자 설정
  nh.advertise(pot_pub);
  nh.subscribe(ros::Subscriber<std_msgs::Int32>("keyboard_input", &keyCallback));
}

void loop()
{
  // 포텐시오미터 값 읽기
  int potValue = analogRead(potPin);
  
  // 메시지에 값 설정
  pot_msg.data = potValue;

  // 메시지 퍼블리시
  pot_pub.publish(&pot_msg);
  
  // ROS 핸들러 스핀
  nh.spinOnce();

  // 100ms 지연
  delay(100);
}

void keyCallback(const std_msgs::Int32 &msg)
{
  int keyValue = msg.data;
  // 받은 키보드 입력 값 처리
  switch (keyValue)
  {
    case 1:
      // 'w' 키 입력 처리 (forward)
      // 원하는 동작 수행
      MotorControl.go(500);

      break;
    case 2:
      // 'a' 키 입력 처리 (left)
      // 원하는 동작 수행
      break;
    case 3:
      // 's' 키 입력 처리 (backward)
      // 원하는 동작 수행
      MotorControl.stop();
      break;
    case 4:
      // 'd' 키 입력 처리 (right)
      // 원하는 동작 수행
      break;
    default:
      // 기타 입력 처리
      break;
  }
}


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
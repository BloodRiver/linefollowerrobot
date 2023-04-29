#define IR1     A1
#define IR2     A2
#define IR3     A3
#define IR4     A4
#define IR5     A5

#define IN1     8
#define IN2     9
#define IN3     10
#define IN4     11
#define ENA     3
#define ENB     5

bool ir1, ir2, ir3, ir4, ir5;
const int forward_speed = 80;
const int turn_speed = 55;
int left = forward_speed, right = forward_speed;
char last_turn = 'F';
bool forward = true;

void rotate_motor()
{
  analogWrite(ENA, left);
  analogWrite(ENB, right);

  if (forward)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  ir1 = digitalRead(A1);
  ir2 = digitalRead(A2);
  ir3 = digitalRead(A3);
  ir4 = digitalRead(A4);
  ir5 = digitalRead(A5);

  
  if (!(ir1 || ir2 || ir3 || ir4 || ir5))  // if none or all of the sensors detect black line
  {
    last_turn = 'r';
  }
  else if (ir1 && ir2 && ir3 && ir4 && ir5)
  {
    last_turn = 'B';
  }
  else if (!ir5)
  {
    last_turn = 'R';
  }
  else if (!ir4)
  {
    last_turn = 'r';
  }
  else if (!ir1)
  {
    last_turn = 'L';
  }
  else if (!ir2)
  {
    last_turn = 'l';  
  }
  else if (!ir3)
  {
    last_turn = 'F';
  }

  forward = true;
  if (last_turn == 'F')
  {
    left = forward_speed;
    right = forward_speed;
  }
  else if (last_turn == 'B')
  {
    left = forward_speed * -1;
    right = forward_speed * -1;
    forward = false;
  }
  else if (last_turn == 'l')
  {
    left = turn_speed;
    right = forward_speed;
  }
  else if (last_turn == 'L')
  {
    left = 0;
    right = forward_speed;
  }
  else if (last_turn == 'r')
  {
    right = turn_speed;
    left = forward_speed;
  }
  else if (last_turn == 'R')
  {
    right = 0;
    left = forward_speed;
  }

  rotate_motor();

}

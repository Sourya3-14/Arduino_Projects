#include <VirtualWire.h>
//z values are commented out as they are not used in this project
#define x A0
#define y A1
// #define z A2

char *data;

int x_val;
int y_val;
// int z_val;
int a=30;
int x_val2;
int y_val2;
// int z_val2;

void setup() 
{
  vw_set_tx_pin(12);
  vw_setup(2000);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  //pinMode(z, INPUT);
  Serial.begin(9600);

  //This will creatw problems if while switching on the remote you tilt it
  // x_val2 = analogRead(x);
  // y_val2 = analogRead(y);
  // z_val2 = analogRead(z);

  // Check stable conddition values and asign those here
  x_val2=335;
  y_val2=335;

  vw_send((uint8_t *)data, strlen("s"));
  vw_wait_tx();
  delay(500);
}

void loop()
{
  x_val = analogRead(x);
  y_val = analogRead(y);
  // z_val = analogRead(z);
  Serial.println(x_val);
  Serial.println(y_val);


  int x_axis = x_val - x_val2;
  int y_axis = y_val - y_val2;
  // int z_axis = z_val - z_val2;
  
  if(y_axis >= a)
  {
    data="f";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Forward");
  }
  else if(y_axis <= -a)
  {
    data="b";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Backward");
  }
  else if(x_axis >= a)
  {
    data="r";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Right");
  }
  else if(x_axis <= -a)
  {
    data="l";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Left");
  }
  else
  {
    data="s";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(500);
    Serial.println("Stop");
  }
}

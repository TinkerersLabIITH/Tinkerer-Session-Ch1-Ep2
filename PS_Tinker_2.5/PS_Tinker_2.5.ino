void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(34,INPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  int ra1= analogRead(34);
  Serial.println(ra1);

 
}

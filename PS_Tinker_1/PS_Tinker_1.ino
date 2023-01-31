 
const int LEDPIN = 12; 

const int PushButton =14;
 
void setup()
{

pinMode(LEDPIN, OUTPUT);

pinMode(PushButton, INPUT);
}

void loop()

{

int Push_button_state = digitalRead(PushButton);

if ( Push_button_state == HIGH )
{ 
digitalWrite(LEDPIN, HIGH); 
}
else 
{
digitalWrite(LEDPIN, LOW); 
}
}

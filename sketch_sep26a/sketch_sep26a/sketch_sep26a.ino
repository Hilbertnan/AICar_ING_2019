int comdata;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    comdata = Serial.read();
    Serial.println(comdata);
  }
}

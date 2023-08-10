String x = "";
String InputData = "";
bool Data = false;
void setup()
{
  Serial.begin(9600);
}
void loop() 
{
  Event();
  if(Data==true)
  {
    if(x == "a")
    {
    Serial.println("Xin chào");
    }
    else if (x == "b")
    {
    Serial.println("Tạm biệt");
    }
    Data = false;
    x = "";
    InputData = "";
  }
}
void Event()
{
  Serial.flush();
  while(Serial.available())
  {
    char in = Serial.read();
    if(in == '\n')
    {
      Data = true;
      x = InputData;
    }
    else
    {
      InputData = in;
    }
  }
}

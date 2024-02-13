void h_switch()//switch
{
  LoginContr();
  String message = F("ok");
  uint16_t resp = 200;
  String argName, argValue;
  for (byte i = 0; i < server.args(); i++)
  {
    argName = server.argName(i);
    //Serial.print(argName);
    //Serial.print("=");
    argValue = server.arg(i);
    //Serial.println(argValue);

    if (argName == F("range1")) {
      range1 = argValue.toInt();
    }
    else if (argName == F("range2")) {
      range2 = argValue.toInt();
    }

    
    else if (argName == F("stop")) {
    /*  analogWrite(swt1_pin, 0);
      analogWrite(swt2_pin, 0);
      analogWrite(swt3_pin, 0);
      analogWrite(swt4_pin, 0);*/

    }

  }
  server.send(resp, F("text/html"), message);
}
//----------------------------------------------------------------------------------------------

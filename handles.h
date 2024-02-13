void LoginContr()
{
  if (AccessMode == true)
  {
    char _AccessLogin[sizeof(AccessLogin)], _AccessPassword[sizeof(AccessPassword)];
    AccessLogin.toCharArray(_AccessLogin, sizeof(_AccessLogin));
    AccessPassword.toCharArray(_AccessPassword, sizeof(_AccessPassword));
    if (!server.authenticate(_AccessLogin, _AccessPassword)) return server.requestAuthentication();
  }
}
//---------------------------------------------------------------------------

String textStyle()
{
  String message;

  message = F(".textStyle1 {");
  message += F("width: 25px; height: 20px; text-align: center;");
  message += F("text-align: center;");
  message += F("}");
  message += F(".textStyle2 {");
  message += F("width: 45px; height: 20px; text-align: center;");
  message += F("text-align: center;");
  message += F("}");
  message += F(".textStyle3 {");
  message += F("width: 130px; height: 20px; text-align: left;");
  message += F("text-align: center;");
  message += F("}");

  return message;
}
//--------------------------------------------
void handleRoot()
{
  LoginContr();
  direct =0;
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<title>ШИМ на ESP</title>");
  message += F("<style type=\"text/css\">");
  message += F(".menu_but {width: 200px; text-align: center; padding: 5px;}");
  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  
  message += F("</script>\n");
  message += F("</head>\n");
  message += F("<body>\n");
  message += F("<form>\n");
  message += F("<h3>ШИМ v.1.0</h3><p>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjOtb\" value=\"Управление\" onclick=\"location.href='/direct1';\" /><br>\n");
  message += F("<p>");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjWifi\" value=\"Настройки\" onclick=\"location.href='/wifi';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjDevPrg\" value=\"Обновление прошивки\" onclick=\"location.href='/update';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Менеджер файлов\" onclick=\"location.href='/spiffs';\" /><br>\n");
  message += F("<p>");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Перезагрузка\" id=\"butt_reboot\" onclick=\"if (confirm('Перезагрузить модуль?') == true) location.href='/reboot'\" /><br>\n");
  message += F("</form>\n");
  message += F(" </body>\n");
  message += F(" </html>\n");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------
void h_save() //save
{
  LoginContr();
  String argName, argValue;
  Serial.println("module save");
  Serial.print("args()=");
  Serial.println(server.args());
  for (byte i = 0; i < server.args(); i++)
  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print("=\"");
    argValue = server.arg(i);
    Serial.print(argValue);
    Serial.println("\"");

    if (argName == F("ssid"))                  ssid = argValue;
    else if (argName == F("password"))     password = argValue;
    else if (argName == F("AccessLogin"))     AccessLogin = argValue;
    else if (argName == F("AccessPassword"))     AccessPassword = argValue;

    else if (argName == F("ip1"))               ip1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip2"))               ip2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip3"))               ip3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip4"))               ip4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("ms1"))               ms1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms2"))               ms2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms3"))               ms3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms4"))               ms4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("gt1"))               gt1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt2"))               gt2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt3"))               gt3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt4"))               gt4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("dn1"))               dn1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn2"))               dn2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn3"))               dn3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn4"))               dn4 = constrain(argValue.toInt(), 0, 255);

    
  }
  writeConfig();
  
  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /index.html\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Настройи сохранены успешно.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/index.html\">сюда</a> для перехода в главное меню.");
  message += F("</body>");
  message += F("</html>");

  server.send(200, F("text/html"), message);

}
//---------------------------------------------------------------------------------

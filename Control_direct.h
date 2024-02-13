
//-----------------------------------------------------------------------------
void h_direct1() {//direct
  LoginContr();
  direct = 1;
  String message;
  message =  F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<title>ШИМ Управление</title>");

  message += F("<style type=\"text/css\">");
  message += F(".slider-wrapper { display: inline-block; width: 20px; height: 350px;  padding: 0;}");
  message += F(".slider-wrapper input {width: 350px; height: 20px; margin: 0; transform-origin: 160px 150px; transform: rotate(-90deg)}");
  message += F(".column-2 {width: 50px; text-align: center; vertical-align: middle;}");
  message += F("</style>");

  message += F("<script type=\"text/javascript\">");
  message += F("function openUrl(url) {\n");
  message +=  F("var request = new XMLHttpRequest();\n");
  message +=  F("request.open('GET', url, true);\n");
  message +=  F("request.send(null);\n ");
  message += F("};\n ");
  message += F("function updControls(){\n");
  message +=  F("openUrl('/switch?range1=' + document.getElementById('range1').value+'&range2='+document.getElementById('range2').value);\n");
  message +=  F("document.getElementById('str1').innerHTML = document.getElementById('range1').value;\n");
  message +=  F("document.getElementById('str2').innerHTML = document.getElementById('range2').value;\n");
  message += F("}\n");
  message += F("setInterval(updControls, 100);\n");
  message += F("</script>");

  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>ШИМ Управление</h3><p>");

  message += F("<table cellspacing=\"1\" border=\"0\">");
  
  message += F("<tr>");
  message +=  F("<td class=\"column-2\">");
  message +=  F("</td>");
  
  message +=  F("<td class=\"column-2\">");
  message += F("<span id=\"str1\">.</span> </p>\n");
  message +=  F("</td>");
    message +=  F("<td class=\"column-2\">");
  message +=  F("</td>");

  message +=  F("<td class=\"column-2\">");
  message += F("<span id=\"str2\">.</span> </p>\n");
  message +=  F("</td>");
  message += F("</tr>");

  message += F("<tr>");
    message +=  F("<td class=\"column-2\">");
  message +=  F("</td>");

  message +=  F("<td class=\"column-2\">");
  message += F("<div class=\"slider-wrapper\">");
  message += F("<input type=\"range\" id=\"range1\" min=\"0\" max=\"1023\" value=\"0\" step=\"1\">");
  message += F("</div>");
  message +=  F("</td>");
    message +=  F("<td class=\"column-2\">");
  message +=  F("</td>");

  message +=  F("<td class=\"column-2\">");
  message += F("<div class=\"slider-wrapper\">");
  message += F("<input type=\"range\" id=\"range2\" min=\"0\" max=\"1023\" value=\"0\" step=\"1\">");
  message += F("</div>");
  message +=  F("</td>");
  message += F("</tr>");

  message += F("</table>");
message += F("<p>");
message += F("<input type=\"button\" value=\"Стоп\" onclick=\"document.getElementById('range1').value=0;document.getElementById('range2').value=0;\"><p>");
  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\">");
  message += F("</form>");
  message += F("</body>");
  message += F("</html>");
  server.send(200, "text/html", message);
}
//-----------------------------------------------------------------------------
void working_direct1() {
  if (prev_range1 != range1) {
      analogWrite(swt1_pin, range1);
    prev_range1 = range1;
    Serial.print(F("r1 = "));
    Serial.println(range1);
    
  }
  if (prev_range2 != range2) {
      analogWrite(swt2_pin, range2);
    prev_range2 = range2;
    Serial.print(F("r2 = "));
    Serial.println(range2);
    
  }


}
//-----------------------------------------------------------------------------
void working_stop() {
  analogWrite(swt1_pin, 0);
  analogWrite(swt2_pin, 0);

}
//--------------------------------------

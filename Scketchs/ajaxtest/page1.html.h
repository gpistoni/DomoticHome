
// use this tools
// https://www.willpeavy.com/minifier/
// http://tomeko.net/online_tools/cpp_text_escape.php?lang=en


const char HTML_page1[] PROGMEM  = 
"<!DOCTYPE html><html> <head> <script>function GetArduinoInputs() { nocache = \"&nocache=\" + Math.random() * 1000000; var request = new XMLHttpRequest(); request.onreadystatechange = function(){ if (this.readyState == 4) { if (this.status == 200) { document.getElementById(\"V1\").innerHTML = this.responseXML.getElementsByTagName('value1')[0].childNodes[0].nodeValue; document.getElementById(\"V2\").innerHTML = this.responseXML.getElementsByTagName('value2')[0].childNodes[0].nodeValue; document.getElementById(\"V3\").innerHTML = this.responseXML.getElementsByTagName('value3')[0].childNodes[0].nodeValue; } } } request.ontimeout = function(){document.getElementById(\"xmlID\").innerHTML = \"?\";} request.open(\"GET\", \"ajax\" + nocache, true); request.send(); /*request.timeout = 1000;*/ setTimeout('GetArduinoInputs()', 5000); } </script> </head> <body onload=\"GetArduinoInputs()\"> <title>Ajax with eXML</title> <h1>-HOME-</h1> <div class=\"xml\" id=\"xmlID\"> </div> <h1>-val-</h1> <span id=\"va\"> ..... </span> <h1>-tab-</h1><div class=\"table\"> <div class=\"row\"><div class=\"bars\">Cucina </div> <div class=\"bars\" id=\"V1\">0</div></div><br> <div class=\"row\"><div class=\"bars\">Sala </div> <div class=\"bars\" id=\"V2\">0</div></div><br> <div class=\"row\"><div class=\"bars\">Bagno </div> <div class=\"bars\" id=\"V3\">0</div></div><br> </div> </body></html>"
;



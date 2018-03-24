const char HTML_page1[] = "<!DOCTYPE html><html xmlns='http://www.w3.org/1999/xhtml' dir='ltr'>"
         "<head>"
         "<meta http-equiv='refresh' content='4';url='http://192.168.1.202/' >"
         "<title>Home</title>";

/*
"=====(e
<!DOCTYPE html>
<html>
    <head>
	  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>Ajax with XML</title>
        <script>		
		function Update( Url, Element )
        {
			var request = new XMLHttpRequest();			
			request.open("GET", Url, true);
			request.timeout = 1000;
			
            request.onload = function()
			{
                if (this.readyState == 4) {
                    if (this.status == 200) {
	                    if (this.responseXML != null) {				
                            document.getElementById(Element).innerHTML = this.responseXML.getElementsByTagName('value')[0].childNodes[0].nodeValue;
                        }
                    }
                }
            }
			
			request.ontimeout = function()
			{		
				document.getElementById(Element).innerHTML = "?";			
			}
            request.send(null);
			setTimeout(Update, 1000, Url, Element);
        }
    </script>
    </head>
	
    <body onload="
	Update( 'http://localhost:8080/Qualitron/CounterIn?get'	, 'V1' );
	Update( 'http://localhost:8080/Qualitron/CounterOut?get'	, 'V2' );
	Update( 'http://localhost:8080/Qualitron/TileQueue/Index?get'	, 'V3' )
	Update( 'http://localhost:8080/Qualitron/DefectQueue/Index?get'	, 'V4' )
	">
	
<! ************************************************************** !>
	<style>
  .table{
    width: 100%;
    background: #eeeeee;
    line-height: 32px;
    border: 1px solid black;
  }
  .bars { 
    float: left;
    height: 30px;
    line-height: 30px;
    border: 1px solid black;
    padding-left: 10px;
    padding-right: 10px;
    background: #FFFF33;
    color: #000000;
    }
  .row{
    width: 100%;
    clear: both;
  }
</style>
	<! ************************************************************** !>
        <h1>Qualitron Monitor</h1>
		<div class="table">
		<div class="row"><div class="bars">CounterIn </div><div class="bars" id="Analog0"></div><div class="bars" id="V1">0</div></div><br>
		<div class="row"><div class="bars">CounterOut </div><div class="bars" id="Analog1"></div><div class="bars" id="V2">0</div></div><br>
		<div class="row"><div class="bars">TileIndex: </div><div class="bars" id="Analog2"></div><div class="bars" id="V3">0</div></div><br>
		<div class="row"><div class="bars">DefIndex: </div><div class="bars" id="Analog3"></div><div class="bars" id="V4">0</div></div><br>
		<div class="row"><div class="bars">A4: </div><div class="bars" id="Analog4"></div><div class="bars" id="V5">0</div></div><br>
		<div class="row"><div class="bars">A5: </div><div class="bars" id="Analog5"></div><div class="bars" id="V6">0</div></div><br> 
	</div>
</html>
)=====";
*/

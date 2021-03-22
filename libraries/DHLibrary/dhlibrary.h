// Replace with your network credentials
const char* ssid = "PistoniHome";
const char* password = "giaco1iren1dario";

//declare reset function @ address 0
void(*resetFunc) (void) = 0;

uint8_t LED1pin = 2;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

//setup common
void setupWIFI(void)
{
  Serial.begin(115200);
  delay(1000);

  // Init
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);

  // Setup Connessione
  if (!WiFi.config(local_IP, gateway, subnet))
  {
    Serial.println("STA Failed to configure");
  }
  Serial.println("Connecting to single wifi..");

  // Wait for multiple connection
  Serial.print("Try to Connect to WIFI");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  unsigned long tout = millis() + 10000;
  while (WiFi.status() != WL_CONNECTED && millis() < tout)
  {
    Serial.print(".");
    digitalWrite(LED1pin, LOW);
    delay(200);
    digitalWrite(LED1pin, HIGH);
    delay(200);
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("ESP Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP());
  
}


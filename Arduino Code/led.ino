#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WS2812FX.h>

#define LED_COUNT 24
#define LED_PIN 3

const char* ssid = "WIFI-SSID";
const char* password = "WIFI-PASS";
const char* mqtt_server = "MQTT-SERVER";

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

const char* ledControlTopic = "led/addr";
const char* ledControlEffect = "led/effect";
const char* ledControlBright = "led/bright";
const char* ledControlSpeed = "led/speed";



WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  delay(10);
  Serial.println(); Serial.print("Connecting to "); Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // ... and resubscribe
      client.subscribe(ledControlTopic);
      client.subscribe(ledControlEffect);
      client.subscribe(ledControlSpeed);
      client.subscribe(ledControlBright);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void processRelayCallback(char* topic, char* command) {
          
          if(!strcmp(topic, "led/addr")){
          String r = getValue(command,',',1);
          String g = getValue(command,',',0);
          String b = getValue(command,',',2);
          int R = r.toInt();
          int G = g.toInt();
          int B = b.toInt();
          ws2812fx.setColor(R,G,B);
          ws2812fx.start();
          Serial.println(command);
          } 
          else if (!strcmp(topic, "led/effect")){
            if(!strcmp(command, "STATIC")){
              ws2812fx.setMode(FX_MODE_STATIC);
            }else if(!strcmp(command, "BLINK")){
              ws2812fx.setMode(FX_MODE_BLINK);
            }else if(!strcmp(command, "BREATH")){
              ws2812fx.setMode(FX_MODE_BREATH);
            }else if(!strcmp(command, "COLOR WIPE")){
              ws2812fx.setMode(FX_MODE_COLOR_WIPE);
            }else if(!strcmp(command, "COLOR WIPE INV")){
              ws2812fx.setMode(FX_MODE_COLOR_WIPE_INV);
            }else if(!strcmp(command, "COLOR WIPE REV")){
              ws2812fx.setMode(FX_MODE_COLOR_WIPE_REV);
            }else if(!strcmp(command, "COLOR WIPE REV INV")){
              ws2812fx.setMode(FX_MODE_COLOR_WIPE_REV_INV);
            }else if(!strcmp(command, "COLOR WIPE RANDOM")){
              ws2812fx.setMode(FX_MODE_COLOR_WIPE_RANDOM);
            }else if(!strcmp(command, "RANDOM COLOR")){
              ws2812fx.setMode(FX_MODE_RANDOM_COLOR);
            }else if(!strcmp(command, "SINGLE DYNAMIC")){
              ws2812fx.setMode(FX_MODE_SINGLE_DYNAMIC);
            }else if(!strcmp(command, "MULTI DYNAMIC")){
              ws2812fx.setMode(FX_MODE_MULTI_DYNAMIC);
            }else if(!strcmp(command, "RAINBOW")){
              ws2812fx.setMode(FX_MODE_RAINBOW);
            }else if(!strcmp(command, "RAINBOW CYCLE")){
              ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
            }else if(!strcmp(command, "SCAN")){
              ws2812fx.setMode(FX_MODE_SCAN);
            }else if(!strcmp(command, "DUAL SCAN")){
              ws2812fx.setMode(FX_MODE_DUAL_SCAN);
            }else if(!strcmp(command, "FADE")){
              ws2812fx.setMode(FX_MODE_FADE);
            }else if(!strcmp(command, "THEATER CHASE")){
              ws2812fx.setMode(FX_MODE_THEATER_CHASE);
            }else if(!strcmp(command, "THEATER CHASE RAINBOW")){
              ws2812fx.setMode(FX_MODE_THEATER_CHASE_RAINBOW);
            }else if(!strcmp(command, "RUNNING LIGHTS")){
              ws2812fx.setMode(FX_MODE_RUNNING_LIGHTS);
            }else if(!strcmp(command, "TWINKLE")){
              ws2812fx.setMode(FX_MODE_TWINKLE);
            }else if(!strcmp(command, "TWINKLE RANDOM")){
              ws2812fx.setMode(FX_MODE_TWINKLE_RANDOM);
            }else if(!strcmp(command, "TWINKLE FADE")){
              ws2812fx.setMode(FX_MODE_TWINKLE_FADE);
            }else if(!strcmp(command, "TWINKLE FADE RANDOM")){
              ws2812fx.setMode(FX_MODE_TWINKLE_FADE_RANDOM);
            }else if(!strcmp(command, "SPARKLE")){
              ws2812fx.setMode(FX_MODE_SPARKLE);
            }else if(!strcmp(command, "FLASH SPARKLE")){
              ws2812fx.setMode(FX_MODE_FLASH_SPARKLE);
            }else if(!strcmp(command, "HYPER SPARKLE")){
              ws2812fx.setMode(FX_MODE_HYPER_SPARKLE);
            }else if(!strcmp(command, "STROBE")){
              ws2812fx.setMode(FX_MODE_STROBE);
            }else if(!strcmp(command, "STROBE RAINBOW")){
              ws2812fx.setMode(FX_MODE_STROBE_RAINBOW);
            }else if(!strcmp(command, "MULTI STROBE")){
              ws2812fx.setMode(FX_MODE_MULTI_STROBE);
            }else if(!strcmp(command, "BLINK RAINBOW")){
              ws2812fx.setMode(FX_MODE_BLINK_RAINBOW);
            }else if(!strcmp(command, "CHASE WHITE")){
              ws2812fx.setMode(FX_MODE_CHASE_WHITE);
            }else if(!strcmp(command, "CHASE COLOR")){
              ws2812fx.setMode(FX_MODE_CHASE_COLOR);
            }else if(!strcmp(command, "CHASE RANDOM")){
              ws2812fx.setMode(FX_MODE_CHASE_RANDOM);
            }else if(!strcmp(command, "CHASE RAINBOW")){
              ws2812fx.setMode(FX_MODE_CHASE_RAINBOW);
            }else if(!strcmp(command, "CHASE FLASH")){
              ws2812fx.setMode(FX_MODE_CHASE_FLASH);
            }else if(!strcmp(command, "CHASE FLASH RANDOM")){
              ws2812fx.setMode(FX_MODE_CHASE_FLASH_RANDOM);
            }else if(!strcmp(command, "CHASE RAINBOW WHITE")){
              ws2812fx.setMode(FX_MODE_CHASE_RAINBOW_WHITE);
            }else if(!strcmp(command, "CHASE BLACKOUT")){
              ws2812fx.setMode(FX_MODE_CHASE_BLACKOUT);
            }else if(!strcmp(command, "CHASE BLACKOUT RAINBOW")){
              ws2812fx.setMode(FX_MODE_CHASE_BLACKOUT_RAINBOW);
            }else if(!strcmp(command, "COLOR SWEEP RANDOM")){
              ws2812fx.setMode(FX_MODE_COLOR_SWEEP_RANDOM);
            }else if(!strcmp(command, "RUNNING COLOR")){
              ws2812fx.setMode(FX_MODE_RUNNING_COLOR);
            }else if(!strcmp(command, "RUNNING RED BLUE")){
              ws2812fx.setMode(FX_MODE_RUNNING_RED_BLUE);
            }else if(!strcmp(command, "RUNNING RANDOM")){
              ws2812fx.setMode(FX_MODE_RUNNING_RANDOM);
            }else if(!strcmp(command, "LARSON SCANNER")){
              ws2812fx.setMode(FX_MODE_LARSON_SCANNER);
            }else if(!strcmp(command, "COMET")){
              ws2812fx.setMode(FX_MODE_COMET);
            }else if(!strcmp(command, "FIREWORKS")){
              ws2812fx.setMode(FX_MODE_FIREWORKS);
            }else if(!strcmp(command, "FIREWORKS RANDOM")){
              ws2812fx.setMode(FX_MODE_FIREWORKS_RANDOM);
            }else if(!strcmp(command, "MERRY_CHRISTMAS")){
              ws2812fx.setMode(FX_MODE_MERRY_CHRISTMAS);
            }else if(!strcmp(command, "HALLOWEEN")){
              ws2812fx.setMode(FX_MODE_HALLOWEEN);
            }else if(!strcmp(command, "FIRE FLICKER")){
              ws2812fx.setMode(FX_MODE_FIRE_FLICKER);
            }else if(!strcmp(command, "FIRE FLICKER SOFT")){
              ws2812fx.setMode(FX_MODE_FIRE_FLICKER_SOFT);
            }else if(!strcmp(command, "FIRE FLICKER INTENSE")){
              ws2812fx.setMode(FX_MODE_FIRE_FLICKER_INTENSE);
            }else if(!strcmp(command, "CIRCUS COMBUSTUS")){
              ws2812fx.setMode(FX_MODE_CIRCUS_COMBUSTUS);
            }else if(!strcmp(command, "BICOLOR CHASE")){
              ws2812fx.setMode(FX_MODE_BICOLOR_CHASE);
            }else if(!strcmp(command, "TRICOLOR CHASE")){
              ws2812fx.setMode(FX_MODE_TRICOLOR_CHASE);
            }
            
          } 
          else if (!strcmp(topic, "led/bright")){
            float brightnes = getValue(command,',',0).toFloat() * 100;
            int a = brightnes;
            ws2812fx.setBrightness(a);
            ws2812fx.start();
            Serial.println(a);
          }
          else if (!strcmp(topic, "led/speed")){
            float speeed = getValue(command,',',0).toFloat() * 2000;
            int a = speeed;
            ws2812fx.setSpeed(a);
            Serial.println(a);
            ws2812fx.start();
          }
          Serial.println(topic);
          
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';
  char *cstring = (char *) payload;
  Serial.print(cstring);
  Serial.println();

  processRelayCallback(topic, cstring);
}

void setup() {
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(9600);
  
  setupWiFi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  ws2812fx.init();
  ws2812fx.stop();
}

unsigned long lastMsg = 0;
void loop() {
  ws2812fx.service();
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

}

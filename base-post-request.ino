#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "http://psb19526.seedbox.io/rutorrent/plugins/httprpc/action.php";

const char* serverName = "http://psb19526.seedbox.io/rutorrent/plugins/httprpc/action.php";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected IP=");
  Serial.println(WiFi.localIP());

  Serial.println("Fetching " + url + "... ");

  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  http.addHeader("Authorization", "Basic $AUTH"); // <- replace with token

  String httpRequestData = "mode=list&cmd=d.throttle_name%3D&cmd=d.custom%3Dchk-state&cmd=d.custom%3Dchk-time&cmd=d.custom%3Dsch_ignore&cmd=cat%3D%22%24t.multicall%3Dd.hash%3D%2Ct.scrape_complete%3D%2Ccat%3D%7B%23%7D%22&cmd=cat%3D%22%24t.multicall%3Dd.hash%3D%2Ct.scrape_incomplete%3D%2Ccat%3D%7B%23%7D%22&cmd=d.custom%3Dx-pushbullet&cmd=cat%3D%24d.views%3D&cmd=d.custom%3Dseedingtime&cmd=d.custom%3Daddtime";

  int httpResponseCode = http.POST(httpRequestData);

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  String response = http.getString();
  const char *response1 = response.c_str();
  Serial.print("1: "); Serial.println((long) response1);

  char* response2 = strstr(response1, "Cars.2.2011.2160p.BluRay.REMUX.HEVC.TrueHD.7.1.Atmos-FGT");
  Serial.print("2: "); Serial.println((long) response2);
  char* response3 = response2;
  for (int i = 0; i < 5; i++) {
    response3 = strstr(response3+1, ",");
    Serial.print(".: "); Serial.println((long) response3);
  }
  Serial.print("3: "); Serial.println((long) response3);
  char* response4 = response3 + 2;
  Serial.print("4: "); Serial.println((long) response4);
  char* temp = strstr(response4+1, "\"");
  temp[0] ='\0';

  if (response4 == nullptr) {
    Serial.println("Search was null");
  }

  ptrdiff_t charLength = temp - response4;
  char *eptr;
  long long seeded_bytes = strtoll(response4, &eptr, 10);

  Serial.println(charLength);
  Serial.println(response4);
  Serial.println(seeded_bytes);

  http.end();

}

void loop() {
  delay(100);
}

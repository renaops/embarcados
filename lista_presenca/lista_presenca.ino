#include <Arduino.h>


#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#define MAX_LIST_SIZE 100

AsyncWebServer server(80);

const char* ssid = "";
const char* password = "";

const char* NAME_INPUT = "name_input";
const char* MAT_INPUT = "mat_input";

String attendanceNameList[MAX_LIST_SIZE];
String attendanceMatList[MAX_LIST_SIZE];
int numAttendance = 0;

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

const char* getInputHtmlContent() {
  return R"rawliteral(
  <!DOCTYPE html>
  <html lang="pt-br">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
      
      <title>Formulário de Presença</title>
  </head>
  <body>

      <h2>Formulário de Presença | INF 351</h2>

        <form action="/get" style="padding: 30px;">
          <div class="form-group">
            <label for="name_input">Nome</label>
            <input type="text" class="form-control" id="name_input" name="name_input" aria-describedby="emailHelp" placeholder="Nome Completo">
          </div>
          <div class="form-group">
            <label for="mat_input">Matricula</label>
            <input type="text" class="form-control" id="mat_input" name="mat_input" placeholder="Password">
          </div>
          <button type="submit" class="btn btn-primary">Estou aqui!</button>
        </form>

  </body>
  </html>
)rawliteral";
}

const char* createAttendanceList() {
  String table = "";
  char buffer[10];

  for (int i = 0; i < numAttendance; i++) {
    itoa(i, buffer, 10);
    table += "<tr><th scope=\"row\">" + String(buffer) + "</th><td>" + attendanceNameList[i] + "</td><td>" + attendanceMatList[i] + "</td></tr>";
  }

  return strdup(table.c_str());
}

const char* getAttendanceHtmlContent() {
  const char* attendanceList = createAttendanceList();
  
  const char* htmlContent = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
  <head>
        <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
      
    <title>INF 351</title>
  </head>
  <body>
      <div style="padding: 30px;">
      <h1>Presentes</h1>

      <button onclick="redirectToNewPage()" type="button" style="margin-bottom: 30px;" class="btn btn-primary">Registrar presença</button>

      <table class="table">
          <thead>
            <tr>
              <th scope="col">#</th>
              <th scope="col">Nome</th>
              <th scope="col">Matricula</th>
            </tr>
          </thead>
          <tbody>
      )rawliteral";
      
  const char* htmlContentEnd = R"rawliteral(
          </tbody>
        </table>
      </div>

      <script>
        function redirectToNewPage() {
            window.location.href = 'aqui';
        }
    </script>
  </body>
  </html>
  )rawliteral";
  size_t len = strlen(htmlContent) + strlen(attendanceList) + strlen(htmlContentEnd);
  char* result = (char*)malloc(len + 1);
  strcpy(result, htmlContent);
  strcat(result, attendanceList);
  strcat(result, htmlContentEnd);

  free((void*)attendanceList);

  return result;
}

String successPage() {
  return "<html> <head> </head> <style> body { text-align: center; padding: 40px 0; background: #EBF0F5; } h1 { color: #88B04B; font-family: 'Nunito Sans', 'Helvetica Neue', sans-serif; font-weight: 900; font-size: 40px; margin-bottom: 10px; } p { color: #404F5E; font-family: 'Nunito Sans', 'Helvetica Neue', sans-serif; font-size:20px; margin: 0; } i { color: #9ABC66; font-size: 100px; line-height: 200px; margin-left:-15px; } .card { background: white; padding: 60px; border-radius: 4px; box-shadow: 0 2px 3px #C8D0D8; display: inline-block; margin: 0 auto; } </style> <body> <div class='card'> <h1>Tudo Certo!</h1> <p>Sua precenca foi registrada<br/> <button type='button' style='margin-bottom: 30px;' onclick='redirectToNewPage()' class='btn btn-primary'>Volta para o Inicio</button> </div> <script> function redirectToNewPage() { window.location.href = '/'; } </script> </body></html>";
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", getAttendanceHtmlContent());
  });

  server.on("/aqui", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", getInputHtmlContent());
  });
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;

    if (request->hasParam(NAME_INPUT) && request->hasParam(MAT_INPUT)) {
      String name = request->getParam(NAME_INPUT)->value();
      String mat = request->getParam(MAT_INPUT)->value();

      attendanceNameList[numAttendance] = name;
      attendanceMatList[numAttendance] = mat;

      Serial.println(attendanceNameList[numAttendance]);
      Serial.println(attendanceMatList[numAttendance]);

      numAttendance++;
    }

    else {
      inputMessage = "Error ao registrar presença!";
      inputParam = "none";
    }

    Serial.println(inputMessage);
    request->send(200, "text/html", successPage());
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {

}


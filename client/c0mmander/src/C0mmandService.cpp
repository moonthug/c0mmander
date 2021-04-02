#include "C0mmandService.h"

C0mmandService::C0mmandService(const char* baseUrl) {
  _baseUrl = baseUrl;
  _state = READY;
}

HttpResponse * C0mmandService::_request(String path) {
  HttpResponse * response = new HttpResponse();
  
  String url = _baseUrl + path;

  Serial.println("C0mmandService: GET " + url);
  
  HTTPClient http;

  http.begin(url.c_str());

  int httpResponseCode;
  
  httpResponseCode = http.GET();

  if (httpResponseCode < 0) {
    Serial.print("C0mmandService: Error code: ");
    Serial.println(httpResponseCode);
    response->error = true;
    
    return response;
  }

  String responseBody = http.getString();
  JSONVar data = JSON.parse(responseBody);
  
  if (JSON.typeof(data) == "undefined") {
    Serial.println("C0mmandService: Parsing input failed");
    response->error = true;
    
    return response;
  }
  
  // Free resources
  http.end();

  response->error = false;
  response->data = data;

  Serial.println("C0mmandService: Response");
  Serial.println(responseBody);

  return response;
}

int C0mmandService::fetchC0mmands() {
  Serial.println("C0mmandService: fetchC0mmands() ---");

  _state = FETCHING_C0MMANDS;
  HttpResponse *response = _request("/c0mmands");

  if(response->error) {
    return 0;
  };

  _c0mmandCount = response->data["count"];
  _c0mmands = new C0mmand[_c0mmandCount];

  for(int i = 0; i < _c0mmandCount; i++) {
    C0mmand *c0mmand = new C0mmand();
    c0mmand->id = response->data["commands"][i]["id"];
    c0mmand->name = response->data["commands"][i]["name"];
    _c0mmands[i] = *c0mmand;
  }
        
  _state = FETCHING_C0MMANDS_SUCCESS;

  return _c0mmandCount;
}

String C0mmandService::executeC0mmand() {
  Serial.println("C0mmandService: executeC0mmand() ---");

  _state = EXECUTING_C0MMAND;
  _request("/c0mmands/" + String(_c0mmandId) + "/execute");
  _state = EXECUTING_C0MMAND_SUCCESS;
}

int C0mmandService::getC0mmandCount() {
  return _c0mmandCount;
}

const char * C0mmandService::getC0mmandName() {
  if (_c0mmandId >= _c0mmandCount) {
    return "No Command";
  }
  
  return (_c0mmands + _c0mmandId)->name;
}

void C0mmandService::setC0mmandId(int val) {
  _c0mmandId = val;
}

int C0mmandService::getState() {
  return _state;
}
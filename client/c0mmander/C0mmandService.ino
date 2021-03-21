#include <HTTPClient.h>
#include <Arduino_JSON.h>

const int READY = 0;
const int FETCHING_C0MMANDS = 1;
const int FETCHING_C0MMANDS_SUCCESS = 2;
const int EXECUTING_C0MMAND = 3;
const int EXECUTING_C0MMAND_SUCCESS = 4;
const int EXECUTING_C0MMAND_FAILED = 5;

class C0mmandService {
  private: 
    const char* _baseUrl;
    int _state;

    JSONVar _request(String path) {
      HTTPClient http;

      String url = this->_baseUrl + path;
      http.begin(url.c_str());

      int httpResponseCode;
      
      httpResponseCode = http.GET();

      if (httpResponseCode < 0) {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return null;
      }

      String input = http.getString();
      Serial.println(input);
      JSONVar response = JSON.parse(input);
      
      if (JSON.typeof(response) == "undefined") {
        Serial.println("Parsing input failed!");
        return null;
      }

      delay(1000);
      
      // Free resources
      http.end();

      return response;
    }
    
  public:
    C0mmandService(const char* baseUrl) {
      this->_baseUrl = baseUrl;
      this->_state = READY;
    }
    
    String fetchC0mmands() {
      this->_state = FETCHING_C0MMANDS;
      JSONVar response = this->_request("/c0mmands");

      Serial.println(response["count"]);
      Serial.println(response[0]["name"]);
      
      this->_state = FETCHING_C0MMANDS_SUCCESS;
    }

    String executeC0mmand(int id) {
      this->_state = EXECUTING_C0MMAND;
      this->_request("/c0mmands/" + String(id) + "/execute");
      this->_state = EXECUTING_C0MMAND_SUCCESS;
    }
    
    int getState() {
      return this->_state;
    }
};

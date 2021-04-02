#ifndef C0MMAND_SERVICE_H
#define C0MMAND_SERVICE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const int READY = 0;
const int FETCHING_C0MMANDS = 1;
const int FETCHING_C0MMANDS_SUCCESS = 2;
const int EXECUTING_C0MMAND = 3;
const int EXECUTING_C0MMAND_SUCCESS = 4;
const int EXECUTING_C0MMAND_FAILED = 5;

struct HttpResponse {
  bool    error;
  JSONVar data;
};

struct C0mmand {
  int           id;
  const char *  name;
};

class C0mmandService {
  private: 
    C0mmand *     _c0mmands;
    int           _c0mmandCount;
    int           _c0mmandId;
    const char *  _baseUrl;
    int           _state;

    HttpResponse *  _request(String path);
    
  public:
    C0mmandService(const char* baseUrl);

    int           fetchC0mmands();
    String        executeC0mmand();

    int           getC0mmandCount();
    const char *  getC0mmandName();
    void          setC0mmandId(int val);
    int           getState();
};

#endif
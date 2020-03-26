//
// Created by deni on 26/03/2020.
//

#ifndef TERMINAL_HTTPANSWER_H
#define TERMINAL_HTTPANSWER_H


class HTTPAnswer {
public:
    HTTPAnswer(int htCode, String payload) : htCode(htCode), payload(payload){}
    String getPayLoad();
    int getHtCode();
private:
    String payload;
    int htCode;
};


#endif //TERMINAL_HTTPANSWER_H

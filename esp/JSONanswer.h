//
// Created by deni on 26/03/2020.
//

#ifndef TERMINAL_JSONANSWER_H
#define TERMINAL_JSONANSWER_H


#include "HTTPAnswer.h"
class JSONanswer {
public:
    String httpAnswerToJson(unsigned char cmd, HTTPAnswer httpAnswer);
};


#endif //TERMINAL_JSONANSWER_H

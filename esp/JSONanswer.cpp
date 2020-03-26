//
// Created by deni on 26/03/2020.
//

#include "JSONanswer.h"

String JSONanswer::httpAnswerToJson(unsigned char cmd, HTTPAnswer httpAnswer) {
    String result = "{cmd:\"";
    result += cmd;
    result += "\",httpcode=";
    result += httpAnswer.getHtCode();
    result += ",";
    result += "{";
    result += httpAnswer.getPayLoad();
    result += "}}";
    return result;
}
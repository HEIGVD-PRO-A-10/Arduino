//
// Created by deni on 26/03/2020.
//

#include "HTTPAnswer.h"
String HTTPAnswer::getPayLoad() {
    return this->payload;
}

int HTTPAnswer::getHtCode() {
    return this->htCode;
}
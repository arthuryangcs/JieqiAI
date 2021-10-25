//
// Created by ArthurYangCS on 2021/10/14.
//

#ifndef JIEQIAI_SERVER_H
#define JIEQIAI_SERVER_H

#include "ChessServerImpl.h"
#include "search.h"
#include "base2.h"
#include "hash.h"

const int64_t INTERRUPT_COUNT = 4096; // 搜索若干结点后调用中断
bool bPonderTime;
PositionStruct posProbe;

#endif //JIEQIAI_SERVER_H

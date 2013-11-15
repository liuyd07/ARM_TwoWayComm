#ifndef __DATA_ACQUISTITION_TASK_H_
#define __DATA_ACQUISTITION_TASK_H_

#include "rfcomm.h"
#include "dscomm.h"

void copyBuffer(u8 src[], u8* srcLength, u8 dst[], u8* dstLength);
void dataAcquistTask(void);

#endif

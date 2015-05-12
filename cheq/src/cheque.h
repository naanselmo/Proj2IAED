#pragma once
#include "includes.h"

typedef struct {
    long reference;
	long value;
    long sender;
	long receiver;
} Cheque;

Cheque cheque_init(long reference, long value, long sender, long receiver);
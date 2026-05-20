#pragma once

#ifdef DECLARATION
static const int ORDER_DATATYPE = 1;
static const int ORDER_ID = 2;
static const int ORDER_EXPRESSION_START = 3;
static const int ORDER_EXPRESSION_END = 4;
#elif defined(BLOCK_PARADIGMA)
static const int ORDER_EXPRESSION_START = 1;
static const int ORDER_EXPRESSION_END = 2;
#elif defined(FOR_LOOP)
static const int ORDER_DATATYPE = 1;
static const int ORDER_ID = 2;
static const int ORDER_FROM_START = 3;
static const int ORDER_FROM_END = 4;
static const int ORDER_TO_START = 5;
static const int ORDER_TO_END = 6;
#endif
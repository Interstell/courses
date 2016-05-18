#pragma once
#include "headers.h"
#define _CRT_SECURE_NO_WARNINGS
typedef void(*print_cb)(listener_t listener, int queueNum, int num);
typedef void(*notify_addPrint_cb)(listener_t listener, int queueNum, int num);
typedef void(*notify_removePrint_cb)(listener_t listener, int queueNum, int num);
typedef void(*notify_addTransfer_cb)(listener_t listener, int queueNum, int num);
typedef void(*notify_removeTransfer_cb)(listener_t listener, int queueNum, int num);
typedef void(*notify_fullProcessing_cb)(listener_t listener, int queueNum, int num11, int num12, int num13, int num22, int num23);
typedef void(*notify_fullOverflow_cb)(listener_t listener, int queueNum, int enqueued1, int enqueued2);

void notify_addPrint1(listener_t listener, int queueNum, int elem);
void notify_addPrint2(listener_t listener, int queueNum, int elem);
void notify_removePrint1(listener_t listener, int queueNum, int elem);
void notify_removePrint2(listener_t listener, int queueNum, int elem);
void notify_addTransfer1(listener_t listener, int queueNum, int elem);
void notify_addTransfer2(listener_t listener, int queueNum, int elem);
void notify_removeTransfer1(listener_t listener, int queueNum, int elem);
void notify_removeTransfer2(listener_t listener, int queueNum, int elem);
void notify_processing1(listener_t listener, int queueNum, int num11, int num12, int num13, int num22, int num23);
void notify_processing2(listener_t listener, int queueNum, int num11, int num12, int num13, int num22, int num23);
void notify_overflow1(listener_t listener, int queueNum, int enqueued1, int enqueued2);
void notify_overflow2(listener_t listener, int queueNum, int enqueued1, int enqueued2);



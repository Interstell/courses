#pragma once
#include "headers.h"
#define _CRT_SECURE_NO_WARNINGS
typedef void(*print_cb)(listener_t listener, int queueNum, int num);
typedef void(*addPrint_cb)(listener_t listener, int queueNum, int num);
typedef void(*removePrint_cb)(listener_t listener, int queueNum, int num);
typedef void(*addPrint_transfer_cb)(listener_t listener, int queueNum, int num);
typedef void(*removePrint_transfer_cb)(listener_t listener, int queueNum, int num);
typedef void(*fullProcessing_cb)(void);
typedef void(*fullOverflow_cb)(void);

void addPrint1(listener_t listener, int queueNum, int elem);
void addPrint2(listener_t listener, int queueNum, int elem);
void removePrint1(listener_t listener, int queueNum, int elem);
void removePrint2(listener_t listener, int queueNum, int elem);
void addPrint_transfer1(listener_t listener, int queueNum, int elem);
void addPrint_transfer2(listener_t listener, int queueNum, int elem);
void removePrint_transfer1(listener_t listener, int queueNum, int elem);
void removePrint_transfer2(listener_t listener, int queueNum, int elem);





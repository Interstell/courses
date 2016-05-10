#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "sqlite3.h"
#include "file.h"

extern "C"{
#include "socket.h"
}

typedef struct database_s* database_t;
typedef struct table_s* table_t;

#include "database.hpp"
#include "server_func.hpp"
#include "table.hpp"




#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include "nlohmann/json.hpp"
#include "helpers.h"

#define MAX_REQUEST_LENGTH 4096
#define MAX_LINE_LENGTH 1024

#define MAX_USERNAME_LENGTH 128
#define MAX_PASSWORD_LENGTH 128

/**
 * @brief  Parses input from stdin and creates the request message
 * @note   
 * @retval The string containing the request
 */
char *create_request_message(char *host);

#endif
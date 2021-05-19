#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include "nlohmann/json.hpp"
#include "helpers.h"

#define MAX_REQUEST_LENGTH 4096
#define MAX_LINE_LENGTH 1024
#define MAX_COMMAND_LENGTH 20

#define MAX_USERNAME_LENGTH 128
#define MAX_PASSWORD_LENGTH 128

/**
 * @brief  Parses input from stdin and creates the request message
 * @note   
 * @param   host - the destination host
 * @retval The string containing the request
 */
char *create_request_message(char *host);

/**
 * @brief  Checks if the host send an error
 * @note   
 * @param  *response: the response message
 * @retval 1 if error / 0 if success
 */
int is_error(char *response);

/**
 * @brief  Returns the error message in the response
 * @note   
 * @param  *response: the response
 * @retval the error message
 */
char *get_error_message(char *response);

#endif
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
 * @param   command - side effect return: the command name is stored here
 * @param   cookie - the cookie
 * @retval The string containing the request
 */
char *create_request_message(char *host, char command[], char *cookie);

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

/**
 * @brief  Extract the cookie from the response
 * @note   
 * @param  *response: the response
 * @param  *cookie: side effect return: the cookie is stored here
 * @retval None
 */
void extract_cookie(char *response, char *cookie);

/**
 * @brief  Extract the jwt token from the response
 * @note   
 * @param  *response: the response
 * @param  *jwt: side effect return: the jwt token is stored here
 * @retval None
 */
void extract_jwt(char *response, char *jwt);
#endif
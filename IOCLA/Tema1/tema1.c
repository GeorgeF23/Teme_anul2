#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_LENGTH 15

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

/**
 * Inverseaza un string 
 * @param str - stringul care va fi inversat
 * @param len - lungimea stringului
 */
void reverseString(char *str, int len){
	for(int i = 0; i < len / 2; i++){
		char aux = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = aux;
	}
}

/**
 * Afiseaza un unsigned int
 * @param number - numarul care va fi afisat
 * @return numarul de caractere printate
 */
int printNumberUnsigned(unsigned int number){
	char *numberString = malloc(MAX_NUMBER_LENGTH * sizeof(char));
	int numberLength = 0;

	// Pune fiecare cifra din numar intr-un string, dar inversate
	while(number){ 
		numberString[numberLength++] = '0' + number % 10;
		number /= 10;
	}
	
	// Inverseaza stringul pentru a-l aduce in forma buna
	reverseString(numberString, numberLength);

	write_stdout(numberString, numberLength);
	free(numberString);
	return numberLength;
}

/**
 * Afiseaza un int
 * @param number - numarul care va fi afisat
 * @return numarul de caractere printate
 */
int printNumberSigned(int number){

	if(number < 0){
		write_stdout("-", 1);
		return 1 + printNumberUnsigned(-number);
	} else {
		return printNumberUnsigned(number);
	}
}

/**
 * Afiseaza un numar in hex
 * @param number - numarul care sa fie afisat
 * @return numarul de caractere printate
 */
int printNumberHex(unsigned int number){
	char numberCharacters[] = "0123456789abcdef";
	char *numberString = malloc(MAX_NUMBER_LENGTH * sizeof(char));
	int numberLength = 0;

	while(number){
		numberString[numberLength++] = numberCharacters[number % 16];
		number /= 16;
	}

	reverseString(numberString, numberLength);

	write_stdout(numberString, numberLength);
	free(numberString);
	return numberLength;
}

int iocla_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int characters_printed = 0;

	while(*format){
		if(*format == '%'){
			format++;
			char specifier = *format;
			
			if(specifier == 'd'){
				int number = va_arg(args, int);
				characters_printed += printNumberSigned(number);
			} else if(specifier == 'u'){
				unsigned int number = va_arg(args, unsigned int);
				characters_printed += printNumberUnsigned(number);
			} else if(specifier == 'x'){
				unsigned int number = va_arg(args, unsigned int);
				characters_printed += printNumberHex(number);
			} else if(specifier == 'c'){
				char c = (char)va_arg(args, int);
				characters_printed += write_stdout(&c, 1);
			} else if(specifier == 's'){
				char *string = va_arg(args, char*);
				characters_printed += write_stdout(string, strlen(string));
			} else if(specifier == '%'){
				characters_printed += write_stdout("%", 1);
			}
		} else {
			write_stdout(format, 1);
			characters_printed++;
		}
		format++;
	}
	return characters_printed;
}
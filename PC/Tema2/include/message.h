#ifndef _MESSAGE_H
#define _MESSAGE_H 1
#pragma pack(1)

#define CONTENT_LENGTH 1500



struct message {
    char topic[50];
    unsigned int type:8;
    union {
        struct int_type {
            unsigned char sign;
            uint32_t value;
        } int_info;

        struct short_real_type {
            uint16_t value;
        } short_real_info;

        struct float_type {
            unsigned char sign;
            uint32_t value;
            uint8_t decimal_digits;
        } float_info;

        struct string_info {
            char value[CONTENT_LENGTH];
        } string_info;

    } contents;

};

#endif

#ifndef _MESSAGE_H
#define _MESSAGE_H 1
#pragma pack(1)

#define CONTENT_LENGTH 1500
#define TOPIC_LENGTH 50

#define INT_TYPE 0
#define SHORT_REAL_TYPE 1
#define FLOAT_TYPE 2
#define STRING_TYPE 3
#define CLOSE_CLIENT 4  // Special message type to tell the client to terminate

struct subscription_info {
    char topic[CONTENT_LENGTH];
    uint8_t sf;
};

struct message {
    char topic[TOPIC_LENGTH];
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

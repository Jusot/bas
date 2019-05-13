#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IS_ELECT  (TYPE) ((TYPE) == ELECT)
#define IS_ALIVE  (TYPE) ((TYPE) == ALIVE)
#define IS_VICTORY(TYPE) ((TYPE) == VICTORY)

enum MessageType
{
    ELECT,
    ALIVE,
    VICTORY
};

struct Message
{
    int16_t id;
    int16_t type;
};

#ifdef __cplusplus
}
#endif

#endif // MESSAGE_H
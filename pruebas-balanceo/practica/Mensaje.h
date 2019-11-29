#ifndef __MENSAJE__
#define __MENSAJE__

#define TAM_MAX_DATA 34

struct mensaje {
    int messageType;
    unsigned int requestId;
    int operationId;
    char arguments[TAM_MAX_DATA];
};
#endif
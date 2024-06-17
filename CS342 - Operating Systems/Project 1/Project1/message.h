#include <sys/types.h>
#include <stdint.h>

#define CONREQUEST   0x01
#define CONREPLY     0x02
#define COMLINE      0x03
#define COMRESULT    0x04
#define QUITREQ      0x05
#define QUITREPLY    0x06
#define QUITALL      0x07

struct message {

    uint32_t length; // 4 bytes for length
    uint8_t type;    // 1 byte for message type
    uint8_t padding[3]; // 3 bytes of padding for alignment
    char* data;    // Variable length data
};

#define BUFFER_SIZE 1024
#define COMMAND_SIZE 256
#define MAX_CLIENTS 5
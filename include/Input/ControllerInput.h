typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef struct ControllerInput ControllerInput, *PControllerInput;

struct ControllerInput {
    int down:1;
    int up:1;
    int right:1;
    int left:1;
    undefined field4_0x1;
    undefined field5_0x2;
    undefined field6_0x3;
};

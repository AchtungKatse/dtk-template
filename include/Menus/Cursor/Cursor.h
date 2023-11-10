typedef unsigned char undefined;

typedef unsigned char bool;
typedef unsigned char byte;
typedef long long longlong;
typedef unsigned int uint;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned short ushort;
typedef struct CursorMovement CursorMovement, *PCursorMovement;
namespace Menus::Cursor
{

    struct CursorMovement
    {
        byte left;
        byte right;
        byte up;
        byte down;
        bool (*Validate)(void);
    };

}

#include "Bag/Item.h"
typedef unsigned char    byte;

struct Bag {
    short unk_01; /* might be item count */
    byte itemCounts[538];

    static bool HasItem(Item item);
    static int GetCardCount(Item card);
};

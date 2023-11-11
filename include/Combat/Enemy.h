#include "Bag/Item.h"

enum EntityType
{
    Goomba = 0,
    Koopa = 0xb
};


struct Enemy {
    int field0_0x0;
    int field1_0x4;
    Item catchCardIndex;
    char unk_data_1[0x10];
    char* field19_0x1c;
    char* damageSfx;
    char* fireDamageSfx;
    char* fallingSfx;
    char* fallingDamageSfx;
    char unk_data_2[0x38];

    static Enemy* GetEnemyName(EntityType type);
};

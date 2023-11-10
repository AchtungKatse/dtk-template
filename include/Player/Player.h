#include <Math/Math.h>
#include <Combat/Combat.h>

typedef enum Character {
    Mario=0,
    Peach=1,
    Bowser=2,
    Luigi=3
} Character;

struct Player {
    int state;
    unsigned int field1_0x4; /* Seems to be a bitmask, 0x1 is low jumping (released jump before peak hight) */
    int unk_data_1[0xc];
    enum Character character;
    // byte padding[3];
    short unk_short_1;
    char field53_0x3b;
    int field54_0x3c;
    float animTime; /* The time on the current animation in frames */
    float field56_0x44;
    char unk_data_2[0x8];
    float field65_0x50;
    char unk_data_3[0x8];
    struct Vector3 position;
    char unk_data_4[0xac];
    float animLoopTime; /* The time of the animation in frames but modulus to the total amount of frames */
    char unk_data_5[0x1228];
    int currentCombo; /* Created by retype action */
    int field4852_0x1344;

    uint GetAttackDamage(DamageSource source,EntityType entity);
};

extern Player G_PlayerData;

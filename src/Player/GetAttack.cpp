#include <Player/Player.h>
#include <Player/PlayerStats.h>
#include <Bag/Bag.h>
#include <Bag/Item.h>

uint Player::GetAttackDamage(DamageSource source, EntityType entity)
{
    uint damage;
    bool_t l_hasMarioCard;
    int itemCount;
    bool_t hasPeachCard;
    int bowserCardCount;
    bool_t hasLuigiCard;
    Enemy *enemy;
    Item enemyCatchCard;

    Player &l_PlayerData = G_PlayerData;
    damage = PlayerStats::GetAttack();
    if (source == 0xb)
    {
        damage = 99;
    }
    /* Doubles the damage in certain conditions */
    switch (source)
    {
    case Hammer:
        damage = damage << 1;
        break;

    case Unk_13:
        damage = damage << 1;
        break;

    case 0xf:
        // Player l_PlayerData = G_PlayerData;
        if (l_PlayerData.character == Bowser)
        {
            damage = damage << 2;
        }
        else
        {
            damage = damage << 1;
        }
        break;
    case 4:
        damage = damage << 1;
        break;
    case 5:
        damage = damage << 1;
        break;
    case Fire:
        damage = damage << 1;
        break;
    case 0xe:
        damage = damage << 1;
        break;
    }
    if ((l_PlayerData.state & 0x40000000U) != 0)
    {
        damage = damage << 1;
    }
    else if ((l_PlayerData.unk_data_1[2] & 0x40) != 0)
    {
        damage = damage << 1;
    }

    bool hasCard = false;
    int cardCount = 0;
    switch ( l_PlayerData.character)
    {
        case Bowser:
            hasCard = Bag::HasItem(Item::CC_Bowser);
            if (hasCard)
                cardCount = Bag::GetCardCount(Item::CC_Bowser);

            if (source == Stomp)
            {
                damage = damage << 1;
            }
            break;
        case Luigi:
            hasCard = Bag::HasItem(Item::CC_Luigi);
                if (hasCard)
                    cardCount = Bag::GetCardCount(Item::CC_Luigi);
            break;
        case Mario:
            hasCard = Bag::HasItem(Item::CC_Mario);
                if (hasCard)
                    cardCount = Bag::GetCardCount(Item::CC_Mario);
            break;
        case Peach:
            hasCard = Bag::HasItem(Item::CC_Peach);
                if (hasCard)
                    cardCount = Bag::GetCardCount(Item::CC_Peach);
            break;
        
            
    }
    damage = damage * (cardCount + 1);

    if ((int)entity >= 0)
    {
        enemy = Enemy::GetEnemyName(entity);
        enemyCatchCard = enemy->catchCardIndex;
        if ((enemyCatchCard != 0) && (hasLuigiCard = Bag::HasItem(enemyCatchCard), hasLuigiCard != 0))
        {
            bowserCardCount = Bag::GetCardCount(enemyCatchCard);
            damage = damage * (bowserCardCount + 1);
        }
    }
    if (source == Barry)
    {
        float half = .5;
        damage = (uint)(half * (float)((double)(0x43300000 | damage ^ 0x80000000) - 0.00001) +
                        .9);
    }
    return damage;
}

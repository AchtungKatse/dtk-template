#include "PlayerStats.h"
#include "LifetimeStats.h"

void PlayerStats::AddCoins(int coins)
{
    G_PlayerStats.coins -= coins;
    /* Clamp between 999 and 0 */
    if (999 < G_PlayerStats.coins)
    {
        G_PlayerStats.coins = 999;
    }
    if (G_PlayerStats.coins < 0)
    {
        G_PlayerStats.coins = 0;
    }

    // Dont add negative coins to lifetime coins collected
    if (coins <= 0)
    {
        return;
    }

    // Add to lifetime coins
    G_LifetimeStats.coinsCollected += coins;

    // Do nothing if lifetime coins is within bounds (< 100000)
    if (G_LifetimeStats.coinsCollected <= 99999)
    {
        return;
    }
    G_LifetimeStats.coinsCollected = 99999;
}

void PlayerStats::AddAttack(int add)
{
    G_PlayerStats.attack = G_PlayerStats.attack + add;
    if (99 < G_PlayerStats.attack)
    {
        G_PlayerStats.attack = 99;
    }

    /* If damage is positive do nothing */
    if (0 < G_PlayerStats.attack)
    {
        return;
    }

    /* If damage is less <= 0 then set it to 1 */
    G_PlayerStats.attack = 1;

    return;
}

void PlayerStats::AddScore(int score)
{
    G_PlayerStats.score = G_PlayerStats.score + score;

    // Clamp score
    if (G_PlayerStats.score >= 99999999)
    {
        G_PlayerStats.score = 99999999;
    }

    if (G_PlayerStats.score < 0)
    {
        G_PlayerStats.score = 0;
    }
}

void PlayerStats::AddHealth(int health)
{
    // Add health
    G_PlayerStats.health = G_PlayerStats.health + health;

    // Clamp to max health
    if (G_PlayerStats.health > G_PlayerStats.maxHealth)
    {
        G_PlayerStats.health = G_PlayerStats.maxHealth;
    }

    // Min of 0
    if (G_PlayerStats.health < 0)
    {
        G_PlayerStats.health = 0;
    }

    if (health != 0)
    {
        G_PlayerStats.unk_1 = 10;
    }
}

int PlayerStats::GetCoins(void)
{
    return G_PlayerStats.coins;
}
int GetAttack()
{
    return G_PlayerStats.attack;
}
int GetScore()
{
    return G_PlayerStats.score;
}
int GetHealth()
{
    return G_PlayerStats.health;
}
int GetMaxHealth()
{
    return G_PlayerStats.maxHealth;
}

void PlayerStats::SetCoins(int coins)
{
    G_PlayerStats.coins = coins;
    if (coins > 999)
    {
        G_PlayerStats.coins = 999;
    }
    if (G_PlayerStats.coins < 0)
    {
        G_PlayerStats.coins = 0;
    }
}

void PlayerStats::SetAttack(int attack)
{
    // Set attack
    G_PlayerStats.attack = attack;

    // Clamp to max of 99
    if (99 < attack)
    {
        G_PlayerStats.attack = 99;
    }

    // Set to min of 1
    if (0 < G_PlayerStats.attack)
    {
        return;
    }
    G_PlayerStats.attack = 1;
    return;
}

void PlayerStats::SetHealth(int health)
{
    // Set health
    G_PlayerStats.health = health;
    if (G_PlayerStats.maxHealth < health)
    {
        G_PlayerStats.health = G_PlayerStats.maxHealth;
    }
    if (G_PlayerStats.health < 0)
    {
        G_PlayerStats.health = 0;
    }
    if (health == 0)
    {
        return;
    }
    G_PlayerStats.unk_1 = 10;
    return;
}

void PlayerStats::SetMaxHealth(int value)
{
    G_PlayerStats.maxHealth = value;
    if (999 < value)
    {
        G_PlayerStats.maxHealth = 999;
    }
    if (-1 < G_PlayerStats.maxHealth)
    {
        return;
    }
    G_PlayerStats.maxHealth = 0;
    return;
}

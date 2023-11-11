#include "Player/PlayerStats.h"


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
    if (G_PlayerStats.attack >= 1)
    {
        return;
    }
    G_PlayerStats.attack = 1;
    return;
}

int PlayerStats::GetAttack(int unused)
{
    return G_PlayerStats.attack;
}

void PlayerStats::AddAttack(int add)
{
    G_PlayerStats.attack = G_PlayerStats.attack + add;
    if (99 < G_PlayerStats.attack)
    {
        G_PlayerStats.attack = 99;
    }

    /* If damage is positive do nothing */
    if (G_PlayerStats.attack >= 1)
    {
        return;
    }

    /* If damage is less <= 0 then set it to 1 */
    G_PlayerStats.attack = 1;

    return;
}

void PlayerStats::SetHealth(int health)
{
    // Set health
    PlayerStats& stats = G_PlayerStats;
    stats.health = health;
    if (health > stats.maxHealth)
    {
        stats.health = stats.maxHealth;
    }
    if (stats.health < 0)
    {
        stats.health = 0;
    }
    if (health == 0)
    {
        return;
    }
    stats.unk_1 = 10;
}

int PlayerStats::GetHealth(int unused)
{
    return G_PlayerStats.health;
}

void PlayerStats::AddHealth(int health)
{
    // Add health
    PlayerStats& stats = G_PlayerStats;
    stats.health = stats.health + health;

    // Clamp to max health
    if (stats.health > stats.maxHealth)
    {
        stats.health = stats.maxHealth;
    }

    // Min of 0
    if (stats.health < 0)
    {
        stats.health = 0;
    }

    if (health != 0)
    {
        stats.unk_1 = 10;
    }
}

void PlayerStats::SetMaxHealth(int value)
{
    G_PlayerStats.maxHealth = value;
    if (999 < value)
    {
        G_PlayerStats.maxHealth = 999;
    }
    if (0 <= G_PlayerStats.maxHealth)
    {
        return;
    }
    G_PlayerStats.maxHealth = 0;
    return;
}

int PlayerStats::GetMaxHealth(int unused)
{
    return G_PlayerStats.maxHealth;
}

int PlayerStats::GetScore(int unused)
{
    return G_PlayerStats.score;
}

void PlayerStats::AddScore(int score)
{
    G_PlayerStats.score = G_PlayerStats.score + score;

    // Clamp score
    if (G_PlayerStats.score > 99999999)
    {
        G_PlayerStats.score = 99999999;
    }

    if (G_PlayerStats.score < 0)
    {
        G_PlayerStats.score = 0;
    }
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

int PlayerStats::GetCoins(int unused)
{
    return G_PlayerStats.coins;
}

void PlayerStats::AddCoins(int coins)
{
    PlayerStats& stats = G_PlayerStats;
    G_PlayerStats.coins -= coins;

    /* Clamp between 999 and 0 */
    if (999 < stats.coins)
    {
        stats.coins = 999;
    }
    if (stats.coins < 0)
    {
        stats.coins = 0;
    }

    // Dont add negative coins to lifetime coins collected
    if (coins <= 0)
    {
        return;
    }

    // Add to lifetime coins
    LifetimeStats& lifetime = stats.lifetime;
    G_PlayerStats.lifetime.coinsCollected += coins;

    // Do nothing if lifetime coins is within bounds (< 100000)
    if (G_PlayerStats.lifetime.coinsCollected <= 99999)
    {
        return;
    }
    G_PlayerStats.lifetime.coinsCollected = 99999;
}

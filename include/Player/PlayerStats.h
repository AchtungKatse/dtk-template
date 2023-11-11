struct LifetimeStats
{
    int unk_1;
    int coinsCollected;
    int unk_2;
    int unk_3;
};

struct PlayerStats
{
    int unk_4;
    int level;
    int attack;
    int health;
    int maxHealth;
    int unk_1;
    int score;
    int coins;
    int unk_2;
    int unk_3;
    char unknownData[0x660];
    LifetimeStats lifetime;
    int unk_5;



    static void AddCoins(int coins);
    static void AddAttack(int attack);
    static void AddScore(int score);
    static void AddHealth(int health);

    static int GetCoins(int unused);
    static int GetAttack(int unused);
    static int GetScore(int unused);
    static int GetHealth(int unused);
    static int GetMaxHealth(int unused);

    static void SetCoins(int coins);
    static void SetAttack(int attack);
    static void SetHealth(int health);
    static void SetMaxHealth(int maxHealth);
};

extern PlayerStats G_PlayerStats;

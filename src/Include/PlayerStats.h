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

    void AddCoins(int coins);
    void AddAttack(int attack);
    void AddScore(int score);
    void AddHealth(int health);

    int GetCoins();
    int GetAttack();
    int GetScore();
    int GetHealth();
    int GetMaxHealth();

    void SetCoins(int coins);
    void SetAttack(int attack);
    void SetHealth(int health);
    void SetMaxHealth(int maxHealth);
};

extern PlayerStats G_PlayerStats;

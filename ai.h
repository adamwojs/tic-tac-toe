#ifndef AI_H
#define AI_H

class AIPlayer
{
public:
    AIPlayer(char (&board)[3][3], char player);

    void move ();
    void setPlayer (char player);

protected:
    char player;
    char (&board)[3][3];

    /* Sprawdza czy AI może wykonać zwycięski ruch
     * @return: false jeśli ruch nie jest możliwy, w przeciwnym wypaku true
     */
    bool winningMove ();

    /* Sprawdza czy AI może wykonać ruch którym zablokuje wygraną przeciwnika
     * @return: false jeśli ruch nie jest możliwy, w przeciwnym wypadku true
     */
    bool blockEnemy ();

    /* Wykonuje passywny ruch */
    void passive ();
};

#endif // AI_H

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include <cmath>
#include "ai.h"

class Game : public QWidget
{
   Q_OBJECT

public:
    Game(QWidget* parent = 0);
    virtual ~Game();

public slots:
    virtual void newGame();
    virtual void newGameWithAI();

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

private:
    AIPlayer ai;

    /* Rozgrywka komputer - człowiek ? */
    bool gameWithAI;    

    /* Akttualna sytuacja na planszy */
    char board[3][3];

    /* Który gracz wykonuje obecnie ruch ? ('X' lub 'O') */
    char activePlayer;

    /* Rezultat ostatniego wywołania checkWin */
    int isWon;    

    /* Rezultat ostatniego wywołania checkTie */
    bool isTie;

    /* Sprawdza czy aktualny gracz wygrał gre
     * W przypadku wygranej zwraca poczatek i koniec lini w której wystąpiła wygrana.
     * Współrzędne kodowane są jako xyxy po 2 bity
     * Np. Linia od (1, 0) do (1, 2) jest kodowana jako 01000110
     */
    int checkWin();

    /* Sprawdza czy jest remis */
    bool checkTie();

    /* Sprawdza wy nie nastąpiła wygrana, remis itp. */
    void onMove ();
};

#endif // GAME_H

#include <QtGlobal>
#include <ctime>
#include "ai.h"

AIPlayer::AIPlayer(char (&board)[3][3], char player)
    : board(board), player(player)
{
    qsrand(time(0)); 
}

void AIPlayer::move()
{
    if (!winningMove())
        if (!blockEnemy())
            this->passive();
}

void AIPlayer::setPlayer(char player)
{
    this->player = player;
}

bool AIPlayer::winningMove()
{
    for (int i = 0; i < 3; ++i)
    {
        int v = 0;

        v = board[i][0] + board[i][1] + board[i][2];
        if (v == 2 * player)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (!board[i][j])
                {
                    board[i][j] = player;
                    return true;
                }
            }
        }

        v = board[0][i] + board[1][i] + board[2][i];
        if (v == 2 * player)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (!board[j][i])
                {
                    board[j][i] = player;
                    return true;
                }
            }
        }
    }

    if (board[0][0] + board[1][1] + board[2][2] == 2 * player)
    {
        if (!board[0][0])
            board[0][0] = player;
        else
            if (!board[1][1])
                board[1][1] = player;
            else
                board[2][2] = player;

        return true;
    }

    if (board[0][2] + board[1][1] + board[2][0] == 2 * player)
    {
        if (!board[0][2])
            board[0][2] = player;
        else
            if (!board[1][1])
                board[1][1] = player;
            else
                board[2][0] = player;

        return true;
    }

    return false;
}

bool AIPlayer::blockEnemy()
{
    char opponent = (player == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i)
    {
        int v = 0;

        v = board[i][0] + board[i][1] + board[i][2];
        if (v == 2 * opponent)
        {
            for (int j = 0; j < 3; ++j)
                if (!board[i][j])
                {
                    board[i][j] = player;
                    return true;
                }
        }

        v = board[0][i] + board[1][i] + board[2][i];
        if (v == 2 * opponent)
        {
            for (int j = 0; j < 3; ++j)
                if (!board[j][i])
                {
                    board[j][i] = player;
                    return true;
                }
        }
    }

    if (board[0][0] + board[1][1] + board[2][2] == 2 * opponent)
    {
        if (!board[0][0])
            board[0][0] = player;
        else if (!board[1][1])
                board[1][1] = player;
             else
                 board[2][2] = player;

        return true;
    }

    if (board[0][2] + board[1][1] + board[2][0] == 2 * opponent)
    {
        if (!board[0][2])
            board[0][2] = player;
        else if (!board[1][1])
                board[1][1] = player;
            else
                board[2][0] = player;

        return true;
    }

    return false;
}

void AIPlayer::passive()
{
    /* Środek */
    if (!board[1][1])
    {
        board[1][1] = player;
        return ;
    }

    /* Rogi */
    bool corner[4] = { false };
    corner[0] = !board[0][0];
    corner[1] = !board[0][2];
    corner[2] = !board[2][0];
    corner[3] = !board[2][2];    
    if (corner[0] + corner[1] + corner[2] + corner[3] != false)
    {
        int c = 0;
        while (c = qrand() % 4, !corner[c]) {}

        if (corner[c]) {
            switch (c)
            {
                case 0: board[0][0] = player; break;
                case 1: board[0][2] = player; break;
                case 2: board[2][0] = player; break;
                case 3: board[2][2] = player; break;
            }            
        }        

        return ;
    }

    /* Pola [0][1], [1][2], [2][1], [1][0] */                
    bool field[4] = { false };
    field[0] = !board[0][1];
    field[1] = !board[1][2];
    field[2] = !board[2][1];
    field[3] = !board[1][0];

    int f = 0;
    while (f = qrand() % 4, !field[f]) {};

    switch (f)
    {
        case 0: board[0][1] = player; break;
        case 1: board[1][2] = player; break;
        case 2: board[2][1] = player; break;
        case 3: board[1][0] = player; break;
    }
}

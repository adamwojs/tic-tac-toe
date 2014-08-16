#include "game.h"

Game::Game(QWidget* parent)
    : QWidget(parent), ai(board, 'O')
{
    this->setFixedSize(500, 500);
    this->setFocusPolicy(Qt::ClickFocus);
    this->newGameWithAI();
}

Game::~Game() {}

void Game::newGame()
{
    this->activePlayer = 'X';
    this->isWon = false;
    this->isTie = false;
    this->gameWithAI = false;    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = 0;
    this->repaint();      
}

void Game::newGameWithAI()
{    
    this->newGame();
    this->gameWithAI = true;        

    /* Pierwszy ruch wykonywany na zmianę... */
    static bool firstAIMove = true;
    firstAIMove = !firstAIMove;

    if (firstAIMove)
    {
        ai.move();
        this->repaint();
    }
}

void Game::paintEvent(QPaintEvent* event)
{
    QPen pen(Qt::black, 4, Qt::SolidLine);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), Qt::white);

    int a = event->rect().width() / 3;
    int m = a * 0.15;    

    /* Linie */
    for (int i = 1; i < 3; ++i)
    {
        painter.drawLine(
            a * i,
            0,
            a * i,
            event->rect().height()
        );
        painter.drawLine(
            0,
            a * i,
            event->rect().width(),
            a * i
        );
    }

    pen.setWidth(6);
    painter.setPen(pen);
    /* Kółka i krzyżyki */
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {            
            if (board[i][j] == 'X')
            {
                int x1 = a * i;
                int y1 = a * j;
                int x2 = a * (i + 1);
                int y2 = a * (j + 1);

                painter.drawLine(x1 + m, y1 + m, x2 - m, y2 - m);
                painter.drawLine(x2 - m, y1 + m, x1 + m, y2 - m);
            }
            else if (board[i][j] == 'O')
            {
                int w = a;
                int h = a;

                int r = sqrt(2) / 2 * h;
                int x = w * i + m;
                int y = h * j + m;

                painter.drawArc(x, y, r, r, 0, 5760);
            }
        }
    }

    /* Skreślenie */
    if (this->isWon)
    {
        int x1 = (this->isWon & 192) >> 6;
        int y1 = (this->isWon & 48)  >> 4;
        int x2 = (this->isWon & 12)  >> 2;
        int y2 = this->isWon & 3;

        m = a * 0.10;

        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);

        if (x1 == x2)
            painter.drawLine(x1 * a + 0.5 * a, m, x2 * a + 0.5 * a, (y2 + 1) * a - m);
        else if (y1 == y2)
            painter.drawLine(m, y1 * a + 0.5 * a, (x2 + 1) * a - m, y2 * a + 0.5 * a);
        else if (x1 == 0)
            painter.drawLine(m, m, 3 * a - m, 3 * a - m);
        else
            painter.drawLine(3 * a - m, m, m, 3 * a - m);
    }
}

void Game::mousePressEvent(QMouseEvent* event)
{
    int x = event->x() / (this->width() / 3);
    int y = event->y() / (this->width() / 3);

    if (isWon || isTie)
        return ;

    if (!this->board[x][y])
    {
        this->board[x][y] = this->activePlayer;
        this->onMove ();
    }    
}

void Game::keyPressEvent(QKeyEvent* event)
{

    if (isWon || isTie)
        return ;

    if (event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9)
    {
        int x = (event->key() - Qt::Key_1) % 3;
        int y = (event->key() - Qt::Key_1) / 3;

        if (!board[x][y])
        {
            this->board[x][y] = this->activePlayer;
            this->onMove();
        }
    }
}

int Game::checkWin()
{
    for (int i = 0; i < 3; ++i)
    {
        // Linie pionowe
        int h = board[i][0] + board[i][1] + board[i][2];
        if (h == 3 * 'X' || h == 3 * 'O')
            return (i << 6) | (i << 2) | 2;        

        // Linie poziome
        int v = board[0][i] + board[1][i] + board[2][i];
        if (v == 3 * 'X' || v == 3 * 'O')
            return (i << 4) | 8 | i;
    }

    // Przekątna
    int d = board[0][0] + board[1][1] + board[2][2];
    if (d == 3 * 'X' || d == 3 * 'O')
        return 10;

    // Przekątna /
    d = board[0][2] + board[1][1] + board[2][0];
    if (d == 3 * 'X' || d == 3 * 'O')
        return 130;

    return false;
}

bool Game::checkTie()
{    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j  < 3; ++j)
            if (this->board[i][j] == 0)
                return false;

    return true;
}

void Game::onMove ()
{
    this->isWon = this->checkWin();
    this->isTie = this->checkTie();
    this->repaint();
    if (isWon || isTie)
        return ;

    if (gameWithAI)
    {
        ai.move();
        this->isWon = this->checkWin();
        this->isTie = this->checkTie();
        this->repaint();
    }
    else
    {
        this->activePlayer = (this->activePlayer == 'X') ? 'O' : 'X';
    }
}

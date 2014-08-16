#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include "game.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

    public:
        GameWindow ();

    public slots:
        void aboutAuthor ();

    protected:
        Game* game;
};

#endif // GAMEWINDOW_H

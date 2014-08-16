#include "gamewindow.h"

GameWindow::GameWindow()
{
        this->setWindowTitle("Tic tac toe!");
        this->setWindowFlags(Qt::Dialog);

        game = new Game;
        this->setCentralWidget(game);

        QMenuBar* menu = new QMenuBar();
        this->setMenuBar(menu);
        QMenu* gameMenu = menu->addMenu("&Gra");

        QAction* newGame = gameMenu->addAction("Nowa gra z człowiekiem");
        connect(newGame, SIGNAL(triggered()), game, SLOT(newGame()));

        QAction* newGameWithAI = gameMenu->addAction("Nowa gra z komputerem");
        newGameWithAI->setShortcut(QKeySequence("Ctrl+N"));
        connect(newGameWithAI, SIGNAL(triggered()), game, SLOT(newGameWithAI()));

        gameMenu->addSeparator();

        QAction* aboutGame = gameMenu->addAction("O autorze");
        connect(aboutGame, SIGNAL(triggered()), this, SLOT(aboutAuthor()));

        gameMenu->addSeparator();

        QAction* quitGame = gameMenu->addAction("Koniec gry");
        connect(quitGame, SIGNAL(triggered()), qApp, SLOT(quit()));

        this->show();
        this->setFixedSize(this->size());
}

void GameWindow::aboutAuthor()
{
    QMessageBox msg;
    msg.setWindowTitle("O autorze");
    msg.setText(
        "<center>Autorem tej implementacji gry Kółko Krzyżyk jest<br />"
        "<a href=\"mailto:adawo.gmail.com\"><b>Adam \"Adawo\" Wójs</b></a>.<br /> "
        "Kod dostępny na licencji <b>GPL</b>.</center>"
    );
    msg.addButton(QMessageBox::Ok);
    msg.exec();
}

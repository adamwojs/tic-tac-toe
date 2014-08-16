#include <QApplication>
#include <QTextCodec>
#include "gamewindow.h"

int main(int argc, char* argv[]) {
    QApplication app (argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    GameWindow wnd;

    return app.exec ();
}


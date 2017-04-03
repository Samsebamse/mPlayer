#include "mplayer.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    mPlayer w;
    w.show();

    return a.exec();
}

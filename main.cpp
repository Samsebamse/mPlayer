#include "mplayer.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/music_player.png"));
    mPlayer w;
    w.show();

    return a.exec();
}

#ifndef MPLAYER_H
#define MPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <Qstring>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include <Qtime>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QFileDialog>
#include <QKeyEvent>

namespace Ui {
class mPlayer;
}

class mPlayer : public QMainWindow{
    Q_OBJECT


private:
    Ui::mPlayer *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

public:
    explicit mPlayer(QWidget *parent = 0);
    ~mPlayer();


protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:   
    void loadSong(qint64 position);
    void currentValue(qint64 position);

    void on_sliderVolume_sliderMoved(int position);
    void on_sliderProgress_sliderMoved(int position);

    void on_buttonPlay_toggled(bool play);
    void on_buttonRepeat_toggled(bool repeat);
    void on_buttonShuffle_toggled(bool shuffle);
    void on_buttonNext_clicked();
    void on_buttonBack_clicked();

    void on_listWidget_doubleClicked();
    void on_buttonBrowse_clicked();


};

#endif // MPLAYER_H

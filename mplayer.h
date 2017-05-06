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

    bool playing = false;

    qint64 position;
    QString currentpath;
    QString songinfo;
    QTime durationTime;
    QTime currentTime;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private slots:

    void on_buttonPlay_toggled(bool playing);

    void loadSong(qint64 position);

    void currentValue(qint64 position);

    void on_sliderVolume_sliderMoved(int position);

    void on_sliderProgress_sliderMoved(int position);

    void on_listWidget_doubleClicked();
};

#endif // MPLAYER_H

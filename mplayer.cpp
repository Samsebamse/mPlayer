#include "mplayer.h"
#include "ui_mplayer.h"


mPlayer::mPlayer(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::mPlayer){

    ui->setupUi(this);
    ui->labelSonginfo->setText("HELLO THIS IS MY APP");

    player = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);

    player->setVolume(30);
    ui->labelVolume->setText("Volume: " + QString::number(30));
    ui->sliderVolume->setValue(30);

    connect(player, &QMediaPlayer::positionChanged, this, &mPlayer::currentValue);
    connect(player, &QMediaPlayer::durationChanged, this, &mPlayer::loadSong);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &mPlayer::on_sliderVolume_sliderMoved);

    setAcceptDrops(true);
    on_buttonPlay_toggled(false);

}

mPlayer::~mPlayer(){
    delete ui;
}

void mPlayer::dragEnterEvent(QDragEnterEvent *event){
    event->accept();
}

void mPlayer::dragLeaveEvent(QDragLeaveEvent *event){
    event->accept();
}

void mPlayer::dragMoveEvent(QDragMoveEvent *event){
    event->accept();
}

void mPlayer::dropEvent(QDropEvent *event){

    QString path;
    QList<QUrl> list;
    QList<QUrl>::iterator itr;

    list = event->mimeData()->urls();

    for(itr = list.begin(); itr != list.end(); itr++){

        path = itr->fileName();
        ui->listWidget->addItem(path);
        playlist->addMedia(QUrl(itr->url()));
    }
}


void mPlayer::on_buttonPlay_toggled(bool playing){

    if(playing){
        player->play();
        ui->buttonPlay->setText("Playing");

    }
    else{
        player->pause();
        ui->buttonPlay->setText("Paused");     
    }

}

void mPlayer::loadSong(qint64 position){

    ui->sliderProgress->setMaximum(position);
    durationTime.setHMS(0,0,0,0);
    durationTime = durationTime.addMSecs(position);
    ui->labelSonglength->setText(durationTime.toString("mm:ss"));

}

void mPlayer::currentValue(qint64 position){

    ui->sliderProgress->setValue(position);
    currentTime.setHMS(0,0,0,0);
    currentTime = currentTime.addMSecs(position);
    ui->labelProgress->setText(currentTime.toString("mm:ss") + "  /");

}

void mPlayer::on_sliderVolume_sliderMoved(int position){
    player->setVolume(position);
    ui->labelVolume->setText("Volume: " + QString::number(position));

}

void mPlayer::on_sliderProgress_sliderMoved(int position){

    player->setPosition(position);

}

void mPlayer::on_listWidget_doubleClicked(){
    int tracknr = ui->listWidget->currentRow();
    playlist->setCurrentIndex(tracknr);
    on_buttonPlay_toggled(true);
    ui->labelSonginfo->setText(playlist->currentMedia().canonicalUrl().fileName());

}

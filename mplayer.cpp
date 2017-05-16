#include "mplayer.h"
#include "ui_mplayer.h"

/*
 * Constructor of mplayer.cpp class is defined.
 * Here are all the intial values set.
 *
 * Creating two pointers, one for player and one for playlist,
 * which can be accessed anywhere since they are stored in heap memory.
 *
 * Binding change in position with my defined method currentvalue.
 * Binding duration changed with my defined method loadsong.
 * Binding value changed with slider with on_slidervolume_slidermoved.
 *
 * Two first bindings are crucial to this application, since they invoke actions taken by mediaplayer, i.e.
 * examine the changing position of audio files with the respect of time.
*/

mPlayer::mPlayer(QWidget *parent) : QMainWindow(parent), ui(new Ui::mPlayer){

    ui->setupUi(this);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);

    player->setPlaylist(playlist);
    player->setVolume(30);
    ui->labelVolume->setText("Volume: " + QString::number(30));
    ui->sliderVolume->setValue(30);

    connect(player, &QMediaPlayer::positionChanged, this, &mPlayer::currentValue);
    connect(player, &QMediaPlayer::durationChanged, this, &mPlayer::loadSong);
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &mPlayer::on_sliderVolume_sliderMoved);

    setAcceptDrops(true);
}
/*
 * Destructor.
 * Wipes all the allocated heap memory once it is called, since all objects are derived of the parent object.
*/
mPlayer::~mPlayer(){
    delete ui;
}
/*
 * Accepting to drop items.
 * A foreach loop to seek through all files.
*/
void mPlayer::dragEnterEvent(QDragEnterEvent *event){
    event->accept();
}

void mPlayer::dropEvent(QDropEvent *event){
    QString path;
    QList<QUrl> list = event->mimeData()->urls();
    foreach(QUrl url, list){
        path = url.fileName();
        ui->listWidget->addItem(path);
        playlist->addMedia(url);
    }
}
/*
 * Accepting keyboard events. Delete key to remove all selected widgets.
 * A foreach loop to seek through all files.
 * Control key enables to select more than one widget in widgetlist.
*/
void mPlayer::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){
        QList<QListWidgetItem*> list;
        list = ui->listWidget->selectedItems();
        foreach(QListWidgetItem *item, list){
            int tracknr = ui->listWidget->row(item);
            delete ui->listWidget->takeItem(ui->listWidget->row(item));
            playlist->removeMedia(tracknr);
        }
    }
    else if(event->key() == Qt::Key_Control){
        ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    }
     ui->listWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);
}
/*
 * Setting media player to play or pause state.
 */
void mPlayer::on_buttonPlay_toggled(bool play){
    if(play){
        player->play();
        ui->buttonPlay->setIcon(QIcon(":/icon/ic_pause_black_48dp_1x.png"));
    }
    else{
        player->pause();
        ui->buttonPlay->setIcon(QIcon(":/icon/ic_play_arrow_black_48dp_1x.png"));
    }
}
/*
 * Loading a new track. Highlighting and displaying the duration time of current audio file.
 */
void mPlayer::loadSong(qint64 position){
    ui->sliderProgress->setMaximum(position);
    QTime time;
    time.setHMS(0,0,0,0);
    time = time.addMSecs(position);
    ui->labelSonglength->setText(time.toString("mm:ss"));
    ui->labelSonginfo->setText(playlist->currentMedia().canonicalUrl().fileName());

    if(playlist->nextIndex() != playlist->isEmpty()){
        ui->listWidget->item(playlist->currentIndex())->setSelected(true);
        ui->listWidget->setFocus();
    }
}
/*
 * Keeping of the current position of current audio file every second.
 * Position is converted to seconds and then displayed.
 */
void mPlayer::currentValue(qint64 position){
    ui->sliderProgress->setValue(position);
    QTime time;
    time.setHMS(0,0,0,0);
    time = time.addMSecs(position);
    ui->labelProgress->setText(time.toString("mm:ss") + "  /");
}

/*
 * Adjusting position of audio file when progress slider is moved.
 * Enables to fast forward or rewind the current track.
 */

void mPlayer::on_sliderProgress_sliderMoved(int position){
    player->setPosition(position);
}

/*
 * Displaying and adjusting volume.
 */

void mPlayer::on_sliderVolume_sliderMoved(int position){
    player->setVolume(position);
    ui->labelVolume->setText("Volume: " + QString::number(position));
}

/*
 * Enabling double click actions to play audio files.
 */

void mPlayer::on_listWidget_doubleClicked(){
    int tracknr = ui->listWidget->currentRow();
    playlist->setCurrentIndex(tracknr);
    ui->buttonPlay->click();
    on_buttonPlay_toggled(true);
    ui->labelSonginfo->setText(playlist->currentMedia().canonicalUrl().fileName());
}

/*
 * Sets playlist to sequential order or repeat mode.
 */

void mPlayer::on_buttonRepeat_toggled(bool repeat){
    if(repeat){
        playlist->setPlaybackMode(QMediaPlaylist::Loop);     
    }
    else
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
}

/*
 * Plays next or previous track.
 */

void mPlayer::on_buttonNext_clicked(){
    if((playlist->nextIndex() >= 0) && (playlist->nextIndex() < playlist->mediaCount())){
        playlist->next();
        ui->labelSonginfo->setText(playlist->currentMedia().canonicalUrl().fileName());
    }
}

void mPlayer::on_buttonBack_clicked(){
    if((playlist->previousIndex() >= 0) && (playlist->previousIndex() < playlist->mediaCount())){
        playlist->previous();
        ui->labelSonginfo->setText(playlist->currentMedia().canonicalUrl().fileName());
    }
}
/*
 * Sets playlist to sequential order or shuffle mode.
 */
void mPlayer::on_buttonShuffle_toggled(bool shuffle){
    if(shuffle){
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    }
    else
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
}
/*
 * Opening file manager and loops through all selected files.
 * Accepting audio format flac, mp3, wav.
 * Adding selected files to playlist.
 */
void mPlayer::on_buttonBrowse_clicked(){
    QString file;
    QList<QUrl> list;
    QFileDialog filemanager;

    list = filemanager.getOpenFileUrls(
                        this,
                        "Select audiofile(s)",
                        QUrl("C:\\"),
                        "Free Lossless Audio Codec (*.flac);;"
                        "MPEG-2 Audio Layer III (*.mp3);;"
                        "Waveform Audio File (*.wav)"
                        );

    foreach(QUrl url, list){
        file = url.fileName();
        ui->listWidget->addItem(file);
        playlist->addMedia(url);
    }

    ui->labelSonginfo->setText(playlist->media(0).canonicalUrl().fileName());
}

#ifndef AUDIO_H
#define AUDIO_H

#include <QWidget>
#include <stdlib.h>
#include <stdio.h>
#include <QPushButton>
#include <qobject.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>

namespace Ui {
class Audio;
}

class Audio : public QWidget
{
    Q_OBJECT
    
public:
    explicit Audio(QWidget *parent = 0);
    ~Audio();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Audio *ui;
};

#endif // MAINWINDOW_H

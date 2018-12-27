#ifndef EEPROM_H 
#define EEPROM_H

#include <QWidget>
#include <QtCore>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>

namespace Ui {
    class Eeprom;
}

class Eeprom : public QWidget {
    Q_OBJECT
public:
    explicit Eeprom(QWidget *parent = 0);
    ~Eeprom();

protected:
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
private:
    Ui::Eeprom *ui;
	int fd;
	int len;
private slots:
	void writemsg(); 
	void readmsg(); 
protected:
};

#endif

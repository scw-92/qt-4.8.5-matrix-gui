#ifndef VERSION_H
#define VERSION_H

#include <QWidget>

namespace Ui {
class version;
}

class version : public QWidget
{
    Q_OBJECT

public:
    explicit version(QWidget *parent = 0);
    ~version();

private:
    Ui::version *ui;
};

#endif // VERSION_H

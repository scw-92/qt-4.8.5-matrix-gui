#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>


#define __APLEX_QT_INFO__
#define __APLEX_QT_LED__
#define __APLEX_QT_GPIO__
#define __APLEX_QT_BUZZER__
#define __APLEX_QT_BACKLIGHT__
#define __APLEX_QT_EEPROM__
#define __APLEX_QT_NETWORK__
#define __APLEX_QT_PING__
#define __APLEX_QT_USB__
#define __APLEX_QT_SD__
#define __APLEX_QT_UART__
//#define __APLEX_QT_WATCHDOG__
#define __APLEX_QT_CANTEST__
//#define __APLEX_QT_AUDIO__
#define __APLEX_QT_RTCTEST__
#define __APLEX_QT_IFCONFIG__
//#define __APLEX_QT_VERSION__
//#define __APLEX_QT_PERF__

#ifdef __APLEX_QT_INFO__
#include "./info/info.h"
#endif

#ifdef __APLEX_QT_LED__
#include "./led/led.h"
#endif

#ifdef __APLEX_QT_GPIO__
#include "./gpio/myGpio.h"
#endif

#ifdef __APLEX_QT_BUZZER__
#include "./buzzer/buzzer.h"
#endif

#ifdef __APLEX_QT_BACKLIGHT__
#include "./backlight/backlight.h"
#endif

#ifdef __APLEX_QT_EEPROM__
#include "./eeprom/eeprom.h"
#endif

#ifdef __APLEX_QT_NETWORK__
#include "./network/network.h"
#endif

#ifdef __APLEX_QT_PING__
#include "./ping/ping.h"
#endif

#ifdef __APLEX_QT_USB__
#include "./usb/usb.h"
#endif

#ifdef __APLEX_QT_SD__
#include "./SD/sd.h"
#endif

#ifdef __APLEX_QT_UART__
#include "./uart/uart.h"
#endif

#ifdef __APLEX_QT_WATCHDOG__
#include "./watchdog/watchdog.h"
#endif

#ifdef __APLEX_QT_CANTEST__
#include "./can/canTest.h"
#endif

#ifdef __APLEX_QT_AUDIO__
#include "./audio/audio.h"
#endif

#ifdef __APLEX_QT_RTCTEST__
#include "./rtc/rtcTest.h"
#endif

#ifdef __APLEX_QT_VERSION__
#include "./version/version.h"
#endif

#ifdef __APLEX_QT_IFCONFIG__
#include "./ifconfig/dpifconfig.h"
#endif

#ifdef __APLEX_QT_PERF__
#include "./OnOff/onoff.h"
#include "./burncpu/burnCpu.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTabWidget *tabWidget;
    void updateSizes(int index);

public:

#ifdef __APLEX_QT_INFO__
    Info *info;
#endif

#ifdef __APLEX_QT_LED__
    Led *led;
#endif

#ifdef __APLEX_QT_GPIO__
    MyGpio *gpio;
#endif

#ifdef __APLEX_QT_BUZZER__
    Buzzer *buzzer;
#endif

#ifdef __APLEX_QT_BACKLIGHT__
    Backlight *backlight;
#endif

#ifdef __APLEX_QT_EEPROM__
    Eeprom *eeprom;
#endif

#ifdef __APLEX_QT_NETWORK__
    Network *network;
#endif

#ifdef __APLEX_QT_PING__
    Ping *ping;
#endif

#ifdef __APLEX_QT_RTCTEST__
    RtcTest *rtc;
#endif

#ifdef __APLEX_QT_USB__
    Usb *usb;
#endif

#ifdef __APLEX_QT_USB__
    Sd *sd;
#endif

#ifdef __APLEX_QT_UART__
    Uart *uart;
#endif

#ifdef __APLEX_QT_WATCHDOG__
    Watchdog *watchdog;
#endif

#ifdef __APLEX_QT_CANTEST__
    CanTest *can;
#endif

#ifdef __APLEX_QT_AUDIO__
    Audio *audio;
#endif

#ifdef __APLEX_QT_IFCONFIG__
    dpifconfig *aplex_ifconfig;
#endif

#ifdef __APLEX_QT_VERSION__
    version *version1;
#endif

#ifdef __APLEX_QT_PERF__
      OnOff *onoff;
      BurnCpu *burnCpu;
#endif

private slots:

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T17:31:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    led/led.cpp \
    buzzer/buzzer.cpp \
    eeprom/eeprom.cpp \
    inputpanel/myinputpanelcontext.cpp \
    inputpanel/myinputpanel.cpp \
    ping/ping.cpp \
    usb/usb.cpp \
    SD/sd.cpp \
    uart/uart.cpp \
    watchdog/watchdog.cpp \
    can/thread.cpp \
    can/canTest.cpp \
    network/qipaddressedititem.cpp \
    network/qipaddressedit.cpp \
    network/network.cpp \
    network/interface.cpp \
    audio/audio.cpp \
    backlight/backlight.cpp \
    rtc/rtcTest.cpp \
    info/info.cpp \
    burncpu/parser.cpp \
    burncpu/burnCpu.cpp \
    gpio/myGpio.cpp \
    version/version.cpp \
    ifconfig/dpifconfig.cpp

HEADERS  += mainwindow.h \
    led/led.h \
    buzzer/buzzer.h \
    eeprom/eeprom.h \
    inputpanel/myinputpanelcontext.h \
    inputpanel/myinputpanel.h \
    ping/ping.h \
    usb/usb.h \
    SD/sd.h \
    uart/uart.h \
    watchdog/watchdog.h \
    can/thread.h \
    can/canTest.h \
    network/qipaddressedititem.h \
    network/qipaddressedit.h \
    network/network.h \
    network/interface.h \
    audio/audio.h \
    backlight/backlight.h \
    rtc/rtcTest.h \
    info/info.h \
    burncpu/parser.h \
    burncpu/burnCpu.h \
    gpio/myGpio.h \
    version/version.h \
    ifconfig/dpifconfig.h

FORMS    += mainwindow.ui \
    led/led.ui \
    buzzer/buzzer.ui \
    eeprom/eeprom.ui \
    inputpanel/myinputpanelform.ui \
    ping/ping.ui \
    usb/usb.ui \
    SD/sd.ui \
    uart/uart.ui \
    watchdog/watchdog.ui \
    can/canTest.ui \
    network/network.ui \
    audio/audio.ui \
    backlight/backlight.ui \
    rtc/rtcTest.ui \
    info/info.ui \
    burncpu/burnCpu.ui \
    gpio/myGpio.ui \
    version/version.ui \
    ifconfig/dpifconfig.ui

OTHER_FILES +=

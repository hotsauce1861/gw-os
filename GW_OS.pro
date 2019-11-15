TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    gw_os/gw_event.c \
    gw_os/gw_fifo.c \
    gw_os/gw_list.c \
    gw_os/gw_msgs.c \
    gw_os/gw_tasks.c \
    gw_os/gw_timer.c \
    main.c \
    test/test_list.c
INCLUDEPATH += gw_os
HEADERS += \
    gw_os/gw_event.h \
    gw_os/gw_fifo.h \
    gw_os/gw_hal.h \
    gw_os/gw_list.h \
    gw_os/gw_msgs.h \
    gw_os/gw_tasks.h \
    gw_os/gw_timer.h \
    gw_os/gw_type.h

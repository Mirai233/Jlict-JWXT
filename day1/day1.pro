QT += core gui widgets network webenginewidgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myhttp.cpp \
    mylabel.cpp \
    form.cpp \
    loadingdialog.cpp

HEADERS += \
    chinese.h \
    mainwindow.h \
    myhttp.h \
    mylabel.h \
    form.h \
    loadingdialog.h

RESOURCES += \
    resource.qrc

RC_FILE += J.rc

DISTFILES += \
    J.rc \
    Style.qss \
    checkbox_checked.png \
    radiobutton-checked-md.png \
    radiobutton-unchecked-md.png \
    checkbox_unchecked.png

FORMS += \
    form.ui


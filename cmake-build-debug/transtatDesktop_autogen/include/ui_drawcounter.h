/********************************************************************************
** Form generated from reading UI file 'drawcounter.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWCOUNTER_H
#define UI_DRAWCOUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawCounter
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbl_mode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbl_user;
    QLineEdit *le_counter;
    QLabel *lbl_user_2;
    QLineEdit *le_counter_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_user_3;
    QLineEdit *le_counter_3;
    QLabel *lbl_user_4;
    QLineEdit *le_counter_4;
    QWidget *imgViewer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_apply;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DrawCounter)
    {
        if (DrawCounter->objectName().isEmpty())
            DrawCounter->setObjectName(QStringLiteral("DrawCounter"));
        DrawCounter->resize(1288, 1031);
        DrawCounter->setStyleSheet(QLatin1String("\n"
"QWidget\n"
"{\n"
"	background-color:#ffffff;\n"
"        color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
"QFrame{\n"
"background-color: #DCDCDC;\n"
"}\n"
"\n"
"QPushButton{\n"
"background-color: #657786;\n"
"color: #FFFFFF;\n"
"font-size:12px;\n"
"padding-left: 10px;\n"
"padding-right:10px;\n"
"}\n"
"QLabel{\n"
"background-color:rgba(0,0,0,0%);\n"
"color:#000000;\n"
"font-size: 14px;\n"
"padding-right:10px;\n"
"}\n"
"QPushButton::hover{\n"
"\n"
"background-color: #696969;\n"
"color: #FFFFFF;\n"
" border-style: outset;\n"
"    border-width: 2px;\n"
"    border-color: #FFFFFF;\n"
"}\n"
"QPushButton::pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0.511, x2:1, y2:0.511, stop:0 rgba(0, 207, 179, 255),stop:1 rgba(70, 255, 230, 255));\n"
"\n"
"}\n"
"QGroupBox{\n"
"background-color:transparent;\n"
"qproperty-alignment: AlignLeft;\n"
"font-weight:bold;\n"
"	font-size: 12px;\n"
"color: #000000;\n"
"}\n"
"QLineEdit{\n"
"border:1px  solid#2F4F4F;\n"
"color:black;\n"
"padding-left: 20px;\n"
"paddi"
                        "ng-right:20px;\n"
"font-size:12px;\n"
"background-color: #ffffff;\n"
"}\n"
"QLineEdit:hover{\n"
"border:2px  solid#898F9C;\n"
"color:black;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"font-size:12px;\n"
"background-color: #ffffff;\n"
"}\n"
"QLineEdit:focus{\n"
"border:2px  solid#4267B2;\n"
"color:black;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"font-size:12px;\n"
"background-color: #ffffff;\n"
"}\n"
"\n"
"QComboBox{\n"
"border:2px  solid#2F4F4F;\n"
"color:black;\n"
"font-size: 12px;\n"
"padding-left: 20px;\n"
"padding-right:20px;\n"
"background-color: #ffffff;\n"
"}\n"
"QGroupBox{\n"
"\n"
"border:1px  solid#000000;\n"
"border-color:#000000;\n"
"color:#000000;\n"
"\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(DrawCounter);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_mode = new QLabel(DrawCounter);
        lbl_mode->setObjectName(QStringLiteral("lbl_mode"));
        lbl_mode->setMinimumSize(QSize(320, 40));
        lbl_mode->setMaximumSize(QSize(320, 40));
        lbl_mode->setStyleSheet(QLatin1String("font: 16pt \"MS Shell Dlg 2\";\n"
"color:#4267B2;"));
        lbl_mode->setFrameShape(QFrame::NoFrame);
        lbl_mode->setFrameShadow(QFrame::Plain);
        lbl_mode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(lbl_mode);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbl_user = new QLabel(DrawCounter);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));
        lbl_user->setMinimumSize(QSize(120, 40));
        lbl_user->setMaximumSize(QSize(120, 40));
        lbl_user->setStyleSheet(QStringLiteral(""));
        lbl_user->setFrameShape(QFrame::Panel);
        lbl_user->setFrameShadow(QFrame::Raised);
        lbl_user->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lbl_user);

        le_counter = new QLineEdit(DrawCounter);
        le_counter->setObjectName(QStringLiteral("le_counter"));
        le_counter->setMinimumSize(QSize(400, 40));
        le_counter->setMaximumSize(QSize(400, 40));
        le_counter->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(le_counter);

        lbl_user_2 = new QLabel(DrawCounter);
        lbl_user_2->setObjectName(QStringLiteral("lbl_user_2"));
        lbl_user_2->setMinimumSize(QSize(120, 40));
        lbl_user_2->setMaximumSize(QSize(120, 40));
        lbl_user_2->setStyleSheet(QStringLiteral(""));
        lbl_user_2->setFrameShape(QFrame::Panel);
        lbl_user_2->setFrameShadow(QFrame::Raised);
        lbl_user_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lbl_user_2);

        le_counter_2 = new QLineEdit(DrawCounter);
        le_counter_2->setObjectName(QStringLiteral("le_counter_2"));
        le_counter_2->setMinimumSize(QSize(400, 40));
        le_counter_2->setMaximumSize(QSize(400, 40));
        le_counter_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(le_counter_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_user_3 = new QLabel(DrawCounter);
        lbl_user_3->setObjectName(QStringLiteral("lbl_user_3"));
        lbl_user_3->setMinimumSize(QSize(120, 40));
        lbl_user_3->setMaximumSize(QSize(120, 40));
        lbl_user_3->setStyleSheet(QStringLiteral(""));
        lbl_user_3->setFrameShape(QFrame::Panel);
        lbl_user_3->setFrameShadow(QFrame::Raised);
        lbl_user_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lbl_user_3);

        le_counter_3 = new QLineEdit(DrawCounter);
        le_counter_3->setObjectName(QStringLiteral("le_counter_3"));
        le_counter_3->setMinimumSize(QSize(400, 40));
        le_counter_3->setMaximumSize(QSize(400, 40));
        le_counter_3->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(le_counter_3);

        lbl_user_4 = new QLabel(DrawCounter);
        lbl_user_4->setObjectName(QStringLiteral("lbl_user_4"));
        lbl_user_4->setMinimumSize(QSize(120, 40));
        lbl_user_4->setMaximumSize(QSize(120, 40));
        lbl_user_4->setStyleSheet(QStringLiteral(""));
        lbl_user_4->setFrameShape(QFrame::Panel);
        lbl_user_4->setFrameShadow(QFrame::Raised);
        lbl_user_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lbl_user_4);

        le_counter_4 = new QLineEdit(DrawCounter);
        le_counter_4->setObjectName(QStringLiteral("le_counter_4"));
        le_counter_4->setMinimumSize(QSize(400, 40));
        le_counter_4->setMaximumSize(QSize(400, 40));
        le_counter_4->setStyleSheet(QStringLiteral(""));

        horizontalLayout_3->addWidget(le_counter_4);


        verticalLayout->addLayout(horizontalLayout_3);

        imgViewer = new QWidget(DrawCounter);
        imgViewer->setObjectName(QStringLiteral("imgViewer"));
        imgViewer->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imgViewer->sizePolicy().hasHeightForWidth());
        imgViewer->setSizePolicy(sizePolicy);
        imgViewer->setMinimumSize(QSize(1024, 768));
        imgViewer->setMaximumSize(QSize(60044, 40084));
        imgViewer->setStyleSheet(QStringLiteral("background-color: rgb(136, 138, 133);"));

        verticalLayout->addWidget(imgViewer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_apply = new QPushButton(DrawCounter);
        btn_apply->setObjectName(QStringLiteral("btn_apply"));
        btn_apply->setMinimumSize(QSize(120, 40));
        btn_apply->setStyleSheet(QStringLiteral("background-color: #00AB66;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/finishing/okay_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_apply->setIcon(icon);
        btn_apply->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(btn_apply);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_cancel = new QPushButton(DrawCounter);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setMinimumSize(QSize(120, 40));
        btn_cancel->setStyleSheet(QStringLiteral("background-color: #CC0000;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/finishing/cancel_3.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_cancel->setIcon(icon1);
        btn_cancel->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(btn_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DrawCounter);

        QMetaObject::connectSlotsByName(DrawCounter);
    } // setupUi

    void retranslateUi(QDialog *DrawCounter)
    {
        DrawCounter->setWindowTitle(QApplication::translate("DrawCounter", "Dialog", Q_NULLPTR));
        lbl_mode->setText(QApplication::translate("DrawCounter", "Draw Counter Line", Q_NULLPTR));
        lbl_user->setText(QApplication::translate("DrawCounter", "Counter Name", Q_NULLPTR));
        le_counter->setText(QString());
        le_counter->setPlaceholderText(QApplication::translate("DrawCounter", "Please Enter Counter Name", Q_NULLPTR));
        lbl_user_2->setText(QApplication::translate("DrawCounter", "Counter Name", Q_NULLPTR));
        le_counter_2->setText(QString());
        le_counter_2->setPlaceholderText(QApplication::translate("DrawCounter", "Please Enter Counter Name", Q_NULLPTR));
        lbl_user_3->setText(QApplication::translate("DrawCounter", "Counter Name", Q_NULLPTR));
        le_counter_3->setText(QString());
        le_counter_3->setPlaceholderText(QApplication::translate("DrawCounter", "Please Enter Counter Name", Q_NULLPTR));
        lbl_user_4->setText(QApplication::translate("DrawCounter", "Counter Name", Q_NULLPTR));
        le_counter_4->setText(QString());
        le_counter_4->setPlaceholderText(QApplication::translate("DrawCounter", "Please Enter Counter Name", Q_NULLPTR));
        btn_apply->setText(QApplication::translate("DrawCounter", "Apply", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("DrawCounter", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DrawCounter: public Ui_DrawCounter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWCOUNTER_H

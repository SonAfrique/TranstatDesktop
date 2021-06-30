/********************************************************************************
** Form generated from reading UI file 'magnifyvisuals.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAGNIFYVISUALS_H
#define UI_MAGNIFYVISUALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MagnifyVisuals
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbl_mode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbl_user;
    QLineEdit *le_counter;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *data_visual;

    void setupUi(QDialog *MagnifyVisuals)
    {
        if (MagnifyVisuals->objectName().isEmpty())
            MagnifyVisuals->setObjectName(QStringLiteral("MagnifyVisuals"));
        MagnifyVisuals->resize(1078, 1012);
        MagnifyVisuals->setStyleSheet(QLatin1String("\n"
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
        verticalLayout = new QVBoxLayout(MagnifyVisuals);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_mode = new QLabel(MagnifyVisuals);
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
        lbl_user = new QLabel(MagnifyVisuals);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));
        lbl_user->setMinimumSize(QSize(120, 40));
        lbl_user->setMaximumSize(QSize(120, 40));
        lbl_user->setStyleSheet(QStringLiteral(""));
        lbl_user->setFrameShape(QFrame::Panel);
        lbl_user->setFrameShadow(QFrame::Raised);
        lbl_user->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lbl_user);

        le_counter = new QLineEdit(MagnifyVisuals);
        le_counter->setObjectName(QStringLiteral("le_counter"));
        le_counter->setMinimumSize(QSize(400, 40));
        le_counter->setMaximumSize(QSize(400, 40));
        le_counter->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(le_counter);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(MagnifyVisuals);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(900, 900));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        data_visual = new QHBoxLayout();
        data_visual->setObjectName(QStringLiteral("data_visual"));

        verticalLayout_2->addLayout(data_visual);


        verticalLayout->addWidget(frame);


        retranslateUi(MagnifyVisuals);

        QMetaObject::connectSlotsByName(MagnifyVisuals);
    } // setupUi

    void retranslateUi(QDialog *MagnifyVisuals)
    {
        MagnifyVisuals->setWindowTitle(QApplication::translate("MagnifyVisuals", "Dialog", Q_NULLPTR));
        lbl_mode->setText(QApplication::translate("MagnifyVisuals", "Visual Magnifier", Q_NULLPTR));
        lbl_user->setText(QApplication::translate("MagnifyVisuals", "Counter Name", Q_NULLPTR));
        le_counter->setText(QString());
        le_counter->setPlaceholderText(QApplication::translate("MagnifyVisuals", "Please Enter Counter Name", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MagnifyVisuals: public Ui_MagnifyVisuals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAGNIFYVISUALS_H

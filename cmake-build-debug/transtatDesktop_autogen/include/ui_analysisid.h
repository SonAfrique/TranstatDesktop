/********************************************************************************
** Form generated from reading UI file 'analysisid.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSISID_H
#define UI_ANALYSISID_H

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

QT_BEGIN_NAMESPACE

class Ui_AnalysisId
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_mode;
    QLabel *lbl_user;
    QLineEdit *le_analysis_id;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_save;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_cancel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *AnalysisId)
    {
        if (AnalysisId->objectName().isEmpty())
            AnalysisId->setObjectName(QStringLiteral("AnalysisId"));
        AnalysisId->resize(420, 260);
        AnalysisId->setStyleSheet(QLatin1String("\n"
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
        verticalLayout = new QVBoxLayout(AnalysisId);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_mode = new QLabel(AnalysisId);
        lbl_mode->setObjectName(QStringLiteral("lbl_mode"));
        lbl_mode->setMinimumSize(QSize(320, 40));
        lbl_mode->setMaximumSize(QSize(320, 40));
        lbl_mode->setStyleSheet(QLatin1String("font: 16pt \"MS Shell Dlg 2\";\n"
"color:#4267B2;"));
        lbl_mode->setFrameShape(QFrame::NoFrame);
        lbl_mode->setFrameShadow(QFrame::Plain);
        lbl_mode->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(lbl_mode);

        lbl_user = new QLabel(AnalysisId);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));
        lbl_user->setMinimumSize(QSize(120, 40));
        lbl_user->setMaximumSize(QSize(120, 40));
        lbl_user->setStyleSheet(QStringLiteral(""));
        lbl_user->setFrameShape(QFrame::Panel);
        lbl_user->setFrameShadow(QFrame::Raised);
        lbl_user->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(lbl_user);

        le_analysis_id = new QLineEdit(AnalysisId);
        le_analysis_id->setObjectName(QStringLiteral("le_analysis_id"));
        le_analysis_id->setMinimumSize(QSize(400, 40));
        le_analysis_id->setMaximumSize(QSize(400, 40));
        le_analysis_id->setStyleSheet(QStringLiteral(""));

        verticalLayout_2->addWidget(le_analysis_id);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_save = new QPushButton(AnalysisId);
        btn_save->setObjectName(QStringLiteral("btn_save"));
        btn_save->setMinimumSize(QSize(120, 40));
        btn_save->setStyleSheet(QStringLiteral("background-color: #00AB66;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/finishing/okay_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_save->setIcon(icon);
        btn_save->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(btn_save);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_cancel = new QPushButton(AnalysisId);
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

        verticalSpacer_2 = new QSpacerItem(20, 22, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(AnalysisId);

        QMetaObject::connectSlotsByName(AnalysisId);
    } // setupUi

    void retranslateUi(QDialog *AnalysisId)
    {
        AnalysisId->setWindowTitle(QApplication::translate("AnalysisId", "Dialog", Q_NULLPTR));
        lbl_mode->setText(QApplication::translate("AnalysisId", "Analysis Task Identification", Q_NULLPTR));
        lbl_user->setText(QApplication::translate("AnalysisId", "Analysis Id", Q_NULLPTR));
        le_analysis_id->setText(QString());
        le_analysis_id->setPlaceholderText(QApplication::translate("AnalysisId", "Please Enter Counter Analysis Id", Q_NULLPTR));
        btn_save->setText(QApplication::translate("AnalysisId", "Save", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("AnalysisId", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AnalysisId: public Ui_AnalysisId {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISID_H

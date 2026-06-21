/********************************************************************************
** Form generated from reading UI file 'primitives_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRIMITIVES_MANAGER_H
#define UI_PRIMITIVES_MANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_tab_widget_with_checkboxes.h"

QT_BEGIN_NAMESPACE

class Ui_cPrimitivesManager
{
public:
    QVBoxLayout *verticalLayout;
    MyCheckBox *checkBox_show_wireframe_primitives;
    QGridLayout *gridLayout_23;
    QPushButton *pushButton_add_primitive_plane;
    QPushButton *pushButton_add_primitive_sphere;
    QPushButton *pushButton_add_primitive_box;
    QPushButton *pushButton_add_primitive_circle;
    QPushButton *pushButton_add_primitive_water;
    QPushButton *pushButton_add_primitive_cylinder;
    QPushButton *pushButton_add_primitive_cone;
    QPushButton *pushButton_add_primitive_torus;
    QPushButton *pushButton_add_primitive_rectangle;
    QPushButton *pushButton_add_primitive_prism;
    QPushButton *pushButton_add_primitive_ellipsoid;
    QPushButton *pushButton_add_primitive_capsule;
    QPushButton *pushButton_add_primitive_hexprism;
    QPushButton *pushButton_add_primitive_lava_plane;
    QPushButton *pushButton_add_primitive_octahedron;
    QPushButton *pushButton_add_primitive_pyramid;
    QPushButton *pushButton_add_primitive_terrain_plane;
    QGridLayout *gridLayout;
    QPushButton *pushButton_deletePrimitive;
    QPushButton *pushButton_placePrimitive;
    QPushButton *pushButton_alignRotation;
    QPushButton *pushButton_duplicatePrimitive;
    QPushButton *pushButton_enableAll;
    QPushButton *pushButton_disableAll;
    QPushButton *pushButton_onlySelected;
    MyTabWidgetWithCheckboxes *tabWidget_primitives;

    void setupUi(QWidget *cPrimitivesManager)
    {
        if (cPrimitivesManager->objectName().isEmpty())
            cPrimitivesManager->setObjectName(QString::fromUtf8("cPrimitivesManager"));
        cPrimitivesManager->resize(299, 685);
        verticalLayout = new QVBoxLayout(cPrimitivesManager);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        checkBox_show_wireframe_primitives = new MyCheckBox(cPrimitivesManager);
        checkBox_show_wireframe_primitives->setObjectName(QString::fromUtf8("checkBox_show_wireframe_primitives"));

        verticalLayout->addWidget(checkBox_show_wireframe_primitives);

        gridLayout_23 = new QGridLayout();
        gridLayout_23->setSpacing(2);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        pushButton_add_primitive_plane = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_plane->setObjectName(QString::fromUtf8("pushButton_add_primitive_plane"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(pushButton_add_primitive_plane->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_plane->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/primitives/icons/plane.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_plane->setIcon(icon);
        pushButton_add_primitive_plane->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_plane, 3, 1, 1, 1);

        pushButton_add_primitive_sphere = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_sphere->setObjectName(QString::fromUtf8("pushButton_add_primitive_sphere"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_sphere->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_sphere->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/primitives/icons/sphere.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_sphere->setIcon(icon1);
        pushButton_add_primitive_sphere->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_sphere, 2, 2, 1, 1);

        pushButton_add_primitive_box = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_box->setObjectName(QString::fromUtf8("pushButton_add_primitive_box"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_box->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_box->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/primitives/icons/box.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_box->setIcon(icon2);
        pushButton_add_primitive_box->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_box, 0, 2, 1, 1);

        pushButton_add_primitive_circle = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_circle->setObjectName(QString::fromUtf8("pushButton_add_primitive_circle"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_circle->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_circle->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/primitives/icons/circle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_circle->setIcon(icon3);
        pushButton_add_primitive_circle->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_circle, 0, 1, 1, 1);

        pushButton_add_primitive_water = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_water->setObjectName(QString::fromUtf8("pushButton_add_primitive_water"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_water->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_water->setSizePolicy(sizePolicy);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/primitives/icons/water.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_water->setIcon(icon4);
        pushButton_add_primitive_water->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_water, 3, 2, 1, 1);

        pushButton_add_primitive_cylinder = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_cylinder->setObjectName(QString::fromUtf8("pushButton_add_primitive_cylinder"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_cylinder->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_cylinder->setSizePolicy(sizePolicy);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/primitives/icons/cylinder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_cylinder->setIcon(icon5);
        pushButton_add_primitive_cylinder->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_cylinder, 2, 0, 1, 1);

        pushButton_add_primitive_cone = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_cone->setObjectName(QString::fromUtf8("pushButton_add_primitive_cone"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_cone->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_cone->setSizePolicy(sizePolicy);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/primitives/icons/cone.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_cone->setIcon(icon6);
        pushButton_add_primitive_cone->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_cone, 2, 1, 1, 1);

        pushButton_add_primitive_torus = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_torus->setObjectName(QString::fromUtf8("pushButton_add_primitive_torus"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_torus->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_torus->setSizePolicy(sizePolicy);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/primitives/icons/torus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_torus->setIcon(icon7);
        pushButton_add_primitive_torus->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_torus, 3, 0, 1, 1);

        pushButton_add_primitive_rectangle = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_rectangle->setObjectName(QString::fromUtf8("pushButton_add_primitive_rectangle"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_rectangle->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_rectangle->setSizePolicy(sizePolicy);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/primitives/icons/rectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_rectangle->setIcon(icon8);
        pushButton_add_primitive_rectangle->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_rectangle, 0, 0, 1, 1);

        pushButton_add_primitive_prism = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_prism->setObjectName(QString::fromUtf8("pushButton_add_primitive_prism"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_prism->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_prism->setSizePolicy(sizePolicy);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/primitives/icons/prism.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_prism->setIcon(icon9);
        pushButton_add_primitive_prism->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_prism, 4, 0, 1, 1);

        pushButton_add_primitive_ellipsoid = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_ellipsoid->setObjectName(QString::fromUtf8("pushButton_add_primitive_ellipsoid"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_ellipsoid->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_ellipsoid->setSizePolicy(sizePolicy);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/primitives/icons/ellipsoid.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_add_primitive_ellipsoid->setIcon(icon10);
        pushButton_add_primitive_ellipsoid->setIconSize(QSize(32, 32));

        gridLayout_23->addWidget(pushButton_add_primitive_ellipsoid, 4, 1, 1, 1);

        pushButton_add_primitive_capsule = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_capsule->setObjectName(QString::fromUtf8("pushButton_add_primitive_capsule"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_capsule->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_capsule->setSizePolicy(sizePolicy);

        gridLayout_23->addWidget(pushButton_add_primitive_capsule, 5, 0, 1, 1);

        pushButton_add_primitive_hexprism = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_hexprism->setObjectName(QString::fromUtf8("pushButton_add_primitive_hexprism"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_hexprism->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_hexprism->setSizePolicy(sizePolicy);

        gridLayout_23->addWidget(pushButton_add_primitive_hexprism, 5, 1, 1, 1);

        pushButton_add_primitive_lava_plane = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_lava_plane->setObjectName(QString::fromUtf8("pushButton_add_primitive_lava_plane"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_lava_plane->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_lava_plane->setSizePolicy(sizePolicy);

        gridLayout_23->addWidget(pushButton_add_primitive_lava_plane, 6, 0, 1, 1);

        pushButton_add_primitive_octahedron = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_octahedron->setObjectName(QString::fromUtf8("pushButton_add_primitive_octahedron"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_octahedron->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_octahedron->setSizePolicy(sizePolicy);

        gridLayout_23->addWidget(pushButton_add_primitive_octahedron, 6, 1, 1, 1);

        pushButton_add_primitive_pyramid = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_pyramid->setObjectName(QString::fromUtf8("pushButton_add_primitive_pyramid"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_pyramid->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_pyramid->setSizePolicy(sizePolicy);

        gridLayout_23->addWidget(pushButton_add_primitive_pyramid, 7, 0, 1, 1);

        pushButton_add_primitive_terrain_plane = new QPushButton(cPrimitivesManager);
        pushButton_add_primitive_terrain_plane->setObjectName(QString::fromUtf8("pushButton_add_primitive_terrain_plane"));
        sizePolicy.setHeightForWidth(pushButton_add_primitive_terrain_plane->sizePolicy().hasHeightForWidth());
        pushButton_add_primitive_terrain_plane->setSizePolicy(sizePolicy);

        gridLayout_23->addWidget(pushButton_add_primitive_terrain_plane, 7, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_23);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 10, -1, -1);
        pushButton_deletePrimitive = new QPushButton(cPrimitivesManager);
        pushButton_deletePrimitive->setObjectName(QString::fromUtf8("pushButton_deletePrimitive"));

        gridLayout->addWidget(pushButton_deletePrimitive, 0, 1, 1, 1);

        pushButton_placePrimitive = new QPushButton(cPrimitivesManager);
        pushButton_placePrimitive->setObjectName(QString::fromUtf8("pushButton_placePrimitive"));

        gridLayout->addWidget(pushButton_placePrimitive, 0, 2, 1, 1);

        pushButton_alignRotation = new QPushButton(cPrimitivesManager);
        pushButton_alignRotation->setObjectName(QString::fromUtf8("pushButton_alignRotation"));

        gridLayout->addWidget(pushButton_alignRotation, 1, 0, 1, 1);

        pushButton_duplicatePrimitive = new QPushButton(cPrimitivesManager);
        pushButton_duplicatePrimitive->setObjectName(QString::fromUtf8("pushButton_duplicatePrimitive"));

        gridLayout->addWidget(pushButton_duplicatePrimitive, 0, 0, 1, 1);

        pushButton_enableAll = new QPushButton(cPrimitivesManager);
        pushButton_enableAll->setObjectName(QString::fromUtf8("pushButton_enableAll"));

        gridLayout->addWidget(pushButton_enableAll, 2, 0, 1, 1);

        pushButton_disableAll = new QPushButton(cPrimitivesManager);
        pushButton_disableAll->setObjectName(QString::fromUtf8("pushButton_disableAll"));

        gridLayout->addWidget(pushButton_disableAll, 2, 1, 1, 1);

        pushButton_onlySelected = new QPushButton(cPrimitivesManager);
        pushButton_onlySelected->setObjectName(QString::fromUtf8("pushButton_onlySelected"));

        gridLayout->addWidget(pushButton_onlySelected, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tabWidget_primitives = new MyTabWidgetWithCheckboxes(cPrimitivesManager);
        tabWidget_primitives->setObjectName(QString::fromUtf8("tabWidget_primitives"));

        verticalLayout->addWidget(tabWidget_primitives);


        retranslateUi(cPrimitivesManager);

        tabWidget_primitives->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(cPrimitivesManager);
    } // setupUi

    void retranslateUi(QWidget *cPrimitivesManager)
    {
        cPrimitivesManager->setWindowTitle(QCoreApplication::translate("cPrimitivesManager", "Form", nullptr));
        checkBox_show_wireframe_primitives->setText(QCoreApplication::translate("cPrimitivesManager", "Show wire-frame preview of primitives", nullptr));
        pushButton_add_primitive_plane->setText(QString());
        pushButton_add_primitive_sphere->setText(QString());
        pushButton_add_primitive_box->setText(QString());
        pushButton_add_primitive_circle->setText(QString());
        pushButton_add_primitive_water->setText(QString());
        pushButton_add_primitive_cylinder->setText(QString());
        pushButton_add_primitive_cone->setText(QString());
        pushButton_add_primitive_torus->setText(QString());
        pushButton_add_primitive_rectangle->setText(QString());
        pushButton_add_primitive_capsule->setText(QCoreApplication::translate("cPrimitivesManager", "Capsule", nullptr));
        pushButton_add_primitive_hexprism->setText(QCoreApplication::translate("cPrimitivesManager", "HexPrism", nullptr));
        pushButton_add_primitive_lava_plane->setText(QCoreApplication::translate("cPrimitivesManager", "Lava Plane", nullptr));
        pushButton_add_primitive_octahedron->setText(QCoreApplication::translate("cPrimitivesManager", "Octahedron", nullptr));
        pushButton_add_primitive_pyramid->setText(QCoreApplication::translate("cPrimitivesManager", "Pyramid", nullptr));
        pushButton_add_primitive_terrain_plane->setText(QCoreApplication::translate("cPrimitivesManager", "Terrain Plane", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_deletePrimitive->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Delete the selected light source.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_deletePrimitive->setText(QCoreApplication::translate("cPrimitivesManager", "Delete\n"
"primitive", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_placePrimitive->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Place a light source using the mouse pointer.</p><p>Light position (for selected light tab) can be manipulated in following ways:</p><p>- mouse click on the image places light in front of selected point (offset by placement distance.) Placement distance from the selected point can be adjusted using mouse wheel + alt key.</p><p>- move light by dragging the mouse pointer while holding left mouse button. Moves light while maintaining placement distance</p><p>- rotating mouse wheel while holding control key moves light forward/backward</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_placePrimitive->setText(QCoreApplication::translate("cPrimitivesManager", "Place/move\n"
"primitive", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_alignRotation->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Duplicate the selected light source. All parameters will be copied to the new one.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_alignRotation->setText(QCoreApplication::translate("cPrimitivesManager", "Align rotation\n"
"to the camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_duplicatePrimitive->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Duplicate the selected light source. All parameters will be copied to the new one.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_duplicatePrimitive->setText(QCoreApplication::translate("cPrimitivesManager", "Duplicate\n"
"primitive", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_enableAll->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Duplicate the selected light source. All parameters will be copied to the new one.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_enableAll->setText(QCoreApplication::translate("cPrimitivesManager", "Enable all", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_disableAll->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Duplicate the selected light source. All parameters will be copied to the new one.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_disableAll->setText(QCoreApplication::translate("cPrimitivesManager", "Disable all", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_onlySelected->setToolTip(QCoreApplication::translate("cPrimitivesManager", "<html><head/><body><p>Duplicate the selected light source. All parameters will be copied to the new one.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_onlySelected->setText(QCoreApplication::translate("cPrimitivesManager", "Only selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cPrimitivesManager: public Ui_cPrimitivesManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIMITIVES_MANAGER_H

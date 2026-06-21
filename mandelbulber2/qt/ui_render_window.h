/********************************************************************************
** Form generated from reading UI file 'render_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDER_WINDOW_H
#define UI_RENDER_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dock_animation.h"
#include "dock_effects.h"
#include "dock_fake_lights.h"
#include "dock_fractal.h"
#include "dock_gamepad.h"
#include "dock_image_adjustments.h"
#include "dock_measurements.h"
#include "dock_mutation.h"
#include "dock_navigation.h"
#include "dock_pattern_lines.h"
#include "dock_queue.h"
#include "dock_rendering_engine.h"
#include "dock_statistics.h"
#include "material_manager_view.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_log_widget.h"
#include "my_scrolled_area.h"

QT_BEGIN_NAMESPACE

class Ui_RenderWindow
{
public:
    QAction *actionSave_as_JPG;
    QAction *actionSave_as_PNG;
    QAction *actionSave_as_PNG_16_bit;
    QAction *actionSave_as_PNG_16_bit_with_alpha_channel;
    QAction *actionLoad_settings;
    QAction *actionLoad_settings_from_clipboard;
    QAction *actionSave_settings;
    QAction *actionSave_settings_to_clipboard;
    QAction *actionSave_settings_as;
    QAction *actionProgramPreferences;
    QAction *actionQuit;
    QAction *actionSave_docks_positions;
    QAction *actionDefault_docks_positions;
    QAction *actionAnimation_docks_positions;
    QAction *actionAbout_Qt;
    QAction *actionAbout_Manual;
    QAction *actionAbout_ThirdParty;
    QAction *actionAbout_Mandelbulber;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionImport_settings_from_old_Mandelbulber;
    QAction *actionImport_settings_from_Mandelbulb3d;
    QAction *actionExportVoxelLayers;
    QAction *actionLoad_example;
    QAction *actionShow_mutation_dock;
    QAction *actionShow_animation_dock;
    QAction *actionShow_gamepad_dock;
    QAction *actionShow_queue_dock;
    QAction *actionShow_info_dock;
    QAction *actionShow_toolbar;
    QAction *actionStack_all_docks;
    QAction *actionShow_statistics_dock;
    QAction *actionSave_as_IMAGE;
    QAction *actionSave_as_EXR;
    QAction *actionSave_as_TIFF;
    QAction *actionAdd_Settings_to_Toolbar;
    QAction *actionAdd_CustomWindowStateToMenu;
    QAction *actionShow_fake_lights_dock;
    QAction *actionShow_measurement_dock;
    QAction *actionExport_Mesh;
    QAction *actionTest;
    QAction *actionRemove_Window_settings;
    QAction *actionUser_Manual;
    QAction *actionUser_News;
    QAction *actionUser_HotKeys;
    QAction *actionDetach_image_from_main_window;
    QAction *actionRandomizeAll;
    QAction *actionCleanSettings;
    QAction *actionRender_Image;
    QAction *actionStop_rendering;
    QAction *actionSave_as_default_settings;
    QAction *actionReset_to_default;
    QAction *actionDelete_default_settings;
    QAction *actionSettings_browser;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetWithImage;
    QVBoxLayout *verticalLayout_3;
    MyScrolledArea *scrollAreaForImage;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *scrollAreaLayoutRenderedImage;
    QVBoxLayout *verticalLayout_center;
    QHBoxLayout *hl_zoom;
    QLabel *label;
    MyComboBox *comboBox_image_preview_scale;
    QFrame *line;
    MyCheckBox *checkBox_show_cursor;
    QFrame *line_2;
    QLabel *label_mouse_click_functions;
    MyComboBox *comboBox_mouse_click_function;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_multiMode;
    QToolButton *toolButton_rotMode;
    QToolButton *toolButton_rollMode;
    QToolButton *toolButton_rotAroundMode;
    QToolButton *toolButton_moveMode;
    QToolButton *toolButton_preciseRotation;
    QLabel *label_2;
    MyComboBox *comboBox_grid_type;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menuImage;
    QMenu *menuFile;
    QMenu *menuRecent_Settings_list;
    QMenu *menuView;
    QMenu *menuSaved_window_layouts;
    QMenu *menuAbout;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QDockWidget *dockWidget_image_adjustments;
    QWidget *dockWidgetLeftContents;
    QVBoxLayout *verticalLayout_23;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_imageAdjustments;
    QVBoxLayout *verticalLayout_19;
    cDockImageAdjustments *widgetImageAdjustments;
    QDockWidget *dockWidget_navigation;
    QWidget *dockWidgetRightContents;
    QVBoxLayout *verticalLayout_24;
    cDockNavigation *widgetDockNavigation;
    QToolBar *toolBar;
    QDockWidget *dockWidget_effects;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_26;
    cDockEffects *widgetEffects;
    QDockWidget *dockWidget_mutation;
    QWidget *dockWidgetContents_mutation;
    QVBoxLayout *verticalLayout_mutation;
    QScrollArea *scrollArea_mutation;
    QWidget *scrollAreaWidgetContents_mutation;
    QVBoxLayout *verticalLayout_mutation_inner;
    cDockMutation *widgetDockMutation;
    QDockWidget *dockWidget_fake_lights;
    QWidget *dockWidgetContents_fake_lights;
    QVBoxLayout *verticalLayout_fake_lights;
    QScrollArea *scrollArea_fake_lights;
    QWidget *scrollAreaWidgetContents_fake_lights;
    QVBoxLayout *verticalLayout_fake_lights_scroll;
    cDockFakeLights *widgetFakeLights;
    QDockWidget *dockWidget_pattern_lines;
    QWidget *dockWidgetContents_pattern_lines;
    QVBoxLayout *verticalLayout_pattern_lines_wrap;
    QScrollArea *scrollArea_pattern_lines_dock;
    QWidget *scrollAreaWidgetContents_pattern_lines;
    QVBoxLayout *verticalLayout_pattern_lines_inner;
    cDockPatternLines *widgetPatternLines;
    QDockWidget *dockWidget_julia;
    QWidget *dockWidgetContents_julia;
    QVBoxLayout *verticalLayout_julia_dock;
    QScrollArea *scrollArea_julia_dock;
    QWidget *scrollAreaWidgetContents_julia;
    QVBoxLayout *verticalLayout_julia_inner;
    QLabel *label_julia_dock_placeholder;
    QDockWidget *dockWidget_primitives;
    QWidget *dockWidgetContents_primitives;
    QVBoxLayout *verticalLayout_primitives_dock;
    QLabel *label_primitives_dock_placeholder;
    QDockWidget *dockWidget_objects;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea_5;
    QWidget *scrollAreaWidgetContents_6;
    QVBoxLayout *verticalLayout_59;
    cDockFractal *widgetDockFractal;
    QDockWidget *dockWidget_rendering_engine;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_42;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_46;
    cDockRenderingEngine *widgetDockRenderingEngine;
    QDockWidget *dockWidget_info;
    QWidget *dockWidgetContents_info;
    QHBoxLayout *horizontalLayout_13;
    MyLogWidget *log_text;
    QDockWidget *dockWidget_animation;
    QWidget *dockWidgetContents_animation;
    QHBoxLayout *horizontalLayout_14;
    cDockAnimation *widgetDockAnimation;
    QDockWidget *dockWidget_histogram;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout_61;
    cDockStatistics *widgetDockStatistics;
    QDockWidget *dockWidget_queue_dock;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_78;
    QScrollArea *scrollArea_12;
    QWidget *scrollAreaWidgetContents_13;
    QVBoxLayout *verticalLayout_93;
    cDockQueue *widgetDockQueue;
    QDockWidget *dockWidget_measurement;
    QWidget *dockWidgetContents_6;
    QVBoxLayout *verticalLayout_118;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_7;
    QVBoxLayout *verticalLayout_4;
    cDockMeasurements *widgetDockMeasurements;
    QDockWidget *dockWidget_materialEditor;
    QWidget *dockWidgetContents_7;
    QVBoxLayout *verticalLayout_31;
    QScrollArea *scrollArea_material;
    QWidget *scrollAreaWidgetContents_material;
    QVBoxLayout *verticalLayout_materials;
    QDockWidget *dockWidget_Materials;
    QWidget *dockWidgetContents_8;
    QVBoxLayout *verticalLayout_32;
    cMaterialManagerView *widget_material_list_view;
    QDockWidget *dockWidget_gamepad_dock;
    QWidget *dockWidgetContents_9;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea_13;
    QWidget *scrollAreaWidgetContents_14;
    QVBoxLayout *verticalLayout_94;
    cDockGamepad *widgetDockGamepad;

    void setupUi(QMainWindow *RenderWindow)
    {
        if (RenderWindow->objectName().isEmpty())
            RenderWindow->setObjectName(QString::fromUtf8("RenderWindow"));
        RenderWindow->resize(1422, 1061);
        QFont font;
        font.setPointSize(8);
        font.setStyleStrategy(QFont::PreferAntialias);
        RenderWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/system/icons/mandelbulber.png"), QSize(), QIcon::Normal, QIcon::Off);
        RenderWindow->setWindowIcon(icon);
        RenderWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        RenderWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionSave_as_JPG = new QAction(RenderWindow);
        actionSave_as_JPG->setObjectName(QString::fromUtf8("actionSave_as_JPG"));
        QIcon icon1;
        QString iconThemeName = QString::fromUtf8("document-save-as");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/document-save-as.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave_as_JPG->setIcon(icon1);
        actionSave_as_PNG = new QAction(RenderWindow);
        actionSave_as_PNG->setObjectName(QString::fromUtf8("actionSave_as_PNG"));
        actionSave_as_PNG->setIcon(icon1);
        actionSave_as_PNG_16_bit = new QAction(RenderWindow);
        actionSave_as_PNG_16_bit->setObjectName(QString::fromUtf8("actionSave_as_PNG_16_bit"));
        actionSave_as_PNG_16_bit->setIcon(icon1);
        actionSave_as_PNG_16_bit_with_alpha_channel = new QAction(RenderWindow);
        actionSave_as_PNG_16_bit_with_alpha_channel->setObjectName(QString::fromUtf8("actionSave_as_PNG_16_bit_with_alpha_channel"));
        actionSave_as_PNG_16_bit_with_alpha_channel->setIcon(icon1);
        actionLoad_settings = new QAction(RenderWindow);
        actionLoad_settings->setObjectName(QString::fromUtf8("actionLoad_settings"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/document-open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionLoad_settings->setIcon(icon2);
#if QT_CONFIG(shortcut)
        actionLoad_settings->setShortcut(QString::fromUtf8("Ctrl+O"));
#endif // QT_CONFIG(shortcut)
        actionLoad_settings_from_clipboard = new QAction(RenderWindow);
        actionLoad_settings_from_clipboard->setObjectName(QString::fromUtf8("actionLoad_settings_from_clipboard"));
        actionLoad_settings_from_clipboard->setIcon(icon2);
#if QT_CONFIG(shortcut)
        actionLoad_settings_from_clipboard->setShortcut(QString::fromUtf8("Alt+O"));
#endif // QT_CONFIG(shortcut)
        actionSave_settings = new QAction(RenderWindow);
        actionSave_settings->setObjectName(QString::fromUtf8("actionSave_settings"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/document-save.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave_settings->setIcon(icon3);
#if QT_CONFIG(shortcut)
        actionSave_settings->setShortcut(QString::fromUtf8("Ctrl+S"));
#endif // QT_CONFIG(shortcut)
        actionSave_settings_to_clipboard = new QAction(RenderWindow);
        actionSave_settings_to_clipboard->setObjectName(QString::fromUtf8("actionSave_settings_to_clipboard"));
        actionSave_settings_to_clipboard->setIcon(icon3);
#if QT_CONFIG(shortcut)
        actionSave_settings_to_clipboard->setShortcut(QString::fromUtf8("Alt+S"));
#endif // QT_CONFIG(shortcut)
        actionSave_settings_as = new QAction(RenderWindow);
        actionSave_settings_as->setObjectName(QString::fromUtf8("actionSave_settings_as"));
        actionSave_settings_as->setIcon(icon3);
#if QT_CONFIG(shortcut)
        actionSave_settings_as->setShortcut(QString::fromUtf8("Ctrl+Shift+S"));
#endif // QT_CONFIG(shortcut)
        actionProgramPreferences = new QAction(RenderWindow);
        actionProgramPreferences->setObjectName(QString::fromUtf8("actionProgramPreferences"));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("preferences-system");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/system/icons/preferences-system.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionProgramPreferences->setIcon(icon4);
#if QT_CONFIG(shortcut)
        actionProgramPreferences->setShortcut(QString::fromUtf8("Ctrl+P"));
#endif // QT_CONFIG(shortcut)
        actionQuit = new QAction(RenderWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon5;
        iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8(":/system/icons/system-shutdown.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionQuit->setIcon(icon5);
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QString::fromUtf8("Ctrl+Q"));
#endif // QT_CONFIG(shortcut)
        actionSave_docks_positions = new QAction(RenderWindow);
        actionSave_docks_positions->setObjectName(QString::fromUtf8("actionSave_docks_positions"));
        actionSave_docks_positions->setIcon(icon3);
        actionDefault_docks_positions = new QAction(RenderWindow);
        actionDefault_docks_positions->setObjectName(QString::fromUtf8("actionDefault_docks_positions"));
        QIcon icon6;
        iconThemeName = QString::fromUtf8("edit-undo");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8(":/system/icons/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionDefault_docks_positions->setIcon(icon6);
        actionAnimation_docks_positions = new QAction(RenderWindow);
        actionAnimation_docks_positions->setObjectName(QString::fromUtf8("actionAnimation_docks_positions"));
        QIcon icon7;
        iconThemeName = QString::fromUtf8("video-x-generic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QString::fromUtf8(":/system/icons/video-x-generic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionAnimation_docks_positions->setIcon(icon7);
        actionAbout_Qt = new QAction(RenderWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionAbout_Manual = new QAction(RenderWindow);
        actionAbout_Manual->setObjectName(QString::fromUtf8("actionAbout_Manual"));
        actionAbout_ThirdParty = new QAction(RenderWindow);
        actionAbout_ThirdParty->setObjectName(QString::fromUtf8("actionAbout_ThirdParty"));
        actionAbout_Mandelbulber = new QAction(RenderWindow);
        actionAbout_Mandelbulber->setObjectName(QString::fromUtf8("actionAbout_Mandelbulber"));
        actionAbout_Mandelbulber->setIcon(icon);
        actionUndo = new QAction(RenderWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionUndo->setIcon(icon6);
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QString::fromUtf8("Ctrl+Z"));
#endif // QT_CONFIG(shortcut)
        actionRedo = new QAction(RenderWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon8;
        iconThemeName = QString::fromUtf8("edit-redo");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QString::fromUtf8(":/system/icons/edit-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionRedo->setIcon(icon8);
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QString::fromUtf8("Ctrl+Y"));
#endif // QT_CONFIG(shortcut)
        actionImport_settings_from_old_Mandelbulber = new QAction(RenderWindow);
        actionImport_settings_from_old_Mandelbulber->setObjectName(QString::fromUtf8("actionImport_settings_from_old_Mandelbulber"));
        actionImport_settings_from_old_Mandelbulber->setIcon(icon2);
#if QT_CONFIG(shortcut)
        actionImport_settings_from_old_Mandelbulber->setShortcut(QString::fromUtf8("Ctrl+I"));
#endif // QT_CONFIG(shortcut)
        actionImport_settings_from_Mandelbulb3d = new QAction(RenderWindow);
        actionImport_settings_from_Mandelbulb3d->setObjectName(QString::fromUtf8("actionImport_settings_from_Mandelbulb3d"));
        actionImport_settings_from_Mandelbulb3d->setIcon(icon2);
#if QT_CONFIG(shortcut)
        actionImport_settings_from_Mandelbulb3d->setShortcut(QString::fromUtf8("Ctrl+Alt+I"));
#endif // QT_CONFIG(shortcut)
        actionExportVoxelLayers = new QAction(RenderWindow);
        actionExportVoxelLayers->setObjectName(QString::fromUtf8("actionExportVoxelLayers"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/system/icons/layer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExportVoxelLayers->setIcon(icon9);
        actionLoad_example = new QAction(RenderWindow);
        actionLoad_example->setObjectName(QString::fromUtf8("actionLoad_example"));
        actionLoad_example->setIcon(icon2);
#if QT_CONFIG(shortcut)
        actionLoad_example->setShortcut(QString::fromUtf8("Ctrl+Alt+O"));
#endif // QT_CONFIG(shortcut)
        actionShow_mutation_dock = new QAction(RenderWindow);
        actionShow_mutation_dock->setObjectName(QString::fromUtf8("actionShow_mutation_dock"));
        actionShow_mutation_dock->setCheckable(true);
        actionShow_mutation_dock->setVisible(true);
        actionShow_animation_dock = new QAction(RenderWindow);
        actionShow_animation_dock->setObjectName(QString::fromUtf8("actionShow_animation_dock"));
        actionShow_animation_dock->setCheckable(true);
        actionShow_animation_dock->setVisible(true);
        actionShow_gamepad_dock = new QAction(RenderWindow);
        actionShow_gamepad_dock->setObjectName(QString::fromUtf8("actionShow_gamepad_dock"));
        actionShow_gamepad_dock->setCheckable(true);
        actionShow_gamepad_dock->setVisible(true);
        actionShow_queue_dock = new QAction(RenderWindow);
        actionShow_queue_dock->setObjectName(QString::fromUtf8("actionShow_queue_dock"));
        actionShow_queue_dock->setCheckable(true);
        actionShow_queue_dock->setVisible(true);
        actionShow_info_dock = new QAction(RenderWindow);
        actionShow_info_dock->setObjectName(QString::fromUtf8("actionShow_info_dock"));
        actionShow_info_dock->setCheckable(true);
        actionShow_info_dock->setVisible(true);
        actionShow_toolbar = new QAction(RenderWindow);
        actionShow_toolbar->setObjectName(QString::fromUtf8("actionShow_toolbar"));
        actionShow_toolbar->setCheckable(true);
        actionShow_toolbar->setVisible(true);
        actionStack_all_docks = new QAction(RenderWindow);
        actionStack_all_docks->setObjectName(QString::fromUtf8("actionStack_all_docks"));
        QIcon icon10;
        iconThemeName = QString::fromUtf8("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon10 = QIcon::fromTheme(iconThemeName);
        } else {
            icon10.addFile(QString::fromUtf8(":/system/icons/list-remove.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionStack_all_docks->setIcon(icon10);
        actionShow_statistics_dock = new QAction(RenderWindow);
        actionShow_statistics_dock->setObjectName(QString::fromUtf8("actionShow_statistics_dock"));
        actionShow_statistics_dock->setCheckable(true);
        actionSave_as_IMAGE = new QAction(RenderWindow);
        actionSave_as_IMAGE->setObjectName(QString::fromUtf8("actionSave_as_IMAGE"));
        actionSave_as_IMAGE->setIcon(icon1);
#if QT_CONFIG(shortcut)
        actionSave_as_IMAGE->setShortcut(QString::fromUtf8("Ctrl+Alt+S"));
#endif // QT_CONFIG(shortcut)
        actionSave_as_EXR = new QAction(RenderWindow);
        actionSave_as_EXR->setObjectName(QString::fromUtf8("actionSave_as_EXR"));
        actionSave_as_EXR->setIcon(icon1);
        actionSave_as_TIFF = new QAction(RenderWindow);
        actionSave_as_TIFF->setObjectName(QString::fromUtf8("actionSave_as_TIFF"));
        actionSave_as_TIFF->setIcon(icon1);
        actionAdd_Settings_to_Toolbar = new QAction(RenderWindow);
        actionAdd_Settings_to_Toolbar->setObjectName(QString::fromUtf8("actionAdd_Settings_to_Toolbar"));
        QIcon icon11;
        iconThemeName = QString::fromUtf8("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon11 = QIcon::fromTheme(iconThemeName);
        } else {
            icon11.addFile(QString::fromUtf8(":/system/icons/list-add.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionAdd_Settings_to_Toolbar->setIcon(icon11);
        actionAdd_CustomWindowStateToMenu = new QAction(RenderWindow);
        actionAdd_CustomWindowStateToMenu->setObjectName(QString::fromUtf8("actionAdd_CustomWindowStateToMenu"));
        actionAdd_CustomWindowStateToMenu->setIcon(icon11);
        actionShow_fake_lights_dock = new QAction(RenderWindow);
        actionShow_fake_lights_dock->setObjectName(QString::fromUtf8("actionShow_fake_lights_dock"));
        actionShow_fake_lights_dock->setCheckable(true);
        actionShow_measurement_dock = new QAction(RenderWindow);
        actionShow_measurement_dock->setObjectName(QString::fromUtf8("actionShow_measurement_dock"));
        actionShow_measurement_dock->setCheckable(true);
        actionExport_Mesh = new QAction(RenderWindow);
        actionExport_Mesh->setObjectName(QString::fromUtf8("actionExport_Mesh"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/system/icons/mesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport_Mesh->setIcon(icon12);
#if QT_CONFIG(shortcut)
        actionExport_Mesh->setShortcut(QString::fromUtf8("Ctrl+M"));
#endif // QT_CONFIG(shortcut)
        actionTest = new QAction(RenderWindow);
        actionTest->setObjectName(QString::fromUtf8("actionTest"));
        actionRemove_Window_settings = new QAction(RenderWindow);
        actionRemove_Window_settings->setObjectName(QString::fromUtf8("actionRemove_Window_settings"));
        actionRemove_Window_settings->setIcon(icon10);
        actionUser_Manual = new QAction(RenderWindow);
        actionUser_Manual->setObjectName(QString::fromUtf8("actionUser_Manual"));
        QIcon icon13;
        iconThemeName = QString::fromUtf8("help-contents");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon13 = QIcon::fromTheme(iconThemeName);
        } else {
            icon13.addFile(QString::fromUtf8(":/system/icons/help-contents.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionUser_Manual->setIcon(icon13);
#if QT_CONFIG(shortcut)
        actionUser_Manual->setShortcut(QString::fromUtf8("Ctrl+H"));
#endif // QT_CONFIG(shortcut)
        actionUser_News = new QAction(RenderWindow);
        actionUser_News->setObjectName(QString::fromUtf8("actionUser_News"));
        QIcon icon14;
        iconThemeName = QString::fromUtf8("dialog-information");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon14 = QIcon::fromTheme(iconThemeName);
        } else {
            icon14.addFile(QString::fromUtf8(":/system/icons/dialog-information.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionUser_News->setIcon(icon14);
        actionUser_HotKeys = new QAction(RenderWindow);
        actionUser_HotKeys->setObjectName(QString::fromUtf8("actionUser_HotKeys"));
        actionUser_HotKeys->setIcon(icon14);
#if QT_CONFIG(shortcut)
        actionUser_HotKeys->setShortcut(QString::fromUtf8("Alt+H"));
#endif // QT_CONFIG(shortcut)
        actionDetach_image_from_main_window = new QAction(RenderWindow);
        actionDetach_image_from_main_window->setObjectName(QString::fromUtf8("actionDetach_image_from_main_window"));
        actionDetach_image_from_main_window->setCheckable(true);
        actionRandomizeAll = new QAction(RenderWindow);
        actionRandomizeAll->setObjectName(QString::fromUtf8("actionRandomizeAll"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/gradient/icons/dice_colors.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRandomizeAll->setIcon(icon15);
        actionCleanSettings = new QAction(RenderWindow);
        actionCleanSettings->setObjectName(QString::fromUtf8("actionCleanSettings"));
        actionRender_Image = new QAction(RenderWindow);
        actionRender_Image->setObjectName(QString::fromUtf8("actionRender_Image"));
        QIcon icon16;
        iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon16 = QIcon::fromTheme(iconThemeName);
        } else {
            icon16.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionRender_Image->setIcon(icon16);
        actionStop_rendering = new QAction(RenderWindow);
        actionStop_rendering->setObjectName(QString::fromUtf8("actionStop_rendering"));
        QIcon icon17;
        iconThemeName = QString::fromUtf8("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon17 = QIcon::fromTheme(iconThemeName);
        } else {
            icon17.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionStop_rendering->setIcon(icon17);
        actionSave_as_default_settings = new QAction(RenderWindow);
        actionSave_as_default_settings->setObjectName(QString::fromUtf8("actionSave_as_default_settings"));
        actionReset_to_default = new QAction(RenderWindow);
        actionReset_to_default->setObjectName(QString::fromUtf8("actionReset_to_default"));
        QIcon icon18;
        iconThemeName = QString::fromUtf8("document-new");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon18 = QIcon::fromTheme(iconThemeName);
        } else {
            icon18.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionReset_to_default->setIcon(icon18);
        actionDelete_default_settings = new QAction(RenderWindow);
        actionDelete_default_settings->setObjectName(QString::fromUtf8("actionDelete_default_settings"));
        actionSettings_browser = new QAction(RenderWindow);
        actionSettings_browser->setObjectName(QString::fromUtf8("actionSettings_browser"));
        actionSettings_browser->setIcon(icon2);
        centralwidget = new QWidget(RenderWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        widgetWithImage = new QWidget(centralwidget);
        widgetWithImage->setObjectName(QString::fromUtf8("widgetWithImage"));
        verticalLayout_3 = new QVBoxLayout(widgetWithImage);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollAreaForImage = new MyScrolledArea(widgetWithImage);
        scrollAreaForImage->setObjectName(QString::fromUtf8("scrollAreaForImage"));
        scrollAreaForImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaForImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaForImage->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1215, 817));
        scrollAreaLayoutRenderedImage = new QVBoxLayout(scrollAreaWidgetContents);
        scrollAreaLayoutRenderedImage->setSpacing(0);
        scrollAreaLayoutRenderedImage->setContentsMargins(2, 2, 2, 2);
        scrollAreaLayoutRenderedImage->setObjectName(QString::fromUtf8("scrollAreaLayoutRenderedImage"));
        scrollAreaLayoutRenderedImage->setContentsMargins(0, 0, 0, 0);
        scrollAreaForImage->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollAreaForImage);

        verticalLayout_center = new QVBoxLayout();
        verticalLayout_center->setSpacing(2);
        verticalLayout_center->setObjectName(QString::fromUtf8("verticalLayout_center"));
        hl_zoom = new QHBoxLayout();
        hl_zoom->setSpacing(2);
        hl_zoom->setObjectName(QString::fromUtf8("hl_zoom"));
        label = new QLabel(widgetWithImage);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 0));

        hl_zoom->addWidget(label);

        comboBox_image_preview_scale = new MyComboBox(widgetWithImage);
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->addItem(QString());
        comboBox_image_preview_scale->setObjectName(QString::fromUtf8("comboBox_image_preview_scale"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_image_preview_scale->sizePolicy().hasHeightForWidth());
        comboBox_image_preview_scale->setSizePolicy(sizePolicy1);
        comboBox_image_preview_scale->setEditable(true);

        hl_zoom->addWidget(comboBox_image_preview_scale);

        line = new QFrame(widgetWithImage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        hl_zoom->addWidget(line);

        checkBox_show_cursor = new MyCheckBox(widgetWithImage);
        checkBox_show_cursor->setObjectName(QString::fromUtf8("checkBox_show_cursor"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_show_cursor->sizePolicy().hasHeightForWidth());
        checkBox_show_cursor->setSizePolicy(sizePolicy2);

        hl_zoom->addWidget(checkBox_show_cursor);

        line_2 = new QFrame(widgetWithImage);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        hl_zoom->addWidget(line_2);

        label_mouse_click_functions = new QLabel(widgetWithImage);
        label_mouse_click_functions->setObjectName(QString::fromUtf8("label_mouse_click_functions"));

        hl_zoom->addWidget(label_mouse_click_functions);

        comboBox_mouse_click_function = new MyComboBox(widgetWithImage);
        comboBox_mouse_click_function->addItem(QString());
        comboBox_mouse_click_function->setObjectName(QString::fromUtf8("comboBox_mouse_click_function"));
        sizePolicy1.setHeightForWidth(comboBox_mouse_click_function->sizePolicy().hasHeightForWidth());
        comboBox_mouse_click_function->setSizePolicy(sizePolicy1);
        comboBox_mouse_click_function->setMinimumSize(QSize(150, 0));

        hl_zoom->addWidget(comboBox_mouse_click_function);

        frame = new QFrame(widgetWithImage);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        toolButton_multiMode = new QToolButton(frame);
        toolButton_multiMode->setObjectName(QString::fromUtf8("toolButton_multiMode"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/navigation/icons/auto.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_multiMode->setIcon(icon19);
        toolButton_multiMode->setCheckable(true);
        toolButton_multiMode->setChecked(true);
        toolButton_multiMode->setAutoExclusive(true);

        horizontalLayout->addWidget(toolButton_multiMode);

        toolButton_rotMode = new QToolButton(frame);
        toolButton_rotMode->setObjectName(QString::fromUtf8("toolButton_rotMode"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/navigation/icons/rot.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_rotMode->setIcon(icon20);
        toolButton_rotMode->setCheckable(true);
        toolButton_rotMode->setAutoExclusive(true);

        horizontalLayout->addWidget(toolButton_rotMode);

        toolButton_rollMode = new QToolButton(frame);
        toolButton_rollMode->setObjectName(QString::fromUtf8("toolButton_rollMode"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/navigation/icons/roll.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_rollMode->setIcon(icon21);
        toolButton_rollMode->setCheckable(true);
        toolButton_rollMode->setAutoExclusive(true);

        horizontalLayout->addWidget(toolButton_rollMode);

        toolButton_rotAroundMode = new QToolButton(frame);
        toolButton_rotAroundMode->setObjectName(QString::fromUtf8("toolButton_rotAroundMode"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/navigation/icons/rot-around.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_rotAroundMode->setIcon(icon22);
        toolButton_rotAroundMode->setCheckable(true);
        toolButton_rotAroundMode->setAutoExclusive(true);

        horizontalLayout->addWidget(toolButton_rotAroundMode);

        toolButton_moveMode = new QToolButton(frame);
        toolButton_moveMode->setObjectName(QString::fromUtf8("toolButton_moveMode"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/navigation/icons/cross.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_moveMode->setIcon(icon23);
        toolButton_moveMode->setCheckable(true);
        toolButton_moveMode->setAutoExclusive(true);

        horizontalLayout->addWidget(toolButton_moveMode);


        hl_zoom->addWidget(frame);

        toolButton_preciseRotation = new QToolButton(widgetWithImage);
        toolButton_preciseRotation->setObjectName(QString::fromUtf8("toolButton_preciseRotation"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/navigation/icons/precise.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_preciseRotation->setIcon(icon24);
        toolButton_preciseRotation->setCheckable(true);

        hl_zoom->addWidget(toolButton_preciseRotation);

        label_2 = new QLabel(widgetWithImage);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hl_zoom->addWidget(label_2);

        comboBox_grid_type = new MyComboBox(widgetWithImage);
        comboBox_grid_type->addItem(QString());
        comboBox_grid_type->addItem(QString());
        comboBox_grid_type->addItem(QString());
        comboBox_grid_type->setObjectName(QString::fromUtf8("comboBox_grid_type"));

        hl_zoom->addWidget(comboBox_grid_type);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hl_zoom->addItem(horizontalSpacer);


        verticalLayout_center->addLayout(hl_zoom);


        verticalLayout_3->addLayout(verticalLayout_center);


        verticalLayout->addWidget(widgetWithImage);

        RenderWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RenderWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1422, 17));
        menuImage = new QMenu(menubar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuRecent_Settings_list = new QMenu(menuFile);
        menuRecent_Settings_list->setObjectName(QString::fromUtf8("menuRecent_Settings_list"));
        menuRecent_Settings_list->setIcon(icon2);
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSaved_window_layouts = new QMenu(menuView);
        menuSaved_window_layouts->setObjectName(QString::fromUtf8("menuSaved_window_layouts"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        RenderWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RenderWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QFont font1;
        font1.setPointSize(12);
        font1.setStyleStrategy(QFont::PreferAntialias);
        statusbar->setFont(font1);
        statusbar->setLayoutDirection(Qt::LeftToRight);
        RenderWindow->setStatusBar(statusbar);
        dockWidget_image_adjustments = new QDockWidget(RenderWindow);
        dockWidget_image_adjustments->setObjectName(QString::fromUtf8("dockWidget_image_adjustments"));
        dockWidget_image_adjustments->setFloating(false);
        dockWidget_image_adjustments->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetLeftContents = new QWidget();
        dockWidgetLeftContents->setObjectName(QString::fromUtf8("dockWidgetLeftContents"));
        verticalLayout_23 = new QVBoxLayout(dockWidgetLeftContents);
        verticalLayout_23->setSpacing(2);
        verticalLayout_23->setContentsMargins(2, 2, 2, 2);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        verticalLayout_23->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(dockWidgetLeftContents);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_imageAdjustments = new QWidget();
        scrollAreaWidgetContents_imageAdjustments->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_imageAdjustments"));
        scrollAreaWidgetContents_imageAdjustments->setGeometry(QRect(0, 0, 73, 146));
        verticalLayout_19 = new QVBoxLayout(scrollAreaWidgetContents_imageAdjustments);
        verticalLayout_19->setSpacing(2);
        verticalLayout_19->setContentsMargins(2, 2, 2, 2);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(2, 2, 2, 2);
        widgetImageAdjustments = new cDockImageAdjustments(scrollAreaWidgetContents_imageAdjustments);
        widgetImageAdjustments->setObjectName(QString::fromUtf8("widgetImageAdjustments"));

        verticalLayout_19->addWidget(widgetImageAdjustments);

        scrollArea->setWidget(scrollAreaWidgetContents_imageAdjustments);

        verticalLayout_23->addWidget(scrollArea);

        dockWidget_image_adjustments->setWidget(dockWidgetLeftContents);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_image_adjustments);
        dockWidget_navigation = new QDockWidget(RenderWindow);
        dockWidget_navigation->setObjectName(QString::fromUtf8("dockWidget_navigation"));
        dockWidget_navigation->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetRightContents = new QWidget();
        dockWidgetRightContents->setObjectName(QString::fromUtf8("dockWidgetRightContents"));
        verticalLayout_24 = new QVBoxLayout(dockWidgetRightContents);
        verticalLayout_24->setSpacing(2);
        verticalLayout_24->setContentsMargins(2, 2, 2, 2);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(2, 2, 2, 2);
        widgetDockNavigation = new cDockNavigation(dockWidgetRightContents);
        widgetDockNavigation->setObjectName(QString::fromUtf8("widgetDockNavigation"));

        verticalLayout_24->addWidget(widgetDockNavigation);

        dockWidget_navigation->setWidget(dockWidgetRightContents);
        RenderWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_navigation);
        toolBar = new QToolBar(RenderWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        RenderWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget_effects = new QDockWidget(RenderWindow);
        dockWidget_effects->setObjectName(QString::fromUtf8("dockWidget_effects"));
        dockWidget_effects->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        scrollArea_2 = new QScrollArea(dockWidgetContents_3);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 73, 146));
        verticalLayout_26 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_26->setSpacing(2);
        verticalLayout_26->setContentsMargins(2, 2, 2, 2);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        verticalLayout_26->setContentsMargins(2, 2, 2, 2);
        widgetEffects = new cDockEffects(scrollAreaWidgetContents_3);
        widgetEffects->setObjectName(QString::fromUtf8("widgetEffects"));

        verticalLayout_26->addWidget(widgetEffects);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_6->addWidget(scrollArea_2);

        dockWidget_effects->setWidget(dockWidgetContents_3);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_effects);
        dockWidget_mutation = new QDockWidget(RenderWindow);
        dockWidget_mutation->setObjectName(QString::fromUtf8("dockWidget_mutation"));
        dockWidget_mutation->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_mutation = new QWidget();
        dockWidgetContents_mutation->setObjectName(QString::fromUtf8("dockWidgetContents_mutation"));
        verticalLayout_mutation = new QVBoxLayout(dockWidgetContents_mutation);
        verticalLayout_mutation->setSpacing(2);
        verticalLayout_mutation->setContentsMargins(2, 2, 2, 2);
        verticalLayout_mutation->setObjectName(QString::fromUtf8("verticalLayout_mutation"));
        verticalLayout_mutation->setContentsMargins(2, 2, 2, 2);
        scrollArea_mutation = new QScrollArea(dockWidgetContents_mutation);
        scrollArea_mutation->setObjectName(QString::fromUtf8("scrollArea_mutation"));
        scrollArea_mutation->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_mutation->setWidgetResizable(true);
        scrollAreaWidgetContents_mutation = new QWidget();
        scrollAreaWidgetContents_mutation->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_mutation"));
        scrollAreaWidgetContents_mutation->setGeometry(QRect(0, 0, 440, 600));
        verticalLayout_mutation_inner = new QVBoxLayout(scrollAreaWidgetContents_mutation);
        verticalLayout_mutation_inner->setSpacing(2);
        verticalLayout_mutation_inner->setContentsMargins(2, 2, 2, 2);
        verticalLayout_mutation_inner->setObjectName(QString::fromUtf8("verticalLayout_mutation_inner"));
        verticalLayout_mutation_inner->setContentsMargins(2, 2, 2, 2);
        widgetDockMutation = new cDockMutation(scrollAreaWidgetContents_mutation);
        widgetDockMutation->setObjectName(QString::fromUtf8("widgetDockMutation"));

        verticalLayout_mutation_inner->addWidget(widgetDockMutation);

        scrollArea_mutation->setWidget(scrollAreaWidgetContents_mutation);

        verticalLayout_mutation->addWidget(scrollArea_mutation);

        dockWidget_mutation->setWidget(dockWidgetContents_mutation);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_mutation);
        dockWidget_fake_lights = new QDockWidget(RenderWindow);
        dockWidget_fake_lights->setObjectName(QString::fromUtf8("dockWidget_fake_lights"));
        dockWidget_fake_lights->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_fake_lights = new QWidget();
        dockWidgetContents_fake_lights->setObjectName(QString::fromUtf8("dockWidgetContents_fake_lights"));
        verticalLayout_fake_lights = new QVBoxLayout(dockWidgetContents_fake_lights);
        verticalLayout_fake_lights->setSpacing(2);
        verticalLayout_fake_lights->setContentsMargins(2, 2, 2, 2);
        verticalLayout_fake_lights->setObjectName(QString::fromUtf8("verticalLayout_fake_lights"));
        verticalLayout_fake_lights->setContentsMargins(2, 2, 2, 2);
        scrollArea_fake_lights = new QScrollArea(dockWidgetContents_fake_lights);
        scrollArea_fake_lights->setObjectName(QString::fromUtf8("scrollArea_fake_lights"));
        scrollArea_fake_lights->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_fake_lights->setWidgetResizable(true);
        scrollAreaWidgetContents_fake_lights = new QWidget();
        scrollAreaWidgetContents_fake_lights->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fake_lights"));
        scrollAreaWidgetContents_fake_lights->setGeometry(QRect(0, 0, 73, 146));
        verticalLayout_fake_lights_scroll = new QVBoxLayout(scrollAreaWidgetContents_fake_lights);
        verticalLayout_fake_lights_scroll->setSpacing(2);
        verticalLayout_fake_lights_scroll->setContentsMargins(2, 2, 2, 2);
        verticalLayout_fake_lights_scroll->setObjectName(QString::fromUtf8("verticalLayout_fake_lights_scroll"));
        verticalLayout_fake_lights_scroll->setContentsMargins(2, 2, 2, 2);
        widgetFakeLights = new cDockFakeLights(scrollAreaWidgetContents_fake_lights);
        widgetFakeLights->setObjectName(QString::fromUtf8("widgetFakeLights"));

        verticalLayout_fake_lights_scroll->addWidget(widgetFakeLights);

        scrollArea_fake_lights->setWidget(scrollAreaWidgetContents_fake_lights);

        verticalLayout_fake_lights->addWidget(scrollArea_fake_lights);

        dockWidget_fake_lights->setWidget(dockWidgetContents_fake_lights);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_fake_lights);
        dockWidget_pattern_lines = new QDockWidget(RenderWindow);
        dockWidget_pattern_lines->setObjectName(QString::fromUtf8("dockWidget_pattern_lines"));
        dockWidget_pattern_lines->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_pattern_lines = new QWidget();
        dockWidgetContents_pattern_lines->setObjectName(QString::fromUtf8("dockWidgetContents_pattern_lines"));
        verticalLayout_pattern_lines_wrap = new QVBoxLayout(dockWidgetContents_pattern_lines);
        verticalLayout_pattern_lines_wrap->setSpacing(2);
        verticalLayout_pattern_lines_wrap->setContentsMargins(2, 2, 2, 2);
        verticalLayout_pattern_lines_wrap->setObjectName(QString::fromUtf8("verticalLayout_pattern_lines_wrap"));
        verticalLayout_pattern_lines_wrap->setContentsMargins(2, 2, 2, 2);
        scrollArea_pattern_lines_dock = new QScrollArea(dockWidgetContents_pattern_lines);
        scrollArea_pattern_lines_dock->setObjectName(QString::fromUtf8("scrollArea_pattern_lines_dock"));
        scrollArea_pattern_lines_dock->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_pattern_lines_dock->setWidgetResizable(true);
        scrollAreaWidgetContents_pattern_lines = new QWidget();
        scrollAreaWidgetContents_pattern_lines->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_pattern_lines"));
        scrollAreaWidgetContents_pattern_lines->setGeometry(QRect(0, 0, 480, 900));
        verticalLayout_pattern_lines_inner = new QVBoxLayout(scrollAreaWidgetContents_pattern_lines);
        verticalLayout_pattern_lines_inner->setSpacing(2);
        verticalLayout_pattern_lines_inner->setContentsMargins(2, 2, 2, 2);
        verticalLayout_pattern_lines_inner->setObjectName(QString::fromUtf8("verticalLayout_pattern_lines_inner"));
        verticalLayout_pattern_lines_inner->setContentsMargins(2, 2, 2, 2);
        widgetPatternLines = new cDockPatternLines(scrollAreaWidgetContents_pattern_lines);
        widgetPatternLines->setObjectName(QString::fromUtf8("widgetPatternLines"));

        verticalLayout_pattern_lines_inner->addWidget(widgetPatternLines);

        scrollArea_pattern_lines_dock->setWidget(scrollAreaWidgetContents_pattern_lines);

        verticalLayout_pattern_lines_wrap->addWidget(scrollArea_pattern_lines_dock);

        dockWidget_pattern_lines->setWidget(dockWidgetContents_pattern_lines);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_pattern_lines);
        dockWidget_julia = new QDockWidget(RenderWindow);
        dockWidget_julia->setObjectName(QString::fromUtf8("dockWidget_julia"));
        dockWidget_julia->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_julia = new QWidget();
        dockWidgetContents_julia->setObjectName(QString::fromUtf8("dockWidgetContents_julia"));
        verticalLayout_julia_dock = new QVBoxLayout(dockWidgetContents_julia);
        verticalLayout_julia_dock->setSpacing(2);
        verticalLayout_julia_dock->setContentsMargins(2, 2, 2, 2);
        verticalLayout_julia_dock->setObjectName(QString::fromUtf8("verticalLayout_julia_dock"));
        verticalLayout_julia_dock->setContentsMargins(2, 2, 2, 2);
        scrollArea_julia_dock = new QScrollArea(dockWidgetContents_julia);
        scrollArea_julia_dock->setObjectName(QString::fromUtf8("scrollArea_julia_dock"));
        scrollArea_julia_dock->setWidgetResizable(true);
        scrollAreaWidgetContents_julia = new QWidget();
        scrollAreaWidgetContents_julia->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_julia"));
        scrollAreaWidgetContents_julia->setGeometry(QRect(0, 0, 400, 600));
        verticalLayout_julia_inner = new QVBoxLayout(scrollAreaWidgetContents_julia);
        verticalLayout_julia_inner->setSpacing(2);
        verticalLayout_julia_inner->setContentsMargins(2, 2, 2, 2);
        verticalLayout_julia_inner->setObjectName(QString::fromUtf8("verticalLayout_julia_inner"));
        label_julia_dock_placeholder = new QLabel(scrollAreaWidgetContents_julia);
        label_julia_dock_placeholder->setObjectName(QString::fromUtf8("label_julia_dock_placeholder"));

        verticalLayout_julia_inner->addWidget(label_julia_dock_placeholder);

        scrollArea_julia_dock->setWidget(scrollAreaWidgetContents_julia);

        verticalLayout_julia_dock->addWidget(scrollArea_julia_dock);

        dockWidget_julia->setWidget(dockWidgetContents_julia);
        RenderWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_julia);
        dockWidget_primitives = new QDockWidget(RenderWindow);
        dockWidget_primitives->setObjectName(QString::fromUtf8("dockWidget_primitives"));
        dockWidget_primitives->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_primitives = new QWidget();
        dockWidgetContents_primitives->setObjectName(QString::fromUtf8("dockWidgetContents_primitives"));
        verticalLayout_primitives_dock = new QVBoxLayout(dockWidgetContents_primitives);
        verticalLayout_primitives_dock->setSpacing(2);
        verticalLayout_primitives_dock->setContentsMargins(2, 2, 2, 2);
        verticalLayout_primitives_dock->setObjectName(QString::fromUtf8("verticalLayout_primitives_dock"));
        verticalLayout_primitives_dock->setContentsMargins(2, 2, 2, 2);
        label_primitives_dock_placeholder = new QLabel(dockWidgetContents_primitives);
        label_primitives_dock_placeholder->setObjectName(QString::fromUtf8("label_primitives_dock_placeholder"));

        verticalLayout_primitives_dock->addWidget(label_primitives_dock_placeholder);

        dockWidget_primitives->setWidget(dockWidgetContents_primitives);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_primitives);
        dockWidget_objects = new QDockWidget(RenderWindow);
        dockWidget_objects->setObjectName(QString::fromUtf8("dockWidget_objects"));
        dockWidget_objects->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_7 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        scrollArea_5 = new QScrollArea(dockWidgetContents_2);
        scrollArea_5->setObjectName(QString::fromUtf8("scrollArea_5"));
        scrollArea_5->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 73, 146));
        verticalLayout_59 = new QVBoxLayout(scrollAreaWidgetContents_6);
        verticalLayout_59->setSpacing(2);
        verticalLayout_59->setContentsMargins(2, 2, 2, 2);
        verticalLayout_59->setObjectName(QString::fromUtf8("verticalLayout_59"));
        verticalLayout_59->setContentsMargins(2, 2, 2, 2);
        widgetDockFractal = new cDockFractal(scrollAreaWidgetContents_6);
        widgetDockFractal->setObjectName(QString::fromUtf8("widgetDockFractal"));

        verticalLayout_59->addWidget(widgetDockFractal);

        scrollArea_5->setWidget(scrollAreaWidgetContents_6);

        verticalLayout_7->addWidget(scrollArea_5);

        dockWidget_objects->setWidget(dockWidgetContents_2);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_objects);
        dockWidget_rendering_engine = new QDockWidget(RenderWindow);
        dockWidget_rendering_engine->setObjectName(QString::fromUtf8("dockWidget_rendering_engine"));
        dockWidget_rendering_engine->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_42 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_42->setSpacing(2);
        verticalLayout_42->setContentsMargins(2, 2, 2, 2);
        verticalLayout_42->setObjectName(QString::fromUtf8("verticalLayout_42"));
        verticalLayout_42->setContentsMargins(2, 2, 2, 2);
        scrollArea_3 = new QScrollArea(dockWidgetContents);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 73, 146));
        verticalLayout_46 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_46->setSpacing(2);
        verticalLayout_46->setContentsMargins(2, 2, 2, 2);
        verticalLayout_46->setObjectName(QString::fromUtf8("verticalLayout_46"));
        verticalLayout_46->setContentsMargins(2, 2, 2, 2);
        widgetDockRenderingEngine = new cDockRenderingEngine(scrollAreaWidgetContents_4);
        widgetDockRenderingEngine->setObjectName(QString::fromUtf8("widgetDockRenderingEngine"));

        verticalLayout_46->addWidget(widgetDockRenderingEngine);

        scrollArea_3->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_42->addWidget(scrollArea_3);

        dockWidget_rendering_engine->setWidget(dockWidgetContents);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_rendering_engine);
        dockWidget_info = new QDockWidget(RenderWindow);
        dockWidget_info->setObjectName(QString::fromUtf8("dockWidget_info"));
        dockWidget_info->setEnabled(true);
        dockWidget_info->setFloating(false);
        dockWidgetContents_info = new QWidget();
        dockWidgetContents_info->setObjectName(QString::fromUtf8("dockWidgetContents_info"));
        horizontalLayout_13 = new QHBoxLayout(dockWidgetContents_info);
        horizontalLayout_13->setSpacing(2);
        horizontalLayout_13->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(2, 2, 2, 2);
        log_text = new MyLogWidget(dockWidgetContents_info);
        log_text->setObjectName(QString::fromUtf8("log_text"));

        horizontalLayout_13->addWidget(log_text);

        horizontalLayout_13->setStretch(0, 6);
        dockWidget_info->setWidget(dockWidgetContents_info);
        RenderWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_info);
        dockWidget_animation = new QDockWidget(RenderWindow);
        dockWidget_animation->setObjectName(QString::fromUtf8("dockWidget_animation"));
        dockWidgetContents_animation = new QWidget();
        dockWidgetContents_animation->setObjectName(QString::fromUtf8("dockWidgetContents_animation"));
        horizontalLayout_14 = new QHBoxLayout(dockWidgetContents_animation);
        horizontalLayout_14->setSpacing(2);
        horizontalLayout_14->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(2, 2, 2, 2);
        widgetDockAnimation = new cDockAnimation(dockWidgetContents_animation);
        widgetDockAnimation->setObjectName(QString::fromUtf8("widgetDockAnimation"));

        horizontalLayout_14->addWidget(widgetDockAnimation);

        dockWidget_animation->setWidget(dockWidgetContents_animation);
        RenderWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_animation);
        dockWidget_histogram = new QDockWidget(RenderWindow);
        dockWidget_histogram->setObjectName(QString::fromUtf8("dockWidget_histogram"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        verticalLayout_61 = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout_61->setSpacing(2);
        verticalLayout_61->setContentsMargins(2, 2, 2, 2);
        verticalLayout_61->setObjectName(QString::fromUtf8("verticalLayout_61"));
        verticalLayout_61->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_61->setContentsMargins(2, 2, 2, 2);
        widgetDockStatistics = new cDockStatistics(dockWidgetContents_4);
        widgetDockStatistics->setObjectName(QString::fromUtf8("widgetDockStatistics"));

        verticalLayout_61->addWidget(widgetDockStatistics);

        dockWidget_histogram->setWidget(dockWidgetContents_4);
        RenderWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_histogram);
        dockWidget_queue_dock = new QDockWidget(RenderWindow);
        dockWidget_queue_dock->setObjectName(QString::fromUtf8("dockWidget_queue_dock"));
        dockWidget_queue_dock->setFloating(false);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        verticalLayout_78 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_78->setSpacing(2);
        verticalLayout_78->setContentsMargins(2, 2, 2, 2);
        verticalLayout_78->setObjectName(QString::fromUtf8("verticalLayout_78"));
        verticalLayout_78->setContentsMargins(2, 2, 2, 2);
        scrollArea_12 = new QScrollArea(dockWidgetContents_5);
        scrollArea_12->setObjectName(QString::fromUtf8("scrollArea_12"));
        scrollArea_12->setWidgetResizable(true);
        scrollAreaWidgetContents_13 = new QWidget();
        scrollAreaWidgetContents_13->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_13"));
        scrollAreaWidgetContents_13->setGeometry(QRect(0, 0, 370, 73));
        verticalLayout_93 = new QVBoxLayout(scrollAreaWidgetContents_13);
        verticalLayout_93->setSpacing(2);
        verticalLayout_93->setContentsMargins(2, 2, 2, 2);
        verticalLayout_93->setObjectName(QString::fromUtf8("verticalLayout_93"));
        verticalLayout_93->setContentsMargins(2, 2, 2, 2);
        widgetDockQueue = new cDockQueue(scrollAreaWidgetContents_13);
        widgetDockQueue->setObjectName(QString::fromUtf8("widgetDockQueue"));

        verticalLayout_93->addWidget(widgetDockQueue);

        scrollArea_12->setWidget(scrollAreaWidgetContents_13);

        verticalLayout_78->addWidget(scrollArea_12);

        dockWidget_queue_dock->setWidget(dockWidgetContents_5);
        RenderWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_queue_dock);
        dockWidget_measurement = new QDockWidget(RenderWindow);
        dockWidget_measurement->setObjectName(QString::fromUtf8("dockWidget_measurement"));
        dockWidget_measurement->setFloating(false);
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        verticalLayout_118 = new QVBoxLayout(dockWidgetContents_6);
        verticalLayout_118->setSpacing(2);
        verticalLayout_118->setContentsMargins(2, 2, 2, 2);
        verticalLayout_118->setObjectName(QString::fromUtf8("verticalLayout_118"));
        verticalLayout_118->setContentsMargins(2, 2, 2, 2);
        scrollArea_4 = new QScrollArea(dockWidgetContents_6);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_7 = new QWidget();
        scrollAreaWidgetContents_7->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_7"));
        scrollAreaWidgetContents_7->setGeometry(QRect(0, 0, 89, 319));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_7);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        widgetDockMeasurements = new cDockMeasurements(scrollAreaWidgetContents_7);
        widgetDockMeasurements->setObjectName(QString::fromUtf8("widgetDockMeasurements"));

        verticalLayout_4->addWidget(widgetDockMeasurements);

        scrollArea_4->setWidget(scrollAreaWidgetContents_7);

        verticalLayout_118->addWidget(scrollArea_4);

        dockWidget_measurement->setWidget(dockWidgetContents_6);
        RenderWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_measurement);
        dockWidget_materialEditor = new QDockWidget(RenderWindow);
        dockWidget_materialEditor->setObjectName(QString::fromUtf8("dockWidget_materialEditor"));
        dockWidget_materialEditor->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_7 = new QWidget();
        dockWidgetContents_7->setObjectName(QString::fromUtf8("dockWidgetContents_7"));
        verticalLayout_31 = new QVBoxLayout(dockWidgetContents_7);
        verticalLayout_31->setSpacing(2);
        verticalLayout_31->setContentsMargins(2, 2, 2, 2);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        verticalLayout_31->setContentsMargins(2, 2, 2, 2);
        scrollArea_material = new QScrollArea(dockWidgetContents_7);
        scrollArea_material->setObjectName(QString::fromUtf8("scrollArea_material"));
        scrollArea_material->setWidgetResizable(true);
        scrollAreaWidgetContents_material = new QWidget();
        scrollAreaWidgetContents_material->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_material"));
        scrollAreaWidgetContents_material->setGeometry(QRect(0, 0, 73, 146));
        verticalLayout_materials = new QVBoxLayout(scrollAreaWidgetContents_material);
        verticalLayout_materials->setSpacing(3);
        verticalLayout_materials->setContentsMargins(2, 2, 2, 2);
        verticalLayout_materials->setObjectName(QString::fromUtf8("verticalLayout_materials"));
        verticalLayout_materials->setContentsMargins(2, 2, 2, 2);
        scrollArea_material->setWidget(scrollAreaWidgetContents_material);

        verticalLayout_31->addWidget(scrollArea_material);

        dockWidget_materialEditor->setWidget(dockWidgetContents_7);
        RenderWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_materialEditor);
        dockWidget_Materials = new QDockWidget(RenderWindow);
        dockWidget_Materials->setObjectName(QString::fromUtf8("dockWidget_Materials"));
        dockWidget_Materials->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_8 = new QWidget();
        dockWidgetContents_8->setObjectName(QString::fromUtf8("dockWidgetContents_8"));
        verticalLayout_32 = new QVBoxLayout(dockWidgetContents_8);
        verticalLayout_32->setSpacing(2);
        verticalLayout_32->setContentsMargins(2, 2, 2, 2);
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        verticalLayout_32->setContentsMargins(2, 2, 2, 2);
        widget_material_list_view = new cMaterialManagerView(dockWidgetContents_8);
        widget_material_list_view->setObjectName(QString::fromUtf8("widget_material_list_view"));

        verticalLayout_32->addWidget(widget_material_list_view);

        dockWidget_Materials->setWidget(dockWidgetContents_8);
        RenderWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget_Materials);
        dockWidget_gamepad_dock = new QDockWidget(RenderWindow);
        dockWidget_gamepad_dock->setObjectName(QString::fromUtf8("dockWidget_gamepad_dock"));
        dockWidgetContents_9 = new QWidget();
        dockWidgetContents_9->setObjectName(QString::fromUtf8("dockWidgetContents_9"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_9);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea_13 = new QScrollArea(dockWidgetContents_9);
        scrollArea_13->setObjectName(QString::fromUtf8("scrollArea_13"));
        scrollArea_13->setWidgetResizable(true);
        scrollAreaWidgetContents_14 = new QWidget();
        scrollAreaWidgetContents_14->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_14"));
        scrollAreaWidgetContents_14->setGeometry(QRect(0, 0, 73, 359));
        verticalLayout_94 = new QVBoxLayout(scrollAreaWidgetContents_14);
        verticalLayout_94->setSpacing(2);
        verticalLayout_94->setContentsMargins(2, 2, 2, 2);
        verticalLayout_94->setObjectName(QString::fromUtf8("verticalLayout_94"));
        verticalLayout_94->setContentsMargins(2, 2, 2, 2);
        widgetDockGamepad = new cDockGamepad(scrollAreaWidgetContents_14);
        widgetDockGamepad->setObjectName(QString::fromUtf8("widgetDockGamepad"));

        verticalLayout_94->addWidget(widgetDockGamepad);

        scrollArea_13->setWidget(scrollAreaWidgetContents_14);

        verticalLayout_2->addWidget(scrollArea_13);

        dockWidget_gamepad_dock->setWidget(dockWidgetContents_9);
        RenderWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget_gamepad_dock);
        QWidget::setTabOrder(scrollArea, scrollArea_2);
        QWidget::setTabOrder(scrollArea_2, scrollArea_5);
        QWidget::setTabOrder(scrollArea_5, scrollArea_3);
        QWidget::setTabOrder(scrollArea_3, scrollArea_material);
        QWidget::setTabOrder(scrollArea_material, comboBox_image_preview_scale);
        QWidget::setTabOrder(comboBox_image_preview_scale, checkBox_show_cursor);
        QWidget::setTabOrder(checkBox_show_cursor, comboBox_mouse_click_function);
        QWidget::setTabOrder(comboBox_mouse_click_function, scrollArea_12);
        QWidget::setTabOrder(scrollArea_12, scrollArea_13);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuImage->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuImage->addAction(actionSave_as_IMAGE);
        menuImage->addAction(actionSave_as_JPG);
        menuImage->addAction(actionSave_as_PNG);
        menuImage->addAction(actionSave_as_PNG_16_bit);
        menuImage->addAction(actionSave_as_PNG_16_bit_with_alpha_channel);
        menuImage->addAction(actionSave_as_EXR);
        menuImage->addAction(actionSave_as_TIFF);
        menuFile->addAction(actionReset_to_default);
        menuFile->addAction(actionLoad_settings);
        menuFile->addAction(actionLoad_settings_from_clipboard);
        menuFile->addAction(actionSettings_browser);
        menuFile->addAction(actionLoad_example);
        menuFile->addAction(menuRecent_Settings_list->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionSave_settings);
        menuFile->addAction(actionSave_settings_to_clipboard);
        menuFile->addSeparator();
        menuFile->addAction(actionImport_settings_from_old_Mandelbulber);
        menuFile->addAction(actionImport_settings_from_Mandelbulb3d);
        menuFile->addSeparator();
        menuFile->addAction(actionExportVoxelLayers);
        menuFile->addAction(actionExport_Mesh);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_as_default_settings);
        menuFile->addAction(actionDelete_default_settings);
        menuFile->addSeparator();
        menuFile->addAction(actionProgramPreferences);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuView->addAction(actionSave_docks_positions);
        menuView->addAction(actionDefault_docks_positions);
        menuView->addAction(actionAnimation_docks_positions);
        menuView->addAction(actionStack_all_docks);
        menuView->addAction(menuSaved_window_layouts->menuAction());
        menuView->addSeparator();
        menuView->addAction(actionDetach_image_from_main_window);
        menuView->addSeparator();
        menuView->addAction(actionShow_animation_dock);
        menuView->addAction(actionShow_info_dock);
        menuView->addAction(actionShow_toolbar);
        menuView->addAction(actionShow_statistics_dock);
        menuView->addAction(actionShow_gamepad_dock);
        menuView->addAction(actionShow_queue_dock);
        menuView->addAction(actionShow_measurement_dock);
        menuView->addAction(actionShow_fake_lights_dock);
        menuView->addAction(actionShow_mutation_dock);
        menuView->addSeparator();
        menuSaved_window_layouts->addAction(actionAdd_CustomWindowStateToMenu);
        menuSaved_window_layouts->addAction(actionRemove_Window_settings);
        menuSaved_window_layouts->addSeparator();
        menuAbout->addAction(actionAbout_Mandelbulber);
        menuAbout->addAction(actionAbout_Qt);
        menuAbout->addAction(actionAbout_ThirdParty);
        menuEdit->addAction(actionRender_Image);
        menuEdit->addAction(actionStop_rendering);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionRandomizeAll);
        menuEdit->addAction(actionCleanSettings);
        menuHelp->addAction(actionUser_Manual);
        menuHelp->addAction(actionUser_News);
        menuHelp->addAction(actionUser_HotKeys);
        toolBar->addAction(actionAdd_Settings_to_Toolbar);

        retranslateUi(RenderWindow);

        comboBox_image_preview_scale->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RenderWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RenderWindow)
    {
        RenderWindow->setWindowTitle(QCoreApplication::translate("RenderWindow", "3x3lion", nullptr));
        actionSave_as_JPG->setText(QCoreApplication::translate("RenderWindow", "&Save as JPG...", nullptr));
        actionSave_as_PNG->setText(QCoreApplication::translate("RenderWindow", "Save &as PNG...", nullptr));
        actionSave_as_PNG_16_bit->setText(QCoreApplication::translate("RenderWindow", "Save as &PNG 16 bit...", nullptr));
        actionSave_as_PNG_16_bit_with_alpha_channel->setText(QCoreApplication::translate("RenderWindow", "Save as PNG &16 bit with alpha channel", nullptr));
        actionLoad_settings->setText(QCoreApplication::translate("RenderWindow", "&Load settings...", nullptr));
        actionLoad_settings_from_clipboard->setText(QCoreApplication::translate("RenderWindow", "Load settings &from clipboard...", nullptr));
        actionSave_settings->setText(QCoreApplication::translate("RenderWindow", "&Save settings", nullptr));
        actionSave_settings_to_clipboard->setText(QCoreApplication::translate("RenderWindow", "Save settings &to clipboard", nullptr));
        actionSave_settings_as->setText(QCoreApplication::translate("RenderWindow", "Save settings as...", nullptr));
#if QT_CONFIG(statustip)
        actionSave_settings_as->setStatusTip(QCoreApplication::translate("RenderWindow", "Save settings in selected file", nullptr));
#endif // QT_CONFIG(statustip)
        actionProgramPreferences->setText(QCoreApplication::translate("RenderWindow", "&Program Preferences", nullptr));
        actionQuit->setText(QCoreApplication::translate("RenderWindow", "&Quit", nullptr));
        actionSave_docks_positions->setText(QCoreApplication::translate("RenderWindow", "&Save window layout as startup", nullptr));
        actionDefault_docks_positions->setText(QCoreApplication::translate("RenderWindow", "&Reset window layout to default", nullptr));
        actionAnimation_docks_positions->setText(QCoreApplication::translate("RenderWindow", "&Window layout for animation", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("RenderWindow", "About &Qt", nullptr));
        actionAbout_Manual->setText(QCoreApplication::translate("RenderWindow", "About &User Manual", nullptr));
        actionAbout_ThirdParty->setText(QCoreApplication::translate("RenderWindow", "About &Third Party", nullptr));
        actionAbout_Mandelbulber->setText(QCoreApplication::translate("RenderWindow", "&About Mandelbulber", nullptr));
        actionUndo->setText(QCoreApplication::translate("RenderWindow", "&Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("RenderWindow", "&Redo", nullptr));
        actionImport_settings_from_old_Mandelbulber->setText(QCoreApplication::translate("RenderWindow", "&Import settings from old Mandelbulber (v1.21)...", nullptr));
        actionImport_settings_from_Mandelbulb3d->setText(QCoreApplication::translate("RenderWindow", "&Import settings from Mandelbulb3d...", nullptr));
        actionExportVoxelLayers->setText(QCoreApplication::translate("RenderWindow", "Export &Voxel Layers", nullptr));
        actionLoad_example->setText(QCoreApplication::translate("RenderWindow", "Load &example...", nullptr));
        actionShow_mutation_dock->setText(QCoreApplication::translate("RenderWindow", "Show &mutation dock", nullptr));
        actionShow_animation_dock->setText(QCoreApplication::translate("RenderWindow", "Show a&nimation dock", nullptr));
        actionShow_gamepad_dock->setText(QCoreApplication::translate("RenderWindow", "Show &gamepad dock", nullptr));
        actionShow_queue_dock->setText(QCoreApplication::translate("RenderWindow", "Show &queue dock", nullptr));
        actionShow_info_dock->setText(QCoreApplication::translate("RenderWindow", "Show &Info dock", nullptr));
        actionShow_toolbar->setText(QCoreApplication::translate("RenderWindow", "Show &toolbar", nullptr));
        actionStack_all_docks->setText(QCoreApplication::translate("RenderWindow", "Sta&ck all docks", nullptr));
        actionShow_statistics_dock->setText(QCoreApplication::translate("RenderWindow", "S&how statistics", nullptr));
        actionSave_as_IMAGE->setText(QCoreApplication::translate("RenderWindow", "Save as Image", nullptr));
        actionSave_as_EXR->setText(QCoreApplication::translate("RenderWindow", "Save as &EXR", nullptr));
        actionSave_as_TIFF->setText(QCoreApplication::translate("RenderWindow", "Save as &TIFF", nullptr));
        actionAdd_Settings_to_Toolbar->setText(QCoreApplication::translate("RenderWindow", "Add current settings to toolbar", nullptr));
        actionAdd_CustomWindowStateToMenu->setText(QCoreApplication::translate("RenderWindow", "Add c&urrent window settings", nullptr));
        actionShow_fake_lights_dock->setText(QCoreApplication::translate("RenderWindow", "Fake Lights dock", nullptr));
        actionShow_measurement_dock->setText(QCoreApplication::translate("RenderWindow", "Show &measurement dock", nullptr));
        actionExport_Mesh->setText(QCoreApplication::translate("RenderWindow", "Export &Mesh", nullptr));
        actionTest->setText(QCoreApplication::translate("RenderWindow", "Test", nullptr));
        actionRemove_Window_settings->setText(QCoreApplication::translate("RenderWindow", "&Remove Window settings...", nullptr));
        actionUser_Manual->setText(QCoreApplication::translate("RenderWindow", "&User Manual", nullptr));
        actionUser_News->setText(QCoreApplication::translate("RenderWindow", "&News", nullptr));
        actionUser_HotKeys->setText(QCoreApplication::translate("RenderWindow", "&HotKeys", nullptr));
        actionDetach_image_from_main_window->setText(QCoreApplication::translate("RenderWindow", "Detach image &from main window", nullptr));
        actionRandomizeAll->setText(QCoreApplication::translate("RenderWindow", "Randomize all...", nullptr));
        actionCleanSettings->setText(QCoreApplication::translate("RenderWindow", "Clean settings...", nullptr));
        actionRender_Image->setText(QCoreApplication::translate("RenderWindow", "Render Image", nullptr));
#if QT_CONFIG(shortcut)
        actionRender_Image->setShortcut(QCoreApplication::translate("RenderWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStop_rendering->setText(QCoreApplication::translate("RenderWindow", "Stop rendering", nullptr));
#if QT_CONFIG(shortcut)
        actionStop_rendering->setShortcut(QCoreApplication::translate("RenderWindow", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as_default_settings->setText(QCoreApplication::translate("RenderWindow", "Save as default settings", nullptr));
        actionReset_to_default->setText(QCoreApplication::translate("RenderWindow", "New", nullptr));
#if QT_CONFIG(shortcut)
        actionReset_to_default->setShortcut(QCoreApplication::translate("RenderWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete_default_settings->setText(QCoreApplication::translate("RenderWindow", "Delete default settings", nullptr));
        actionSettings_browser->setText(QCoreApplication::translate("RenderWindow", "Thumbnail browser...", nullptr));
        label->setText(QCoreApplication::translate("RenderWindow", "Zoom:", nullptr));
        comboBox_image_preview_scale->setItemText(0, QCoreApplication::translate("RenderWindow", "Fit", nullptr));
        comboBox_image_preview_scale->setItemText(1, QCoreApplication::translate("RenderWindow", "400%", nullptr));
        comboBox_image_preview_scale->setItemText(2, QCoreApplication::translate("RenderWindow", "200%", nullptr));
        comboBox_image_preview_scale->setItemText(3, QCoreApplication::translate("RenderWindow", "100%", nullptr));
        comboBox_image_preview_scale->setItemText(4, QCoreApplication::translate("RenderWindow", "50%", nullptr));
        comboBox_image_preview_scale->setItemText(5, QCoreApplication::translate("RenderWindow", "25%", nullptr));
        comboBox_image_preview_scale->setItemText(6, QCoreApplication::translate("RenderWindow", "10%", nullptr));

        checkBox_show_cursor->setText(QCoreApplication::translate("RenderWindow", "Cursor", nullptr));
        label_mouse_click_functions->setText(QCoreApplication::translate("RenderWindow", "Mouse function:", nullptr));
        comboBox_mouse_click_function->setItemText(0, QCoreApplication::translate("RenderWindow", "No action", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_mouse_click_function->setToolTip(QCoreApplication::translate("RenderWindow", "<html><head/><body><p>Select the action performed when clicking on the image.</p><ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">No action</span> \342\200\223 disables mouse click actions.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Move the camera</span> \342\200\223 moves the camera or target (depends on movement/rotation mode).</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Set fog visibility</span> \342\200\223 sets the visibility distance for the basic fog effect.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0;"
                        " text-indent:0px;\"><span style=\" font-weight:600;\">Set DOF focus</span> \342\200\223 sets the focal distance/object for depth of field.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Get Julia constant</span> \342\200\223 samples the Julia constant from the clicked point.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Place light #n</span> \342\200\223 places the selected light at the clicked point. <br/>Ctrl + Mouse wheel: move light forward/backward <br/>Alt + Mouse wheel: adjust placement depth</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Place primitive</span> \342\200\223 places the selected primitive at the clicked point.</li><li style=\" margin-top:0px; margin-botto"
                        "m:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Place center of random light</span> \342\200\223 sets the distribution center for random lights.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Get coordinates</span> \342\200\223 shows 3D coordinates and distance at the clicked point.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Wrap limits around object</span> \342\200\223 adjusts render limits to the clicked object.</li><li style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Flight speed control</span> \342\200\223 LMB: speed up, RMB: slow down, arrows: strafe, Z/X: roll, Space: pause, Shift: orthogonal move.</li></ul></bo"
                        "dy></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        toolButton_multiMode->setToolTip(QCoreApplication::translate("RenderWindow", "Auto - Rotation mode depends on used button", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_multiMode->setText(QCoreApplication::translate("RenderWindow", "Multi", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_rotMode->setToolTip(QCoreApplication::translate("RenderWindow", "Rotate camera", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_rotMode->setText(QCoreApplication::translate("RenderWindow", "Rot", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_rollMode->setToolTip(QCoreApplication::translate("RenderWindow", "Roll camera", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_rollMode->setText(QCoreApplication::translate("RenderWindow", "Roll", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_rotAroundMode->setToolTip(QCoreApplication::translate("RenderWindow", "Rotate around indicated point", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_rotAroundMode->setText(QCoreApplication::translate("RenderWindow", "RotA", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_moveMode->setToolTip(QCoreApplication::translate("RenderWindow", "Move camera", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_moveMode->setText(QCoreApplication::translate("RenderWindow", "Move", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_preciseRotation->setToolTip(QCoreApplication::translate("RenderWindow", "Precise rotations", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_preciseRotation->setText(QCoreApplication::translate("RenderWindow", "P", nullptr));
        label_2->setText(QCoreApplication::translate("RenderWindow", "Grid:", nullptr));
        comboBox_grid_type->setItemText(0, QCoreApplication::translate("RenderWindow", "Crosshair", nullptr));
        comboBox_grid_type->setItemText(1, QCoreApplication::translate("RenderWindow", "Thirds grid", nullptr));
        comboBox_grid_type->setItemText(2, QCoreApplication::translate("RenderWindow", "Golden ratio", nullptr));

        menuImage->setTitle(QCoreApplication::translate("RenderWindow", "I&mage", nullptr));
        menuFile->setTitle(QCoreApplication::translate("RenderWindow", "File", nullptr));
        menuRecent_Settings_list->setTitle(QCoreApplication::translate("RenderWindow", "&Recent settings...", nullptr));
        menuView->setTitle(QCoreApplication::translate("RenderWindow", "&View", nullptr));
        menuSaved_window_layouts->setTitle(QCoreApplication::translate("RenderWindow", "Saved window &layouts", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("RenderWindow", "A&bout", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("RenderWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("RenderWindow", "Help", nullptr));
        dockWidget_image_adjustments->setWindowTitle(QCoreApplication::translate("RenderWindow", "Image adjustments", nullptr));
        dockWidget_navigation->setWindowTitle(QCoreApplication::translate("RenderWindow", "Navigation", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("RenderWindow", "toolBar", nullptr));
        dockWidget_effects->setWindowTitle(QCoreApplication::translate("RenderWindow", "Effects", nullptr));
        dockWidget_mutation->setWindowTitle(QCoreApplication::translate("RenderWindow", "Mutation", nullptr));
        dockWidget_fake_lights->setWindowTitle(QCoreApplication::translate("RenderWindow", "Fake Lights", nullptr));
        dockWidget_pattern_lines->setWindowTitle(QCoreApplication::translate("RenderWindow", "Patroon-lijnen", nullptr));
        dockWidget_julia->setWindowTitle(QCoreApplication::translate("RenderWindow", "Julia Explorer", nullptr));
        label_julia_dock_placeholder->setText(QCoreApplication::translate("RenderWindow", "Julia Explorer will be loaded here", nullptr));
        dockWidget_primitives->setWindowTitle(QCoreApplication::translate("RenderWindow", "Primitives", nullptr));
        label_primitives_dock_placeholder->setText(QCoreApplication::translate("RenderWindow", "Primitives will be loaded here", nullptr));
        dockWidget_objects->setWindowTitle(QCoreApplication::translate("RenderWindow", "Fractals", nullptr));
        dockWidget_rendering_engine->setWindowTitle(QCoreApplication::translate("RenderWindow", "Rendering engine", nullptr));
        dockWidget_info->setWindowTitle(QCoreApplication::translate("RenderWindow", "Info", nullptr));
        dockWidget_animation->setWindowTitle(QCoreApplication::translate("RenderWindow", "Animation", nullptr));
        dockWidget_histogram->setWindowTitle(QCoreApplication::translate("RenderWindow", "Statistics", nullptr));
#if QT_CONFIG(tooltip)
        dockWidget_queue_dock->setToolTip(QCoreApplication::translate("RenderWindow", "<html><head/><body><p>Queue tool allows for rendering a collection of settings files in the background.</p><p>While the list of settings files is being rendered, you can continue to work in the main window and also add more settings to the queue.</p><p>Methods to manage queue:<br/>- by adding items using <span style=\" font-style:italic;\">Add current settings</span> button<br/>- by editing queue.fractlist file<br/>- by putting files into queue folder and use button <span style=\" font-style:italic;\">Add orphaned<br/></span>- by adding single settings or lists using command line interface</p><p>Temporary settings files are stored in $HOME/.mandelbulber/queue folder and the list is in $HOME/.mandelbulber/queue.fractlist</p><p>The queue can be rendered in another instance of Mandelbulber program, as the queue is shared between applications. You can also launch another Mandelbulber from command line interface with -q option. Then this application will watch queue and render automatically all new items.</p><p>Res"
                        "ult images are saved into $HOME/.mandelbulber/images directory (or another if it's specified in application preferences.)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        dockWidget_queue_dock->setWindowTitle(QCoreApplication::translate("RenderWindow", "Queue", nullptr));
        dockWidget_measurement->setWindowTitle(QCoreApplication::translate("RenderWindow", "Measurement", nullptr));
        dockWidget_materialEditor->setWindowTitle(QCoreApplication::translate("RenderWindow", "Material editor", nullptr));
        dockWidget_Materials->setWindowTitle(QCoreApplication::translate("RenderWindow", "Materials", nullptr));
        dockWidget_gamepad_dock->setWindowTitle(QCoreApplication::translate("RenderWindow", "Gamepad", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RenderWindow: public Ui_RenderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDER_WINDOW_H

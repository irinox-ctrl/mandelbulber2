/********************************************************************************
** Form generated from reading UI file 'preferences_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_DIALOG_H
#define UI_PREFERENCES_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cPreferencesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea_general;
    QWidget *scrollAreaWidgetContents_general;
    QVBoxLayout *verticalLayout_general;
    QGroupBox *groupBox_file_paths;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_file_paths;
    MyLineEdit *text_default_textures_path;
    QLabel *label_settings_path;
    MyLineEdit *text_toolbar_path;
    QLabel *label_image_path;
    MyLineEdit *text_default_settings_path;
    QLabel *label_textures_path;
    QLabel *label_textures_path_2;
    QPushButton *pushButton_select_textures_path;
    QLabel *label_textures_path_3;
    MyLineEdit *text_default_image_path;
    QPushButton *pushButton_select_image_path;
    QPushButton *pushButton_select_toolbar_path;
    QPushButton *pushButton_select_settings_path;
    MyLineEdit *text_default_user_textures_path;
    QPushButton *pushButton_select_user_textures_path;
    QGroupBox *groupBox_system_look_and_feel;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QGridLayout *gridLayout_system_look_and_feel;
    MyComboBox *comboBox_ui_skin;
    MySpinBox *spinboxInt_ui_font_size;
    QComboBox *comboboxLanguage;
    QLabel *label_toolbar_icon_size;
    MyComboBox *comboBox_ui_style_type;
    MySpinBox *spinboxInt_toolbar_icon_size;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_19;
    MyGroupBox *groupCheck_ui_colorize;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_3;
    QLabel *label_16;
    MySpinBox *spinboxInt_ui_colorize_random_seed;
    MySpinBox *spinboxInt_custom_formula_font_size;
    QLabel *label_11;
    MyCheckBox *checkBox_display_tooltips;
    MySpinBox *spinboxInt_ui_layout_spacing;
    QLabel *label_37;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_11;
    QGridLayout *gridLayout_5;
    MyComboBox *comboBox_randomizer_preview_size;
    QLabel *label_17;
    QLabel *label_18;
    MyComboBox *comboBox_randomizer_preview_quality;
    QGroupBox *groupBox_system_look_and_feel_2;
    QVBoxLayout *verticalLayout_9;
    QGridLayout *gridLayout;
    QLabel *label_14;
    MySpinBox *spinboxInt_limit_CPU_cores;
    QLabel *label_20;
    MySpinBox *spinboxInt_maximum_texture_cache_size;
    QGridLayout *gridLayout_system_look_and_feel_2;
    QLabel *label_13;
    MyComboBox *comboBox_threads_priority;
    MyDoubleSpinBox *spinbox_auto_refresh_period;
    QLabel *label_15;
    QLabel *label_threads_priority;
    MySpinBox *spinboxInt_logging_verbosity;
    MyCheckBox *checkBox_console_output_enable;
    QLabel *label_path_to_logfile;
    MyCheckBox *checkBox_quit_do_not_ask_again;
    MyCheckBox *checkBox_description_popup_do_not_show_again;
    QPushButton *pushButton_retrieve_toolbar;
    QPushButton *pushButton_retrieve_materials;
    QSpacerItem *verticalSpacer;
    QWidget *tabImage;
    QVBoxLayout *verticalLayout_8;
    QScrollArea *scrollArea_image;
    QWidget *scrollAreaWidgetContents_image;
    QVBoxLayout *verticalLayout_image;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_12;
    QGridLayout *gridLayout_4;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_9;
    MyCheckBox *checkBox_color_enabled;
    MyComboBox *comboBox_color_quality;
    MyLineEdit *text_color_postfix;
    MyCheckBox *checkBox_alpha_enabled;
    MyComboBox *comboBox_alpha_quality;
    MyLineEdit *text_alpha_postfix;
    MyCheckBox *checkBox_zbuffer_enabled;
    MyComboBox *comboBox_zbuffer_quality;
    MyLineEdit *text_zbuffer_postfix;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    MyCheckBox *checkBox_zbuffer_invert;
    MyCheckBox *checkBox_zbuffer_logarithmic;
    MyGroupBox *groupCheck_zbuffer_constant_range;
    QGridLayout *gridLayout_7;
    QLabel *label_2;
    QLabel *label_3;
    MyLineEdit *logedit_zbuffer_min_depth;
    MyLineEdit *logedit_zbuffer_max_depth;
    QVBoxLayout *verticalLayout_10;
    MyGroupBox *groupCheck_optional_image_channels_enabled;
    QGridLayout *gridLayout_optional_image_channels;
    MyCheckBox *checkBox_diffuse_enabled;
    MyComboBox *comboBox_normal_quality;
    QLabel *label_rerender_required_info;
    MyCheckBox *checkBox_world_enabled;
    MyCheckBox *checkBox_not_denoised_channel_enabled;
    QLabel *label_image_channel_optional;
    MyCheckBox *checkBox_gi_channel_enabled;
    QLabel *label_image_quality_optional;
    MyComboBox *comboBox_normalWorld_quality;
    MyCheckBox *checkBox_normal_enabled;
    MyComboBox *comboBox_world_quality;
    MyComboBox *comboBox_shadow_channel_quality;
    MyComboBox *comboBox_not_denoised_channel_quality;
    MyLineEdit *text_specular_postfix;
    MyLineEdit *text_world_postfix;
    MyCheckBox *checkBox_specular_enabled;
    MyLineEdit *text_diffuse_postfix;
    MyComboBox *comboBox_diffuse_quality;
    MyLineEdit *text_shadow_channel_postfix;
    MyLineEdit *text_normalWorld_postfix;
    QLabel *label_image_postfix_optional;
    MyCheckBox *checkBox_normalWorld_enabled;
    MyLineEdit *text_gi_channel_postfix;
    MyCheckBox *checkBox_shadow_channel_enabled;
    MyComboBox *comboBox_specular_quality;
    MyLineEdit *text_normal_postfix;
    MyComboBox *comboBox_gi_channel_quality;
    MyLineEdit *text_not_denoised_channel_postfix;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    MyCheckBox *checkBox_linear_colorspace;
    MyCheckBox *checkBox_save_channels_in_separate_folders;
    MyCheckBox *checkBox_stereoscopic_in_separate_files;
    QLabel *label_5;
    MyCheckBox *checkBox_append_alpha_png;
    MySpinBox *spinboxInt_jpeg_quality;
    QCheckBox *checkBox_save_settings_with_image;
    QGroupBox *groupBox_thumbnail_options;
    QVBoxLayout *verticalLayout_thumbnail_options;
    QGridLayout *gridLayout_thumbnail_options;
    MyCheckBox *checkBox_thumbnails_with_opencl;
    QPushButton *pushButton_generate_thumbnail_cache;
    QPushButton *pushButton_clear_thumbnail_cache;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabOpenCL;
    QVBoxLayout *verticalLayout_outer_OpenCL;
    QScrollArea *scrollArea_OpenCL;
    QWidget *scrollAreaWidgetContents_OpenCL;
    QVBoxLayout *verticalLayout_OpenCL;
    MyGroupBox *groupCheck_opencl_enabled;
    QVBoxLayout *verticalLayout_opencl_inner;
    QLabel *label_explanation_opencl;
    QGridLayout *gridLayout_opencl_settings;
    QSlider *sliderInt_opencl_memory_limit;
    MySpinBox *spinboxInt_opencl_job_size_multiplier;
    QLabel *label_opencl_device;
    QLabel *label_precision;
    QPushButton *pushButton_select_clang_format_path;
    MyLineEdit *text_clang_format_path;
    QLabel *label_opencl_suggested_memory_limit;
    QLabel *label_opencl_device_2;
    QLabel *label_opencl_memory_limit_2;
    QVBoxLayout *verticalLayout_opencl_device;
    MyComboBox *comboBox_opencl_device_type;
    QListWidget *listWidget_opencl_device_list;
    MyCheckBox *checkBox_opencl_disable_build_cache;
    MyCheckBox *checkBox_opencl_use_fast_relaxed_math;
    MyComboBox *comboBox_opencl_precision;
    QLabel *label_opencl_memory_limit;
    QLabel *label_clang_format_path;
    QListWidget *listWidget_opencl_platform_list;
    MySpinBox *spinboxInt_opencl_memory_limit;
    QLabel *label_explanation_opencl_missing_features;
    QSpacerItem *verticalSpacer_opencl;
    QWidget *tab;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_key_layout_default;
    QPushButton *pushButton_key_layout_mb3d;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFormLayout *formLayout;
    QKeySequenceEdit *keySequenceEdit_key_render;
    QLabel *label_21;
    QKeySequenceEdit *keySequenceEdit_key_stop;
    QLabel *label_22;
    QKeySequenceEdit *keySequenceEdit_key_move_forward;
    QLabel *label_23;
    QKeySequenceEdit *keySequenceEdit_key_move_backward;
    QLabel *label_24;
    QKeySequenceEdit *keySequenceEdit_key_move_left;
    QLabel *label_25;
    QKeySequenceEdit *keySequenceEdit_key_move_right;
    QLabel *label_26;
    QKeySequenceEdit *keySequenceEdit_key_move_up;
    QLabel *label_27;
    QKeySequenceEdit *keySequenceEdit_key_move_down;
    QLabel *label_28;
    QKeySequenceEdit *keySequenceEdit_key_rotate_left;
    QLabel *label_29;
    QKeySequenceEdit *keySequenceEdit_key_rotate_right;
    QLabel *label_30;
    QKeySequenceEdit *keySequenceEdit_key_rotate_up;
    QLabel *label_33;
    QKeySequenceEdit *keySequenceEdit_key_rotate_down;
    QKeySequenceEdit *keySequenceEdit_key_add_keyframe;
    QLabel *label_31;
    QKeySequenceEdit *keySequenceEdit_key_modify_keyframe;
    QLabel *label_32;
    QLabel *label_34;
    QKeySequenceEdit *keySequenceEdit_key_roll_left;
    QKeySequenceEdit *keySequenceEdit_key_roll_right;
    QLabel *label_35;
    QLabel *label_36;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *cPreferencesDialog)
    {
        if (cPreferencesDialog->objectName().isEmpty())
            cPreferencesDialog->setObjectName(QString::fromUtf8("cPreferencesDialog"));
        cPreferencesDialog->resize(658, 942);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("preferences-system");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/preferences-system.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        cPreferencesDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(cPreferencesDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tabWidget = new QTabWidget(cPreferencesDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
        verticalLayout_7 = new QVBoxLayout(tabGeneral);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollArea_general = new QScrollArea(tabGeneral);
        scrollArea_general->setObjectName(QString::fromUtf8("scrollArea_general"));
        scrollArea_general->setWidgetResizable(true);
        scrollAreaWidgetContents_general = new QWidget();
        scrollAreaWidgetContents_general->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_general"));
        scrollAreaWidgetContents_general->setGeometry(QRect(0, 0, 630, 858));
        verticalLayout_general = new QVBoxLayout(scrollAreaWidgetContents_general);
        verticalLayout_general->setSpacing(2);
        verticalLayout_general->setObjectName(QString::fromUtf8("verticalLayout_general"));
        verticalLayout_general->setContentsMargins(2, 2, 2, 2);
        groupBox_file_paths = new QGroupBox(scrollAreaWidgetContents_general);
        groupBox_file_paths->setObjectName(QString::fromUtf8("groupBox_file_paths"));
        verticalLayout_3 = new QVBoxLayout(groupBox_file_paths);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_file_paths = new QGridLayout();
        gridLayout_file_paths->setSpacing(2);
        gridLayout_file_paths->setObjectName(QString::fromUtf8("gridLayout_file_paths"));
        text_default_textures_path = new MyLineEdit(groupBox_file_paths);
        text_default_textures_path->setObjectName(QString::fromUtf8("text_default_textures_path"));

        gridLayout_file_paths->addWidget(text_default_textures_path, 2, 2, 1, 1);

        label_settings_path = new QLabel(groupBox_file_paths);
        label_settings_path->setObjectName(QString::fromUtf8("label_settings_path"));

        gridLayout_file_paths->addWidget(label_settings_path, 1, 0, 1, 1);

        text_toolbar_path = new MyLineEdit(groupBox_file_paths);
        text_toolbar_path->setObjectName(QString::fromUtf8("text_toolbar_path"));

        gridLayout_file_paths->addWidget(text_toolbar_path, 4, 2, 1, 1);

        label_image_path = new QLabel(groupBox_file_paths);
        label_image_path->setObjectName(QString::fromUtf8("label_image_path"));

        gridLayout_file_paths->addWidget(label_image_path, 0, 0, 1, 1);

        text_default_settings_path = new MyLineEdit(groupBox_file_paths);
        text_default_settings_path->setObjectName(QString::fromUtf8("text_default_settings_path"));

        gridLayout_file_paths->addWidget(text_default_settings_path, 1, 2, 1, 1);

        label_textures_path = new QLabel(groupBox_file_paths);
        label_textures_path->setObjectName(QString::fromUtf8("label_textures_path"));

        gridLayout_file_paths->addWidget(label_textures_path, 2, 0, 1, 1);

        label_textures_path_2 = new QLabel(groupBox_file_paths);
        label_textures_path_2->setObjectName(QString::fromUtf8("label_textures_path_2"));

        gridLayout_file_paths->addWidget(label_textures_path_2, 4, 0, 1, 1);

        pushButton_select_textures_path = new QPushButton(groupBox_file_paths);
        pushButton_select_textures_path->setObjectName(QString::fromUtf8("pushButton_select_textures_path"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("folder");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/folder.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_select_textures_path->setIcon(icon1);

        gridLayout_file_paths->addWidget(pushButton_select_textures_path, 2, 3, 1, 1);

        label_textures_path_3 = new QLabel(groupBox_file_paths);
        label_textures_path_3->setObjectName(QString::fromUtf8("label_textures_path_3"));

        gridLayout_file_paths->addWidget(label_textures_path_3, 3, 0, 1, 1);

        text_default_image_path = new MyLineEdit(groupBox_file_paths);
        text_default_image_path->setObjectName(QString::fromUtf8("text_default_image_path"));

        gridLayout_file_paths->addWidget(text_default_image_path, 0, 2, 1, 1);

        pushButton_select_image_path = new QPushButton(groupBox_file_paths);
        pushButton_select_image_path->setObjectName(QString::fromUtf8("pushButton_select_image_path"));
        pushButton_select_image_path->setIcon(icon1);

        gridLayout_file_paths->addWidget(pushButton_select_image_path, 0, 3, 1, 1);

        pushButton_select_toolbar_path = new QPushButton(groupBox_file_paths);
        pushButton_select_toolbar_path->setObjectName(QString::fromUtf8("pushButton_select_toolbar_path"));
        pushButton_select_toolbar_path->setIcon(icon1);

        gridLayout_file_paths->addWidget(pushButton_select_toolbar_path, 4, 3, 1, 1);

        pushButton_select_settings_path = new QPushButton(groupBox_file_paths);
        pushButton_select_settings_path->setObjectName(QString::fromUtf8("pushButton_select_settings_path"));
        pushButton_select_settings_path->setIcon(icon1);

        gridLayout_file_paths->addWidget(pushButton_select_settings_path, 1, 3, 1, 1);

        text_default_user_textures_path = new MyLineEdit(groupBox_file_paths);
        text_default_user_textures_path->setObjectName(QString::fromUtf8("text_default_user_textures_path"));

        gridLayout_file_paths->addWidget(text_default_user_textures_path, 3, 2, 1, 1);

        pushButton_select_user_textures_path = new QPushButton(groupBox_file_paths);
        pushButton_select_user_textures_path->setObjectName(QString::fromUtf8("pushButton_select_user_textures_path"));
        pushButton_select_user_textures_path->setIcon(icon1);

        gridLayout_file_paths->addWidget(pushButton_select_user_textures_path, 3, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_file_paths);


        verticalLayout_general->addWidget(groupBox_file_paths);

        groupBox_system_look_and_feel = new QGroupBox(scrollAreaWidgetContents_general);
        groupBox_system_look_and_feel->setObjectName(QString::fromUtf8("groupBox_system_look_and_feel"));
        verticalLayout_5 = new QVBoxLayout(groupBox_system_look_and_feel);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(groupBox_system_look_and_feel);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);

        gridLayout_system_look_and_feel = new QGridLayout();
        gridLayout_system_look_and_feel->setSpacing(2);
        gridLayout_system_look_and_feel->setObjectName(QString::fromUtf8("gridLayout_system_look_and_feel"));
        comboBox_ui_skin = new MyComboBox(groupBox_system_look_and_feel);
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->addItem(QString());
        comboBox_ui_skin->setObjectName(QString::fromUtf8("comboBox_ui_skin"));

        gridLayout_system_look_and_feel->addWidget(comboBox_ui_skin, 2, 1, 1, 1);

        spinboxInt_ui_font_size = new MySpinBox(groupBox_system_look_and_feel);
        spinboxInt_ui_font_size->setObjectName(QString::fromUtf8("spinboxInt_ui_font_size"));
        spinboxInt_ui_font_size->setMinimum(5);
        spinboxInt_ui_font_size->setMaximum(50);

        gridLayout_system_look_and_feel->addWidget(spinboxInt_ui_font_size, 3, 1, 1, 1);

        comboboxLanguage = new QComboBox(groupBox_system_look_and_feel);
        comboboxLanguage->setObjectName(QString::fromUtf8("comboboxLanguage"));

        gridLayout_system_look_and_feel->addWidget(comboboxLanguage, 0, 1, 1, 1);

        label_toolbar_icon_size = new QLabel(groupBox_system_look_and_feel);
        label_toolbar_icon_size->setObjectName(QString::fromUtf8("label_toolbar_icon_size"));

        gridLayout_system_look_and_feel->addWidget(label_toolbar_icon_size, 6, 0, 1, 1);

        comboBox_ui_style_type = new MyComboBox(groupBox_system_look_and_feel);
        comboBox_ui_style_type->setObjectName(QString::fromUtf8("comboBox_ui_style_type"));

        gridLayout_system_look_and_feel->addWidget(comboBox_ui_style_type, 1, 1, 1, 1);

        spinboxInt_toolbar_icon_size = new MySpinBox(groupBox_system_look_and_feel);
        spinboxInt_toolbar_icon_size->setObjectName(QString::fromUtf8("spinboxInt_toolbar_icon_size"));
        spinboxInt_toolbar_icon_size->setMinimum(20);
        spinboxInt_toolbar_icon_size->setMaximum(400);
        spinboxInt_toolbar_icon_size->setValue(40);

        gridLayout_system_look_and_feel->addWidget(spinboxInt_toolbar_icon_size, 6, 1, 1, 1);

        label_6 = new QLabel(groupBox_system_look_and_feel);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_system_look_and_feel->addWidget(label_6, 1, 0, 1, 1);

        label_7 = new QLabel(groupBox_system_look_and_feel);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_system_look_and_feel->addWidget(label_7, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox_system_look_and_feel);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_system_look_and_feel->addWidget(label_4, 2, 0, 1, 1);

        label_19 = new QLabel(groupBox_system_look_and_feel);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setWordWrap(true);

        gridLayout_system_look_and_feel->addWidget(label_19, 5, 0, 1, 1);

        groupCheck_ui_colorize = new MyGroupBox(groupBox_system_look_and_feel);
        groupCheck_ui_colorize->setObjectName(QString::fromUtf8("groupCheck_ui_colorize"));
        groupCheck_ui_colorize->setCheckable(true);
        verticalLayout_2 = new QVBoxLayout(groupCheck_ui_colorize);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_16 = new QLabel(groupCheck_ui_colorize);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_3->addWidget(label_16, 0, 0, 1, 1);

        spinboxInt_ui_colorize_random_seed = new MySpinBox(groupCheck_ui_colorize);
        spinboxInt_ui_colorize_random_seed->setObjectName(QString::fromUtf8("spinboxInt_ui_colorize_random_seed"));
        spinboxInt_ui_colorize_random_seed->setMinimum(0);
        spinboxInt_ui_colorize_random_seed->setMaximum(65535);
        spinboxInt_ui_colorize_random_seed->setValue(0);

        gridLayout_3->addWidget(spinboxInt_ui_colorize_random_seed, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);


        gridLayout_system_look_and_feel->addWidget(groupCheck_ui_colorize, 8, 0, 1, 2);

        spinboxInt_custom_formula_font_size = new MySpinBox(groupBox_system_look_and_feel);
        spinboxInt_custom_formula_font_size->setObjectName(QString::fromUtf8("spinboxInt_custom_formula_font_size"));
        spinboxInt_custom_formula_font_size->setMinimum(5);
        spinboxInt_custom_formula_font_size->setMaximum(50);

        gridLayout_system_look_and_feel->addWidget(spinboxInt_custom_formula_font_size, 5, 1, 1, 1);

        label_11 = new QLabel(groupBox_system_look_and_feel);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_system_look_and_feel->addWidget(label_11, 0, 0, 1, 1);

        checkBox_display_tooltips = new MyCheckBox(groupBox_system_look_and_feel);
        checkBox_display_tooltips->setObjectName(QString::fromUtf8("checkBox_display_tooltips"));

        gridLayout_system_look_and_feel->addWidget(checkBox_display_tooltips, 7, 0, 1, 2);

        spinboxInt_ui_layout_spacing = new MySpinBox(groupBox_system_look_and_feel);
        spinboxInt_ui_layout_spacing->setObjectName(QString::fromUtf8("spinboxInt_ui_layout_spacing"));
        spinboxInt_ui_layout_spacing->setMinimum(1);
        spinboxInt_ui_layout_spacing->setMaximum(50);

        gridLayout_system_look_and_feel->addWidget(spinboxInt_ui_layout_spacing, 4, 1, 1, 1);

        label_37 = new QLabel(groupBox_system_look_and_feel);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_system_look_and_feel->addWidget(label_37, 4, 0, 1, 1);


        verticalLayout_5->addLayout(gridLayout_system_look_and_feel);


        verticalLayout_general->addWidget(groupBox_system_look_and_feel);

        groupBox = new QGroupBox(scrollAreaWidgetContents_general);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_11 = new QVBoxLayout(groupBox);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        comboBox_randomizer_preview_size = new MyComboBox(groupBox);
        comboBox_randomizer_preview_size->addItem(QString());
        comboBox_randomizer_preview_size->addItem(QString());
        comboBox_randomizer_preview_size->addItem(QString());
        comboBox_randomizer_preview_size->setObjectName(QString::fromUtf8("comboBox_randomizer_preview_size"));

        gridLayout_5->addWidget(comboBox_randomizer_preview_size, 0, 1, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_5->addWidget(label_17, 0, 0, 1, 1);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_5->addWidget(label_18, 1, 0, 1, 1);

        comboBox_randomizer_preview_quality = new MyComboBox(groupBox);
        comboBox_randomizer_preview_quality->addItem(QString());
        comboBox_randomizer_preview_quality->addItem(QString());
        comboBox_randomizer_preview_quality->addItem(QString());
        comboBox_randomizer_preview_quality->setObjectName(QString::fromUtf8("comboBox_randomizer_preview_quality"));

        gridLayout_5->addWidget(comboBox_randomizer_preview_quality, 1, 1, 1, 1);


        verticalLayout_11->addLayout(gridLayout_5);


        verticalLayout_general->addWidget(groupBox);

        groupBox_system_look_and_feel_2 = new QGroupBox(scrollAreaWidgetContents_general);
        groupBox_system_look_and_feel_2->setObjectName(QString::fromUtf8("groupBox_system_look_and_feel_2"));
        verticalLayout_9 = new QVBoxLayout(groupBox_system_look_and_feel_2);
        verticalLayout_9->setSpacing(2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        label_14 = new QLabel(groupBox_system_look_and_feel_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 0, 0, 1, 1);

        spinboxInt_limit_CPU_cores = new MySpinBox(groupBox_system_look_and_feel_2);
        spinboxInt_limit_CPU_cores->setObjectName(QString::fromUtf8("spinboxInt_limit_CPU_cores"));
        spinboxInt_limit_CPU_cores->setMinimum(1);
        spinboxInt_limit_CPU_cores->setMaximum(1000);

        gridLayout->addWidget(spinboxInt_limit_CPU_cores, 0, 1, 1, 1);

        label_20 = new QLabel(groupBox_system_look_and_feel_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 1, 0, 1, 1);

        spinboxInt_maximum_texture_cache_size = new MySpinBox(groupBox_system_look_and_feel_2);
        spinboxInt_maximum_texture_cache_size->setObjectName(QString::fromUtf8("spinboxInt_maximum_texture_cache_size"));
        spinboxInt_maximum_texture_cache_size->setMinimum(1);
        spinboxInt_maximum_texture_cache_size->setMaximum(1024);
        spinboxInt_maximum_texture_cache_size->setSingleStep(1);

        gridLayout->addWidget(spinboxInt_maximum_texture_cache_size, 1, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout);

        gridLayout_system_look_and_feel_2 = new QGridLayout();
        gridLayout_system_look_and_feel_2->setSpacing(2);
        gridLayout_system_look_and_feel_2->setObjectName(QString::fromUtf8("gridLayout_system_look_and_feel_2"));
        label_13 = new QLabel(groupBox_system_look_and_feel_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_system_look_and_feel_2->addWidget(label_13, 2, 0, 1, 1);

        comboBox_threads_priority = new MyComboBox(groupBox_system_look_and_feel_2);
        comboBox_threads_priority->addItem(QString());
        comboBox_threads_priority->addItem(QString());
        comboBox_threads_priority->addItem(QString());
        comboBox_threads_priority->addItem(QString());
        comboBox_threads_priority->setObjectName(QString::fromUtf8("comboBox_threads_priority"));
        comboBox_threads_priority->setFrame(true);

        gridLayout_system_look_and_feel_2->addWidget(comboBox_threads_priority, 0, 1, 1, 1);

        spinbox_auto_refresh_period = new MyDoubleSpinBox(groupBox_system_look_and_feel_2);
        spinbox_auto_refresh_period->setObjectName(QString::fromUtf8("spinbox_auto_refresh_period"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinbox_auto_refresh_period->sizePolicy().hasHeightForWidth());
        spinbox_auto_refresh_period->setSizePolicy(sizePolicy);
        spinbox_auto_refresh_period->setDecimals(2);
        spinbox_auto_refresh_period->setMinimum(0.010000000000000);
        spinbox_auto_refresh_period->setMaximum(100.000000000000000);
        spinbox_auto_refresh_period->setSingleStep(0.100000000000000);

        gridLayout_system_look_and_feel_2->addWidget(spinbox_auto_refresh_period, 1, 1, 1, 1);

        label_15 = new QLabel(groupBox_system_look_and_feel_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_system_look_and_feel_2->addWidget(label_15, 1, 0, 1, 1);

        label_threads_priority = new QLabel(groupBox_system_look_and_feel_2);
        label_threads_priority->setObjectName(QString::fromUtf8("label_threads_priority"));

        gridLayout_system_look_and_feel_2->addWidget(label_threads_priority, 0, 0, 1, 1);

        spinboxInt_logging_verbosity = new MySpinBox(groupBox_system_look_and_feel_2);
        spinboxInt_logging_verbosity->setObjectName(QString::fromUtf8("spinboxInt_logging_verbosity"));
        spinboxInt_logging_verbosity->setMinimum(0);
        spinboxInt_logging_verbosity->setMaximum(3);
        spinboxInt_logging_verbosity->setValue(1);

        gridLayout_system_look_and_feel_2->addWidget(spinboxInt_logging_verbosity, 2, 1, 1, 1);

        checkBox_console_output_enable = new MyCheckBox(groupBox_system_look_and_feel_2);
        checkBox_console_output_enable->setObjectName(QString::fromUtf8("checkBox_console_output_enable"));

        gridLayout_system_look_and_feel_2->addWidget(checkBox_console_output_enable, 3, 0, 1, 2);


        verticalLayout_9->addLayout(gridLayout_system_look_and_feel_2);

        label_path_to_logfile = new QLabel(groupBox_system_look_and_feel_2);
        label_path_to_logfile->setObjectName(QString::fromUtf8("label_path_to_logfile"));
        label_path_to_logfile->setWordWrap(true);

        verticalLayout_9->addWidget(label_path_to_logfile);


        verticalLayout_general->addWidget(groupBox_system_look_and_feel_2);

        checkBox_quit_do_not_ask_again = new MyCheckBox(scrollAreaWidgetContents_general);
        checkBox_quit_do_not_ask_again->setObjectName(QString::fromUtf8("checkBox_quit_do_not_ask_again"));

        verticalLayout_general->addWidget(checkBox_quit_do_not_ask_again);

        checkBox_description_popup_do_not_show_again = new MyCheckBox(scrollAreaWidgetContents_general);
        checkBox_description_popup_do_not_show_again->setObjectName(QString::fromUtf8("checkBox_description_popup_do_not_show_again"));

        verticalLayout_general->addWidget(checkBox_description_popup_do_not_show_again);

        pushButton_retrieve_toolbar = new QPushButton(scrollAreaWidgetContents_general);
        pushButton_retrieve_toolbar->setObjectName(QString::fromUtf8("pushButton_retrieve_toolbar"));

        verticalLayout_general->addWidget(pushButton_retrieve_toolbar);

        pushButton_retrieve_materials = new QPushButton(scrollAreaWidgetContents_general);
        pushButton_retrieve_materials->setObjectName(QString::fromUtf8("pushButton_retrieve_materials"));

        verticalLayout_general->addWidget(pushButton_retrieve_materials);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_general->addItem(verticalSpacer);

        scrollArea_general->setWidget(scrollAreaWidgetContents_general);

        verticalLayout_7->addWidget(scrollArea_general);

        tabWidget->addTab(tabGeneral, icon, QString());
        tabImage = new QWidget();
        tabImage->setObjectName(QString::fromUtf8("tabImage"));
        verticalLayout_8 = new QVBoxLayout(tabImage);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        scrollArea_image = new QScrollArea(tabImage);
        scrollArea_image->setObjectName(QString::fromUtf8("scrollArea_image"));
        scrollArea_image->setWidgetResizable(true);
        scrollAreaWidgetContents_image = new QWidget();
        scrollAreaWidgetContents_image->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_image"));
        scrollAreaWidgetContents_image->setGeometry(QRect(0, 0, 329, 830));
        verticalLayout_image = new QVBoxLayout(scrollAreaWidgetContents_image);
        verticalLayout_image->setSpacing(2);
        verticalLayout_image->setObjectName(QString::fromUtf8("verticalLayout_image"));
        verticalLayout_image->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_6->addWidget(label_12);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 0, 2, 1, 1);

        checkBox_color_enabled = new MyCheckBox(groupBox_4);
        checkBox_color_enabled->setObjectName(QString::fromUtf8("checkBox_color_enabled"));
        checkBox_color_enabled->setChecked(true);

        gridLayout_4->addWidget(checkBox_color_enabled, 1, 0, 1, 1);

        comboBox_color_quality = new MyComboBox(groupBox_4);
        comboBox_color_quality->addItem(QString());
        comboBox_color_quality->addItem(QString());
        comboBox_color_quality->addItem(QString());
        comboBox_color_quality->setObjectName(QString::fromUtf8("comboBox_color_quality"));

        gridLayout_4->addWidget(comboBox_color_quality, 1, 1, 1, 1);

        text_color_postfix = new MyLineEdit(groupBox_4);
        text_color_postfix->setObjectName(QString::fromUtf8("text_color_postfix"));

        gridLayout_4->addWidget(text_color_postfix, 1, 2, 1, 1);

        checkBox_alpha_enabled = new MyCheckBox(groupBox_4);
        checkBox_alpha_enabled->setObjectName(QString::fromUtf8("checkBox_alpha_enabled"));

        gridLayout_4->addWidget(checkBox_alpha_enabled, 2, 0, 1, 1);

        comboBox_alpha_quality = new MyComboBox(groupBox_4);
        comboBox_alpha_quality->addItem(QString());
        comboBox_alpha_quality->addItem(QString());
        comboBox_alpha_quality->addItem(QString());
        comboBox_alpha_quality->setObjectName(QString::fromUtf8("comboBox_alpha_quality"));

        gridLayout_4->addWidget(comboBox_alpha_quality, 2, 1, 1, 1);

        text_alpha_postfix = new MyLineEdit(groupBox_4);
        text_alpha_postfix->setObjectName(QString::fromUtf8("text_alpha_postfix"));

        gridLayout_4->addWidget(text_alpha_postfix, 2, 2, 1, 1);

        checkBox_zbuffer_enabled = new MyCheckBox(groupBox_4);
        checkBox_zbuffer_enabled->setObjectName(QString::fromUtf8("checkBox_zbuffer_enabled"));

        gridLayout_4->addWidget(checkBox_zbuffer_enabled, 3, 0, 1, 1);

        comboBox_zbuffer_quality = new MyComboBox(groupBox_4);
        comboBox_zbuffer_quality->addItem(QString());
        comboBox_zbuffer_quality->addItem(QString());
        comboBox_zbuffer_quality->addItem(QString());
        comboBox_zbuffer_quality->setObjectName(QString::fromUtf8("comboBox_zbuffer_quality"));

        gridLayout_4->addWidget(comboBox_zbuffer_quality, 3, 1, 1, 1);

        text_zbuffer_postfix = new MyLineEdit(groupBox_4);
        text_zbuffer_postfix->setObjectName(QString::fromUtf8("text_zbuffer_postfix"));

        gridLayout_4->addWidget(text_zbuffer_postfix, 3, 2, 1, 1);


        verticalLayout_6->addLayout(gridLayout_4);


        verticalLayout_image->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setSpacing(2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(2, 2, 2, 2);
        checkBox_zbuffer_invert = new MyCheckBox(groupBox_3);
        checkBox_zbuffer_invert->setObjectName(QString::fromUtf8("checkBox_zbuffer_invert"));

        gridLayout_6->addWidget(checkBox_zbuffer_invert, 0, 0, 1, 1);

        checkBox_zbuffer_logarithmic = new MyCheckBox(groupBox_3);
        checkBox_zbuffer_logarithmic->setObjectName(QString::fromUtf8("checkBox_zbuffer_logarithmic"));

        gridLayout_6->addWidget(checkBox_zbuffer_logarithmic, 1, 0, 1, 1);

        groupCheck_zbuffer_constant_range = new MyGroupBox(groupBox_3);
        groupCheck_zbuffer_constant_range->setObjectName(QString::fromUtf8("groupCheck_zbuffer_constant_range"));
        groupCheck_zbuffer_constant_range->setCheckable(true);
        gridLayout_7 = new QGridLayout(groupCheck_zbuffer_constant_range);
        gridLayout_7->setSpacing(2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(2, 2, 2, 2);
        label_2 = new QLabel(groupCheck_zbuffer_constant_range);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_7->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupCheck_zbuffer_constant_range);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_7->addWidget(label_3, 0, 0, 1, 1);

        logedit_zbuffer_min_depth = new MyLineEdit(groupCheck_zbuffer_constant_range);
        logedit_zbuffer_min_depth->setObjectName(QString::fromUtf8("logedit_zbuffer_min_depth"));

        gridLayout_7->addWidget(logedit_zbuffer_min_depth, 0, 1, 1, 1);

        logedit_zbuffer_max_depth = new MyLineEdit(groupCheck_zbuffer_constant_range);
        logedit_zbuffer_max_depth->setObjectName(QString::fromUtf8("logedit_zbuffer_max_depth"));

        gridLayout_7->addWidget(logedit_zbuffer_max_depth, 1, 1, 1, 1);


        gridLayout_6->addWidget(groupCheck_zbuffer_constant_range, 2, 0, 1, 1);


        verticalLayout_image->addWidget(groupBox_3);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupCheck_optional_image_channels_enabled = new MyGroupBox(scrollAreaWidgetContents_image);
        groupCheck_optional_image_channels_enabled->setObjectName(QString::fromUtf8("groupCheck_optional_image_channels_enabled"));
        groupCheck_optional_image_channels_enabled->setCheckable(true);
        gridLayout_optional_image_channels = new QGridLayout(groupCheck_optional_image_channels_enabled);
        gridLayout_optional_image_channels->setSpacing(2);
        gridLayout_optional_image_channels->setObjectName(QString::fromUtf8("gridLayout_optional_image_channels"));
        checkBox_diffuse_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_diffuse_enabled->setObjectName(QString::fromUtf8("checkBox_diffuse_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_diffuse_enabled, 5, 0, 1, 1);

        comboBox_normal_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_normal_quality->addItem(QString());
        comboBox_normal_quality->addItem(QString());
        comboBox_normal_quality->addItem(QString());
        comboBox_normal_quality->setObjectName(QString::fromUtf8("comboBox_normal_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_normal_quality, 2, 1, 1, 1);

        label_rerender_required_info = new QLabel(groupCheck_optional_image_channels_enabled);
        label_rerender_required_info->setObjectName(QString::fromUtf8("label_rerender_required_info"));

        gridLayout_optional_image_channels->addWidget(label_rerender_required_info, 0, 0, 1, 3);

        checkBox_world_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_world_enabled->setObjectName(QString::fromUtf8("checkBox_world_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_world_enabled, 4, 0, 1, 1);

        checkBox_not_denoised_channel_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_not_denoised_channel_enabled->setObjectName(QString::fromUtf8("checkBox_not_denoised_channel_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_not_denoised_channel_enabled, 9, 0, 1, 1);

        label_image_channel_optional = new QLabel(groupCheck_optional_image_channels_enabled);
        label_image_channel_optional->setObjectName(QString::fromUtf8("label_image_channel_optional"));

        gridLayout_optional_image_channels->addWidget(label_image_channel_optional, 1, 0, 1, 1);

        checkBox_gi_channel_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_gi_channel_enabled->setObjectName(QString::fromUtf8("checkBox_gi_channel_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_gi_channel_enabled, 8, 0, 1, 1);

        label_image_quality_optional = new QLabel(groupCheck_optional_image_channels_enabled);
        label_image_quality_optional->setObjectName(QString::fromUtf8("label_image_quality_optional"));

        gridLayout_optional_image_channels->addWidget(label_image_quality_optional, 1, 1, 1, 1);

        comboBox_normalWorld_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_normalWorld_quality->addItem(QString());
        comboBox_normalWorld_quality->addItem(QString());
        comboBox_normalWorld_quality->addItem(QString());
        comboBox_normalWorld_quality->setObjectName(QString::fromUtf8("comboBox_normalWorld_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_normalWorld_quality, 6, 1, 1, 1);

        checkBox_normal_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_normal_enabled->setObjectName(QString::fromUtf8("checkBox_normal_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_normal_enabled, 2, 0, 1, 1);

        comboBox_world_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_world_quality->addItem(QString());
        comboBox_world_quality->addItem(QString());
        comboBox_world_quality->addItem(QString());
        comboBox_world_quality->setObjectName(QString::fromUtf8("comboBox_world_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_world_quality, 4, 1, 1, 1);

        comboBox_shadow_channel_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_shadow_channel_quality->addItem(QString());
        comboBox_shadow_channel_quality->addItem(QString());
        comboBox_shadow_channel_quality->addItem(QString());
        comboBox_shadow_channel_quality->setObjectName(QString::fromUtf8("comboBox_shadow_channel_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_shadow_channel_quality, 7, 1, 1, 1);

        comboBox_not_denoised_channel_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_not_denoised_channel_quality->addItem(QString());
        comboBox_not_denoised_channel_quality->addItem(QString());
        comboBox_not_denoised_channel_quality->addItem(QString());
        comboBox_not_denoised_channel_quality->setObjectName(QString::fromUtf8("comboBox_not_denoised_channel_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_not_denoised_channel_quality, 9, 1, 1, 1);

        text_specular_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_specular_postfix->setObjectName(QString::fromUtf8("text_specular_postfix"));

        gridLayout_optional_image_channels->addWidget(text_specular_postfix, 3, 2, 1, 1);

        text_world_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_world_postfix->setObjectName(QString::fromUtf8("text_world_postfix"));

        gridLayout_optional_image_channels->addWidget(text_world_postfix, 4, 2, 1, 1);

        checkBox_specular_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_specular_enabled->setObjectName(QString::fromUtf8("checkBox_specular_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_specular_enabled, 3, 0, 1, 1);

        text_diffuse_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_diffuse_postfix->setObjectName(QString::fromUtf8("text_diffuse_postfix"));

        gridLayout_optional_image_channels->addWidget(text_diffuse_postfix, 5, 2, 1, 1);

        comboBox_diffuse_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_diffuse_quality->addItem(QString());
        comboBox_diffuse_quality->addItem(QString());
        comboBox_diffuse_quality->addItem(QString());
        comboBox_diffuse_quality->setObjectName(QString::fromUtf8("comboBox_diffuse_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_diffuse_quality, 5, 1, 1, 1);

        text_shadow_channel_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_shadow_channel_postfix->setObjectName(QString::fromUtf8("text_shadow_channel_postfix"));

        gridLayout_optional_image_channels->addWidget(text_shadow_channel_postfix, 7, 2, 1, 1);

        text_normalWorld_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_normalWorld_postfix->setObjectName(QString::fromUtf8("text_normalWorld_postfix"));

        gridLayout_optional_image_channels->addWidget(text_normalWorld_postfix, 6, 2, 1, 1);

        label_image_postfix_optional = new QLabel(groupCheck_optional_image_channels_enabled);
        label_image_postfix_optional->setObjectName(QString::fromUtf8("label_image_postfix_optional"));

        gridLayout_optional_image_channels->addWidget(label_image_postfix_optional, 1, 2, 1, 1);

        checkBox_normalWorld_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_normalWorld_enabled->setObjectName(QString::fromUtf8("checkBox_normalWorld_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_normalWorld_enabled, 6, 0, 1, 1);

        text_gi_channel_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_gi_channel_postfix->setObjectName(QString::fromUtf8("text_gi_channel_postfix"));

        gridLayout_optional_image_channels->addWidget(text_gi_channel_postfix, 8, 2, 1, 1);

        checkBox_shadow_channel_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_shadow_channel_enabled->setObjectName(QString::fromUtf8("checkBox_shadow_channel_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_shadow_channel_enabled, 7, 0, 1, 1);

        comboBox_specular_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_specular_quality->addItem(QString());
        comboBox_specular_quality->addItem(QString());
        comboBox_specular_quality->addItem(QString());
        comboBox_specular_quality->setObjectName(QString::fromUtf8("comboBox_specular_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_specular_quality, 3, 1, 1, 1);

        text_normal_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_normal_postfix->setObjectName(QString::fromUtf8("text_normal_postfix"));

        gridLayout_optional_image_channels->addWidget(text_normal_postfix, 2, 2, 1, 1);

        comboBox_gi_channel_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_gi_channel_quality->addItem(QString());
        comboBox_gi_channel_quality->addItem(QString());
        comboBox_gi_channel_quality->addItem(QString());
        comboBox_gi_channel_quality->setObjectName(QString::fromUtf8("comboBox_gi_channel_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_gi_channel_quality, 8, 1, 1, 1);

        text_not_denoised_channel_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_not_denoised_channel_postfix->setObjectName(QString::fromUtf8("text_not_denoised_channel_postfix"));

        gridLayout_optional_image_channels->addWidget(text_not_denoised_channel_postfix, 9, 2, 1, 1);


        verticalLayout_10->addWidget(groupCheck_optional_image_channels_enabled);


        verticalLayout_image->addLayout(verticalLayout_10);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox_linear_colorspace = new MyCheckBox(groupBox_2);
        checkBox_linear_colorspace->setObjectName(QString::fromUtf8("checkBox_linear_colorspace"));

        gridLayout_2->addWidget(checkBox_linear_colorspace, 4, 0, 1, 2);

        checkBox_save_channels_in_separate_folders = new MyCheckBox(groupBox_2);
        checkBox_save_channels_in_separate_folders->setObjectName(QString::fromUtf8("checkBox_save_channels_in_separate_folders"));

        gridLayout_2->addWidget(checkBox_save_channels_in_separate_folders, 3, 0, 1, 2);

        checkBox_stereoscopic_in_separate_files = new MyCheckBox(groupBox_2);
        checkBox_stereoscopic_in_separate_files->setObjectName(QString::fromUtf8("checkBox_stereoscopic_in_separate_files"));

        gridLayout_2->addWidget(checkBox_stereoscopic_in_separate_files, 5, 0, 1, 2);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        checkBox_append_alpha_png = new MyCheckBox(groupBox_2);
        checkBox_append_alpha_png->setObjectName(QString::fromUtf8("checkBox_append_alpha_png"));

        gridLayout_2->addWidget(checkBox_append_alpha_png, 2, 0, 1, 1);

        spinboxInt_jpeg_quality = new MySpinBox(groupBox_2);
        spinboxInt_jpeg_quality->setObjectName(QString::fromUtf8("spinboxInt_jpeg_quality"));
        spinboxInt_jpeg_quality->setMinimum(1);
        spinboxInt_jpeg_quality->setMaximum(100);

        gridLayout_2->addWidget(spinboxInt_jpeg_quality, 0, 1, 1, 1);

        checkBox_save_settings_with_image = new QCheckBox(groupBox_2);
        checkBox_save_settings_with_image->setObjectName(QString::fromUtf8("checkBox_save_settings_with_image"));

        gridLayout_2->addWidget(checkBox_save_settings_with_image, 1, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_image->addWidget(groupBox_2);

        groupBox_thumbnail_options = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox_thumbnail_options->setObjectName(QString::fromUtf8("groupBox_thumbnail_options"));
        verticalLayout_thumbnail_options = new QVBoxLayout(groupBox_thumbnail_options);
        verticalLayout_thumbnail_options->setSpacing(2);
        verticalLayout_thumbnail_options->setObjectName(QString::fromUtf8("verticalLayout_thumbnail_options"));
        verticalLayout_thumbnail_options->setContentsMargins(2, 2, 2, 2);
        gridLayout_thumbnail_options = new QGridLayout();
        gridLayout_thumbnail_options->setSpacing(2);
        gridLayout_thumbnail_options->setObjectName(QString::fromUtf8("gridLayout_thumbnail_options"));
        checkBox_thumbnails_with_opencl = new MyCheckBox(groupBox_thumbnail_options);
        checkBox_thumbnails_with_opencl->setObjectName(QString::fromUtf8("checkBox_thumbnails_with_opencl"));

        gridLayout_thumbnail_options->addWidget(checkBox_thumbnails_with_opencl, 1, 0, 1, 2);

        pushButton_generate_thumbnail_cache = new QPushButton(groupBox_thumbnail_options);
        pushButton_generate_thumbnail_cache->setObjectName(QString::fromUtf8("pushButton_generate_thumbnail_cache"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/applications-graphics.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_generate_thumbnail_cache->setIcon(icon2);

        gridLayout_thumbnail_options->addWidget(pushButton_generate_thumbnail_cache, 0, 1, 1, 1);

        pushButton_clear_thumbnail_cache = new QPushButton(groupBox_thumbnail_options);
        pushButton_clear_thumbnail_cache->setObjectName(QString::fromUtf8("pushButton_clear_thumbnail_cache"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/process-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_clear_thumbnail_cache->setIcon(icon3);

        gridLayout_thumbnail_options->addWidget(pushButton_clear_thumbnail_cache, 0, 0, 1, 1);


        verticalLayout_thumbnail_options->addLayout(gridLayout_thumbnail_options);


        verticalLayout_image->addWidget(groupBox_thumbnail_options);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_image->addItem(verticalSpacer_2);

        scrollArea_image->setWidget(scrollAreaWidgetContents_image);

        verticalLayout_8->addWidget(scrollArea_image);

        QIcon icon4;
        iconThemeName = QString::fromUtf8("image-x-generic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/system/icons/image-x-generic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        tabWidget->addTab(tabImage, icon4, QString());
        tabOpenCL = new QWidget();
        tabOpenCL->setObjectName(QString::fromUtf8("tabOpenCL"));
        verticalLayout_outer_OpenCL = new QVBoxLayout(tabOpenCL);
        verticalLayout_outer_OpenCL->setObjectName(QString::fromUtf8("verticalLayout_outer_OpenCL"));
        scrollArea_OpenCL = new QScrollArea(tabOpenCL);
        scrollArea_OpenCL->setObjectName(QString::fromUtf8("scrollArea_OpenCL"));
        scrollArea_OpenCL->setWidgetResizable(true);
        scrollAreaWidgetContents_OpenCL = new QWidget();
        scrollAreaWidgetContents_OpenCL->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_OpenCL"));
        scrollAreaWidgetContents_OpenCL->setGeometry(QRect(0, 0, 233, 774));
        verticalLayout_OpenCL = new QVBoxLayout(scrollAreaWidgetContents_OpenCL);
        verticalLayout_OpenCL->setSpacing(2);
        verticalLayout_OpenCL->setObjectName(QString::fromUtf8("verticalLayout_OpenCL"));
        verticalLayout_OpenCL->setContentsMargins(2, 2, 2, 2);
        groupCheck_opencl_enabled = new MyGroupBox(scrollAreaWidgetContents_OpenCL);
        groupCheck_opencl_enabled->setObjectName(QString::fromUtf8("groupCheck_opencl_enabled"));
        groupCheck_opencl_enabled->setCheckable(true);
        verticalLayout_opencl_inner = new QVBoxLayout(groupCheck_opencl_enabled);
        verticalLayout_opencl_inner->setSpacing(2);
        verticalLayout_opencl_inner->setObjectName(QString::fromUtf8("verticalLayout_opencl_inner"));
        verticalLayout_opencl_inner->setContentsMargins(2, 2, 2, 2);
        label_explanation_opencl = new QLabel(groupCheck_opencl_enabled);
        label_explanation_opencl->setObjectName(QString::fromUtf8("label_explanation_opencl"));
        label_explanation_opencl->setWordWrap(true);

        verticalLayout_opencl_inner->addWidget(label_explanation_opencl);

        gridLayout_opencl_settings = new QGridLayout();
        gridLayout_opencl_settings->setSpacing(2);
        gridLayout_opencl_settings->setObjectName(QString::fromUtf8("gridLayout_opencl_settings"));
        sliderInt_opencl_memory_limit = new QSlider(groupCheck_opencl_enabled);
        sliderInt_opencl_memory_limit->setObjectName(QString::fromUtf8("sliderInt_opencl_memory_limit"));
        sliderInt_opencl_memory_limit->setMinimum(1);
        sliderInt_opencl_memory_limit->setMaximum(100000);
        sliderInt_opencl_memory_limit->setSingleStep(8);
        sliderInt_opencl_memory_limit->setPageStep(64);
        sliderInt_opencl_memory_limit->setOrientation(Qt::Horizontal);

        gridLayout_opencl_settings->addWidget(sliderInt_opencl_memory_limit, 4, 1, 1, 1);

        spinboxInt_opencl_job_size_multiplier = new MySpinBox(groupCheck_opencl_enabled);
        spinboxInt_opencl_job_size_multiplier->setObjectName(QString::fromUtf8("spinboxInt_opencl_job_size_multiplier"));
        spinboxInt_opencl_job_size_multiplier->setMinimum(1);
        spinboxInt_opencl_job_size_multiplier->setMaximum(100000);

        gridLayout_opencl_settings->addWidget(spinboxInt_opencl_job_size_multiplier, 3, 2, 1, 1);

        label_opencl_device = new QLabel(groupCheck_opencl_enabled);
        label_opencl_device->setObjectName(QString::fromUtf8("label_opencl_device"));

        gridLayout_opencl_settings->addWidget(label_opencl_device, 1, 0, 1, 1);

        label_precision = new QLabel(groupCheck_opencl_enabled);
        label_precision->setObjectName(QString::fromUtf8("label_precision"));

        gridLayout_opencl_settings->addWidget(label_precision, 2, 0, 1, 1);

        pushButton_select_clang_format_path = new QPushButton(groupCheck_opencl_enabled);
        pushButton_select_clang_format_path->setObjectName(QString::fromUtf8("pushButton_select_clang_format_path"));
        pushButton_select_clang_format_path->setIcon(icon1);

        gridLayout_opencl_settings->addWidget(pushButton_select_clang_format_path, 8, 2, 1, 1);

        text_clang_format_path = new MyLineEdit(groupCheck_opencl_enabled);
        text_clang_format_path->setObjectName(QString::fromUtf8("text_clang_format_path"));

        gridLayout_opencl_settings->addWidget(text_clang_format_path, 8, 1, 1, 1);

        label_opencl_suggested_memory_limit = new QLabel(groupCheck_opencl_enabled);
        label_opencl_suggested_memory_limit->setObjectName(QString::fromUtf8("label_opencl_suggested_memory_limit"));
        label_opencl_suggested_memory_limit->setWordWrap(true);

        gridLayout_opencl_settings->addWidget(label_opencl_suggested_memory_limit, 5, 0, 1, 3);

        label_opencl_device_2 = new QLabel(groupCheck_opencl_enabled);
        label_opencl_device_2->setObjectName(QString::fromUtf8("label_opencl_device_2"));

        gridLayout_opencl_settings->addWidget(label_opencl_device_2, 0, 0, 1, 1);

        label_opencl_memory_limit_2 = new QLabel(groupCheck_opencl_enabled);
        label_opencl_memory_limit_2->setObjectName(QString::fromUtf8("label_opencl_memory_limit_2"));

        gridLayout_opencl_settings->addWidget(label_opencl_memory_limit_2, 3, 0, 1, 2);

        verticalLayout_opencl_device = new QVBoxLayout();
        verticalLayout_opencl_device->setObjectName(QString::fromUtf8("verticalLayout_opencl_device"));
        comboBox_opencl_device_type = new MyComboBox(groupCheck_opencl_enabled);
        comboBox_opencl_device_type->addItem(QString());
        comboBox_opencl_device_type->addItem(QString());
        comboBox_opencl_device_type->addItem(QString());
        comboBox_opencl_device_type->addItem(QString());
        comboBox_opencl_device_type->addItem(QString());
        comboBox_opencl_device_type->setObjectName(QString::fromUtf8("comboBox_opencl_device_type"));

        verticalLayout_opencl_device->addWidget(comboBox_opencl_device_type);

        listWidget_opencl_device_list = new QListWidget(groupCheck_opencl_enabled);
        listWidget_opencl_device_list->setObjectName(QString::fromUtf8("listWidget_opencl_device_list"));
        listWidget_opencl_device_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget_opencl_device_list->setLayoutMode(QListView::SinglePass);
        listWidget_opencl_device_list->setViewMode(QListView::ListMode);

        verticalLayout_opencl_device->addWidget(listWidget_opencl_device_list);


        gridLayout_opencl_settings->addLayout(verticalLayout_opencl_device, 1, 1, 1, 2);

        checkBox_opencl_disable_build_cache = new MyCheckBox(groupCheck_opencl_enabled);
        checkBox_opencl_disable_build_cache->setObjectName(QString::fromUtf8("checkBox_opencl_disable_build_cache"));

        gridLayout_opencl_settings->addWidget(checkBox_opencl_disable_build_cache, 7, 0, 1, 3);

        checkBox_opencl_use_fast_relaxed_math = new MyCheckBox(groupCheck_opencl_enabled);
        checkBox_opencl_use_fast_relaxed_math->setObjectName(QString::fromUtf8("checkBox_opencl_use_fast_relaxed_math"));

        gridLayout_opencl_settings->addWidget(checkBox_opencl_use_fast_relaxed_math, 6, 0, 1, 3);

        comboBox_opencl_precision = new MyComboBox(groupCheck_opencl_enabled);
        comboBox_opencl_precision->addItem(QString());
        comboBox_opencl_precision->addItem(QString());
        comboBox_opencl_precision->setObjectName(QString::fromUtf8("comboBox_opencl_precision"));
        comboBox_opencl_precision->setEnabled(false);
        comboBox_opencl_precision->setEditable(false);

        gridLayout_opencl_settings->addWidget(comboBox_opencl_precision, 2, 1, 1, 2);

        label_opencl_memory_limit = new QLabel(groupCheck_opencl_enabled);
        label_opencl_memory_limit->setObjectName(QString::fromUtf8("label_opencl_memory_limit"));

        gridLayout_opencl_settings->addWidget(label_opencl_memory_limit, 4, 0, 1, 1);

        label_clang_format_path = new QLabel(groupCheck_opencl_enabled);
        label_clang_format_path->setObjectName(QString::fromUtf8("label_clang_format_path"));

        gridLayout_opencl_settings->addWidget(label_clang_format_path, 8, 0, 1, 1);

        listWidget_opencl_platform_list = new QListWidget(groupCheck_opencl_enabled);
        listWidget_opencl_platform_list->setObjectName(QString::fromUtf8("listWidget_opencl_platform_list"));
        listWidget_opencl_platform_list->setSelectionMode(QAbstractItemView::SingleSelection);
        listWidget_opencl_platform_list->setResizeMode(QListView::Adjust);
        listWidget_opencl_platform_list->setLayoutMode(QListView::SinglePass);
        listWidget_opencl_platform_list->setViewMode(QListView::ListMode);

        gridLayout_opencl_settings->addWidget(listWidget_opencl_platform_list, 0, 1, 1, 2);

        spinboxInt_opencl_memory_limit = new MySpinBox(groupCheck_opencl_enabled);
        spinboxInt_opencl_memory_limit->setObjectName(QString::fromUtf8("spinboxInt_opencl_memory_limit"));
        spinboxInt_opencl_memory_limit->setMinimum(1);
        spinboxInt_opencl_memory_limit->setMaximum(100000);

        gridLayout_opencl_settings->addWidget(spinboxInt_opencl_memory_limit, 4, 2, 1, 1);


        verticalLayout_opencl_inner->addLayout(gridLayout_opencl_settings);

        label_explanation_opencl_missing_features = new QLabel(groupCheck_opencl_enabled);
        label_explanation_opencl_missing_features->setObjectName(QString::fromUtf8("label_explanation_opencl_missing_features"));
        label_explanation_opencl_missing_features->setWordWrap(true);

        verticalLayout_opencl_inner->addWidget(label_explanation_opencl_missing_features);


        verticalLayout_OpenCL->addWidget(groupCheck_opencl_enabled);

        verticalSpacer_opencl = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_OpenCL->addItem(verticalSpacer_opencl);

        scrollArea_OpenCL->setWidget(scrollAreaWidgetContents_OpenCL);

        verticalLayout_outer_OpenCL->addWidget(scrollArea_OpenCL);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/system/icons/gpu.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabOpenCL, icon5, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_12 = new QVBoxLayout(tab);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_key_layout_default = new QPushButton(tab);
        pushButton_key_layout_default->setObjectName(QString::fromUtf8("pushButton_key_layout_default"));

        horizontalLayout->addWidget(pushButton_key_layout_default);

        pushButton_key_layout_mb3d = new QPushButton(tab);
        pushButton_key_layout_mb3d->setObjectName(QString::fromUtf8("pushButton_key_layout_mb3d"));

        horizontalLayout->addWidget(pushButton_key_layout_mb3d);


        verticalLayout_12->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 136, 460));
        formLayout = new QFormLayout(scrollAreaWidgetContents);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        keySequenceEdit_key_render = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_render->setObjectName(QString::fromUtf8("keySequenceEdit_key_render"));

        formLayout->setWidget(0, QFormLayout::LabelRole, keySequenceEdit_key_render);

        label_21 = new QLabel(scrollAreaWidgetContents);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_21);

        keySequenceEdit_key_stop = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_stop->setObjectName(QString::fromUtf8("keySequenceEdit_key_stop"));

        formLayout->setWidget(1, QFormLayout::LabelRole, keySequenceEdit_key_stop);

        label_22 = new QLabel(scrollAreaWidgetContents);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        formLayout->setWidget(1, QFormLayout::FieldRole, label_22);

        keySequenceEdit_key_move_forward = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_move_forward->setObjectName(QString::fromUtf8("keySequenceEdit_key_move_forward"));

        formLayout->setWidget(2, QFormLayout::LabelRole, keySequenceEdit_key_move_forward);

        label_23 = new QLabel(scrollAreaWidgetContents);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        formLayout->setWidget(2, QFormLayout::FieldRole, label_23);

        keySequenceEdit_key_move_backward = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_move_backward->setObjectName(QString::fromUtf8("keySequenceEdit_key_move_backward"));

        formLayout->setWidget(3, QFormLayout::LabelRole, keySequenceEdit_key_move_backward);

        label_24 = new QLabel(scrollAreaWidgetContents);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        formLayout->setWidget(3, QFormLayout::FieldRole, label_24);

        keySequenceEdit_key_move_left = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_move_left->setObjectName(QString::fromUtf8("keySequenceEdit_key_move_left"));

        formLayout->setWidget(4, QFormLayout::LabelRole, keySequenceEdit_key_move_left);

        label_25 = new QLabel(scrollAreaWidgetContents);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        formLayout->setWidget(4, QFormLayout::FieldRole, label_25);

        keySequenceEdit_key_move_right = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_move_right->setObjectName(QString::fromUtf8("keySequenceEdit_key_move_right"));

        formLayout->setWidget(5, QFormLayout::LabelRole, keySequenceEdit_key_move_right);

        label_26 = new QLabel(scrollAreaWidgetContents);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        formLayout->setWidget(5, QFormLayout::FieldRole, label_26);

        keySequenceEdit_key_move_up = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_move_up->setObjectName(QString::fromUtf8("keySequenceEdit_key_move_up"));

        formLayout->setWidget(6, QFormLayout::LabelRole, keySequenceEdit_key_move_up);

        label_27 = new QLabel(scrollAreaWidgetContents);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout->setWidget(6, QFormLayout::FieldRole, label_27);

        keySequenceEdit_key_move_down = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_move_down->setObjectName(QString::fromUtf8("keySequenceEdit_key_move_down"));

        formLayout->setWidget(7, QFormLayout::LabelRole, keySequenceEdit_key_move_down);

        label_28 = new QLabel(scrollAreaWidgetContents);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        formLayout->setWidget(7, QFormLayout::FieldRole, label_28);

        keySequenceEdit_key_rotate_left = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_rotate_left->setObjectName(QString::fromUtf8("keySequenceEdit_key_rotate_left"));

        formLayout->setWidget(8, QFormLayout::LabelRole, keySequenceEdit_key_rotate_left);

        label_29 = new QLabel(scrollAreaWidgetContents);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        formLayout->setWidget(8, QFormLayout::FieldRole, label_29);

        keySequenceEdit_key_rotate_right = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_rotate_right->setObjectName(QString::fromUtf8("keySequenceEdit_key_rotate_right"));

        formLayout->setWidget(9, QFormLayout::LabelRole, keySequenceEdit_key_rotate_right);

        label_30 = new QLabel(scrollAreaWidgetContents);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        formLayout->setWidget(9, QFormLayout::FieldRole, label_30);

        keySequenceEdit_key_rotate_up = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_rotate_up->setObjectName(QString::fromUtf8("keySequenceEdit_key_rotate_up"));

        formLayout->setWidget(10, QFormLayout::LabelRole, keySequenceEdit_key_rotate_up);

        label_33 = new QLabel(scrollAreaWidgetContents);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        formLayout->setWidget(10, QFormLayout::FieldRole, label_33);

        keySequenceEdit_key_rotate_down = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_rotate_down->setObjectName(QString::fromUtf8("keySequenceEdit_key_rotate_down"));

        formLayout->setWidget(11, QFormLayout::LabelRole, keySequenceEdit_key_rotate_down);

        keySequenceEdit_key_add_keyframe = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_add_keyframe->setObjectName(QString::fromUtf8("keySequenceEdit_key_add_keyframe"));

        formLayout->setWidget(14, QFormLayout::LabelRole, keySequenceEdit_key_add_keyframe);

        label_31 = new QLabel(scrollAreaWidgetContents);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        formLayout->setWidget(14, QFormLayout::FieldRole, label_31);

        keySequenceEdit_key_modify_keyframe = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_modify_keyframe->setObjectName(QString::fromUtf8("keySequenceEdit_key_modify_keyframe"));

        formLayout->setWidget(15, QFormLayout::LabelRole, keySequenceEdit_key_modify_keyframe);

        label_32 = new QLabel(scrollAreaWidgetContents);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        formLayout->setWidget(15, QFormLayout::FieldRole, label_32);

        label_34 = new QLabel(scrollAreaWidgetContents);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        formLayout->setWidget(11, QFormLayout::FieldRole, label_34);

        keySequenceEdit_key_roll_left = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_roll_left->setObjectName(QString::fromUtf8("keySequenceEdit_key_roll_left"));

        formLayout->setWidget(12, QFormLayout::LabelRole, keySequenceEdit_key_roll_left);

        keySequenceEdit_key_roll_right = new QKeySequenceEdit(scrollAreaWidgetContents);
        keySequenceEdit_key_roll_right->setObjectName(QString::fromUtf8("keySequenceEdit_key_roll_right"));

        formLayout->setWidget(13, QFormLayout::LabelRole, keySequenceEdit_key_roll_right);

        label_35 = new QLabel(scrollAreaWidgetContents);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        formLayout->setWidget(12, QFormLayout::FieldRole, label_35);

        label_36 = new QLabel(scrollAreaWidgetContents);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        formLayout->setWidget(13, QFormLayout::FieldRole, label_36);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_12->addWidget(scrollArea);

        QIcon icon6;
        iconThemeName = QString::fromUtf8("input-keyboard");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        tabWidget->addTab(tab, icon6, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(cPreferencesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        QWidget::setTabOrder(tabWidget, scrollArea_general);
        QWidget::setTabOrder(scrollArea_general, text_default_image_path);
        QWidget::setTabOrder(text_default_image_path, pushButton_select_image_path);
        QWidget::setTabOrder(pushButton_select_image_path, text_default_settings_path);
        QWidget::setTabOrder(text_default_settings_path, pushButton_select_settings_path);
        QWidget::setTabOrder(pushButton_select_settings_path, text_default_textures_path);
        QWidget::setTabOrder(text_default_textures_path, pushButton_select_textures_path);
        QWidget::setTabOrder(pushButton_select_textures_path, comboboxLanguage);
        QWidget::setTabOrder(comboboxLanguage, comboBox_ui_style_type);
        QWidget::setTabOrder(comboBox_ui_style_type, comboBox_ui_skin);
        QWidget::setTabOrder(comboBox_ui_skin, spinboxInt_ui_font_size);
        QWidget::setTabOrder(spinboxInt_ui_font_size, spinboxInt_toolbar_icon_size);
        QWidget::setTabOrder(spinboxInt_toolbar_icon_size, spinboxInt_limit_CPU_cores);
        QWidget::setTabOrder(spinboxInt_limit_CPU_cores, comboBox_threads_priority);
        QWidget::setTabOrder(comboBox_threads_priority, spinboxInt_logging_verbosity);
        QWidget::setTabOrder(spinboxInt_logging_verbosity, checkBox_quit_do_not_ask_again);
        QWidget::setTabOrder(checkBox_quit_do_not_ask_again, checkBox_description_popup_do_not_show_again);
        QWidget::setTabOrder(checkBox_description_popup_do_not_show_again, pushButton_retrieve_toolbar);
        QWidget::setTabOrder(pushButton_retrieve_toolbar, pushButton_retrieve_materials);
        QWidget::setTabOrder(pushButton_retrieve_materials, scrollArea_image);
        QWidget::setTabOrder(scrollArea_image, checkBox_color_enabled);
        QWidget::setTabOrder(checkBox_color_enabled, comboBox_color_quality);
        QWidget::setTabOrder(comboBox_color_quality, text_color_postfix);
        QWidget::setTabOrder(text_color_postfix, checkBox_alpha_enabled);
        QWidget::setTabOrder(checkBox_alpha_enabled, comboBox_alpha_quality);
        QWidget::setTabOrder(comboBox_alpha_quality, text_alpha_postfix);
        QWidget::setTabOrder(text_alpha_postfix, checkBox_zbuffer_enabled);
        QWidget::setTabOrder(checkBox_zbuffer_enabled, comboBox_zbuffer_quality);
        QWidget::setTabOrder(comboBox_zbuffer_quality, text_zbuffer_postfix);
        QWidget::setTabOrder(text_zbuffer_postfix, checkBox_normal_enabled);
        QWidget::setTabOrder(checkBox_normal_enabled, comboBox_normal_quality);
        QWidget::setTabOrder(comboBox_normal_quality, text_normal_postfix);
        QWidget::setTabOrder(text_normal_postfix, checkBox_specular_enabled);
        QWidget::setTabOrder(checkBox_specular_enabled, comboBox_specular_quality);
        QWidget::setTabOrder(comboBox_specular_quality, text_specular_postfix);
        QWidget::setTabOrder(text_specular_postfix, spinboxInt_jpeg_quality);
        QWidget::setTabOrder(spinboxInt_jpeg_quality, checkBox_save_channels_in_separate_folders);
        QWidget::setTabOrder(checkBox_save_channels_in_separate_folders, pushButton_clear_thumbnail_cache);
        QWidget::setTabOrder(pushButton_clear_thumbnail_cache, pushButton_generate_thumbnail_cache);
        QWidget::setTabOrder(pushButton_generate_thumbnail_cache, scrollArea_OpenCL);
        QWidget::setTabOrder(scrollArea_OpenCL, groupCheck_opencl_enabled);
        QWidget::setTabOrder(groupCheck_opencl_enabled, comboBox_opencl_precision);
        QWidget::setTabOrder(comboBox_opencl_precision, sliderInt_opencl_memory_limit);
        QWidget::setTabOrder(sliderInt_opencl_memory_limit, spinboxInt_opencl_memory_limit);

        retranslateUi(cPreferencesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), cPreferencesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), cPreferencesDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cPreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *cPreferencesDialog)
    {
        cPreferencesDialog->setWindowTitle(QCoreApplication::translate("cPreferencesDialog", "Program Preferences", nullptr));
        groupBox_file_paths->setTitle(QCoreApplication::translate("cPreferencesDialog", "Default file paths", nullptr));
        label_settings_path->setText(QCoreApplication::translate("cPreferencesDialog", "Settings:", nullptr));
        label_image_path->setText(QCoreApplication::translate("cPreferencesDialog", "Images:", nullptr));
        label_textures_path->setText(QCoreApplication::translate("cPreferencesDialog", "Default textures:", nullptr));
        label_textures_path_2->setText(QCoreApplication::translate("cPreferencesDialog", "Toolbar", nullptr));
        pushButton_select_textures_path->setText(QString());
        label_textures_path_3->setText(QCoreApplication::translate("cPreferencesDialog", "User textures:", nullptr));
        pushButton_select_image_path->setText(QString());
        pushButton_select_toolbar_path->setText(QString());
        pushButton_select_settings_path->setText(QString());
        pushButton_select_user_textures_path->setText(QString());
        groupBox_system_look_and_feel->setTitle(QCoreApplication::translate("cPreferencesDialog", "System Look and Feel", nullptr));
        label->setText(QCoreApplication::translate("cPreferencesDialog", "To apply changes of these settings you need to restart the application", nullptr));
        comboBox_ui_skin->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "normal", nullptr));
        comboBox_ui_skin->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "dark", nullptr));
        comboBox_ui_skin->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "light", nullptr));
        comboBox_ui_skin->setItemText(3, QCoreApplication::translate("cPreferencesDialog", "space light", nullptr));
        comboBox_ui_skin->setItemText(4, QCoreApplication::translate("cPreferencesDialog", "space dark", nullptr));
        comboBox_ui_skin->setItemText(5, QCoreApplication::translate("cPreferencesDialog", "space dark green", nullptr));
        comboBox_ui_skin->setItemText(6, QCoreApplication::translate("cPreferencesDialog", "space dark blue", nullptr));
        comboBox_ui_skin->setItemText(7, QCoreApplication::translate("cPreferencesDialog", "space dark red", nullptr));
        comboBox_ui_skin->setItemText(8, QCoreApplication::translate("cPreferencesDialog", "3x3lion", nullptr));

#if QT_CONFIG(tooltip)
        comboboxLanguage->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>Language of application texts.</p><p>You need to restart application to apply changes.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_toolbar_icon_size->setText(QCoreApplication::translate("cPreferencesDialog", "Toolbar icon size (pixels)", nullptr));
        label_6->setText(QCoreApplication::translate("cPreferencesDialog", "UI Style type", nullptr));
        label_7->setText(QCoreApplication::translate("cPreferencesDialog", "UI font size (points)", nullptr));
        label_4->setText(QCoreApplication::translate("cPreferencesDialog", "UI Skin", nullptr));
        label_19->setText(QCoreApplication::translate("cPreferencesDialog", "Custom formula editor font size (points)", nullptr));
        groupCheck_ui_colorize->setTitle(QCoreApplication::translate("cPreferencesDialog", "Colorize group&Boxes", nullptr));
        label_16->setText(QCoreApplication::translate("cPreferencesDialog", "Seed for random colors", nullptr));
        label_11->setText(QCoreApplication::translate("cPreferencesDialog", "Language", nullptr));
        checkBox_display_tooltips->setText(QCoreApplication::translate("cPreferencesDialog", "Display tooltips", nullptr));
        label_37->setText(QCoreApplication::translate("cPreferencesDialog", "UI layout spacing", nullptr));
        groupBox->setTitle(QCoreApplication::translate("cPreferencesDialog", "Randomizer", nullptr));
        comboBox_randomizer_preview_size->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "Small", nullptr));
        comboBox_randomizer_preview_size->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "Medium", nullptr));
        comboBox_randomizer_preview_size->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "Big", nullptr));

        label_17->setText(QCoreApplication::translate("cPreferencesDialog", "Preview size", nullptr));
        label_18->setText(QCoreApplication::translate("cPreferencesDialog", "Preview quality", nullptr));
        comboBox_randomizer_preview_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "Low", nullptr));
        comboBox_randomizer_preview_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "Medium", nullptr));
        comboBox_randomizer_preview_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "High", nullptr));

        groupBox_system_look_and_feel_2->setTitle(QCoreApplication::translate("cPreferencesDialog", "Advanced", nullptr));
        label_14->setText(QCoreApplication::translate("cPreferencesDialog", "Max. number of CPU cores to use", nullptr));
        label_20->setText(QCoreApplication::translate("cPreferencesDialog", "Max. RAM for texture cache (GB)", nullptr));
        label_13->setText(QCoreApplication::translate("cPreferencesDialog", "Logging verbosity level", nullptr));
        comboBox_threads_priority->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "Lowest priority", nullptr));
        comboBox_threads_priority->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "Low priority", nullptr));
        comboBox_threads_priority->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "Normal priority", nullptr));
        comboBox_threads_priority->setItemText(3, QCoreApplication::translate("cPreferencesDialog", "High priority", nullptr));

#if QT_CONFIG(tooltip)
        spinbox_auto_refresh_period->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>Multiplies fractal c constant by this value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_auto_refresh_period->setPrefix(QString());
        spinbox_auto_refresh_period->setSuffix(QString());
        label_15->setText(QCoreApplication::translate("cPreferencesDialog", "Image auto-refresh period [seconds]", nullptr));
        label_threads_priority->setText(QCoreApplication::translate("cPreferencesDialog", "Rendering threads priority", nullptr));
        checkBox_console_output_enable->setText(QCoreApplication::translate("cPreferencesDialog", "Console debug output", nullptr));
        label_path_to_logfile->setText(QCoreApplication::translate("cPreferencesDialog", "Path to log file:", nullptr));
        checkBox_quit_do_not_ask_again->setText(QCoreApplication::translate("cPreferencesDialog", "Do not ask for quit confirmation", nullptr));
        checkBox_description_popup_do_not_show_again->setText(QCoreApplication::translate("cPreferencesDialog", "Do not show description on settings load", nullptr));
        pushButton_retrieve_toolbar->setText(QCoreApplication::translate("cPreferencesDialog", "Retrieve default toolbar presets", nullptr));
        pushButton_retrieve_materials->setText(QCoreApplication::translate("cPreferencesDialog", "Retrieve default materials in material folder", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QCoreApplication::translate("cPreferencesDialog", "General", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_4->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p><span style=\" font-weight:600;\">JPG</span></p><p>The quality value will be ignored, since JPG only supports 8 bit precision.</p><p>Every image channel will be saved as a separate file with appended postfix.</p><p><span style=\" font-weight:600;\">PNG</span></p><p>The quality value can be 8 bit or 16 bit (32 bit will result in 16 bit precision).</p><p>Every image channel will be saved as a separate file. </p><p>Only exception can be alpha channel:</p><p>If both Color and Alpha channel are selected and &quot;Append alpha to image (only PNG and TIFF)&quot;, then color + alpha will be saved to a RGBA image with quality and postfix of color row.</p><p><span style=\" font-weight:600;\">TIFF</span></p><p>The quality value can be 8 bit, 16 bit or 32 bit.</p><p>Every image channel will be saved as a separate file. </p><p>Only exception can be alpha channel:</p><p>If both Color and Alpha channel are selected and &quot;Append alpha to image (only PNG and TIFF)&quot;, then color + alpha will be sav"
                        "ed to a RGBA image with quality and postfix of color row.</p><p><span style=\" font-weight:600;\">EXR</span></p><p>The quality value can be 16 bit or 32 bit (8 bit will result in 16 bit precision).</p><p>The postfix will be ignored since all image channels will be saved to one file.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_4->setTitle(QCoreApplication::translate("cPreferencesDialog", "Image Settings", nullptr));
        label_12->setText(QCoreApplication::translate("cPreferencesDialog", "These settings affect \"Save as JPG/PNG/EXR/TIFF\" actions\n"
" and saving animation frames.", nullptr));
        label_10->setText(QCoreApplication::translate("cPreferencesDialog", "Image Channel", nullptr));
        label_8->setText(QCoreApplication::translate("cPreferencesDialog", "Quality", nullptr));
        label_9->setText(QCoreApplication::translate("cPreferencesDialog", "Postfix", nullptr));
        checkBox_color_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Color", nullptr));
        comboBox_color_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_color_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_color_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_color_postfix->setText(QString());
        checkBox_alpha_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Alpha", nullptr));
        comboBox_alpha_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_alpha_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_alpha_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_alpha_postfix->setText(QString());
        checkBox_zbuffer_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Z Buffer", nullptr));
        comboBox_zbuffer_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_zbuffer_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_zbuffer_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_zbuffer_postfix->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("cPreferencesDialog", "Z-buffer options", nullptr));
        checkBox_zbuffer_invert->setText(QCoreApplication::translate("cPreferencesDialog", "Invert z-buffer", nullptr));
        checkBox_zbuffer_logarithmic->setText(QCoreApplication::translate("cPreferencesDialog", "Logarithmic scale", nullptr));
        groupCheck_zbuffer_constant_range->setTitle(QCoreApplication::translate("cPreferencesDialog", "Use constant depth range", nullptr));
        label_2->setText(QCoreApplication::translate("cPreferencesDialog", "maximum z-depth", nullptr));
        label_3->setText(QCoreApplication::translate("cPreferencesDialog", "minimum z-depth", nullptr));
        groupCheck_optional_image_channels_enabled->setTitle(QCoreApplication::translate("cPreferencesDialog", "Op&tional Image Channels", nullptr));
        checkBox_diffuse_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Diffuse", nullptr));
        comboBox_normal_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_normal_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_normal_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        label_rerender_required_info->setText(QCoreApplication::translate("cPreferencesDialog", "Following channels are only rendered on demand\n"
"and will only be present after enabling and re-render.", nullptr));
        checkBox_world_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "World", nullptr));
        checkBox_not_denoised_channel_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Not denoised", nullptr));
        label_image_channel_optional->setText(QCoreApplication::translate("cPreferencesDialog", "Image Channel", nullptr));
        checkBox_gi_channel_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Global illumination", nullptr));
        label_image_quality_optional->setText(QCoreApplication::translate("cPreferencesDialog", "Quality", nullptr));
        comboBox_normalWorld_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_normalWorld_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_normalWorld_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        checkBox_normal_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Surface Normal", nullptr));
        comboBox_world_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_world_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_world_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        comboBox_shadow_channel_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_shadow_channel_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_shadow_channel_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        comboBox_not_denoised_channel_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_not_denoised_channel_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_not_denoised_channel_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_specular_postfix->setText(QString());
        text_world_postfix->setText(QString());
        checkBox_specular_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Specular", nullptr));
        text_diffuse_postfix->setText(QString());
        comboBox_diffuse_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_diffuse_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_diffuse_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_shadow_channel_postfix->setText(QString());
        text_normalWorld_postfix->setText(QString());
        label_image_postfix_optional->setText(QCoreApplication::translate("cPreferencesDialog", "Postfix", nullptr));
        checkBox_normalWorld_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "World Normal", nullptr));
        text_gi_channel_postfix->setText(QString());
        checkBox_shadow_channel_enabled->setText(QCoreApplication::translate("cPreferencesDialog", "Shadows", nullptr));
        comboBox_specular_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_specular_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_specular_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_normal_postfix->setText(QString());
        comboBox_gi_channel_quality->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "8 bit", nullptr));
        comboBox_gi_channel_quality->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "16 bit", nullptr));
        comboBox_gi_channel_quality->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "32 bit", nullptr));

        text_not_denoised_channel_postfix->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("cPreferencesDialog", "Misc Image Settings", nullptr));
        checkBox_linear_colorspace->setText(QCoreApplication::translate("cPreferencesDialog", "Use linear colorspace (only EXR)", nullptr));
        checkBox_save_channels_in_separate_folders->setText(QCoreApplication::translate("cPreferencesDialog", "Save each channel in separate folder", nullptr));
        checkBox_stereoscopic_in_separate_files->setText(QCoreApplication::translate("cPreferencesDialog", "Save stereoscopic left and right images in separate files\n"
"(stereoscopic mode has to be \"left-right\")", nullptr));
        label_5->setText(QCoreApplication::translate("cPreferencesDialog", "JPEG quality:", nullptr));
        checkBox_append_alpha_png->setText(QCoreApplication::translate("cPreferencesDialog", "Append alpha to image (only PNG and TIFF)", nullptr));
        checkBox_save_settings_with_image->setText(QCoreApplication::translate("cPreferencesDialog", "Save fractal settings together with the image", nullptr));
        groupBox_thumbnail_options->setTitle(QCoreApplication::translate("cPreferencesDialog", "Thumbnail options", nullptr));
        checkBox_thumbnails_with_opencl->setText(QCoreApplication::translate("cPreferencesDialog", "Render thumbnails with OpenCL (if OpenCL enabled)", nullptr));
        pushButton_generate_thumbnail_cache->setText(QCoreApplication::translate("cPreferencesDialog", "Generate", nullptr));
        pushButton_clear_thumbnail_cache->setText(QCoreApplication::translate("cPreferencesDialog", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabImage), QCoreApplication::translate("cPreferencesDialog", "Image", nullptr));
        groupCheck_opencl_enabled->setTitle(QCoreApplication::translate("cPreferencesDialog", "OpenCL ena&ble", nullptr));
        label_explanation_opencl->setText(QCoreApplication::translate("cPreferencesDialog", "This will offload the rendering to an OpenCL device (GPU, CPU, Accelerator Card).", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_opencl_job_size_multiplier->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>Job size multiplier increases size of OpenCL jobs (size of tiles).</p><p>Higher value can increase rendering speed, but too high can slow down rendering.</p><p>Too high value can cause higher GPU memory usage makeing the program unstable. It also increases the time of rendering a single tile, which can cause GPU driver timeouts.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_opencl_device->setText(QCoreApplication::translate("cPreferencesDialog", "Device", nullptr));
        label_precision->setText(QCoreApplication::translate("cPreferencesDialog", "Precision", nullptr));
        pushButton_select_clang_format_path->setText(QString());
        label_opencl_suggested_memory_limit->setText(QCoreApplication::translate("cPreferencesDialog", "Suggested memory limit:", nullptr));
        label_opencl_device_2->setText(QCoreApplication::translate("cPreferencesDialog", "Platforms", nullptr));
        label_opencl_memory_limit_2->setText(QCoreApplication::translate("cPreferencesDialog", "Job size multiplier:", nullptr));
        comboBox_opencl_device_type->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "All GPU devices", nullptr));
        comboBox_opencl_device_type->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "Default device", nullptr));
        comboBox_opencl_device_type->setItemText(2, QCoreApplication::translate("cPreferencesDialog", "All devices", nullptr));
        comboBox_opencl_device_type->setItemText(3, QCoreApplication::translate("cPreferencesDialog", "All CPU devices", nullptr));
        comboBox_opencl_device_type->setItemText(4, QCoreApplication::translate("cPreferencesDialog", "All accelerators", nullptr));

#if QT_CONFIG(tooltip)
        checkBox_opencl_disable_build_cache->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>It disables 'compute cache' used by NVidia driver. It is sometimes needed to use this option to refresh precompiled OpenCL programs after changing OpenCL source files (e.g. after upgrade of the program).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_opencl_disable_build_cache->setText(QCoreApplication::translate("cPreferencesDialog", "Disable cache for OpenCL programs", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_opencl_use_fast_relaxed_math->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>It enables -cl-fast-relaxed-math OpenCL flag. It provides additional speed by removing some checks to the math operations like division by zero or Not-a-Number. In some cases it can lead to unpredictable results.</p><p>It is needed to restart the program to apply this option.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_opencl_use_fast_relaxed_math->setText(QCoreApplication::translate("cPreferencesDialog", "Use fast relaxed math", nullptr));
        comboBox_opencl_precision->setItemText(0, QCoreApplication::translate("cPreferencesDialog", "single", nullptr));
        comboBox_opencl_precision->setItemText(1, QCoreApplication::translate("cPreferencesDialog", "double", nullptr));

        label_opencl_memory_limit->setText(QCoreApplication::translate("cPreferencesDialog", "Memory Limit:", nullptr));
        label_clang_format_path->setText(QCoreApplication::translate("cPreferencesDialog", "clang-format path:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_opencl_memory_limit->setToolTip(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>Memory limit for single memory buffer used by OpenCL programs.</p><p>It should be set not higher than suggested memory limit showed below.</p><p>If SSAO or DOF effects need more memory than limit, they will be rendered using CPU.</p><p>Higher memory limit can allow rendering SSAO and DOF effects using GPU at higher resolution, but program can produce errors or be unstable.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_explanation_opencl_missing_features->setText(QCoreApplication::translate("cPreferencesDialog", "<html><head/><body><p>Mandelbulber can use OpenCL to accelerate rendering.<br/>For more information about setup and workflow see the User Manual<br/>under Menu &gt; Help &gt; User Manual.<br/></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOpenCL), QCoreApplication::translate("cPreferencesDialog", "OpenCL (GPU)", nullptr));
        pushButton_key_layout_default->setText(QCoreApplication::translate("cPreferencesDialog", "Default layout", nullptr));
        pushButton_key_layout_mb3d->setText(QCoreApplication::translate("cPreferencesDialog", "MB3D layout", nullptr));
        label_21->setText(QCoreApplication::translate("cPreferencesDialog", "Render", nullptr));
        label_22->setText(QCoreApplication::translate("cPreferencesDialog", "Stop", nullptr));
        label_23->setText(QCoreApplication::translate("cPreferencesDialog", "Move forward", nullptr));
        label_24->setText(QCoreApplication::translate("cPreferencesDialog", "Move backward", nullptr));
        label_25->setText(QCoreApplication::translate("cPreferencesDialog", "Move left", nullptr));
        label_26->setText(QCoreApplication::translate("cPreferencesDialog", "Move right", nullptr));
        label_27->setText(QCoreApplication::translate("cPreferencesDialog", "Move up", nullptr));
        label_28->setText(QCoreApplication::translate("cPreferencesDialog", "Move down", nullptr));
        label_29->setText(QCoreApplication::translate("cPreferencesDialog", "Rotate left", nullptr));
        label_30->setText(QCoreApplication::translate("cPreferencesDialog", "Rotate right", nullptr));
        label_33->setText(QCoreApplication::translate("cPreferencesDialog", "Rotate up", nullptr));
        label_31->setText(QCoreApplication::translate("cPreferencesDialog", "Add keyframe", nullptr));
        label_32->setText(QCoreApplication::translate("cPreferencesDialog", "Modify keyframe", nullptr));
        label_34->setText(QCoreApplication::translate("cPreferencesDialog", "Rotate down", nullptr));
        label_35->setText(QCoreApplication::translate("cPreferencesDialog", "Roll left", nullptr));
        label_36->setText(QCoreApplication::translate("cPreferencesDialog", "Roll right", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("cPreferencesDialog", "Shortcuts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cPreferencesDialog: public Ui_cPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_DIALOG_H

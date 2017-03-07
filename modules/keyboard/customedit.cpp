/**
 * Copyright (C) 2016 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "customedit.h"
#include "translucentframe.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

keyboard::CustomEdit::CustomEdit(keyboard::KeyboardWork *work, QWidget *parent):
    ContentWidget(parent),
    m_work(work),
    m_commandGroup(new SettingsGroup),
    m_name(new LineEditWidget),
    m_command(new LineEditWidget),
    m_short(new ShortcutItem)
{
    setTitle(tr("Shortcuts"));
    TranslucentFrame *widget = new TranslucentFrame;
    QVBoxLayout *mainlayout = new QVBoxLayout;
    QHBoxLayout *buttonlayout = new QHBoxLayout;

    mainlayout->setMargin(0);
    buttonlayout->setMargin(0);
    mainlayout->setSpacing(0);
    buttonlayout->setSpacing(1);

    m_command->setPlaceholderText(tr("Required"));
    QPushButton *pushbutton = new QPushButton("...");
    pushbutton->setFixedWidth(50);
    m_command->addRightWidget(pushbutton);

    m_commandGroup->appendItem(m_name);
    m_commandGroup->appendItem(m_command);
    m_commandGroup->appendItem(m_short);

    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    QPushButton *okButton = new QPushButton(tr("Save"));


    buttonlayout->addWidget(cancelButton);
    buttonlayout->addWidget(okButton);

    mainlayout->addWidget(m_commandGroup);
    mainlayout->addSpacing(10);
    mainlayout->addLayout(buttonlayout);

    widget->setLayout(mainlayout);

    setContent(widget);

    connect(cancelButton, &QPushButton::clicked, this, &CustomEdit::back);
    connect(cancelButton, &QPushButton::clicked, this, &CustomEdit::requestEditFinished);
    connect(okButton, &QPushButton::clicked, this, &CustomEdit::onClick);
    connect(okButton, &QPushButton::clicked, this, &CustomEdit::requestEditFinished);
    connect(pushbutton, &QPushButton::clicked, this, &CustomEdit::onOpenFile);
    connect(m_short, &ShortcutItem::shortcutChangd, this, &CustomEdit::shortcutChangd);
    connect(m_short, &ShortcutItem::requestDisableShortcut, this, &CustomEdit::requestDisableShortcut);
}

void keyboard::CustomEdit::setShortcut(keyboard::ShortcutInfo *info)
{
    m_info = info;
    m_short->setShortcutInfo(info);
    m_short->setTitle(tr("Shortcuts"));

    m_name->setTitle(tr("Name"));
    m_command->setTitle(tr("Command"));

    m_name->setText(m_info->name);
    m_command->setText(m_info->command);
}

void keyboard::CustomEdit::onClick()
{
    m_info->name = m_name->text();
    m_info->command = m_command->text();

    m_info->item->setTitle(m_name->text());

    m_work->modifyShortcutEdit(m_info);
    sendBackSignal();
}

void keyboard::CustomEdit::onOpenFile()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Choose File"), tr("/usr/bin"));
    m_command->setText(file);
}
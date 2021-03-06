/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BRIGHTNESSPAGE_H
#define BRIGHTNESSPAGE_H

#include "contentwidget.h"
#include "switchwidget.h"

#include <QVBoxLayout>

namespace dcc {

namespace widgets {
class TipsLabel;
}

namespace display {

class Monitor;
class DisplayModel;
class BrightnessPage : public ContentWidget
{
    Q_OBJECT

public:
    explicit BrightnessPage(QWidget *parent = 0);

    void setModel(DisplayModel *model);

signals:
    void requestSetMonitorBrightness(Monitor *mon, const double brightness) const;
    void requestSetNightMode(const bool nightmode);

private:
    void initUI();
    void initConnect();

private:
    DisplayModel *m_displayModel;

    QVBoxLayout *m_centralLayout;

    dcc::widgets::SwitchWidget *m_nightMode;
    widgets::TipsLabel *m_nightTips;
};

}

}

#endif // BRIGHTNESSPAGE_H

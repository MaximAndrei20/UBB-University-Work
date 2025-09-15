#include "mochtest3.h"
#include "mochtest3Plugin.h"

#include <QtCore/QtPlugin>

mochtest3Plugin::mochtest3Plugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void mochtest3Plugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool mochtest3Plugin::isInitialized() const
{
    return initialized;
}

QWidget *mochtest3Plugin::createWidget(QWidget *parent)
{
    return new mochtest3(parent);
}

QString mochtest3Plugin::name() const
{
    return "mochtest3";
}

QString mochtest3Plugin::group() const
{
    return "My Plugins";
}

QIcon mochtest3Plugin::icon() const
{
    return QIcon();
}

QString mochtest3Plugin::toolTip() const
{
    return QString();
}

QString mochtest3Plugin::whatsThis() const
{
    return QString();
}

bool mochtest3Plugin::isContainer() const
{
    return false;
}

QString mochtest3Plugin::domXml() const
{
    return "<widget class=\"mochtest3\" name=\"mochtest3\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString mochtest3Plugin::includeFile() const
{
    return "mochtest3.h";
}

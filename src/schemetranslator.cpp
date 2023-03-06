#include <QJsonObject>

#include "schemetranslator.h"

SchemeTranslator::SchemeTranslator(QObject *parent)
    : QObject{parent}
{

}

void SchemeTranslator::writeToJsonFile(Scheme scheme)
{
    QJsonObject modelDataValue;
    {
        int count = scheme.preset.modelData.loops.size();
        for (int i = 0; i < count; ++i)
        {
            QString key = "loop"+QString::number(i);
            //modelDataValue.insert(key,)
        }
    }

    QJsonObject testTypeValue;
    {

    }

    QJsonObject presetValue;
    {
        presetValue.insert("name",scheme.preset.name);
        presetValue.insert("unit",scheme.preset.unit);
        presetValue.insert("auto_switch",scheme.preset.switchMode);
        presetValue.insert("ed_volt",scheme.preset.ratedVoltage);
        presetValue.insert("ed_curr",scheme.preset.ratedCurrent);
        presetValue.insert("model_data",modelDataValue);
    }

    QJsonObject schemeValue;
    {
        schemeValue.insert("name",scheme.name);
        schemeValue.insert("user",scheme.user);
        schemeValue.insert("create_date",scheme.createDate.toString());
        schemeValue.insert("update_date",scheme.updateDate.toString());
        schemeValue.insert("description",scheme.description);
        schemeValue.insert("version",scheme.version);
        schemeValue.insert("pre_set",presetValue);
        schemeValue.insert("test_type",testTypeValue);
    }
}

void SchemeTranslator::readFromJsonFile(QString& filePath)
{

}

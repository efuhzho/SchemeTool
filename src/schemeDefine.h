#pragma once

#include <QString>
#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

typedef struct phaseData
{
    float mag;
    float ang;
    float freq;
    float dc;

    QJsonObject toJson()
    {
        QJsonObject phaseDataValue;
        phaseDataValue.insert("mag",mag);
        phaseDataValue.insert("ang",ang);
        phaseDataValue.insert("freq",freq);
        phaseDataValue.insert("dc",dc);
        return phaseDataValue;
    }
}PhaseData;

typedef struct parameter
{
    QString phaseName;
    PhaseData phaseData;
}Parameter;

typedef struct state
{
    QVector<Parameter> parameters;

    QJsonObject toJson()
    {
        QJsonObject stateValue;
        for (int i = 0; i < parameters.size(); ++i)
        {
            stateValue.insert(parameters[i].phaseName,parameters[i].phaseData.toJson());
        }
        return stateValue;
    }
}State;

typedef struct loop
{
    QVector<State> states;

    QJsonObject toJson()
    {
        QJsonObject loopValue;
        for (int i = 0; i < states.size(); ++i)
        {
            QString key = "state"+QString::number(i);
            loopValue.insert(key,states[i].toJson());
        }
        return loopValue;
    }
}Loop;

typedef struct modelData
{
    QVector<loop> loops;

    QJsonObject toJson()
    {
        QJsonObject modelDataValue;
        for (int i = 0; i < loops.size(); ++i)
        {
            QString key = "loop"+QString::number(i);
            modelDataValue.insert(key,loops[i].toJson());
        }
        return modelDataValue;
    }
}ModelData;

typedef struct subtypeItem
{
    QString name;
    QString id;
    QString unit;
    float var;
    ModelData modelData;
    QJsonObject toJson()
    {
        QJsonObject itemValue;
        itemValue.insert("name",name);
        itemValue.insert("id",id);
        itemValue.insert("unit",unit);
        itemValue.insert("var",var);
        itemValue.insert("model_data",modelData.toJson());
        return itemValue;
    }
}SubTypeItem;

typedef struct subType
{
    QVector<SubTypeItem> items;
    QJsonArray toJson()
    {
        QJsonArray subTypeValue;
        for (int i = 0; i < items.size(); ++i)
        {
            subTypeValue.append(items[i].toJson());
        }
        return subTypeValue;
    }
}SubType;

typedef struct testType
{
    QString name;
    QString id;
    SubType subType;
    QJsonObject toJson()
    {
        QJsonObject testTypeValue;
        testTypeValue.insert("name",name);
        testTypeValue.insert("id",id);
        testTypeValue.insert("subtype",subType.toJson());
    }
}TestType;

typedef struct preset
{
    QString name;
    QString unit;
    QString switchMode;
    float ratedVoltage;
    float ratedCurrent;
    ModelData modelData;
}Preset;

typedef struct scheme
{
    QString name;
    QString user;
    QDate createDate;
    QDate updateDate;
    QString description;
    QString version;
    Preset preset;
    TestType testType;
}Scheme;


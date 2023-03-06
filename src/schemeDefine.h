#pragma once

#include <QString>
#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

typedef struct phaseData
{    
    float mag = 0;
    float ang = 0;
    float freq = 50;
    float dc = 0;

    void fromJson(QJsonObject phaseDataValue)
    {
        if(
                !phaseDataValue.contains("mag")||
                !phaseDataValue.contains("ang")||
                !phaseDataValue.contains("freq")||
                !phaseDataValue.contains("dc"))
        {
            return;
        }
        mag = phaseDataValue["mag"].toDouble();
        ang = phaseDataValue["ang"].toDouble();
        freq = phaseDataValue["freq"].toDouble();
        dc = phaseDataValue["dc"].toDouble();
    }

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

    void fromJson(QJsonObject stateValue)
    {
        QStringList stateKeys = stateValue.keys();
        Parameter para;

        for (int i = 0; i < stateKeys.size(); ++i)
        {
            QString key = stateKeys[i];
            QJsonValue value = stateValue[key];

            if(value.isObject())
            {
                QJsonObject phasedata = value.toObject();
                para.phaseName = key;
                para.phaseData.fromJson(phasedata);
                parameters.append(para);
            }
        }
    }

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

    void fromJson(QJsonObject loopValue)
    {
        QStringList stateKeys = loopValue.keys();
        State state;
        for (int i = 0; i < stateKeys.size(); ++i)
        {
            QString key = stateKeys[i];
            QJsonValue value = loopValue[key];
            if(value.isObject())
            {
                QJsonObject stateData = value.toObject();
                state.fromJson(stateData);
                states.append(state);
            }
        }
    }

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

    void fromJson(QJsonObject modelDataValue)
    {
        QStringList loopKeys = modelDataValue.keys();
        Loop loop;

        for (int i = 0; i < loopKeys.size(); ++i)
        {
            QString key = loopKeys[i];
            QJsonValue value = modelDataValue[key];
            if(value.isObject())
            {
                QJsonObject loopData = value.toObject();
                loop.fromJson(loopData);
                loops.append(loop);
            }
        }
    }

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

    void fromJson(QJsonObject itemValue)
    {
        //TODO if(itemValue.contains("name"))
        name = itemValue["name"].toString();
        id = itemValue["id"].toString();
        unit = itemValue["unit"].toString();
        var = itemValue["var"].toDouble();
        QJsonValue value = itemValue["model_data"];
        if(value.isObject())
        {
            QJsonObject modelobj = value.toObject();
            modelData.fromJson(modelobj);
        }
    }

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

typedef struct testType
{
    QString name;
    QString id;
    QVector<SubTypeItem> subTypes;

    void fromJson(QJsonObject testTypeValue)
    {
        name = testTypeValue["name"].toString();
        id = testTypeValue["id"].toString();
        SubTypeItem item;
        QJsonValue value = testTypeValue["subtype"];
        if(!value.isArray())
        {
            return;
        }

        QJsonArray subTypeValues = testTypeValue["subtype"].toArray();
        for (int i = 0; i < subTypeValues.size(); ++i)
        {
            if(!subTypeValues[i].isObject())
            {
                return;
            }
            item.fromJson(subTypeValues[i].toObject());
            subTypes.append(item);
        }
    }

    QJsonObject toJson()
    {
        QJsonObject testTypeValue;
        testTypeValue.insert("name",name);
        testTypeValue.insert("id",id);

        QJsonArray subTypeValue;
        for (int i = 0; i < subTypes.size(); ++i)
        {
            subTypeValue.append(subTypes[i].toJson());
        }

        testTypeValue.insert("subtype",subTypeValue);
        return testTypeValue;
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

    void fromJson(QJsonObject presetValue)
    {
        //TODO if()
        name = presetValue["name"].toString();
        unit = presetValue["unit"].toString();
        switchMode = presetValue["auto_switch"].toString();
        ratedVoltage = presetValue["ed_volt"].toDouble();
        ratedCurrent = presetValue["ed_curr"].toDouble();
        modelData.fromJson(presetValue["model_data"].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject presetValue;
        presetValue.insert("name",name);
        presetValue.insert("unit",unit);
        presetValue.insert("auto_switch",switchMode);
        presetValue.insert("ed_volt",ratedVoltage);
        presetValue.insert("ed_curr",ratedCurrent);
        presetValue.insert("model_data",modelData.toJson());
        return presetValue;
    }
}Preset;

typedef struct schemeValue
{
    QString name;
    QString user;
    QDate createDate;
    QDate updateDate;
    QString description;
    QString version;
    Preset preset;
    TestType testType;

    void fromJson(QJsonObject schemeValue)
    {
        name = schemeValue["name"].toString();
        user = schemeValue["user"].toString();
        createDate =QDate::fromString(schemeValue["create_date"].toString());
        updateDate =QDate::fromString(schemeValue["update_date"].toString());
        description = schemeValue["description"].toString();
        version = schemeValue["version"].toString();
        preset.fromJson(schemeValue["pre_set"].toObject());
        testType.fromJson(schemeValue["test_type"].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject schemeValue;
        schemeValue.insert("name",name);
        schemeValue.insert("user",user);
        schemeValue.insert("create_date",createDate.toString());
        schemeValue.insert("update_date",updateDate.toString());
        schemeValue.insert("description",description);
        schemeValue.insert("version",version);
        schemeValue.insert("pre_set",preset.toJson());
        schemeValue.insert("test_type",testType.toJson());
        return schemeValue;
    }
}SchemeValue;

typedef struct scheme
{
    QString key{"scheme"};
    SchemeValue value;

    void fromJson(QJsonObject scheme)
    {
        if(!scheme.contains(key))
        {
            return;
        }
        value.fromJson(scheme[key].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject scheme;
        scheme.insert(key,value.toJson());
        return scheme;
    }
}Scheme;




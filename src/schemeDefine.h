﻿#pragma once

#include <QString>
#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

typedef struct phaseData
{
    double mag ;
    double ang ;
    double freq ;
    double dc ;

    void fromJson(QJsonObject phaseDataValue)
    {
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

    void addParameter(QString key,PhaseData data)
    {
        Parameter para;
        para.phaseName = key;
        para.phaseData = data;
        parameters.append(para);
    }
}State;

typedef struct loopValue
{
    QString stateKey;
    State stateValue;
}LoopValue;

typedef struct loop
{
    QVector<LoopValue> states;

    void fromJson(QJsonObject loopValue)
    {
        QStringList stateKeys = loopValue.keys();
        LoopValue state;
        for (int i = 0; i < stateKeys.size(); ++i)
        {
            QString key = stateKeys[i];
            QJsonValue value = loopValue[key];
            if(value.isObject())
            {
                state.stateKey = key;
                state.stateValue.fromJson( value.toObject( ) );
                states.append(state);
            }
        }
    }

    QJsonObject toJson()
    {
        QJsonObject loopValue;
        for (int i = 0; i < states.size(); ++i)
        {
            loopValue.insert(states[i].stateKey, states[i].stateValue.toJson() );
        }
        return loopValue;
    }

    void addState(/*LoopValue item*/)
    {
        LoopValue item;
        int count = states.size();
        item.stateKey = "state"+QString::number(count);
        states.append(item);
    }

    bool deleteState()
    {
        int count = states.size();
        if(count>1)
        {
            states.removeLast();
            return true;
        }
        return false;
    }
}Loop;

typedef struct modelDataValue
{
    QString key;
    Loop loopValue;
}ModelDataValue;

typedef struct modelData
{
    QVector<ModelDataValue> loops;

    void fromJson(QJsonObject modelDataValue)
    {
        QStringList loopKeys = modelDataValue.keys();

        for (int i = 0; i < loopKeys.size(); ++i)
        {            
            ModelDataValue loop;
            QString key = loopKeys[i];
            QJsonValue value = modelDataValue[key];
            if(value.isObject())
            {
                loop.key = key;
                loop.loopValue.fromJson(value.toObject());
                loops.append(loop);
            }
        }
    }

    QJsonObject toJson()
    {
        QJsonObject modelDataValue;
        for (int i = 0; i < loops.size(); ++i)
        {
            modelDataValue.insert(loops[i].key, loops[i].loopValue.toJson() );
        }
        return modelDataValue;
    }

    void addLoop(/*ModelDataValue item*/)
    {
        ModelDataValue item;
        int count = loops.size();
        item.key = "loop"+QString::number(count);
        loops.append(item);
        this->loops[count].loopValue.addState();
    }

    bool deleteLoop()
    {
        int count = loops.size();
        if(count>1)
        {
            loops.removeLast();
            return true;
        }
        return false;
    }
}ModelData;

typedef struct testPoint
{
    QString name;
    QString id;
    QString unit;
    QString var;
    ModelData modelData;

    void fromJson(QJsonObject itemValue)
    {
        //TODO if(itemValue.contains("name"))
        name = itemValue["name"].toString();
        id = itemValue["id"].toString();
        unit = itemValue["unit"].toString();
        if(itemValue["var"].isDouble())
        {
            auto num = itemValue["var"].toDouble();
            var = QString::number(num,'g');
        }
        else
        {
            var = itemValue["var"].toString();
        }

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

        bool ok;
        var.toDouble(&ok);
        if(ok)
        {
            itemValue.insert("var",var.toDouble());
        }
        else
        {
            itemValue.insert("var",var);
        }

        itemValue.insert("model_data",modelData.toJson());
        return itemValue;
    }
}TestPoint;

typedef struct subTpye
{
    QString name;
    QString id;
    QString type;
    QVector<TestPoint> testPoints;

    void fromJson(QJsonObject subtypeData)
    {
        name = subtypeData["name"].toString();
        id = subtypeData["id"].toString();
        type = subtypeData["type"].toString();
        QJsonValue value = subtypeData["item"];
        if(!value.isArray())
        {
            return;
        }
        QJsonArray itemsValue = value.toArray();

        for (int i = 0; i < itemsValue.size(); ++i)
        {
            if(!itemsValue[i].isObject())
            {
                return;
            }
            testPoint item;
            item.fromJson(itemsValue[i].toObject());
            testPoints.append(item);
        }
    }

    QJsonObject toJson()
    {
        QJsonObject subtypeData;
        subtypeData.insert("name",name);
        subtypeData.insert("id",id);
        subtypeData.insert("type",type);
        QJsonArray itemsValue;
        for (int i = 0; i < testPoints.size(); ++i)
        {
            itemsValue.append(testPoints[i].toJson());
        }
        subtypeData.insert("item",itemsValue);

        return subtypeData;
    }

}SubType;

typedef struct testType
{
    QString name;
    QString id;
    QVector<SubType> subTypes;

    void fromJson(QJsonObject testTypeValue)
    {
        name = testTypeValue["name"].toString();
        id = testTypeValue["id"].toString();
        QJsonValue value = testTypeValue["subtype"];
        if(!value.isArray())
        {
            return;
        }

        QJsonArray subTypeValues = testTypeValue["subtype"].toArray();
        for (int i = 0; i < subTypeValues.size(); ++i)
        {            
            SubType item;
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
    double ratedVoltage;
    double ratedCurrent;
    ModelData modelData;

    void fromJson(QJsonObject presetValue)
    {
        //TODO if()
        name = presetValue["name"].toString();
        unit = presetValue["unit"].toString();
        switchMode = presetValue["auto_switch"].toString();
        ratedVoltage = presetValue["ed_volt"].toDouble();
        ratedVoltage = round(ratedVoltage*100)/100;
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

typedef struct scheme
{
    QString name;
    QString user;
    QString createDate;
    QString updateDate;
    QString description;
    QString version;
    Preset preset;
    TestType testType;

    void fromJson(QJsonObject schemeValue)
    {
        name = schemeValue["name"].toString();
        user = schemeValue["user"].toString();
        createDate =schemeValue["create_date"].toString();
        updateDate =schemeValue["update_date"].toString();
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
        schemeValue.insert("create_date",createDate);
        schemeValue.insert("update_date",updateDate);
        schemeValue.insert("description",description);
        schemeValue.insert("version",version);
        schemeValue.insert("pre_set",preset.toJson());
        schemeValue.insert("test_type",testType.toJson());
        return schemeValue;
    }
}Scheme;

typedef struct scheme
{
    QString schemeKey{"scheme"};
    Scheme schemeValue;

    void fromJson(QJsonObject scheme)
    {
        if(!scheme.contains(schemeKey))
        {
            return;
        }
        schemeValue.fromJson(scheme[schemeKey].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject scheme;
        scheme.insert(schemeKey,schemeValue.toJson());
        return scheme;
    }
}Scheme;




#ifndef SCHEMEMODELDEFINE_H
#define SCHEMEMODELDEFINE_H

#include <QString>
#include <QDate>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

typedef struct parameter
{
    double mag = 0;
    double ang =0;
    double freq = 50;
    double dc =0;

    void fromJson(const QJsonObject paraJson)
    {
        mag = paraJson["mag"].toDouble();
        ang = paraJson["ang"].toDouble();
        freq = paraJson["freq"].toDouble();
        dc = paraJson["dc"].toDouble();
    }

    QJsonObject toJson()
    {
        QJsonObject paraJson;
        paraJson.insert("mag",mag);
        paraJson.insert("ang",ang);
        paraJson.insert("freq",freq);
        paraJson.insert("dc",dc);
        return paraJson;
    }
}Parameter;

typedef struct state
{
    QMap<QString,Parameter> parameters;

    void fromJson(const QJsonObject stateJson)
    {
        QStringList paranames = stateJson.keys();

        for (int i = 0; i < paranames.size(); ++i)
        {
            QString paraName = paranames[i];
            if(!stateJson[paraName].isObject())
            {
                return;
            }

            QJsonObject paraObj = stateJson[paraName].toObject();
            Parameter para;
            para.fromJson(paraObj);
            parameters.insert(paraName,para);
        }
    }

    QJsonObject toJson()
    {
        QJsonObject stateJson;

        QMap<QString,Parameter>::const_iterator iter = parameters.begin();
        while (iter!=parameters.end())
        {
            QString paraName = iter.key();
            Parameter value = iter.value();
            stateJson.insert(paraName,value.toJson());
            ++iter;
        }

        return stateJson;
    }

    void  addParameter(QString paraname)
    {
        Parameter para;
        parameters.insert(paraname,para);
    }

    bool deleteParameter(QString paraname)
    {
        return parameters.remove(paraname);
    }

}State;

typedef struct loop
{
    QMap<QString,State> states;

    void fromJson(const QJsonObject loopObj)
    {
        QStringList statenames = loopObj.keys();

        for (int i = 0; i < statenames.size(); ++i)
        {
            QString statename = statenames[i];
            QJsonValue value = loopObj[statename];
            if(!value.isObject())
            {
                return;
            }
            QJsonObject stateObj = value.toObject();
            State state;
            state.fromJson(stateObj);
            states.insert(statename,state);
        }
    }

    QJsonObject toJson()
    {
        QJsonObject loopObj;

        QMap<QString,State>::const_iterator iter = states.begin();
        while (iter!=states.end())
        {
            QString statename = iter.key();
            State value = iter.value();
            loopObj.insert(statename,value.toJson());
            ++iter;
        }

        return loopObj;
    }

    void addState()
    {
        int stateCount = states.size();
        QString stateName = "state"+QString::number(stateCount);
        State state;
        states.insert(stateName,state);
    }

    bool deleteState()
    {
        if(states.isEmpty())
        {
            return false;
        }
        return  states.remove(states.lastKey());
    }
}Loop;

typedef struct modelData
{
    QMap<QString,Loop> loops;

    void fromJson(const QJsonObject loopObj)
    {
        QStringList loopnames = loopObj.keys();

        for (int i = 0; i < loopnames.size(); ++i)
        {
            QString loopname = loopnames[i];
            QJsonValue value = loopObj[loopname];

            if(!value.isObject())
            {
                return;
            }

            QJsonObject loopobj = value.toObject();
            Loop loop;
            loop.fromJson(loopobj);
            loops.insert(loopname,loop);
        }
    }

    QJsonObject toJson()
    {
        QJsonObject modeldataObj;

        QMap<QString,Loop>::const_iterator iter = loops.begin();
        while (iter!=loops.end())
        {
            QString loopname = iter.key();
            Loop value = iter.value( );
            modeldataObj.insert(loopname, value.toJson());
            ++iter;
        }

        return modeldataObj;
    }

    void addLoop()
    {
        int loopCount = loops.size();
        QString loopName = "loop"+QString::number(loopCount);
        Loop loop;
        loops.insert(loopName,loop);
    }

    bool deleteLoop()
    {
        if(loops.isEmpty())
        {
            return false;
        }
        return loops.remove(loops.lastKey());
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

    void addTestPoint(QVariant var,QString unit)
    {
        TestPoint point;
        point.unit = unit;

        bool ok;
        var.toDouble(&ok);
        QString strVar;
        if(ok)
        {
            strVar = QString::number(var.toDouble());
        }
        else
        {
            strVar = var.toString();
        }

        point.var = strVar;

        point.id = id +"_"+ strVar;

        if(id == "volt")
        {
            point.name = strVar+unit+"Un";
        }
        else if (id == "curr") {
            point.name = strVar+unit+"In";
        }
        else if (id == "freq") {
            point.name = strVar+unit;
        }
        else if (id == "pf") {
            point.name = "PF="+strVar;
        }
        else if (id == "pq") {
            point.name = strVar+unit+"电流";
        }
        else {
            point.name = strVar+unit;
        }

        testPoints.append(point);
        //TODO NAME? ID?
    }

    void deleteTestPoint(int index)
    {
        testPoints.remove(index);
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
    double edCurr;
    double edVolt;
    ModelData modelData;

    void fromJson(QJsonObject presetValue)
    {
        //TODO if()
        name = presetValue["name"].toString();
        unit = presetValue["unit"].toString();
        switchMode = presetValue["auto_switch"].toString();
        edVolt = presetValue["ed_volt"].toDouble();
        //edVolt = round(edVolt*100)/100;
        edCurr = presetValue["ed_curr"].toDouble();
        modelData.fromJson(presetValue["model_data"].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject presetValue;
        presetValue.insert("name",name);
        presetValue.insert("unit",unit);
        presetValue.insert("auto_switch",switchMode);
        presetValue.insert("ed_volt", edVolt );
        presetValue.insert("ed_curr", edCurr );
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

    void fromJson(QJsonObject schemeObj)
    {
        name = schemeObj["name"].toString();
        user = schemeObj["user"].toString();
        createDate =schemeObj["create_date"].toString();
        updateDate =schemeObj["update_date"].toString();
        description = schemeObj["description"].toString();
        version = schemeObj["version"].toString();
        preset.fromJson(schemeObj["pre_set"].toObject());
        testType.fromJson(schemeObj["test_type"].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject schemeObj;
        schemeObj.insert("name",name);
        schemeObj.insert("user",user);
        schemeObj.insert("create_date",createDate);
        schemeObj.insert("update_date",updateDate);
        schemeObj.insert("description",description);
        schemeObj.insert("version",version);
        schemeObj.insert("pre_set",preset.toJson());
        schemeObj.insert("test_type",testType.toJson());
        return schemeObj;
    }
}Scheme;

typedef struct schemeModel
{
    QString schemeKey{"scheme"};
    Scheme scheme;

    void fromJson(QJsonObject schemeModelObj)
    {
        if(!schemeModelObj.contains(schemeKey))
        {
            return;
        }
        scheme.fromJson(schemeModelObj[schemeKey].toObject());
    }

    QJsonObject toJson()
    {
        QJsonObject schemeModelObj;
        schemeModelObj.insert(schemeKey,scheme.toJson());
        return schemeModelObj;
    }
}SchemeModel;

#endif // SCHEMEMODELDEFINE_H

/*********************************************************************************
**
** Copyright (c) 2017 The Regents of the University of California
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Renamed, modifed by Peter Sempolinski

#include "CFDanalysisType.h"

CFDanalysisType::CFDanalysisType(QString configFile)
{
    QFile inFile(configFile);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = inFile.readAll();
    inFile.close();

    myConfiguration = QJsonDocument::fromJson(val);

    QJsonObject obj    = myConfiguration.object();
    myName = obj["name"].toString();
}

QJsonDocument * CFDanalysisType::getRawConfig()
{
    return &myConfiguration;
}

QString CFDanalysisType::getInternalName()
{
    QJsonObject obj = myConfiguration.object();
    return obj["internalName"].toString();
}

QString CFDanalysisType::getName()
{
    QJsonObject obj = myConfiguration.object();
    return obj["name"].toString();
}

QStringList CFDanalysisType::getStageNames()
{
    QJsonObject obj = myConfiguration.object();
    QJsonObject stageList = obj["stages"].toObject();

    return stageList.keys();
}

bool CFDanalysisType::isDebugOnly()
{
    QJsonObject obj = myConfiguration.object();
    if (!obj.contains("debugOnly"))
    {
        return false;
    }
    if (!obj["debugOnly"].isBool())
    {
        return false;
    }
    if (obj["debugOnly"].toBool() == true)
    {
        return true;
    }
    return false;
}



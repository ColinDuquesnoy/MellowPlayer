#pragma once

#include "IUserScript.hpp"
#include <QObject>

namespace MellowPlayer::Domain
{
    class UserScriptBase: public QObject, public IUserScript
    {
    public:
        QString path() const override;
        QString code() const override;
        QString name() const override;
        void setName(const QString& name) override;

    protected:
        QString code_;
        QString path_;

    private:
        QString name_;
    };
}

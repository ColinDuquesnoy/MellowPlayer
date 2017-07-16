#pragma once

namespace MellowPlayer::Application {

    enum class UpdateChannel {
        Stable,
        Beta,
        Continuous
    };

    class UpdateChannelStringer {
    public:
        static QString toString(UpdateChannel channelType) {
            QString string;

            switch (channelType) {
                case UpdateChannel::Stable:
                    string = "Stable";
                    break;
                case UpdateChannel::Beta:
                    string = "Beta";
                    break;
                case UpdateChannel::Continuous:
                    string = "Continuous";
                    break;
            }

            return string;
        }

        static UpdateChannel fromString(const QString& channelName) {
            UpdateChannel channel;

            if (channelName == "Continuous")
                channel = UpdateChannel::Continuous;
            else if (channelName == "Beta")
                channel = UpdateChannel::Beta;
            else
                channel = UpdateChannel::Stable;

            return  channel;
        }
    };

}

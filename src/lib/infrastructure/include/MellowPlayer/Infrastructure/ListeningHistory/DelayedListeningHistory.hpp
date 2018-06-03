#pragma once

#include <MellowPlayer/Domain/ListeningHistory/ListeningHistory.hpp>
#include <MellowPlayer/Infrastructure/ITimer.hpp>
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class DelayedListeningHistory: public Domain::ListeningHistory
    {
    public:
        DelayedListeningHistory(Domain::IListeningHistoryDatabase& model, Domain::IPlayer& player_, Domain::Settings& settings,
                                std::unique_ptr<ITimer> timer);

    public slots:
        void addSong(Domain::Song *song);

    private:
        std::unique_ptr<ITimer> _timer;
    };
}

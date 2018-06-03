#include <MellowPlayer/Infrastructure/ListeningHistory/DelayedListeningHistory.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

#define DELAY 5000


DelayedListeningHistory::DelayedListeningHistory(IListeningHistoryDatabase& model, IPlayer& player, Settings& settings, unique_ptr<ITimer> timer)
        : ListeningHistory(model, player, settings),
          _timer(move(timer))
{
}

void DelayedListeningHistory::addSong(Song *song)
{
    if (song == nullptr)
        return;

    shared_ptr<Song> songCopy = song->clone();
    _timer->stop();
    _timer->start(DELAY, [=]()
    {
        if (*songCopy == *player_.currentSong())
            ListeningHistory::addSong(songCopy.get());
    });
}

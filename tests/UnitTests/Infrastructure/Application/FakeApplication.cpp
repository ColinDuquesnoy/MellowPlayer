#include "FakeApplication.hpp"

void MellowPlayer::Infrastructure::Tests::FakeApplication::initialize()
{
    isInitialized = true;
    emit initialized();
}

int MellowPlayer::Infrastructure::Tests::FakeApplication::run()
{
    isRunning = true;
    return returnCode;
}

void MellowPlayer::Infrastructure::Tests::FakeApplication::quit()
{
    quitRequested = true;
}

void MellowPlayer::Infrastructure::Tests::FakeApplication::restart()
{
    restartRequested = true;
}

void MellowPlayer::Infrastructure::Tests::FakeApplication::restoreWindow()
{
    restoreWindowRequested = true;
}

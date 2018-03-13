#include <MellowPlayer/Presentation/ViewModels/DevToolsWindowViewModel.hpp>

using namespace MellowPlayer::Presentation;

DevToolsWindowViewModel::DevToolsWindowViewModel(IContextProperties& contextProperties)
        : ContextProperty("_devTools", this, contextProperties)
{

}

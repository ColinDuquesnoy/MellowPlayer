#include "ContextProperty.hpp"
#include "ContextProperties.hpp"

using namespace MellowPlayer::Presentation;

ContextProperty::ContextProperty(IContextProperties& contextProperties)
{
    contextProperties.add(*this);
}

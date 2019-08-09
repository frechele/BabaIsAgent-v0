// Copyright(c) 2019 Hyeonsu Kim

#include <Baba/Common/Utils.h>

namespace Baba::Utils
{
bool ValidateWord(const Object& object)
{
    return object.GetProperty().test(static_cast<std::size_t>(ObjectName::WORD));
}

bool ValidateWord(const Object& object,
                  const std::vector<WordClass>& filteredClasses)
{
    if (!ValidateWord(object))
    {
        return false;
    }

    for (auto& cls : filteredClasses)
    {
        if (object.GetWordClass() == cls)
        {
            return true;
        }
    }

    return false;
}
}  // namespace Baba::Utils

#pragma once

namespace MathUtils
{
    template<typename TVal>
    TVal Clamp(TVal val, TVal min, TVal max)
    {
        if (val <= min)
        {
            return min;
        }
        else if (val >= max)
        {
            return max;
        }

        return val;
    }
}

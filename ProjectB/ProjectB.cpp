#include "pch.h"

#include "ProjectB.h"

#include "../ProjectC/ProjectC.h"

namespace ProjectB
{
    void Helper::Method()
    {
        ProjectC::Helper::Method();
    }
}
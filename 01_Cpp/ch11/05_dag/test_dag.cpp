
#include "dag.h"

int main()
{
    ModuleA ma1("A1", {});
    ModuleA ma2("A2", {"A1"});
    ModuleB mb1("B1", {"A1", "A2"});
    ModuleA ma3("A3", {"B1"});

    Executor e;
    e.add(&ma1);
    e.add(&ma2);
    e.add(&ma3);
    e.add(&mb1);

    e.execute();

    return 0;
}
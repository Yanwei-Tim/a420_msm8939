#include "shared.rsh"

int i;
rs_allocation ai;

void instance_test() {
    // Set our allocation based on the global input value.
    rsSetElementAt(ai, &i, 0);
}


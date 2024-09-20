#include <stdio.h>
#include "app.h"

int main() {
    setvbuf(stdout, NULL, _IOLBF, 0);
    init();
}

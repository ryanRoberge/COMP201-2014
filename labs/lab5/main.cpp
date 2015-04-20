#include "controller.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
	srand(time(0));
    Controller c;
    c.loop();
    return 0;
}

#include "model.h"
#include "view.h"

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

// Handle input
class Controller {
public:
    Controller();
    ~Controller();
    // Event loop
    void loop();
<<<<<<< HEAD
	void wipeShow();
=======
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
private:
    Model * model;
    View * view;
};
#endif
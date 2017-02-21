#include <Python.h>

#include <stdio.h>
#include <inttypes.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <errno.h>

#include "tsl2561.h"



static PyObject *
lux(PyObject *self, PyObject *noarg)
{
    // const char *command;
    // int sts;
    int fd = 0;
    // int lux;

    /*
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
        */
    fd = wiringPiI2CSetup(TSL2561_ADDR_LOW);

    return PyLong_FromLong(getLux(fd));
}

// Module commands
static PyMethodDef tsl2562Methods[] = {
    {"lux",  lux, METH_NOARGS,
     "Get lux."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

// Module definition
static struct PyModuleDef tsl2561module = {
   PyModuleDef_HEAD_INIT,
   "tsl2561",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   tsl2562Methods
};

// Module init
PyMODINIT_FUNC
PyInit_tsl2561(void)
{
    return PyModule_Create(&tsl2561module);
}

/*
void main(){
    int fd = 0;
    fd = wiringPiI2CSetup(TSL2561_ADDR_LOW);
    int lux;

    lux = getLux(fd);
      // system ("tput clear");
    printf("Lux: %d\n", lux);
}
*/

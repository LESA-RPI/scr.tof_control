IRMA MATRIX SDK README
======================

Welcome to the IRMA MATRIX SDK !

As you can read this, you have successfully extracted the SDK archive. Here
is an outline of the folders that have been created inside the destination
directory:

.
|
+--demos
|  |
|  +--..
|  :
|
+--docs
|  |
|  +--html-reference
|  |  |
|  |  +--..
|  |  :
|  |
|  +--other
|
+--include
|  |
|  +--3rd_party
|  |  |
|  |  +--boost-1_46_1
|  |  |  |
|  |  |  +--boost
|  |  |     |
|  |  |     +--..
|  |  |     :
|  |  |
|  |  +--boost-1_55_0
|  |     |
|  |     +--boost
|  |        |
|  |        +--..
|  |        :
|  |
|  +--iris
|     |
|     +--sensor-api
|        |
|        +--iris
|           |
|           +--..
|           :
|  
+--lib
   |
   +--<toolchain name>
      |
      +--3rd_party
      |  |
      |  +--boost-<version>
      |     |
      |     +--shared
      |     |
      |     +--static
      |
      +--iris
         |
         +--sensor-api
            |
            +--shared
            |
            +--static
   
You can find the code examples in the demos subdirectory. Please note that
for all except the examples 1, 2 and 11, you will need to set the SENSOR_URL
symbol to a value that matches your DIST500 hardware by modifying the #define
statement in the .cpp files accordingly.

An environment variable named MATRIX_SDK_DIR is used; it points to the
installation directory and is used by the qmake project file provided with
the demos. It is recommended to run the appropriate "build_demos_*.sh" script
inside the demos directory which will call qmake and make with MATRIX_SDK_DIR
set to its parent directory which is right if you didn't change the file 
structure.

The qmake make specifications mentioned in scripts "build_demos_*.sh" refer
to the system where the SDK was built. Adaption to your system is necessary
if you want to use the scripts.

Copy file "common_*_static.pri" to file "common.pri" if you are going to use 
static libraries and "common_*_shared.pri" to file "common.pri" otherwise.
Depending on your system configuration addition of settings
CONFIG -= qt core gui
QT -= core gui
to the Qt project include file may be necessary.

Please mind that you have to make the "libIrmaMatrix*" shared libraries and
the boost shared libraries known to the dynamic loader in order to be able
to run the compiled demos:
"export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<install dir>/lib/<toolchain name>/iris/sensor-api/shared"
"export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<install dir>/lib/<toolchain name>/3rd_party/boost-<version>/shared"

When using the API in your projects, you need to add
<install dir>/include/iris/sensor-api and
<install dir>/include/3rd_party/boost-<version> to your include file search path.
Also ensure to add <install dir>/lib/<toolchain name>/iris/sensor-api/shared or
<install dir>/lib/<toolchain name>/iris/sensor-api/static to the library search
path and add IrmaMatrix[.a] to the list of libraries. If you use shared
libraries you have to define the symbol SENSORAPI_DLL.

The Sensor API Tutorial PDF is part of the provided files. It is within the
<install dir>\docs\other folder. The full reference is available in HTML
format in the <install dir>\docs\html-reference directory.

Information about sensor diagnostics is provided in \docs\other\IrmaMatrixSensorStatuses_en.xlsx.

You may want to use the run_demo.sh script to execute the demos.

Readme for ColorMachineLibrary (CML)
====================================

CML is a self-contained implementation of color transformations used in
scientific color science and standards, based on informations from the
literature and reference material from standartization institutes.

CML is written in C and is available in this package as a precompiled
dynamic library.

If you consider incorporating CML into a bigger project and need (paid) help
in engineering, feel free to contact.

Designed and implemented by Tobias Stamm.
Email: cml@manderc.com





Installation
============

The folder "include/CML" contains all needed header files as well as the
header- and implementation-files of the color classes. It is recommended to
copy the folder "CML" as a whole to the default include directory of your IDE,
your system or any place of your desire. It is recommended to use the following
paths:

XCode:          /usr/local/include
VisualStudio:   C:\Program Files (x86)\Microsoft Visual Studio\VC\include



In the "lib" folder, you find libraries for MacOSX (32/64-Bit Universal) and
Windows-32 as well as Windows-64. Copy the files contained to the following
places:

mac/libcml.dylib:   /usr/local/lib

win32/libcml.lib:   C:\Program Files (x86)\Microsoft Visual Studio\VC\lib
win32/libcml.dll:   C:\Windows\SysWOW64

x64/libcml.lib:     C:\Program Files (x86)\Microsoft Visual Studio\VC\lib\amd64
x64/libcml.dll:     C:\Windows\System32






Building your own code
======================

In order to use CML in your own code, you need to set the following build
settings:


In XCode:
---------

Go to the build settings of your target and add the following settings:

- Other linker flags: -lcml
- Add a library search path: /usr/local/lib

Don't forget the dash - for the linker flags! If you installed the libraries
in a different folder, you need to set the library search path accordingly.


In Visual Studio:
-----------------

Go to: Project properties -> Configuration Properties -> Linker -> Input

Edit the "Additional Dependencies" attribute and add libcml.lib to the list.
If you close the dialog, VisualStudio will show something like
libcml.lib;%(AdditionalDependencies) in the property.


If it is not working yet:
-------------------------

Even if you did put the include files (the whole CML folder) and the library
files into the appropriate folders as described above, there might be some more
settings to do. You might need to perform some of the following tasks up until
it finally works without errors and warnings:

- Add the header search path in the build settings.
- Make sure, that your code builds for the architecture supported by this
  CML distribution.
- Optionally: Add a preprocessor macro CML_DEBUG=0 or CML_DEBUG=1
- Optionally: Add a preprocessor macro for Release: NDEBUG


When using ColorClasses:
------------------------

Simply copy all files of the ColorClasses folder to your project. They
originally are located in the folder include/CML/ColorClasses.





Contact
=======

Please contact cml@manderc.com for requests, bugs, hints, clarification and
similar things. Note that German is the preferred choice of correspondance
but English is offered as a common language of inter-communication.

If you consider incorporating CML into a bigger project and need (paid) help
in engineering, feel free to contact.






Version Notice
==============

This software is public domain since 2021-11-21.


WorkTracker2
============

*Note:* This README is still a work-in-progress. It will be finalized
        once the application is finished.

Revamp of the older WorkTracker application: 
https://github.com/the-codeslinger/WorkTracker


## Development


### Requirements

* CMake 3.16.3
* Qt 6

### Build

Depending on you environment setup for Qt, you are required to export
the path where CMake can find the Qt *.cmake files.

Example on my Linux installation:

    export CMAKE_PREFIX_PATH=/opt/Qt/6.0.0/gcc_64

Example on my Windows installation:

    set CMAKE_PREFIX_PATH=C:\Apps\Qt6\6.0.0\mingw81_64
    OR
    set CMAKE_PREFIX_PATH=C:\Apps\Qt6\6.0.0\msvc2019_64

If you use Qt Creator for development then this should not be 
necessary.

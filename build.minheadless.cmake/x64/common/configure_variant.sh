#!/bin/sh
VARIANT_FOLDER="$1"
VARIANT_NAME="$2"
OS_NAME="`uname`"
GENERATOR_NAME="Unix Makefiles"
CMAKE_EXTRA_ARGS=""
OSX_SDK_ROOT_FOLDER="/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/"
OSX_VALID_SDKS="MacOSX10.12.sdk MacOSX10.14.sdk"

rm -rf "./$VARIANT_FOLDER"
mkdir "./$VARIANT_FOLDER"
cd "./$VARIANT_FOLDER"

if [ "$OS_NAME" != "Darwin" ]; then
    OS_NAME="`uname -o`"
fi

if [ "$OS_NAME" = "Darwin" ]; then
    # Find the oldest valid SDK
    OSX_SELECTED_SDK=""
    for SDK in $OSX_VALID_SDKS; do
        if [ "$OSX_SELECTED_SDK" == "" ]; then
            if [ -e "${OSX_SDK_ROOT_FOLDER}/${SDK}" ]; then
                OSX_SELECTED_SDK="$SDK"
                break
            fi
        fi
    done

    if [ "$OSX_SELECTED_SDK" == "" ]; then
        echo "Not valid OS X SDK found. Aborting the build process."
        exit 1
    fi
    
    echo "Selected OS X SDK $OSX_SELECTED_SDK"
    CMAKE_EXTRA_ARGS="${CMAKE_EXTRA_ARGS} -DCMAKE_OSX_SYSROOT=${OSX_SDK_ROOT_FOLDER}/${OSX_SELECTED_SDK}"
fi

if [ "$OS_NAME" = "Msys" ]; then
    GENERATOR_NAME="MSYS Makefiles"
fi

if [ "$OS_NAME" = "Cygwin" ]; then
    CMAKE_EXTRA_ARGS="-DCMAKE_TOOLCHAIN_FILE=../../common/Toolchain-mingw32-cygwin.cmake"
    export CC="x86_64-w64-mingw32-gcc"
    export CXX="x86_64-w64-mingw32-g++"
fi

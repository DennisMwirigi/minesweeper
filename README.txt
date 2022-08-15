README

Let $TOP_DIR denote the directory containing this README file.
Let $INSTALL_DIR denote the directory into which this
software is to be installed.
To build and install the software, use the commands:
    cd $TOP_DIR
    cmake -H. -Bbin -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
    cmake --build bin --clean-first --target install

To run a demonstration, use the commands:
    $INSTALL_DIR/bin/demo
#!/bin/bash
build()
{
    mkdir -p build
    cd tools/cmaketools/
    python generate.py ../../cmake_conf
    cd -
    make -C dcnode/proto/
    #cd -
    make -C dagent/proto/
    cd build && cmake ../ && make
    cd -
}
###########################
clean()
{
    echo "clean files ..."
    find . -name *.pyc
    find . -name *.pyc | xargs rm -f
    find . -name '*.pb.cc'
    find . -name '*.pb.cc' | xargs rm -f
    find . -name '*.pb.h'
    find . -name '*.pb.h' | xargs rm -f
    cd build && make clean
}

inst_all()
{
    cd build && make install
}

run_test()
{
    echo "todo"
    cd bin && ./dcagent test
}

list()
{
    echo "usage:./automake.sh <option>  "
    echo "option as follow:"
    echo -e "\trebuild"
    echo -e "\tbuild"
    echo -e "\tclean"
    echo -e "\tlist"
    echo -e "\tinstall"
    echo -e "\ttest"
}

if [[ ! -d build ]];then
    echo "init project compiling ..."
    build
fi

case $1 in
    build)
        cd build && make
        ;;
    rebuild)
        build
        ;;
    clean)
        clean
        ;;
    install)
        inst_all
        ;;
    test)
        run_test
        ;;
    *)
        list
esac
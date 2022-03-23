#!/bin/bash

usage()
{
cat << EOF

Usage:  `basename $0` [options]

    -d | --kernel-source DIR - specify the kernel source directory
    -h | --help - print out options

EOF
}

ex()
{
    echo "$@"
    if ! "$@"; then
        printf "\nFailed executing $@\n\n"
        exit 1
    fi
}

while [ ! -z "$1" ]; do
    case $1 in
        -d | --kernel-source | -kernel-source)
            shift
            kernel_source_dir=$1
        ;;

        -h | --help)
            usage
            exit 0
        ;;

        *)
            echo
            echo "Wrong parameter $1"
            echo
            usage
            exit 1
        ;;
    esac
    shift
done

if [ -z "$kernel_source_dir" ]; then
    echo
    echo "Please speficy the kernel source directory"
    echo
    usage
    exit 1
fi

patches_dir=$(dirname $(readlink -f $0))

if ( patch --follow-symlinks < /dev/null 2>&1 1>/dev/null ) ; then
    extra_patch_parameters="${extra_patch_parameters} --follow-symlinks"
fi

for patch_file in $patches_dir/*.patch
do
    echo $patch_file
    ex patch ${extra_patch_parameters} -d $kernel_source_dir -p1 -l -i ${patch_file}
done

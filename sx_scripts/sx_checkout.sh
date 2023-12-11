#!/bin/bash
#
# Copyright © 2008-2022 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of Nvidia Corporation and its affiliates
# (the "Company") and all right, title, and interest in and to the software
# product, including all associated intellectual property rights, are and
# shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#

# get ref to "real" stdout
exec 3>&1

# Execute command w/ echo and exit if it fails
ex()
{
        echo "$@" >&3
        eval "$@"
        if [ $? -ne 0 ]; then
                printf "\nFailed executing $@\n" >&3
                exit 1
        fi
}

# Like ex above, but command is self echoing on stderr
xex()
{
        eval "$@" 2>&3
        if [ $? -ne 0 ]; then
                printf "\nFailed executing $@\n" >&3
                exit 1
        fi
}

# branch defaults to master
branch=${1:-master}

# make sure we have the list of all the other files and dirs
if [ ! -e sx_scripts/checkout_files ]; then
	ex git checkout ${branch} sx_scripts/checkout_files
fi

xex xargs -rt git ls-tree -r --name-only ${branch} <sx_scripts/checkout_files |
	xex xargs -rt git checkout ${branch}

rm -f sx_scripts/checkout_files

ex git update-ref HEAD ${branch}

ln -snf sx_scripts/configure
ln -snf sx_scripts/Makefile
ln -snf sx_scripts/makefile
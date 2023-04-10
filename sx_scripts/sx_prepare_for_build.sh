#!/bin/sh
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


GIT_URL=$1
GIT_BRANCH=$2

if [[ -z $GIT_URL ]]; then
  echo need GIT URL
  exit
fi

if [[ -z $GIT_BRANCH ]]; then
  echo need GIT branch
  exit
fi

mkdir sxd_kernel
cd sxd_kernel

echo === cloning bare
git clone -s --bare $GIT_URL .git
perl -ni -e "s/(bare = ).*/\${1}false/;print" .git/config
echo === checkout the checkout script
git checkout $GIT_BRANCH -- `git ls-tree -r --name-only $GIT_BRANCH sx_scripts/sx_checkout.sh`
echo === running the checkout script
./sx_scripts/sx_checkout.sh $GIT_BRANCH
git update-ref HEAD $GIT_BRANCH

echo === Done. Now exec:
echo "    cd sxd_kernel; ./configure "
echo "or:"
echo "    sx_prepare_rpm.sh"
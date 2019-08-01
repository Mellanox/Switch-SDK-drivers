#!/bin/bash
#
# Copyright (C) Mellanox Technologies, Ltd. 2008-2018 ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of Mellanox Technologies, Ltd.
# (the "Company") and all right, title, and interest in and to the software product,
# including all associated intellectual property rights, are and shall
# remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#
ex()
{
        makedist_log=$1
        shift
        if [ ! -z $makedist_log ]; then
            echo "$@ >> $makedist_log"
            eval "$@" >> $makedist_log 2>&1
        else
            echo "$@"
            eval "$@"
        fi
        status=$?
        if [ $status -ne 0 ]; then
                if [ ! -z $makedist_log ]; then
                    echo "Failed executing $@ >> $makedist_log" >&2
                    tail $makedist_log >&2
                else
                    echo "Failed executing $@" >&2
                fi
        		echo Build failed in $tmpdir >&2
                if [ ! -z $makedist_log ]; then
                    echo See log file $makedist_log >&2
                fi
                exit $status
        fi
}

CWD=`pwd`
project=${project:-"sx_kernel"}
tmpdir=`mktemp -d /tmp/build-$project-XXXXXX`
giturl=${giturl:-${CWD}}
head=${head:-`git show-ref -s -h -- HEAD`}
destdir=${destdir:-${CWD}}

# Add reference to local git directory on git.openfabrics.org
# git_reference_dir=${git_reference_dir:-"/mswg/git/switchx/sxd_kernel.git/"}

git_extra_flags=
if [ ! -z ${git_reference_dir} ] && [ -d ${git_reference_dir} ]; then
	git_extra_flags="--reference ${git_reference_dir}"
fi

# create a tree with only the 'fixes' patches applied
ex "" git clone -q -s -n $git_extra_flags $giturl $tmpdir/$project-fixes
ex "" pushd $tmpdir/$project-fixes
ex $tmpdir/$project-fixes.log \
	$CWD/sx_scripts/sx_checkout.sh $head
ex $tmpdir/$project-fixes.log BACKPORT_DIR='NONE' \
#Some QUILT versions create files with 0 permissions
#work around this
if [ -d .pc ]
then
	ex "" chmod -R u+rw .pc
	ex "" chmod -R o+r .pc
fi
ex "" cd $tmpdir
ex "" tar czf $tmpdir/$project-fixes.tgz $project-fixes
ex "" popd

# create a tree with no patches applied
ex "" git clone -q -s -n $git_extra_flags $giturl $tmpdir/$project
ex "" pushd $tmpdir/$project
ex $tmpdir/$project.log $CWD/sx_scripts/sx_checkout.sh $head
ex "" cd ..
ex "" tar czf $tmpdir/$project.tgz $project
ex "" popd

results=`(cd $tmpdir; ls *tgz)`
ex "" mv $tmpdir/*tgz $destdir
ex "" rm -fr $tmpdir
echo $results
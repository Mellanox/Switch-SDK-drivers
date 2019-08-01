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

#/bin/bash

MFA2PATH=$1

# If module $1 is loaded return - 0 else - 1
is_module()
{
	local RC
	/sbin/lsmod | grep -w "$1" > /dev/null
	RC=$?
	return $RC
}

print_usage()
{
	echo "Usage: `basename $0` <path_to_mfa2_file>"
}

if [ -z $MFA2PATH ]; then
	print_usage
	exit 1
fi

case "$1" in
	-h | --help)
		print_usage
		exit 0
		;;
	-*)
		echo "Error: Unknown option: $1" >&2
		print_usage
		exit 1 
		;;
	*)  # No more options
		;;
esac

if ! is_module sx_core; then
	echo "SX driver is not loaded"
	exit 1
fi

size=${#1}
if [ $size -lt 5 ]; then
	echo "Path too short"
	print_usage
	exit 1
fi

mfa2_name=$(basename $MFA2PATH)

if [ ${mfa2_name: -5} != ".mfa2" ]; then
	echo "Input file must be .mfa2 file!"
	print_usage
	exit 1
fi

mkdir -p /lib/firmware/
\cp -v $MFA2PATH /lib/firmware/
/sbin/modprobe mlxfw mfa2_file=${mfa2_name}
RC=$?
rm -vf /lib/firmware/${mfa2_name}
if [ $RC -ne 0 ]; then
	echo "Fail to burn FW"
	exit $RC
fi

/sbin/modprobe -r mlxfw
RC=$?
if [ $RC -ne 0 ]; then
	echo "Failed to unload mlxfw"
	exit $RC
fi

echo "FW burn script finish with success"


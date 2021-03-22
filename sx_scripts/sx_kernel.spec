#
# Copyright (c) 2006-2010 Mellanox Technologies. All rights reserved.
#
# This Software is licensed under one of the following licenses:
#
# 1) under the terms of the "Common Public License 1.0" a copy of which is
#    available from the Open Source Initiative, see
#    http://www.opensource.org/licenses/cpl.php.
#
# 2) under the terms of the "The BSD License" a copy of which is
#    available from the Open Source Initiative, see
#    http://www.opensource.org/licenses/bsd-license.php.
#
# 3) under the terms of the "GNU General Public License (GPL) Version 2" a
#    copy of which is available from the Open Source Initiative, see
#    http://www.opensource.org/licenses/gpl-license.php.
#
# Licensee has the right to choose one of the above licenses.
#
# Redistributions of source code must retain the above copyright
# notice and one of the license notices.
#
# Redistributions in binary form must reproduce both the above copyright
# notice, one of the license notices in the documentation
# and/or other materials provided with the distribution.
#
#

%{!?configure_options: %define configure_options %{nil}}
%{!?extra_make_options: %define extra_make_options %{nil}}

%{!?KVERSION: %define KVERSION %(uname -r)}
%define krelver %(echo -n %{KVERSION} | sed -e 's/-/_/g')

%{!?LIB_MOD_DIR: %define LIB_MOD_DIR /lib/modules/%{KVERSION}/updates}

%{!?K_SRC: %define K_SRC /lib/modules/%{KVERSION}/build}

%{!?KERNEL_SOURCES: %define KERNEL_SOURCES /lib/modules/%{KVERSION}/source}

# Disable debugging
%define debug_package %{nil}
%define __check_files %{nil}

%{!?_name: %define _name sx_kernel}
%{!?_version: %define _version @SED_VERSION@}
%{!?_release: %define _release @SED_RELEASE@}

Summary: SwitchX drivers for SX
Name: %{_name}
Version: %(echo @SED_VERSION@ | sed 's/-/_/g')
Release: %{_release}%{?extra_release}
License: GPL/BSD
Url: http://www.mellanox.com
Group: System Environment/Base
Source: %{_name}-%{_version}-%{_release}.tar.gz
BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{_version}-%{release}-XXXXXX)
Vendor: Mellanox
%description 
SwitchX low level drivers

For use by SX-SDK: SwitchX Manager software

%package devel
PreReq: coreutils
PreReq: kernel
Prereq: pciutils
Requires: sx_kernel
Version: %(echo @SED_VERSION@ | sed 's/-/_/g')
Release: %{_release}
Summary: SwitchX Driver symvers
Group: System Environment/Libraries
%description -n sx_kernel-devel
Modules.symvers file

#################################################################################################################################

%prep
%setup -n %{_name}-%{_version}-%{_release}

###
### build
###
%build

./configure --prefix=%{_prefix} --kernel-version %{KVERSION} --kernel-sources %{K_SRC} --modules-dir %{LIB_MOD_DIR} %{configure_options}

make kernel %{extra_make_options} # MODULES_DIR=/lib/modules/%{KVERSION} DESTDIR=$RPM_BUILD_ROOT

###
### install
###
%install
make install_kernel %{extra_make_options} MODULES_DIR=%{LIB_MOD_DIR} DESTDIR=$RPM_BUILD_ROOT
modsyms=`find $RPM_BUILD_DIR/%{_name}-%{_version}-%{_release} -name Module.symvers -o -name Modules.symvers`
install -d $RPM_BUILD_ROOT/%{_prefix}/src/%{_name}
for modsym in $modsyms
do
        cat $modsym >> $RPM_BUILD_ROOT/%{_prefix}/src/%{_name}/Module.symvers
done

%clean
#Remove installed driver after rpm build finished
rm -rf $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_DIR/%{_name}-%{_version}

%post
if [ $1 = 1 ]; then # 1 : This package is being installed for the first time
	depmod -a
fi

%preun


%postun
depmod -a

%files
%defattr(-,root,root,-)
/lib/modules/%{KVERSION}/updates
/etc/udev/rules.d/91-sx.rules
%config /etc/modprobe.d/sx.modprobe.conf
/etc/modprobe.d/blacklist-sx.conf
/etc/init.d/sxdkernel

%files devel
%defattr(-,root,root,-)
%dir %{_prefix}/src
%{_prefix}/src/%{_name}


%changelog
* Mon Aug 11 2010 Doron Tsur <doront@mellanox.co.il>
- Added blacklist for sx 

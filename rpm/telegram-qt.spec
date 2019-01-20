Name: telegram-qt
Summary: Qt library for Telegram network

%define version_major 0
%define version_minor 2
%define version_patch 0

Version: %{version_major}.%{version_minor}.%{version_patch}
Release: 1
Group: System/Libraries
License: LGPLv2.1
URL: https://github.com/Kaffeine/telegram-qt
Source0: https://github.com/Kaffeine/telegram-qt/releases/download/telegram-qt-%{version}/telegram-qt-%{version}.tar.bz2
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(Qt5Network)
BuildRequires: pkgconfig(Qt5Qml)
BuildRequires: pkgconfig(openssl)
BuildRequires: cmake >= 2.8

%description
%{summary}.

%package qt5
Summary: Qt library for Telegram network
Group: Development/Libraries
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
Requires: qt5-qtcore
Requires: qt5-qtnetwork
Requires: openssl

%description qt5
%{summary}.

%package qt5-devel
Summary:    Development headers and pkg-config for TelegramQt library
Group:      Development/Libraries
Requires:   %{name}-qt5%{?_isa} = %{version}-%{release}
%description qt5-devel
%{summary}.

%package qt5-declarative
Summary:    Declarative plugin for TelegramQt library
Group:      Development/Libraries
Requires:   %{name}-qt5%{?_isa} = %{version}-%{release}
Requires: qt5-qtdeclarative
%description qt5-declarative
%{summary}.

%package qt5-declarative-devel
Summary:    Development headers and pkg-config for TelegramQtQml library
Group:      Development/Libraries
Requires:   %{name}-qt5-declarative%{?_isa} = %{version}-%{release}
%description qt5-declarative-devel
%{summary}.

%prep
%setup -q

%build
mkdir build
cd build

%cmake \
    -DENABLE_TESTAPP=FALSE \
    -DBUILD_VERSION="%{version}" \
    ..

make %{?_smp_mflags}

%install
cd build

rm -rf %{buildroot}
%make_install

%post qt5 -p /sbin/ldconfig
%postun qt5 -p /sbin/ldconfig

%post qt5-declarative -p /sbin/ldconfig
%postun qt5-declarative -p /sbin/ldconfig

%files qt5
%defattr(-,root,root,-)
%{_libdir}/libTelegramQt5.so.%{version_major}.%{version_minor}
%{_libdir}/libTelegramQt5.so.%{version_major}.%{version_minor}.%{version_patch}

%files qt5-devel
%defattr(-,root,root,-)
%{_includedir}/TelegramQt5/TelegramQt/*
%{_libdir}/libTelegramQt5.so
%{_libdir}/cmake/TelegramQt5/TelegramQt5Config.cmake
%{_libdir}/cmake/TelegramQt5/TelegramQt5ConfigVersion.cmake
%{_libdir}/pkgconfig/TelegramQt5.pc

%files qt5-declarative
%defattr(-,root,root,-)
%{_libdir}/qt5/qml/TelegramQt/qmldir
%{_libdir}/qt5/qml/TelegramQt/libTelegramQmlPlugin.so
%{_libdir}/libTelegramQt5Qml.so.%{version_major}.%{version_minor}
%{_libdir}/libTelegramQt5Qml.so.%{version_major}.%{version_minor}.%{version_patch}

%files qt5-declarative-devel
%defattr(-,root,root,-)
%{_libdir}/qt5/qml/TelegramQt/plugins.qmltypes
%{_libdir}/libTelegramQt5Qml.so

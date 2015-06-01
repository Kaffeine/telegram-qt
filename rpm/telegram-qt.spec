Name:       telegram-qt

# >> macros
# << macros

Summary:    Draft version of Telegram binding for Qt.
Version:    0.0.1
Release:    1
Group:      System/Libraries
License:    Unknown
URL:        https://github.com/Kaffeine/telegram-qt
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  pkgconfig(Qt5Widgets)
BuildRequires:  pkgconfig(openssl)

%description
%{summary}.

%package testapp
Summary:    TelegramQT test application
Group:      System/Libraries
Requires:   %{name} = %{version}-%{release}

%description testapp
%{summary}.

%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qmake5

make %{?jobs:-j%jobs}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
# << install post

%files
%defattr(-,root,root,-)
%{_libdir}/
# >> files
# << files

%files testapp
%defattr(-,root,root,-)
%{_bindir}/
# >> files testapp
# << files testapp

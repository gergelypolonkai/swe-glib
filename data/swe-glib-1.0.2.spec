Name: swe-glib
Version: 1.0.2
Release: 1%{?dist}
Summary: A GLib style wrapper library around the Swiss Ephemeris library, created by Astrodienst.

Group: Development/Libraries
License: LGPLv3+
URL: http://gergely.polonkai.eu/swe-glib/
Source: https://github.com/gergelypolonkai/%{name}/archive/v%{version}.tar.gz

BuildRequires: pkgconfig
BuildRequires: glib2-devel
BuildRequires: gettext
BuildRequires: automake autoconf libtool
BuildRequires: gtk-doc
Requires: glib2
Requires: %{name}-data = %{version}-%{release}

%description

SWE-GLib is a GLib style wrapper library around the Swiss Ephemeris library,
created by Astrodienst. It can be used for precise astronomical calculation
based on time and topographic location.

%package data
Summary: A GLib style wrapper library around the Swiss Ephemeris library, created by Astrodienst.
Group: Development/Libraries
BuildArch: noarch

%description data
The swe-glib-data package includes data files for the SWE-GLib library.

%package devel
Summary: A GLib style wrapper library around the Swiss Ephemeris library, created by Astrodienst.
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}

%description devel
The swe-glib-devel package includes the header files for the SWE-GLib library.

%package doc
Summary: A GLib style wrapper library around the Swiss Ephemeris library, created by Astrodienst.
Group: Development/Libraries
Requires: %{name} = %{version}-%{release}
BuildArch: noarch

%description doc
The swe-glib-doc package includes documentation for the SWE-GLib library.

%prep
%setup -q


%build
%configure --enable-gtk-doc
make %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}
rm -f $RPM_BUILD_ROOT%{_libdir}/*.la
rm -f $RPM_BUILD_ROOT%{_libdir}/*.a
rm -f $RPM_BUILD_ROOT%{_datadir}/locale/hu/LC_MESSAGES/swe-glib.mo

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%doc ChangeLog
%{_libdir}/libswe-1.75.so.*
%{_libdir}/libswe-glib-1.0.so.*
%{_libdir}/girepository-1.0/SweGlib-1.0.typelib

%files data
%{_datadir}/swe-glib/*.se1

%files doc
%doc %{_datadir}/gtk-doc/html/*

%files devel
%{_includedir}/*
%{_libdir}/pkgconfig/*
%{_datadir}/gir-1.0/SweGlib-1.0.gir
%{_libdir}/libswe-1.75.so
%{_libdir}/libswe-glib-1.0.so

%changelog


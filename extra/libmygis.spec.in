Name: libmygis
Version: @VERSION@
Release: 0
Group: Monitoring/Cron
License: LGPL
Copyright: Copyright 2004-2007 Jeremy Cole and others
Summary: Library for reading and writing GIS formats
URL: http://jcole.us/software/libmygis/
Packager: Jeremy Cole <jeremy@jcole.us>

Source: libmygis-@VERSION@.tar.gz

%prep
%setup

%build
./configure
make

%install
make install

%files 
bin/mysqlgisimport
lib/libmygis.*
include/mygis

%description 
Library for reading and writing GIS formats

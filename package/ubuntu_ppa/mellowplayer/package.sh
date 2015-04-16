#! /bin/bash

package=mellowplayer
email=colin.duquesnoy@gmail.com
version=1.3.0
gpg_key=`cat gpg_key`
echo "gpg key: ${gpg_key}"

function configure(){
    rm debian/changelog
	echo "-- configuring changelog:"
        release=$1
	sed "s/@release@/${release}/g" changelog.in > debian/changelog
	cat debian/changelog
	cp debian/changelog ${package}-${version}/debian/changelog
}

function clean(){
	rm debian/changelog
	rm *.build
	rm *.dsc
	rm *.changes
	rm *.upload
}

function clean_all(){
	clean
	rm -rf ${package}-${version}
	rm *.tar.gz
}

function setup_upstream_tarball(){
	echo "-- setting up upstream tarball:"
	tar -czf mellowplayer.tar.gz ../../../../MellowPlayer/
	tar -xf mellowplayer.tar.gz
	cp -R debian MellowPlayer
	rm -rf MellowPlayer/package
	rm -rf MellowPlayer/.git
	mv MellowPlayer ${package}-${version}
	tar -czf ${package}_${version}.orig.tar.gz ${package}-${version}
}

function make_source_package(){
	echo "---- making package for $release"
	dh_make -y -s -e ${email} -f ../${package}_${version}.orig.tar.gz
	# debuild -us -uc
	debuild -S -sa -k${gpg_key}
}

setup_upstream_tarball
for release in 'trusty' 'utopic' 'vivid'
do 
	clean
	configure ${release}
	pushd ${package}-${version}
    make_source_package
	popd
	dput ppa:colin-duquesnoy/stable *.changes	
done

clean_all


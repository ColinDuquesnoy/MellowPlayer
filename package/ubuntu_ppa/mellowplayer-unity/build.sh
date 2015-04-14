#! /bin/bash

email=colin.duquesnoy@gmail.com
version=1.3.0
gpg_key=`cat gpg_key`
echo "gpg key: ${gpg_key}"

function configure(){
	echo "-- configuring changelog:"
        release=$1
	sed "s/@release@/${release}/g" changelog.in > debian/changelog
	cat debian/changelog
}

function clean(){
	rm debian/changelog
	rm -rf mellowplayer-*
	rm *.build
}

function clean_all(){
	clean
	rm *.dsc
	rm *.tar.gz
	rm *.changes
}

function setup_upstream_tarball(){
	echo "-- setting up upstream tarball:"
	tar -czf mellowplayer.tar.gz ../../../../MellowPlayer/
	tar -xf mellowplayer.tar.gz
	rm -rf MellowPlayer/package
	rm -rf MellowPlayer/.git
	cp -R debian MellowPlayer
	mv MellowPlayer mellowplayer-${version}
	tar -czf mellowplayer_${version}.orig.tar.gz mellowplayer-${version}
}

function make_deb(){
	echo "---- making package for $release"
	dh_make -s -e ${email} -f ../mellowplayer_${version}.orig.tar.gz
	debuild -S -sa -k${gpg_key}
}

clean_all
for release in 'trusty'
do 
	clean
	configure ${release}
	setup_upstream_tarball
	pushd mellowplayer-${version}
	make_deb
	popd
done

clean



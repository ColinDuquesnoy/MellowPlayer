#! /bin/bash

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

dput ppa:colin-duquesnoy/ppa *.changes

rm debian/changelog
rm -rf mellowplayer-*
rm *.build
rm *.dsc
rm *.tar.gz
rm *.changes
rm *.upload

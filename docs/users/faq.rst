FAQ & Known issues
==================

Playback does not start on some services such as Soundcloud or Mixcloud... What can I do?
-----------------------------------------------------------------------------------------

Services that don't use flash often requires proprietary audio codecs to be installed on your system. 

Make sure you have installed the properietary audio codecs (ffmpeg with extra codecs) by following your distribution's install instructions.


The application crash at startup on GNU/Linux with open source NVIDIA drivers. What can I do?
---------------------------------------------------------------------------------------------

Qt/QML applications don't work well with the open source NVIDIA drivers (nouveau). It is recommended to **use the proprietary NVIDIA drivers**.


There is no music playback on Spotify. What can I do?
-----------------------------------------------------

Make sure you have installed both the properietary audio codecs (ffmpeg with extra codecs) and the widevine DRM plugin. The DRM plugin can be extracted from chromium binary archive:

.. code-block:: bash

    wget https://archive.archlinux.org/packages/c/chromium/chromium-61.0.3163.100-1-x86_64.pkg.tar.xz
    wget https://dl.google.com/widevine-cdm/1.4.8.1008-linux-x64.zip
    tar -xvf chromium-61.0.3163.100-1-x86_64.pkg.tar.xz
    unzip 1.4.8.1008-linux-x64.zip

    sudo mkdir /usr/lib/chromium
    sudo cp libwidevinecdm.so /usr/lib/chromium
    sudo cp ./usr/lib/chromium/libwidevinecdmadapter.so /usr/lib/chromium
    sudo chmod 644 /usr/lib/chromium/libwidevinecdm.so
    sudo chmod 644 /usr/lib/chromium/libwidevinecdmadapter.so

Not all advertised services are available on Windows, OSX and the AppImage. Is it normal?
-----------------------------------------------------------------------------------------

The official releases of Qt and our official releases are not built with proprietary audio codecs for licensing reasons. Services that require proprietary codecs are not loaded in the application.

To get those service to work, you'll need to recompile Qt WebEngine and MellowPlayer yourself with proprietary codecs support.

Note that with native GNU/Linux packages of MellowPlayer (Fedora, Ubuntu, Archlinux, openSUSE and KaOS) you just have to install proprietary audio codecs using your distribution's package manager (the package is usually named **ffmpeg-extra**).

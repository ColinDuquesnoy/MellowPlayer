Installation
============

This page will guide you throught the installation of MellowPlayer on the
supported operating systems.

GNU/Linux
---------

We provide an AppImage so that you can try MellowPlayer on any distribution.

Download MellowPlayer-x86_64.AppImage from a `github release`_, make it executable (chmod +x MellowPlayer-x86_64.AppImage) and run it, that's all.

Please note that there are some limitations with the AppImage, it does not include proprietary codecs for licensing reasons.

Distribution specific packages can be download from `openSUSE build service`_ (Ubuntu and openSUSE Tumbleweed are currently supported)

Fedora
++++++

Starting from Fedora 27, MellowPlayer is available from the official stable repositories:

.. code-block:: bash

    sudo dnf install mellowplayer

Proprietary codecs
******************

Most services require proprietary audio codecs to work. You can install them from the `RPMFusion repositories`_:

.. code-block:: bash

    sudo dnf install qt5-qtwebengine-freeworld

Flash 
****** 

Services such as Deezer and Tidal require flash to work. You can install it from the adobe repositories:

.. code-block:: bash

    sudo rpm -ivh http://linuxdownload.adobe.com/adobe-release/adobe-release-i386-1.0-1.noarch.rpm
    sudo rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-adobe-linux
    sudo dnf install flash-player-ppapi

Widevine
*********

Spotify requires the widevine ppapi plugin to work, you can install it by running the below commands:

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


Ubuntu 18.04
++++++++++++

Before installing MellowPlayer, **make sure the universe repository is enabled**:

.. code-block:: bash

    sudo add-apt-repository universe


Install procedure:

.. code-block:: bash

    sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/ColinDuquesnoy/xUbuntu_18.04/ /' > /etc/apt/sources.list.d/mellowplayer.list"
    wget -nv https://download.opensuse.org/repositories/home:ColinDuquesnoy/xUbuntu_18.04/Release.key -O Release.key
    sudo apt-key add - < Release.key
    sudo apt update
    sudo apt install mellowplayer
    
Ubuntu 18.10
++++++++++++

Before installing MellowPlayer, **make sure the universe repository is enabled**:

.. code-block:: bash

    sudo add-apt-repository universe


Install procedure:

.. code-block:: bash

    sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/ColinDuquesnoy/xUbuntu_18.10/ /' > /etc/apt/sources.list.d/mellowplayer.list"
    wget -nv https://download.opensuse.org/repositories/home:ColinDuquesnoy/xUbuntu_18.10/Release.key -O Release.key
    sudo apt-key add - < Release.key
    sudo apt update
    sudo apt install mellowplayer
    
ArchLinux
+++++++++

MellowPlayer is available from the `AUR`_, install it with your favorite AUR tool (e.g. yaourt).


.. code-block:: bash

    yaourt -S mellowplayer

.. _AUR: https://aur.archlinux.org/packages/mellowplayer

openSuse Leap 15
++++++++++++++++

Use the `openSUSE build service`_ web interface or install manually:

.. code-block:: bash

    zypper addrepo https://download.opensuse.org/repositories/home:ColinDuquesnoy/openSUSE_Leap_15.0/home:ColinDuquesnoy.repo
    zypper refresh
    zypper install MellowPlayer


openSuse Tumbleweed
+++++++++++++++++++

Use the `openSUSE build service`_ web interface or install manually:

.. code-block:: bash

    zypper addrepo http://download.opensuse.org/repositories/home:ColinDuquesnoy/openSUSE_Tumbleweed/home:ColinDuquesnoy.repo
    zypper refresh
    zypper install MellowPlayer

KaOS
++++

MellowPlayer is available from `KaOSx/apps`_ repository, just run:

.. code-block:: bash

    $ sudo pacman -S mellowplayer


.. _KaOSx/apps: http://kaosx.tk/packages/index.php?subdir=apps&sortby=name


Other distributions
+++++++++++++++++++

You will have to compile from source. See the `README`_ for build instructions.

.. _README: https://github.com/ColinDuquesnoy/MellowPlayer/blob/qbs/README.md#compilation

OS X
----

Just grab the dmg image from the `official website`_ (click on the **OS X folder**), drag and drop the MellowPlayer application in your **Applications** folder.

Please note the dmg we provide is built with a version of QtWebEngine built without proprietary codecs support (for licensing reasons). If your favorite service require proprietary codecs to work, you'll need to build QtWebEngine with the flag ``use_proprietary_codecs`` and build MellowPlayer using that QtWebEngine version.

Windows
-------

Just grab the windows installer from the `official website`_ (click on the **Windows folder**) and follow the instructions.

Please note the Windows Installer we provide is built with a version of QtWebEngine built without proprietary codecs support (for licensing reasons). If your favorite service require proprietary codecs to work, you'll need to build QtWebEngine with the flag ``use_proprietary_codecs`` and build MellowPlayer using that QtWebEngine version.


.. _README: https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/README.md
.. _official website: http://colinduquesnoy.github.io/MellowPlayer
.. _github release: https://github.com/ColinDuquesnoy/MellowPlayer/releases
.. _openSUSE build service: https://software.opensuse.org//download.html?project=home%3AColinDuquesnoy&package=MellowPlayer
.. _RPMFusion repositories: https://rpmfusion.org/Configuration

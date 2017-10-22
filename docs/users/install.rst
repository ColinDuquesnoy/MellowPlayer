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

Ubuntu 17.10
++++++++++++

TODO when available from software.opensuse.org


ArchLinux
+++++++++

MellowPlayer is available from the `AUR`_, install it with your favorite AUR tool (e.g. yaourt).


.. code-block:: bash

    yaourt -S mellowplayer

.. _AUR: https://aur.archlinux.org/packages/mellowplayer


openSuse Tumbleweed
+++++++++++++++++++

Use the `openSUSE build service`_ web interface or install manually:

.. code-block:: bash

    zypper addrepo https://download.opensuse.org/repositories/home:ColinDuquesnoy/openSUSE_Tumbleweed/home:ColinDuquesnoy.repo
    zypper refresh
    zypper install MellowPlayer

KaOS
++++

MellowPlayer is available from `KaOSx/apps`_ repository, just run:

.. code-block:: bash

    $ sudo pacman -S mellowplayer


.. _KaOSx/apps: http://kaosx.tk/packages/index.php?subdir=apps&sortby=name


Fedora
++++++

Only fedora rawhide is supported at the moment.

Use the `openSUSE build service`_ web interface or install manually:

.. code-block:: bash

    dnf config-manager --add-repo https://download.opensuse.org/repositories/home:ColinDuquesnoy/Fedora_Rawhide/home:ColinDuquesnoy.repo
    dnf install MellowPlayer


Other distributions
+++++++++++++++++++

You will have to compile from source. Grab the latest source release from the `official website`_, extract the archive and run the following commands:

.. code-block:: bash

    $ cmake .
    $ make
    $ sudo make install

Before compiling, you will need to install **Qt >= 5.9 (with QtWebEngine and QtQuickControls2)**.

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
Installation
============

This page will guide you throught the installation of MellowPlayer on the
supported operating systems.

GNU/Linux
---------

We provide an AppImage so that you can try MellowPlayer on any distribution.

Download MellowPlayer-x86_64.AppImage from a `github release`_, make it executable (chmod +x MellowPlayer-x86_64.AppImage) and run it, that's all.

Please note that there are some limitations with the AppImage, it does not include proprietary codecs for licensing reasons.

We plan to provide more distribution specific packages in the future (https://github.com/ColinDuquesnoy/MellowPlayer/issues/107)

KaOS
++++

MellowPlayer is available from `KaOSx/apps`_ repository, just run:

.. code-block:: bash

    $ sudo pacman -S mellowplayer


To start the program, either start it from your applications menu (*Multimedia/MellowPlayer*) or run the following command:

.. code-block:: bash

    $ MellowPlayer

.. _KaOSx/apps: http://kaosx.tk/packages/index.php?subdir=apps&sortby=name

ArchLinux
+++++++++

MellowPlayer is available from the `AUR`_, install it with your favorite AUR tool (e.g. yaourt).


To start the program, either start it from your applications menu or run the following command:

.. code-block:: bash

    $ MellowPlayer

.. _AUR: https://aur.archlinux.org/packages/mellowplayer

openSuse Tumbleweed
+++++++++++++++++++

A rpm package is available for openSUSE TumbleWeed: https://software.opensuse.org//download.html?project=home%3AColinDuquesnoy&package=MellowPlayer

Fedora
++++++

Only fedora rawhide is supported at the moment: https://software.opensuse.org//download.html?project=home%3AColinDuquesnoy&package=MellowPlayer


Other distributions
+++++++++++++++++++

You will have to compile from source. Grab the latest source release from the `official website`_, extract the archive and run the following commands:

.. code-block:: bash

    $ cmake -DBUILD_TESTS=FALSE -DCMAKE_BUILD_TYPE=Release
    $ make
    $ sudo make install

To start the program, either start it from your applications menu or run the following command:

.. code-block:: bash

    $ MellowPlayer

Before compiling, you will need to install **Qt >= 5.9 (with QtWebEngine and QtQuickControls2)**. If you favorite service require proprietary codecs to work, we suggest you check if your distribution provide a version of QtWebEngine compiled with the flag ``use_proprietary_codecs`` or compile it yourself.


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

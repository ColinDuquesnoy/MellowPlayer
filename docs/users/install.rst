Installation
============

This page will guide you throught the installation of MellowPlayer on the
supported operating systems.

GNU/Linux
---------

We provide an AppImage so that you can try MellowPlayer on any distribution.

Download MellowPlayer-x86_64.AppImage from a `github release`_, make it executable (chmod +x MellowPlayer-x86_64.AppImage) and run it, that's all.

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

Before compiling MellowPlayer 2, you will need to install **Qt >= 5.9 (with QtWebEngine and QtQuickControls2)**.


OS X
----

Just grab the dmg image from the `official website`_ (click on the **OS X folder**), drag and drop the MellowPlayer application in your **Applications** folder.

Windows
-------

Just grab the windows installer from the `official website`_ (click on the **Windows folder**) and follow the instructions.


.. _README: https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/README.md
.. _official website: http://colinduquesnoy.github.io/MellowPlayer
.. _github release: https://github.com/ColinDuquesnoy/MellowPlayer/releases

Things to check before reporting an issue
-----------------------------------------

1. Make sure the bug has not already been reported and search in the issue tracker for similar issue.
2. If you're experiencing a crash of the application and are using open source NVIDIA drivers on GNU/Linux: please first try the proprietary NVIDIA drivers before reporting.
3. If you're experiencing a crash of the application and are using the proprietary NVIDIA drivers: make sure you rebooted after your last NVIDIA driver update and make sure to run ``sudo nvidia-xconfig`` before reporting the issue.
4. If you're experiencing troubles playing specific streams on services that don't use flash (e.g. youtube or soundcloud) using the Linux AppImage or the Window/MacOS official installer, you need to build QtWebEngine with support for proprietary codecs and replace the QtWebEngine library used by MellowPlayer. The official Qt release we use to create our official releases is not built with proprietary codecs support for legal reasons. 
If you're using GNU/Linux, check if a native package of MellowPlayer is available for your distribution and use it instead of AppImage. Native packages usually use system ffmpeg and it should be enought to install extra ffmpeg plugins for the missing proprietary codecs.
Note that MP3 is still considered as a proprietary/patented codec prior to Qt 5.11.

Reporting bugs or Wishes
------------------------

Report any bugs you encountered or any wishes on our [issue tracker](https://github.com/ColinDuquesnoy/MellowPlayer/issues).

If you're reporting a bug, **make sure to provide the following information**:

- Information about your **Operating system** (e.g. Windows 8.1, Mac OSX Yosemite,...). If you're on Linux, you'll need to specify the
  name of the distribution and the desktop environment you're using and whether you're using a native package or the AppImage.
- The **music streaming service** that you were using when you encountered the bug if related to a specific streaming service.
- A **clear description** of the bug with **steps to reproduce**.
- You should use **English** to describe your issue. French is also accepted.
- Paste the application log between triple backquotes ```(About > Show Logs)```.

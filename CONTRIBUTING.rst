Contributing to MellowPlayer
============================

Reporting bugs or Wishes
------------------------

Report any bugs you encountered or any wishes on our `issue tracker`_.

If you're reporting a bug, **make sure to provide the following information**:

- **Operating system** (e.g. Windows 8.1, Mac OSX Yosemite,...). If you're on Linux, you'll need to specify the
  name of the distribution and the desktop environment you're using.
- The **music streaming service** that you were using when you encountered the bug.
- A **clear description** of the bug with **steps to reproduce**.
- You should use **English** to describe your issue. French is also accepted.


.. note:: There is a menu action in the application to easily open a new issue: *Help > Report a bug*

.. _issue tracker: https://github.com/ColinDuquesnoy/MellowPlayer/issues

Submitting a pull request
-------------------------

Here are the steps you need to follow to start working on MellowPlayer and submit your work
for evaluation or integration into the main project:

1. Fork the Repo on github.
2. Create a feature or a bugfix branch before you start coding.
3. Add your name to AUTHORS.md
4. Format the code using ``utils/beautify.sh`` (run it from the root source directory).
5. Push to your fork and submit a pull request to **the master branch**.


Adding support for a new service
--------------------------------

Web streaming service integration plugins are now written in pure javascript.

1. Copy the ``plugin`` directory from ``utils/templates`` to ``~/.local/share/mellowplayer/plugins``
2. Rename the ``plugin`` directory to the name of the streaming service (lower case).
3. Edit ``metadata.ini`` (add correct url, name, version,...)
4. Edit ``description.html`` to describe the streaming service
5. Add service logo
6. Implement the functions of ``integration.js``
7. Once your plugin works, submit a pull request!


Adding/Updating a new translation
---------------------------------

**To add a new translation**, follow the below steps:

1. Run the *devhelper script*: ``python3 utils/devhelper.py``
2. Select the **first entry** in the menu (*Add a new translation*)
3. Indicate the code for the language you want to add (e.g. fr, en, es,...)
4. Open app/translations/mellowplayer_lang.ts (where lang is the code you specified in the previous step)
   with Qt linguist
5. Once you've finished translating, save you work and make a release (File->Release)
6. Submit a pull request!

**To update an existing translation**, run the *devhelper script* but, this time, use the **second entry** 
in the menu (*Update translations*). Afterward you can just follow step 4, 5 and 6.

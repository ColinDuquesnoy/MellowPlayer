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

MellowPlayer translations are hosted on transifex: https://www.transifex.com/colinduquesnoy/mellowplayer/

- Create an account at transifex
- Go to the project's homepage and click on the "Join the team" button
- If the language you want to work on does not exists yet, send us a language request. Once the request has been accepted, a new translation file for the requested language will be created automatically by transifex.
- To actually start translating, go to the project's home page on transifex and click on the translate button. This will open the translator tool where you can choose the resource and the language you want to work on.

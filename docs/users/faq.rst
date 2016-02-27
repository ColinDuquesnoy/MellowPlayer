FAQ & Known issues
==================

Known issues
------------

- Mixcloud fails to load due to an ERR_SSL_PROTOCOL_ERROR on GNU/Linux with nss 3.21. This is a well known issue for chromium < 47. QtWebEngine needs to be `patched`_
- Media Player Keys support on OSX and Windows might not work.


FAQ
---

*Empty*


.. _patched: http://pkgs.fedoraproject.org/cgit/rpms/qt5-qtwebengine.git/commit/?id=9a15e3c582902772e7876660afd06f57c4ff48d2

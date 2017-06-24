FAQ & Known issues
==================

Frequently asked questions
--------------------------

- I cannot play music on Spotify and on Mixcloud. What can I do?

Spotify and Mixcloud streaming has become quite tricky since they moved away from flash for managing content.

The official release of Qt and our official releases are not built with proprietary codecs for licensing reasons.

**You need to recompile Qt WebEngine yourself with proprietary codecs support**. *Note that some linux distributions such as KaOS and OpenSuse ships QtWebEngine with proprietary codecs related.*

Spotify also requires the Widevine plugin to work. You can find more information in this `blog post`_.

.. _blog post: http://blog.qt.io/blog/2016/06/03/netflix-qt-webengine-5-7/

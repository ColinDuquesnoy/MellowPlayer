#!/usr/bin/env python3
"""
Bootstrapping MellowPlayer

Detect environment and execute MellowPlayer from source checkout.

.. note:: This script has been inspired by the bootstrap script of SpyderIDE.
"""
import time
time_start = time.time()
import os.path as osp
import platform
import sys


#--- bootstrapping MellowPlayer
print("Executing MellowPlayer from source checkout")


#--- checking minimum python version, we need Python >= 3.4
pyver = "%s%s" % (sys.version_info[0], sys.version_info[1])
if pyver < '34':
    print('Cannot run MellowPlayer with Python %s, Python >= 3.4 is required',
          platform.python_version())
    sys.exit(1)


#--- patching sys.path
DEVPATH = osp.dirname(osp.abspath(__file__))
sys.path.insert(0, DEVPATH)
print("01. Patched sys.path with %s" % DEVPATH)


#--- checking required dependencies
try:
    import PyQt4
except ImportError:
    print('02. WARNING: PyQt4 not detected. Install pyqt4 for python3 and try again...')
    sys.exit(1)
else:
    print('02. PyQt4 detected')


#--- importing MellowPlayer
from mellowplayer.system import get_versions, get_vcs_revision
versions = get_versions()
print("03. Imported MellowPlayer %s (%s)" % (
    versions['mellowplayer'], get_vcs_revision()))
print("    [Python %s %dbits, Qt %s, %s %s on %s]" % \
      (versions['python'], versions['bitness'], versions['qt'],
       versions['qt_api'], versions['qt_api_ver'], versions['system']))


#--- executing MellowPlayer
print("04. Executing app.main()")
from mellowplayer import app
time_lapse = time.time() - time_start
print("Bootstrap completed in " +
      time.strftime("%H:%M:%S.", time.gmtime(time_lapse)) +
      # gmtime() converts float into tuple, but loses milliseconds
      ("%.4f" % time_lapse).split('.')[1])
app.main()

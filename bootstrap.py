#!/usr/bin/env python3
"""
Bootstrapping MellowPlayer

Detect environment and execute MellowPlayer from source
checkout.

"""
import os.path as osp
import platform
import sys


#--- checking minimum python version, we need Python 3
pyver = int(sys.version_info[0])
if pyver < 3:
    print('Cannot run MellowPlayer with Python %s, Python 3 is required' %
          platform.python_version())
    sys.exit(1)


#--- patching sys.path
DEVPATH = osp.dirname(osp.abspath(__file__))
sys.path.insert(0, DEVPATH)
print("Patched sys.path with %s" % DEVPATH)


#--- run app
from mellowplayer.system import get_vcs_revision
print("Executing MellowPlayer from source checkout (%s)" %
      get_vcs_revision())
from mellowplayer.main import main
main()

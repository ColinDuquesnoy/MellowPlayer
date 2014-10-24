#!/usr/bin/env python3
"""
Setup script for MellowPlayer
"""
import sys
from setuptools import setup, find_packages
from mellowplayer import __version__

try:
    from pyqt_distutils.build_ui import build_ui
    cmdclass = {'build_ui': build_ui}
except ImportError:
    build_ui = None
    cmdclass = {}


# get long description
with open('README.rst', 'r') as readme:
    long_desc = readme.read()


data_files = []
if sys.platform == 'linux':
    data_files.append(('/usr/share/applications',
                       ['share/MellowPlayer.desktop']))
    data_files.append(('/usr/share/pixmaps', ['share/icons/MellowPlayer.png']))


setup(
    name='MellowPlayer',
    version=__version__,
    packages=[p for p in find_packages() if 'test' not in p],
    keywords=['Music; Cloud; Grooveshark; Player'],
    data_files=data_files,
    url='https://github.com/ColinDuquesnoy/MellowPlayer',
    license='GPL v2',
    author='Colin Duquesnoy',
    author_email='colin.duquesnoy@gmail.com',
    description='Cloud Music integration for your desktop (cross-platform)',
    long_description=long_desc,
    entry_points={'gui_scripts': ['MellowPlayer = mellowplayer.app:main']},
    cmdclass=cmdclass,
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Environment :: X11 Applications :: Qt',
        'Intended Audience :: End Users/Desktop',
        'License :: OSI Approved :: GNU General Public License v2 (GPLv2)',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: POSIX :: Linux',
        'Operating System :: POSIX :: BSD'
        'Programming Language :: Python :: 3.4',
        'Topic :: Multimedia :: Sound/Audio :: Players',
    ]
)


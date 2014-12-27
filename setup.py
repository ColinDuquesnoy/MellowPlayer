#!/usr/bin/env python3
"""
Setup script for MellowPlayer
"""
import os
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


def collect_data_files():
    def sv_files(path):
        for d in os.listdir(path):
            fn = os.path.join(path, d)
            if os.path.isfile(fn):
                yield fn

    data_files = []
    if sys.platform == 'linux':
        # Desktop file + icon
        data_files.append(('share/applications',
                           ['data/mellowplayer.desktop']))
        data_files.append(('share/pixmaps',
                           ['data/icons/application-x-mellowplayer.png']))
    # Plugins (services and extensions)
    data_files.append(('share/mellowplayer/plugins/services',
                       list(sv_files('data/plugins/services'))))
    data_files.append(('share/mellowplayer/plugins/extensions',
                       list(sv_files('data/plugins/extensions'))))
    return data_files


setup(
    name='MellowPlayer',
    version=__version__,
    packages=find_packages(),
    keywords=['Music; Cloud; Grooveshark; Media Player;'],
    data_files=collect_data_files(),
    url='https://github.com/ColinDuquesnoy/MellowPlayer',
    license='GPL v2',
    author='Colin Duquesnoy',
    author_email='colin.duquesnoy@gmail.com',
    description='Cross-platform cloud music integration for your desktop',
    long_description=long_desc,
    entry_points={'gui_scripts': ['MellowPlayer = mellowplayer.main:main']},
    cmdclass=cmdclass,
    install_requires=['yapsy'],
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

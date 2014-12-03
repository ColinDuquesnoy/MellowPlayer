import functools
import os
import platform
import subprocess
from mellowplayer import __version__


WINDOWS = platform.system() == 'Windows'
LINUX = platform.system() == 'Linux'
DARWIN = platform.system() == 'Darwin'
linux_distribution = None
if LINUX:
    linux_distribution = os.popen(
        '. /etc/os-release && echo "$NAME"').read().splitlines()[0]


def ensure_directory_exists(func):
    @functools.wraps(func)
    def wrapper(*args, **kwds):
        ret = func(*args, **kwds)
        try:
            os.makedirs(ret)
        except OSError:
            pass
        return ret
    return wrapper


@ensure_directory_exists
def get_cache_directory():
    """
    Gets the platform specific cache directory (where we store the log file and
    the temporary files create by the linter).
    :return: platform specific cache directory.
    """
    if WINDOWS:
        return os.path.join(os.path.expanduser("~"), 'MellowPlayer', 'cache')
    elif DARWIN:
        return os.path.join(os.path.expanduser("~"), 'Library',
                            'Caches', 'MellowPlayer')
    else:
        return os.path.join(os.path.expanduser("~"), '.cache', 'MellowPlayer')


def get_versions():
    """ Get version information for components used by MellowPlayer """
    import sys
    import platform

    from mellowplayer.qt import QT_API
    from mellowplayer.qt import QtCore, Qt

    return {
        'mellowplayer': __version__,
        'python': platform.python_version(),  # "2.7.3"
        'bitness': 64 if sys.maxsize > 2**32 else 32,
        'qt': QtCore.QT_VERSION_STR,
        'qt_api': 'PyQt%s' % QT_API,
        'qt_api_ver': Qt.PYQT_VERSION_STR,
        'system': platform.system() + (' - %s' % linux_distribution if LINUX
                                       else '')
    }


def get_vcs_revision():
    def get_git_revision_hash():
        return subprocess.check_output(
            ['git', 'rev-parse', '--short', 'HEAD']).decode('utf-8').replace('\n', '')

    def get_git_branch_name():
        output = subprocess.check_output(['git', 'branch']).decode('utf-8')
        for l in output.splitlines():
            if l.startswith('*'):
                return l.replace(' ', '').replace('*', '')

    return '%s@%s' % (get_git_revision_hash(), get_git_branch_name())

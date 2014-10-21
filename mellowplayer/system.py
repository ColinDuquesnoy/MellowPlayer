import functools
import logging
import os
import platform
from zipfile import ZipFile
from qidle import __version__

WINDOWS = platform.system() == 'Windows'
LINUX = platform.system() == 'Linux'
DARWIN = platform.system() == 'Darwin'


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

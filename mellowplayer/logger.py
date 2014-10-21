"""
This module contains logging utilities.

"""
import logging
import os
from mellowplayer import system


def get_path():
    """
    Returns the log file path
    :return: str
    """
    return os.path.join(system.get_cache_directory(), 'MellowPlayer.log')


def setup(verbose=False):
    """
    Configures the logger, adds a stream handler and a file handler.

    :param version: version of the application
    :param debug: True to enable debug log level, otherwise the info log
        level is used.
    """
    level = logging.DEBUG if verbose else logging.INFO
    handlers = [
        logging.FileHandler(get_path(), mode='w'),
        logging.StreamHandler()
    ]
    logging.basicConfig(
        level=level, handlers=handlers,
        format='%(asctime)s::%(levelname)s::%(name)s::%(message)s',
        datefmt='%Y-%m-%d %H:%M:%S')

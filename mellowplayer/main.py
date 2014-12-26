"""
Main script
"""
import argparse
import logging
from mellowplayer import logger, qt, system


def main():
    # parse args
    parser = argparse.ArgumentParser(
        description='Cloud music service integration for your desktop')
    parser.add_argument('--qt', action='store', dest='qt', type=int, default=5)
    parser.add_argument('--verbose', action='store_true')
    args = parser.parse_args()

    # setup logger
    logger.setup(verbose=args.verbose)
    _logger = logging.getLogger('mellowplayer')


    # configure qt api
    try:
        qt.setup_qt_api(args.qt)
    except ImportError:
        other = {4: 5, 5: 4}[args.qt]
        try:
            _logger.warning('failed to import PyQt%d, trying with PyQt%s',
                            args.qt, other)
            qt.setup_qt_api(other)
        except ImportError:
            _logger.critical('failed to import PyQt%s', other)

    # log versions
    versions = system.get_versions()
    _logger.info("MellowPlayer %s", versions['mellowplayer'])
    _logger.info(
        "[Python %s %dbits, Qt %s, %s %s on %s]",
        versions['python'], versions['bitness'], versions['qt'],
        versions['qt_api'], versions['qt_api_ver'], versions['system'])

    # run application
    from mellowplayer.app import Application
    Application().run()


if __name__ == '__main__':
    main()

#!/usr/bin/env python
"""
This is a small interactive helper script for the MellowPlayer developers and
contributors that automates some boring administration tasks such as:

  - adding a new plugin to the project
  - adding a new translation to the project
  - updating existing translation

Run this tool from the root directory of the project::

    python tools/devtool.py

.. note:: this script will work with both python2 or python3, you don't need
          any additional package.

"""
import glob
import os
import shutil
import sys
import webbrowser



def add_translation():
    """ Adds a new translation to the project. """
    code = ''
    while not code:
        code = read_input('Please indicate the language code of the new '
                          'translation (e.g. en, fr, es and so on...): ')
    print('')
    translation_entry = 'app/translations/mellowplayer_%s.ts' % code
    print('Adding new translation: %s' % translation_entry)

    # Add entry to mellow player
    with open('mellowplayer.pro', 'r') as fin:
        content = '\n'.join(fin.read().splitlines())
    content += '\nTRANSLATIONS +=%s\n' % translation_entry
    with open('mellowplayer.pro', 'w') as fout:
        fout.write(content)

    # Add entry to src/app/mellowplayer.qrc
    qrc_entry = '        <file>translations/mellowplayer_%s.qm</file>\n' % code
    with open('app/mellowplayer.qrc', 'r') as fin:
        lines = fin.read().splitlines(True)
    lines.insert(2, qrc_entry)
    with open('app/mellowplayer.qrc', 'w') as fout:
        fout.write(''.join(lines))

    # update translations
    update_translations()

    # tell user to open qt linguist.
    print('')
    print('The new translation has been added.')
    print('You may now use Qt linguist to translate the application strings.')
    print("Once you're done, you will need "
          'to run qmake and rebuild the application (from Qt Creator)')


def update_translations():
    """ Updates existing translations (run lupdate and lrelease). """
    os.system('lupdate mellowplayer.pro -no-obsolete')
    os.system('lrelease mellowplayer.pro')


def make_win32_release():
    """
    Make a full release on Windows
    """
    def get_env_vars():
        try:
            # load from cache
            with open('envvars.usr', 'r') as f:
                exe, qmake = f.read().splitlines()
        except (OSError, IOError):
            # get build dir to get the full exe path
            exe = ''
            while not exe and not os.path.exists(exe):
                build_dir = read_input('Please indicate the release build directory: ').strip()
                exe = os.path.join(build_dir, 'MellowPlayer.exe')
            # get qmake path
            qmake = ''
            while not qmake and not os.path.exists(qmake):
                qmake = read_input('Please the full path to qmake: ')
            # cache it!
            with open('envvars.usr', 'w') as f:
                f.write('\n'.join([exe, qmake]))
        return exe, qmake

    def make_dist_dir():
        dist_dir = 'bin'
        if os.path.exists(dist_dir):
            shutil.rmtree(dist_dir)
        os.mkdir(dist_dir)
        return dist_dir

    exe, qmake = get_env_vars()
    dist = make_dist_dir()
	
    mellow_plugins_dir = os.path.join(dist, "plugins")
    shutil.copytree(os.path.join(os.getcwd(), 'plugins'), mellow_plugins_dir)
    shutil.copy(os.path.join(os.getcwd(), 'utils', 'windows', 'vc_redist.x86.exe'),
                os.path.join(dist, 'vc_redist.x86.exe'))
	
	# copy qt stuff
    qt_bin_dir = os.path.dirname(qmake)
    qt_root_dir = os.path.abspath(os.path.join(qt_bin_dir, os.pardir))
    snore_plugins_dir = os.path.join(qt_root_dir, "lib", "plugins", "libsnore-qt5")
    iconengines_dir = os.path.abspath(os.path.join(qt_bin_dir, '..',
                                       'plugins', 'iconengines'))
    iconengines_dst = os.path.join(dist, 'iconengines')
    try:
        os.mkdir(iconengines_dst)
    except OSError:
        pass

    imageformats_dir = os.path.abspath(
        os.path.join(qt_bin_dir, '..', 'plugins', 'imageformats'))
    imageformats_dst = os.path.join(dist, 'imageformats')
    try:
        os.mkdir(imageformats_dst)
    except OSError:
        pass

    files = [
        exe,
        os.path.join(qt_bin_dir, 'icudt54.dll'),
        os.path.join(qt_bin_dir, 'icuin54.dll'),
        os.path.join(qt_bin_dir, 'icuuc54.dll'),
        os.path.join(qt_bin_dir, 'Qt5Core.dll'),
        os.path.join(qt_bin_dir, 'Qt5Gui.dll'),
        os.path.join(qt_bin_dir, 'Qt5Multimedia.dll'),
        os.path.join(qt_bin_dir, 'Qt5MultimediaWidgets.dll'),
        os.path.join(qt_bin_dir, 'Qt5Network.dll'),
        os.path.join(qt_bin_dir, 'Qt5OpenGL.dll'),
        os.path.join(qt_bin_dir, 'Qt5Positioning.dll'),
        os.path.join(qt_bin_dir, 'Qt5PrintSupport.dll'),
        os.path.join(qt_bin_dir, 'Qt5Qml.dll'),
        os.path.join(qt_bin_dir, 'Qt5Quick.dll'),
        os.path.join(qt_bin_dir, 'Qt5Sensors.dll'),
        os.path.join(qt_bin_dir, 'Qt5Sql.dll'),
        os.path.join(qt_bin_dir, 'Qt5Svg.dll'),
        os.path.join(qt_bin_dir, 'Qt5WebChannel.dll'),
        os.path.join(qt_bin_dir, 'Qt5WebEngine.dll'),
        os.path.join(qt_bin_dir, 'Qt5WebEngineCore.dll'),
        os.path.join(qt_bin_dir, 'Qt5WebEngineWidgets.dll'),
		os.path.join(qt_bin_dir, 'QtWebEngineProcess.exe'),
		os.path.join(qt_bin_dir, 'Qt5Widgets.dll'),
        os.path.join(qt_bin_dir, 'snorenotify.exe'),
        os.path.join(qt_bin_dir, 'snoresend.exe'),
        os.path.join(qt_bin_dir, 'snoresettings.exe'),
        os.path.join(qt_bin_dir, 'SnoreToast.exe'),
        os.path.join(qt_bin_dir, 'png2ico.exe'),
        os.path.join(qt_bin_dir, 'snore-qt5.dll'),
		os.path.join(qt_root_dir, 'qtwebengine_resources.pak'),
		os.path.join(qt_root_dir, 'qtwebengine_resources_100p.pak'),
		os.path.join(qt_root_dir, 'qtwebengine_resources_200p.pak'),
		os.path.join(qt_root_dir, 'icudtl.dat'),
		os.path.join(snore_plugins_dir, 'libsnore_backend_snoretoast.dll'),
    ]

    for f in files:
        print('copying %s to %s' % (f, dist))
        shutil.copy(f, dist)

	# qt plugins
    plugins_dir = os.path.abspath(os.path.join(qt_bin_dir, '..', 'plugins'))

    plugins = []
    for subdir in ['imageformats', 'iconengines', 'platforms', 'audio', 'mediaservice']:
        root = os.path.join(plugins_dir, subdir)
        for f in os.listdir(root):
            if not f.endswith('.dll') or f.endswith('d.dll'):
                continue
            plugins.append((os.path.join(root, f), subdir))

    for f, dest_dir in plugins:
        dst = os.path.join(dist, dest_dir)
        if not os.path.exists(dst):
            os.makedirs(dst)
        print('copying %s to %s' % (f, dst))
        shutil.copy(f, dst)

    # configure innosetup
    version = read_input('Version string: ')
    with open('utils/windows/setup_templ.iss', 'r') as src, open('setup.iss', 'w') as dst:
        lines = src.readlines()
        data = []
        for l in lines:
            l = l.replace('@VERSION@', version)
            data.append(l)
        dst.writelines(data)

    print('signing mellowplayer executable')
    os.system('c:\DigiCertUtil.exe sign /noInput %s' % os.path.join(dist, 'MellowPlayer.exe'))

    os.environ['PATH'] += ';C:\Program Files (x86)\Inno Setup 5'
    os.system('iscc %s' % os.path.join(os.getcwd(), 'setup.iss'))



def make_osx_release():
    def get_build_dir():
        try:
            # load from cache
            with open('envvars.usr', 'r') as f:
                build_dir = f.read()
        except (OSError, IOError):
            # get build dir
            build_dir = ''
            while not build_dir and not os.path.exists(build_dir):
                build_dir = read_input('Build directory: ')
            # cache it!
            with open('envvars.usr', 'w') as f:
                f.write(build_dir)
        return build_dir

    build_dir = get_build_dir()
    plugins_dir = os.path.join(build_dir, "MellowPlayer.app/Contents/PlugIns/services")
    # os.makedirs(plugins_dir, exist_ok=True)
    shutil.copytree("plugins", plugins_dir)
    os.chdir(build_dir)
    os.system('/Users/Colin/Qt5.6.0-BETA/5.6/clang_64/bin/macdeployqt MellowPlayer.app -dmg')


def make_docs():
    os.system('doxygen docs/Doxyfile')

    answer = read_input("Open documentation [Y/n]?").lower()
    if answer != 'n':
        path = 'file://' + os.path.realpath(os.path.join(
            os.getcwd(), 'docs', '_build', 'html', 'index.html'))
        print(path, webbrowser.open_new_tab(path))


# --- Menu definition
#: The menu dict associate the menu text entry and its associated function.
MENU = {
    '1. Add a new translation': add_translation,
    '2. Update translations': update_translations,
    '3. Make windows release': make_win32_release,
    '4. Make OSX release': make_osx_release,
    '5. Make documentation': make_docs,
    '6. Exit': lambda: sys.exit(0)
}


# --- Helper functions
def read_input(prompt=''):
    """
    Python intepreter independant input function. Reads a string from the
    standard input.

    :param prompt: Optional prompt text.
    :return: The user input (str)
    """
    if sys.version_info[0] == 2:
        return raw_input(prompt)
    else:
        return input(prompt)


def display_menu():
    """ Display the main menu and handle user choice.

    :return: Choice value or None if the choice was invalid.
    """
    print('')
    print('MENU')
    print('----')
    print('')
    for key in sorted(MENU.keys()):
        print(key)
    print('')
    txt = read_input('Choose an option (from 1 to %d): ' % len(MENU))
    try:
        choice = int(txt)
    except ValueError:
        return None
    else:
        if choice not in range(1, len(MENU) + 1):
            return None
        return choice - 1


# --- Application entry point
if __name__ == '__main__':
    choice = None
    while choice is None:
        choice = display_menu()
        print('')
        if choice is None:
            print('Invalid choice, please choose a number between 1 and %d' %
                  len(MENU))
        else:
            MENU[sorted(MENU.keys())[choice]]()
    print('')

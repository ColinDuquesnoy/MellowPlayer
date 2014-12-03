#!/usr/bin/env python3
"""
This scripts freeze the application and try to run the inno setup compiler
to create an setup executable.
"""
import sys
from cx_Freeze import setup, Executable
from mellowplayer import __version__

# Detect system
windows = sys.platform == 'win32'
osx = sys.platform == 'darwin'

app_script = 'mellowplayer/main.py'
app_name = 'Mellow Player'
app_exe = 'MellowPlayer.exe' if windows else 'MellowPlayer'
app_icon = 'share/icons/MellowPlayer.ico' if windows else ''


if len(sys.argv) == 1:
    sys.argv.append('build')

options = {
    'include_files': ['services/']
}

print(
    '### Freezing application\n'
    '#####################################################################\n')
setup(name=app_name,
      version=__version__,
      options={'build_exe': options, 'bdist_mac': {
          'iconfile': app_icon, 'custom_info_plist': 'share/Info.plist'}},
      executables=[
          Executable(app_script, targetName=app_exe,
                     icon=app_icon if windows else None,
                     base='Win32GUI' if windows else None),
      ])

# if windows:
#     print(
#         '\n### Creating windows installer using Inno Setup\n'
#         '#####################################################################'
#         '\n')
#     try:
#         build_dir = glob.glob('build/*')[0]
#         with open('setup.iss.in', 'r') as src, open('setup.iss', 'w') as dst:
#             lines = src.readlines()
#             data = []
#             for l in lines:
#                 l = l.replace('@VERSION@', __version__)
#                 l = l.replace('@BUILD_DIR@', build_dir)
#                 data.append(l)
#             dst.writelines(data)s
#         # if not in PATH, inno setup is usually located in
#         # C:\Program Files (x86)\Inno Setup 5 on Windows
#         os.environ['PATH'] += ';C:\Program Files (x86)\Inno Setup 5'
#         os.system('iscc %s' % os.path.join(os.getcwd(), 'setup.iss'))
#     except Exception as e:
#         print(e)

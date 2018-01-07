import os


def clang_format_recursive(root_path):
    for root, dirs, files in os.walk(root_path):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".hpp"):
                path = os.path.join(root, file)
                print('formatting %s' % path)
                os.system('clang-format -i -style=file %s' % path)


def js_beautify_recursive(root_path):
    for root, dirs, files in os.walk(root_path):
        for file in files:
            if file.endswith(".js"):
                path = os.path.join(root, file)
                print('formatting %s' % path)
                os.system('js-beautify -f %s -o %s' % (path, path))


if __name__ == "__main__":
    if os.getcwd() == os.path.dirname(__file__):
        os.chdir("..")

    clang_format_recursive(os.path.join(os.getcwd(), "src"))
    js_beautify_recursive(os.path.join(os.getcwd(), "plugins"))

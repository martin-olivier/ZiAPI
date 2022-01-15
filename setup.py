#!/usr/bin/env python3

import os
import subprocess

class Color:
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    END = '\033[0m'

def replace_content(file_path : str, search : str, replace : str):
    with open(file_path, 'r') as file :
        filedata = file.read()

    filedata = filedata.replace(search, replace)

    with open(file_path, 'w') as file:
        file.write(filedata)

def process(cmd : list[str]) -> str:
    result = subprocess.run(cmd, stdout=subprocess.PIPE)
    if result.returncode != 0:
        raise Exception()
    return result.stdout.decode()

def main() -> int:
    try:
        name = input("Enter the name of your binary:\n")
        if len(name) == 0:
            raise Exception("the name of your binary cannot be empty")
        name_upper = name.capitalize()
        replace_content("README.md", "binary", name)
        replace_content("README.md", "# CppTemplate", "# " + name_upper)
        replace_content("README.md", "\n- [Python3](https://www.python.org/download/releases/3.0/)", "")
        replace_content(".gitignore", "binary", name)
        replace_content("Makefile", "binary", name)
        replace_content("CMakeLists.txt", "binary", name)
        replace_content("CMakeLists.txt", "Template", name_upper)

        try:
            url = process(["git", "config", "remote.origin.url"]).replace('\n', '')
            user = process(["git", "config", "user.name"]).replace('\n', '')
            user_url = url[0:url.rfind('/')]
            replace_content("README.md", "https://github.com/martin-olivier/CppTemplate", url)
            replace_content("README.md", " - [Martin Olivier](https://github.com/martin-olivier)\n - [Coline Seguret](https://github.com/Cleopha)", " - [" + user + "](" + user_url + ")")
        except:
            print(Color.RED + "git error: Could not change repo link and autors on README.md" + Color.END)

        print(Color.GREEN + "Setup Done" + Color.END)
        os.remove("setup.py")
        exit(0)
    except EOFError:
        print(Color.RED + "Killed by End of file (CTRL D)" + Color.END)
    except KeyboardInterrupt:
        print(Color.RED + "Killed by Keyboard Interrupt (CTRL C)" + Color.END)
    except Exception as e:
        print(Color.RED + "Exception raised : " + Color.END + str(e))
    exit(84)


if __name__ == "__main__":
    main()
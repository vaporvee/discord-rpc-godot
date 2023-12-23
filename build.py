import os
import platform
import sys

yes = {"yes", "y", "ye", ""}
no = {"no", "n"}

if len(sys.argv) > 1:
    choice = sys.argv[1].removeprefix("-")
else:
    sys.stdout.write(
        "Do you want to open only the built project instead of the Godot Editor after building? ([y]es/[n]o): "
    )
    choice = input().lower()
if choice in yes:
    os.system(
        "python -m SCons && python -m SCons target=template_release && cd project && godot"
    )
elif choice in no:
    system = platform.system()
    if system == "Windows": # Windows
        os.system(
            "python -m SCons && python -m SCons target=template_release && godot project/project.godot"
        )
    elif system == "Darwin":  # macOS
        os.system(
            "python -m SCons target=template_release arch=x86_64 && python -m SCons target=template_debug arch=x86_64 && python -m SCons target=template_release arch=arm64 && python -m SCons target=template_debug arch=arm64 && godot project/project.godot"
        )
    else:  # Linux
        os.system(
            "python -m SCons && python -m SCons target=template_release && godot project/project.godot"
        )
else:
    sys.stdout.write("Please respond with 'yes' or 'no'")

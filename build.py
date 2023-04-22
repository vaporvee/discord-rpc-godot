import os
import sys

yes = {'yes','y', 'ye', ''}
no = {'no','n'}

if sys.argv[1]:
    choice = sys.argv[1].removeprefix("-")
else:
    sys.stdout.write("Do you want to open only the built project instead of the Godot Editor after building? ([y]es/[n]o): ")
    choice = input().lower()
if choice in yes:
   os.system("scons && cd project && godot")
elif choice in no:
   os.system("scons && godot project\project.godot")
else:
   sys.stdout.write("Please respond with 'yes' or 'no'")
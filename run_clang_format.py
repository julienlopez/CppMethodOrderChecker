import subprocess
import os

def processDirectory(directory):
	for root, dirs, files in os.walk(directory):
		for i in files:
			if i.endswith(".cpp") or i.endswith(".hpp"):
				print("formatting " + os.path.join(root, i))
				subprocess.call(["clang-format", "-i", os.path.join(root, i)])

root_path=os.getcwd()

directories = [ d for d in os.listdir(root_path) if os.path.isdir(os.path.join(root_path, d)) ]
for directory in directories:
	processDirectory(os.path.join(root_path, directory))
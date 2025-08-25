# chestionare-tracker

A simple code to keep track and get a random test for those who are taking the driving exam in Romania and doing practice tests.

## Quick Setup (Windows CMD)

Clone the repository:
git clone https://github.com/IleaBogdan/chestionare-tracker.git
cd chestionare-tracker

### Build C++ executable
g++ main.cpp -o trackercpp.exe

### Build Python executable (requires PyInstaller)
pyinstaller --onefile main.py --name trackerpy

You'll find the executables under:
- trackercpp.exe (in project folder)
- dist\trackerpy.exe

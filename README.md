About
-----

This project is based on [4ccEditor](https://github.com/the4chancup/4ccEditor) and uses a fork of [pesXdecrypter](https://github.com/the4chancup/pesXdecrypter) for the encrypt/decrypt library so there are differences from the original pesXdecrypter project.

This project is only a wrapper and uses code from the original 4ccEditor project to expose load/save functionalities without the UI elements so it can be built into a .dll file.

It also integrates [rapidcsv](https://github.com/d99kris/rapidcsv) to enable CSV import and export of game data elements (like players and teams).

This project is maintained for personal use, as a learning exercise to create a wrapper and is provided as-is without guarantees of stability.



Usage
-----

This project uses solutions to setup and build it. It already has both x86 and x64 static library files for pesXdecrypter included.
- Go to the Project's properties (right-click the project in solution explorer or select Project > Properties from the menu bar).
- In Configuration Properties > General, change the 'Configuration Type' to your needs.
- To Build, simply run the 'Build Solution' or 'Build pesXeditor' under Build menu.

<b>NOTE:</b> The dll API is intended to be stateless, so data must be freed/destroyed by calling the appropriate functions manually when no longer in use.
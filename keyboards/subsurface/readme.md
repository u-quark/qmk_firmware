Subsurface keyboard firmware
======================

These configuration files are specifically for the Subsurface keyboard. This code was derived from the Atreus firmware, particularly the tshort keymap.

This keyboard uses a TEENSY 2++.

To build the firmware binary hex file with a keymap just do `make` with `KEYMAP` option like:
```
$ make KEYMAP=[default|jack|<name>]
```
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.


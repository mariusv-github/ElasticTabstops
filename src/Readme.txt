Introduction
============

This new version 1.5 of Elastic Tabstops is completely rewritten, optimized and provide many new features:
* New settings architecture: default setting and individual settings.
* New configuration file format, INI-compatible, with optional individual sections for edited files.
* Default settings partially compatible with the old version.
* Global remember option to remember setting option for enabled files.
* Reset settings option to clean and reset the options INI file.
* New, consistent behavior of elastic tab-stops using two types of working range: current selection or the whole file.
* User choice between two computing strategy : global (same through the whole file) or local (old version behavior) tab-stops.
* Efficient and optimized code to find and replace elastic tab-stops with spaces or spaces with tabs (selection or whole file).
* Completely rewritten code to support new Scintilla 2GB+ interface.
* Integrated quick help (this file)

About file structure
--------------------
In this version (1.5) of Elastic Tabstops the text range between the line start or a tab and the next tab or the line end is called **item**.
(In the precedent versions it was a confusion between the Scintilla cell, a pair character+format, and the Elastic Tabstops item called sometimes cell too...)
Each item can have or not an ending tab (normally the last item in a line do not have one but in ElasticTabstops
  there is no different treatments between last items in a line with or without an ending tab).
Each item has an 0-based index (from left to right) and items with the same index from different lines form **columns**.
Columns can be sparse, and this is more likely for higher indexes. A compact zone in a column without absent item is called **column block**.
So any column is composed of one or more column blocks separated by some absent (void) items.
The **item width** is measured without the next tab, while the **column width** is the width of an item text with its next elastic tab.

Elastic Tabstops detect and automatically adjust/maximize tab-stop positions in the current range (globally or current selection)
so successive column widths being the same using one of two possible strategies :
[1] Global (uniform, unique) tab-stop positions per column:
    Every item in the current range with the same index will have a unique column width
    The width of each column is determined by the larger item width (in this column) + minimum tab width padding (a user option)
[2] Local blocks (neighbors) on the same column with uniform tab-stop positions:
    Every item in the current range will have the same column width as the next or previous neighbor with the same index
    but different column blocks of the same column can have different width.
    The width of each column block is determined by the larger item width (in this block) + minimum tab width padding (a user option)

Tips, performance and fine tuning
---------------------------------
Disable "Word wrap" option in NPP when using Elastic Tabstops.

Both elastic tabs strategies can be quite compute intensive and can slow down Notepad++ responsiveness for very big files.
We recommend to keep activated size and line number thresholds, adapted to your CPU/memory speed.

We recommend to not enable by default all files extensions (with extensions=* ), and to enable manually each opened file where you really need elastic tabs.
Then you can activate the global option "Remember enabled files" if you wish to keep the current settings for individuals files you work with.

Warning: Replacing tabs by spaces or spaces by tabs for a whole big file can takes a very long time...
This version (1.4) is 2GB+ compatible using 64 bits position with Scintilla messages but this not mean elastic tabstops can by normally
activated for so big files for the whole range. We recommend in these cases to active elastic tabstops only for the current selection,
or copy the wished working range in a new small file then copy back the modified result into the big file.

Settings & configuration
========================
Version 1.5 rebuild all configurations options and change the format of ElasticTabstops.ini to standard INI format.
Now there is a default configuration applied to each new/opened file and an individual configuration for each opened file.

Default configuration
---------------------
The default configuration is load and saved to section [Default settings] of configuration file ElasticTabstops.ini.
The user can watch and edit this file by clicking the menu item "Save and edit default settings...".
Changing and saving this file will not modify individual settings of opened files.
The user can reset the configuration file the its default state by using "Reset and save default settings".

Default options are:

extensions=list_of_space_separated_extensions (default !*)
; files with a particular extension where elastic tabstops will be enabled or disabled by default,
; but then the user can switch the enabling state for each opened file individually...
; and "remember_enabled_files" option allow to memorize these individual settings for each file
; for each new/opened file without individual settings, the list of extensions is parsed to match with its extension
; the first extension matching (positive or negative) will stop list parsing (so * or !* will always stop parsing extensions list)
; extensions= .c .h .cpp .hpp       only C/C++ files will be enabled by default
; extensions= !.txt !.py *          all files enabled by default except for text and Python files
; extensions= .txt !* .csv          only text files will be enabled by default, all after !* is ignored

remember_enabled_files=1 or 0 (default 0)
; if activated, the plug-in will remember (in INI configuration file under the section named by the file path)
; the individual options for any enabled file and will forget (delete) its section and individual options for any disabled file 
; if deactivated, the plug-in will not remember any individual option for any opened file and
; will not use nor delete any individual section from INI configuration file
; currently the individual options memorized in the file section are: "sel_only" and "glob_tabs"

sel_only=1 or 0 (default 1)
; the active range for applying elastic tabstops will be the current selected lines or all the file

glob_tabs=1 or 0 (default 1)
; elastic tabs computing strategy will be global or local on active range

min_padding=1 to 255 (default 1)
; the number of space characters to be added to the right of the largest item on a column or column block

keep_leading_tabs=1 or 0 (default 0)
; do not replace the leading tabs with spaces

Except "remember_enabled_files" option, the is no menu item to display or modify any particular default option.
The user can change these options only by manually editing and saving the configuration file ("Save and edit default settings...").

Individual configuration
------------------------
Individual options for the foreground file are displayed and can be modified through the menu items "Enabled", "Selection Only and "Global Tabs".

Each opened file will normally inherit the default settings for enabling, active range (sel_only) and strategy (glob_tabs).
But if the global option "remember_enabled_files" is active and the INI configuration file has a section for the current
file then the plug-in will use these individual options rather than the default ones.
If the remember option is active when a file is closed then the individual settings are saved for enabled file under its INI section.
And if the current file is not enabled then its INI file section will be deleted.
If the remember option is not active then the INI file is not used for loading nor for saving any individual option.

The name of the individual file section in INI file is the file's full path where characters '[' and ']' are replaced by '<' and '>'.
Even it is not recommended, the user can create new individual sections or manually delete some obsolete sections in INI file.

Warning: Resetting default options will delete any individual configuration inside the INI file.

Editing/replacing operations
============================
On an enabled file the user can replaced elastic tabs by spaces using "Convert Tabstops to Spaces" or spaces by tabs using "Convert Spaces to Tabs".
Note: Generally these two operations are not opposite operations (even in some particular cases they can be).
Both replacement operations use the same active range as elastic tabs (selected lines or the whole file).

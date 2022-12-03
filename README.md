![Elastic Tabstops logo](/img/logo.gif)

Notepad++ plugin for [Elastic Tabstops](http://nickgravgaard.com/elastic-tabstops/).

New version 1.5 (for Notepad++ version higher than 8.4.4) rewritten, optimized, and providing many new features:
* New settings architecture: default setting and individual settings.
* New configuration file format, INI-compatible, with optional individual sections for edited files.
* Default settings partially compatible with the old version.
* Global remember option to remember setting option for enabled files.
* Reset settings option to clean and reset the options INI file.
* New, consistent behavior of elastic tab-stops using two types of working range: current selection or the whole file.
* User choice between two computing strategy : global (same through the whole file) or local (old version behavior) tab-stops.
* Efficient and optimized code to find and replace elastic tab-stops with spaces or spaces with tabs (selection or whole file).
* Completely rewritten code to support new Scintilla 2GB+ interface.
* Integrated quick help.

[![Build status](https://ci.appveyor.com/api/projects/status/github/dail8859/ElasticTabstops?branch=master&svg=true)](https://ci.appveyor.com/project/dail8859/ElasticTabstops/branch/master)

## Installation
Use the built in Plugin Admin to install the plugin.

## Development
The code is developed using Visual Studio 2017. Building the code will generate a DLL which can be used by Notepad++. For convenience, Visual Studio copies the DLL into the Notepad++ plugin directory.

## License
This code is released under the [GNU General Public License version 2](http://www.gnu.org/licenses/gpl-2.0.txt).

Parts of this were originally released under the MIT license Copyright (c) 2007-2014 Nick Gravgaard, David Kinder

Image(s) Copyright(c)2006-2015 Nick Gravgaard and licensed under a Creative Commons Attribution 3.0 Licence.

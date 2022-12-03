// This file is part of ElasticTabstops.
// 
// Copyright (C)2016-2022 Justin Dailey <dail8859@yahoo.com>, Marius Vasiliu <Polytech Paris Saclay>
// 
// ElasticTabstops is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#define VERSION_LEV1        1
#define VERSION_LEV2        5
#define VERSION_LEV3        0
#define VERSION_LEV4        0

#define VERSION_NUM         VERSION_LEV1,VERSION_LEV2,VERSION_LEV3,VERSION_LEV4
#define CONCAT_(a,b,c,d)    a##b##c##d
#define CONCAT(a,b,c,d)     CONCAT_(a,b,c,d)
#define VERSION_LINEAR      CONCAT(VERSION_LEV1,VERSION_LEV2,VERSION_LEV3,VERSION_LEV4)
#define QUOTE_(str)         #str
#define QUOTE(str)          QUOTE_(str)
#define VERSION_LINEAR_TEXT QUOTE(VERSION_LINEAR)
#define VERSION_SERVER      VERSION_LEV1.VERSION_LEV2.VERSION_LEV3
#define VERSION_SERVER_STR  QUOTE(VERSION_SERVER)
#define VERSION_TEXT        TEXT(VERSION_SERVER_STR) // This must match the tag pushed on the server
#define VERSION_STAGE       TEXT("release") // "alpha", "beta", ""

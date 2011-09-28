/*
 *  Copyright (C) 2011 XXX
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

import("filter.lib");

//tf2(b0,b1,b2,a1,a2) = iir((b0,b1,b2),(a1,a2));

tf3(b0,b1,b2,b3,a1,a2,a3) = iir((b0,b1,b2,b3),(a1,a2,a3));

tf4(b0,b1,b2,b3,b4,a1,a2,a3,a4) = iir((b0,b1,b2,b3,b4),(a1,a2,a3,a4));



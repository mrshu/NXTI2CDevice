
// RelativeNXTCompass.cpp

// Initial version: mrShu, 2013

/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "RelativeNXTCompass.h"


RelativeNXTCompass::RelativeNXTCompass(uint8_t i2c_address)
: NXTI2CDevice(i2c_address)
{
    _north = 0;
}

uint8_t RelativeNXTCompass::read_raw()
{
    byte r[2];
    r[0] = readByte(0x44);
    r[1] = readByte(0x45);
    delay(10);

    Serial.print(r[0]);
    Serial.print(' ');
    Serial.println(r[1]);

    return ((r[1] * 256) + r[0]);
}


void RelativeNXTCompass::set_north()
{
    _north = read_raw();
}

uint8_t RelativeNXTCompass::angle()
{
    uint8_t relative_angle = (read_raw() - _north + 360) % 360;

    if (relative_angle < 0)
        relative_angle += 360;

    return relative_angle;
}

uint8_t RelativeNXTCompass::real_north()
{
    return _north;
}


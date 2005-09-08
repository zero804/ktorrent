/***************************************************************************
 *   Copyright (C) 2005 by Joris Guisson                                   *
 *   joris.guisson@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ***************************************************************************/
#include <qtooltip.h>
#include <klocale.h>

#include <libtorrent/bitset.h>
#include <libtorrent/torrentcontrol.h>
#include "availabilitychunkbar.h"

AvailabilityChunkBar::AvailabilityChunkBar(QWidget* parent, const char* name): ChunkBar(parent, name)
{
	QToolTip::add(this, i18n("<img src=\"available_color\">&nbsp; - Available Chunks<br><img src=\"unavailable_color\">&nbsp; - Unavailable Chunks<br><img src=\"excluded_color\">&nbsp; - Excluded Chunks"));
}


AvailabilityChunkBar::~AvailabilityChunkBar()
{
}


void AvailabilityChunkBar::fillBitSet(bt::BitSet& bs)
{
	if (curr_tc)
		curr_tc->availableChunksToBitSet(bs);
}

#include "availabilitychunkbar.moc"

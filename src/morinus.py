#!/usr/bin/env python
# coding=utf-8


#Morinus, Astrology program
#Copyright (C) 2008-  Robert Nagy, robert.pluto@gmail.com

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

import os
import sys
import wx
import options
import mtexts
import morin
import infos
import mrbaseapp


class Morinus(mrbaseapp.MrApp):
	def OnInit(self):
		super(Morinus, self).OnInit()
		try:
			progPath = os.path.dirname(sys.argv[0])
			os.chdir(progPath)
		except:
			pass

		self.SetAppName(infos.MYAPPNAME)
		#wx.SetDefaultPyEncoding('utf-8') removed from wx
		opts = options.Options()
		mtexts.setLang(opts.langid)

		frame = morin.MFrame(None, -1, mtexts.txts['Morinus'], opts)
		self.SetTopWindow(frame)
		frame.Show(True)

		return True


if __name__ == '__main__':
	app = Morinus(0)
	app.MainLoop()

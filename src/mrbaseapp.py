#!/usr/bin/env python
# encoding: utf-8
"""
mrbaseapp.py

Created by Vaclav Spirhanzl on 2012-09-03.
"""

import wx
import sys
import traceback


def ExceptionHook(exctype, value, trace):
    """Handler for all unhandled exceptions
    @param exctype: Exception Type
    @param value: Error Value
    @param trace: Trace back info
    """
    # Format the traceback
    exc = traceback.format_exception(exctype, value, trace)
    ftrace = ''.join(exc)
    app = wx.GetApp()
    if app:
        msg = 'An unexpected error has occurred:\n {0:>s}'.format(ftrace)
        wx.MessageBox(msg, app.GetAppName(),
                      style=wx.ICON_ERROR|wx.OK)
        app.Exit()
    else:
        sys.stderr.write(ftrace)


class MrApp(wx.App):
	def __init__(self, *args, **kwargs):
		# __init__ is called only after OnInit()
		super(MrApp, self).__init__(*args, **kwargs)
		if not sys.excepthook is ExceptionHook:
			sys.excepthook = ExceptionHook
		return

	def OnInit(self):
		sys.excepthook = ExceptionHook
		return True
	
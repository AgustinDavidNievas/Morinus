import wx
import stripwnd
import mrclasses


class StripFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(StripFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		self.w = stripwnd.StripWnd(self, chrt, options, parent)
		self.SetMinSize((200, 200))

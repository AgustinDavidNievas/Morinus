import wx
import fixstarswnd
import mrclasses


class FixStarsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(FixStarsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = fixstarswnd.FixStarsWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

import wx
import fixstarsaspectswnd
import mrclasses


class FixStarsAspectsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(FixStarsAspectsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		aw = fixstarsaspectswnd.FixStarsAspectsWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

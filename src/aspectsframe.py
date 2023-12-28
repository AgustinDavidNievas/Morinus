import wx
import aspectswnd
import mrclasses


class AspectsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(AspectsFrame, self).__init__(parent, -1, title, wx.DefaultPosition,
											wx.Size(640, 400))

		aw = aspectswnd.AspectsWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

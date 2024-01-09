import wx
import speedswnd
import mrclasses


class SpeedsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(SpeedsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = speedswnd.SpeedsWnd(self, chrt, options, parent)
		
		self.SetMinSize((200,200))



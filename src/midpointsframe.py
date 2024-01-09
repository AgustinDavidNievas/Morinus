import wx
import midpointswnd
import mrclasses


class MidPointsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(MidPointsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = midpointswnd.MidPointsWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

import wx
import almutenzodswnd
import mrclasses


class AlmutenZodsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(AlmutenZodsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		aw = almutenzodswnd.AlmutenZodsWnd(self, chrt, options, parent)
		
		self.SetMinSize((200,200))



import wx
import miscwnd
import mrclasses


class MiscFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(MiscFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = miscwnd.MiscWnd(self, chrt, options, parent)
		
		self.SetMinSize((200,200))



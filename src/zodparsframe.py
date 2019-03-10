import wx
import zodparswnd
import mrclasses

class ZodParsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(ZodParsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		self.w = zodparswnd.ZodParsWnd(self, chrt, options, parent)
		self.SetMinSize((200,200))



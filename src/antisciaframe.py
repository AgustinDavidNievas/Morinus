import wx
import antisciawnd
import mrclasses


class AntisciaFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(AntisciaFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		self.w = antisciawnd.AntisciaWnd(self, chrt, options, parent)
		self.SetMinSize((200, 200))

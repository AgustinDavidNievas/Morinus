import wx
import munposwnd
import mrclasses


class MunPosFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(MunPosFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = munposwnd.MunPosWnd(self, chrt, options, parent)
		
		self.SetMinSize((200,200))



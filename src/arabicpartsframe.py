import wx
import arabicpartswnd
import mrclasses


class ArabicPartsFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(ArabicPartsFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = arabicpartswnd.ArabicPartsWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

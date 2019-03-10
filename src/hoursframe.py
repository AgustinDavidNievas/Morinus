import wx
import hourswnd
import mrclasses


class HoursFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(HoursFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		sw = hourswnd.HoursWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

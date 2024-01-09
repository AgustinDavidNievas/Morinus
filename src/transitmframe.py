import wx
import transitmwnd
import mrclasses


class TransitMonthFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, trans, year, month, chrt, options):
		super(TransitMonthFrame, self).__init__(parent, -1, title,
												wx.DefaultPosition,
												wx.Size(640, 400))

		w = transitmwnd.TransitMonthWnd(self, trans, year, month, chrt, options, parent)

		self.SetMinSize((200, 200))

import wx
import almutenchartwnd
import mrclasses


class AlmutenChartFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options):
		super(AlmutenChartFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		aw = almutenchartwnd.AlmutenChartWnd(self, chrt, options, parent)
		
		self.SetMinSize((200,200))



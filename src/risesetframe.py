import wx
import risesetwnd
import mrclasses


class RiseSetFrame(mrclasses.MrSecondFrame):
	XSIZE = 640
	YSIZE = 400

	def __init__(self, parent, title, chrt, options):
		super(RiseSetFrame, self).__init__(parent, -1, title, wx.DefaultPosition,
											wx.Size(RiseSetFrame.XSIZE, RiseSetFrame.YSIZE))

		rw = risesetwnd.RiseSetWnd(self, chrt, options, parent)

		self.SetMinSize((200, 200))

import wx
import customerwnd
import mtexts
import mrclasses


class CustomerFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, chrt, options, cpt):
		super(CustomerFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		self.w = customerwnd.CustomerWnd(self, chrt, options, parent, cpt)
		self.SetMinSize((200, 200))

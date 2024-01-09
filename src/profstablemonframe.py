import wx
import profectionsmonwnd
import mrclasses


class ProfsTableMonFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, pchrts, dates, opts, mainsigs, age):
		super(ProfsTableMonFrame, self).__init__(parent, -1, title, wx.DefaultPosition, wx.Size(640, 400))

		self.parent = parent
		self.mainsigs = mainsigs
		self.sw = profectionsmonwnd.ProfectionsMonWnd(self, age, pchrts, dates, opts, parent, mainsigs)

		self.SetMinSize((200, 200))
